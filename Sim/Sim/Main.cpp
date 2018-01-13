#include <WinSock2.h> /* Biblioteca para os sockets */
#include <string>	  /* Biblioteca para trabalhar com strings */
#include <stdio.h>	  /* Biblioteca para trabalhar com operações de IO (Entrada-Saída) */
#include <conio.h>	  /* Biblioteca para trabalhar com o console */
#include <process.h>  /* _beginthread() */
#include "MemoryUtils.h"
#include "HttpUtils.h"
#include "StringUtils.h"
#include "FileUtils.h"
#include "Shlwapi.h"

using namespace std;

#pragma comment(lib, "Ws2_32.lib") /* Diz ao linker para usar esta Biblioteca (Válido Somente para o Visual Studio) */
#pragma comment(lib, "Shlwapi.lib")

#ifdef _DEBUG
# define _printf(fmtstr, ...) printf(fmtstr, ##__VA_ARGS__)
#else
# define _printf(fmtstr, ...)
#endif

void MainThreadCliente(void *ClienteSock);
void TesteWebM();

int main() {
	WSAData wsaData;
	SOCKET ServSock;
	int NetWorkError;
	SOCKADDR_IN ServInfo;
	
	SetConsoleTitle("Sim - Acesso Remoto");
	_printf("Inicializando o servidor...\r\n");

	/* Inicializa o Windows Sockets na versão 2.2 */
	if (WSAStartup(0x202, &wsaData) == SOCKET_ERROR) { /* Checagem de erro */
		NetWorkError = WSAGetLastError();
		_printf("Erro: WSAStartup() -> %d\r\n", NetWorkError);
		WSACleanup();
		return NetWorkError;
	}

	/* Inicializa o socket que vai escutar os clientes */
	ServSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); /* Cria o socket para o servidor */
	if (ServSock == SOCKET_ERROR) { /* Checagem de erro */
		NetWorkError = WSAGetLastError();
		_printf("Erro: socket() -> %d\r\n", NetWorkError);
		WSACleanup();
		return NetWorkError;
	}

	/* Define a porta do servidor e outras coisas */
	ZeroMemory(&ServInfo, sizeof(ServInfo)); /* Nos Tutoriais por ai eu vi que o pessoal zerava esse valor */
	ServInfo.sin_family = AF_INET;			 /* Família (ARPA INTERNET PROTOCOLS) - "A mais usada" */
	ServInfo.sin_port = htons(2014);		 /* Porta que o servidor vai escutar. htons significa "host to network short" */;
	ServInfo.sin_addr.s_addr = INADDR_ANY;	 /* INADDR_ANY indica que o servidor vai escutar qualquer ip, e não somente um especifico */

	/* Associa o ServSocket com as características informadas na variável ServInfo */
	if (bind(ServSock, (struct sockaddr*)&ServInfo, sizeof(sockaddr)) == SOCKET_ERROR) { /* Checagem de erro */
		NetWorkError = WSAGetLastError();
		_printf("Erro: bind() -> %d\r\n", NetWorkError);
		WSACleanup();
		return NetWorkError;
	}

	listen(ServSock, 0xFF); /* Ativa de fato o servidor para escutar até 0xFF(255) Conexões. */

	//Um Thread para fazer o teste do video no formato WebM
	//_beginthread(TesteWebM, 0, NULL);
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TesteWebM, NULL, 0, 0);
	
	_printf("Pronto e aguardando clientes.\r\n");
	/* Looping infinito para poder aceitar conexões quantas vezes quiser */
	while(true) {
		SOCKET *ClienteSock = (SOCKET*)malloc(sizeof(SOCKET));

		*ClienteSock = accept(ServSock, NULL, NULL); /* Aceita o pedido de conexão de um cliente */
		
		if (*ClienteSock != INVALID_SOCKET)
			_beginthread(MainThreadCliente, 0, ClienteSock);
		else
			xfree(&ClienteSock);
	}

	return 0;
}

void TesteWebM() {
	_printf("Thread Criado\n");

	
}

void MainThreadCliente(void *ClienteSock) {
	SOCKET *Cliente = (SOCKET*)ClienteSock;
	string RawHead, CaminhoReal;
	char CaminhoAtual[_MAX_PATH + 1];
	Head *_Head = NULL;

	try {
		_printf("Novo Cliente (0x%X)->%d\r\n", Cliente, *Cliente);

		/* Lê o cabeçalho HTTP de requisição de serviço */
		RawHead = ReadHttpHead(*Cliente);
		_Head = new Head(RawHead);

		_printf("\r\n%s", RawHead.c_str());

		/* Pega o caminho real apartir do caminho relativo */
		GetModuleFileName(NULL, CaminhoAtual, _MAX_PATH);
		PathRemoveFileSpec(CaminhoAtual);
		CaminhoReal.append(CaminhoAtual);
		CaminhoReal.append("\\www");
		CaminhoReal.append(_Head->Path);
		CaminhoReal = ReplaceInString("/", "\\", CaminhoReal);

		if (FileExists(CaminhoReal.c_str())) {
			SendFileWithHead(*Cliente, CaminhoReal.c_str());
		}
		else if (FileExists(CaminhoReal.append("\\index.html").c_str())) {
			SendFileWithHead(*Cliente, CaminhoReal.c_str());
		}
		else {
			char Resposta[] = "HTTP/1.1 404 Not Found!\r\n\r\n404 Not Found!";
			send(*Cliente, Resposta, strlen(Resposta), 0);
		}
	}
	catch (int) { }
	
	if (_Head != NULL)
		delete _Head;
	closesocket(*Cliente);
	xfree(&Cliente);
}
