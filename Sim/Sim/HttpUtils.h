#ifndef HttpUtils_H
#define HttpUtils_H

#include <string>
#include <WinSock2.h>
#include "MemoryUtils.h"
#include "StringUtils.h"

using namespace std;

string ReadHttpHead(SOCKET Socket);
bool SendFile(SOCKET Socket, const char *Path);
bool SendFileWithHead(SOCKET Socket, const char *Path);
const char* GetContentTypeFromPath(const char *Path);

struct HttpParam;

class Head {
private:
	struct _HttpParam;

	int length;
	struct _HttpParam *Parametros;
public:
	char *Metodo, *Path, *Versao;

	Head(string RawHead);
	~Head();
	int Count();
	void add(HttpParam *Parametro);
	bool removeIndex(int index);
	bool removeAndFreeAtIndex(int index);
	bool getHttpParam(int index, HttpParam *Destino);
};

#endif