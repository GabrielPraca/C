#ifndef StringUtils_H
#define StringUtils_H

#include <string>
#include <Windows.h>

using namespace std;

char* GetTextoAteDelim(const char* Texto, const char* Delimitador, int Inicio);
string ReplaceInString(const char *De, const char *Para, string StrOriginal);

#endif