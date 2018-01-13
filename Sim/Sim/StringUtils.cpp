#include <string>
#include <Windows.h>

using namespace std;

char* GetTextoAteDelim(const char* Texto, const char* Delimitador, int Inicio) {
		string tmpStr;
		char *TextoFinal;
		int Pos = Inicio,
			SizeDelim = strlen(Delimitador);

		while(Texto != 0) {
			Pos++;

			if (!strncmp(Texto + Pos - 1, Delimitador, SizeDelim))
				break;
		}

		TextoFinal = (char*)malloc(Pos - Inicio);
		ZeroMemory(TextoFinal, Pos - Inicio);
		memcpy(TextoFinal, Texto + Inicio, Pos - Inicio - 1);

		return TextoFinal;
}

string ReplaceInString(const char *De, const char *Para, string StrOriginal) {
	string Repleaced = string(StrOriginal);
	int iIni;

	while((iIni = Repleaced.find(De)) != -1)
		Repleaced = Repleaced.replace(iIni, strlen(Para), Para);

	return Repleaced;
}