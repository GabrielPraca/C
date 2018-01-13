#include <stdio.h>
#include <fstream>
#include "HttpUtils.h"
#include "MemoryUtils.h"
#include "FileUtils.h"

string ReadHttpHead(SOCKET Socket) {
	string RawHead;
	char *Buffer = (char*)malloc(2);
	Buffer[1] = 0;
	int Qtde = 0;

	while((Qtde = recv(Socket, Buffer, 1, 0)) != 0) {
		RawHead.append(Buffer); /* Adiciona o caractere recebido ao Head */

		if (!strcmp(RawHead.c_str() + RawHead.length() - 4, "\r\n\r\n")) /* Todo Head Http termina em "\r\n\r\n" */
			break;														 /* Então aqui ele para de receber o head quando ele encontra isso */
	}

	xfree(&Buffer);

	if(Qtde == 0) /* Qtde == 0 ocorre quando o socket fechou */
		throw -1; /* Provoca um erro */

	return RawHead;
}

bool SendFile(SOCKET Socket, const char *Path) {
	FILE *Arquivo = NULL;
	ifstream Arq;

	size_t BufSize = 4096, Lido = 0;
	char titulo[256];
	void *Buffer = malloc(BufSize);

	try {
		Arquivo = fopen(Path, "rb");
		Arq.open(Path);
		
		if (Arquivo != NULL) {
			while((Lido = fread(Buffer, 1, BufSize, Arquivo))  > 0) {
				if (send(Socket, (char*)Buffer, Lido, 0) == -1) {
					xfree(&Buffer);
					fclose(Arquivo);
					return false;
				}
			}

			xfree(&Buffer);
			fclose(Arquivo);
			return true;
		}
	}
	catch(int) { }

	if (Arquivo != NULL)
		fclose(Arquivo);
	xfree(&Buffer);

	return false;
}

bool SendFileWithHead(SOCKET Socket, const char *Path) {
	char *Head = NULL;

	if (FileExists(Path)) {
		//Envia o Cabeçalho
		Head = (char*)malloc(0xFFFF);
		int Len = sprintf(Head, "HTTP/1.1 200 OK\r\nContent-Type: %s\r\nContent-Length: %d\r\n\r\n", GetContentTypeFromPath(Path), GetFileSize(Path));
		send(Socket, Head, Len, 0);
		xfree(&Head);

		//Envia o arquivo
		SendFile(Socket, Path);
	}

	return true;
}

const char* GetContentTypeFromPath(const char *Path) {
	string SPath = string(Path);

	try {
		SPath = SPath.substr(SPath.find_last_of('.') + 1);
		
		if (!strcmp(SPath.c_str(), "html"))
			return "text/html";
		else if (!strcmp(SPath.c_str(), "png"))
			return "application/octet-stream";
		else
			return "application/octet-stream";
	}
	catch(int) { return "application/octet-stream"; }
}

#pragma region Classe Head

struct HttpParam {
	char *Nome, *Valor;
};

struct Head::_HttpParam {
	char *Nome, *Valor;
	struct _HttpParam *Prox, *Ant;
};

Head::Head(string RawHead) {
	int Pos = 0;
	string tmpStr;
	length = 0;
	Parametros = NULL;

	//Lê o Método
	Metodo = GetTextoAteDelim(RawHead.c_str(), " ", Pos);
	Pos += strlen(Metodo) + 1;
		
	//Lê o Path
	Path = GetTextoAteDelim(RawHead.c_str(), " ", Pos);
	Pos += strlen(Path) + 1;

	//Lê a Versão HTTP
	Versao = GetTextoAteDelim(RawHead.c_str(), "\r\n", Pos);
	Pos += strlen(Versao) + 2;

	//Lê os Parâmetros
	while(strncmp(RawHead.c_str() + Pos, "\r\n", 2)) {
		HttpParam Parametro;
			
		Parametro.Nome = GetTextoAteDelim(RawHead.c_str(), ":", Pos);
		Pos += strlen(Parametro.Nome) + 2;
		Parametro.Valor = GetTextoAteDelim(RawHead.c_str(), "\r\n", Pos);
		Pos += strlen(Parametro.Valor) + 2;

		add(&Parametro);
	}
}

Head::~Head() {
	xfree(&Metodo);
	xfree(&Path);
	xfree(&Versao);

	while(removeAndFreeAtIndex(0)) { }
}

int Head::Count() {
	return length;
}

void Head::add(HttpParam *Parametro) {
	_HttpParam *Param = (_HttpParam*)malloc(sizeof(_HttpParam));
	memset(Param, 0, sizeof(_HttpParam));
		
	Param->Nome = Parametro->Nome;
	Param->Valor = Parametro->Valor;

	if (length == 0)
		Parametros = Param;
	else {
		int pos = 0;
		_HttpParam *UltimoParam = Parametros;

		while (pos++ < length - 1)
			UltimoParam = UltimoParam->Prox;

		UltimoParam->Prox = Param;
		Param->Ant = UltimoParam;
	}

	length++;
}

bool Head::removeIndex(int index) {
	_HttpParam *Parametro = NULL;
	int Pos = 0;

	if (index < 0 || index > length - 1)
		return false;

	Parametro = Parametros; // Defini para começar na primeira posição

	if (index == 0 && length > 1)
		Parametros = Parametros->Prox;

	while(Pos++ < index)
		Parametro = Parametro->Prox;

	if (Parametro->Ant != NULL)
		(Parametro->Ant)->Prox = Parametro->Prox;
	if (Parametro->Prox != NULL)
		(Parametro->Prox)->Ant = Parametro->Ant;

	xfree(&Parametro);
	length--;

	return true;
}

bool Head::removeAndFreeAtIndex(int index) {
	HttpParam Parametro;

	if (index < 0 || index > length - 1)
		return false;

	getHttpParam(index, &Parametro);
	xfree(&Parametro.Nome);
	xfree(&Parametro.Valor);
	removeIndex(index);

	return true;
}

bool Head::getHttpParam(int index, HttpParam *Destino) {
	int pos = 0;
	_HttpParam *Parametro = NULL;

	if (index >= 0 && index < length) {
		Parametro = Parametros;

		while (pos++ < index)
			Parametro = Parametro->Prox;

		Destino->Nome = Parametro->Nome;
		Destino->Valor = Parametro->Valor;

		return true;
	}

	return false;
}

#pragma endregion