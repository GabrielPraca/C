#include <Windows.h>
#include <stdio.h>

bool FileExists(const char *Path) {
	DWORD Atribs = GetFileAttributes(Path);
	if (Atribs != 0xFFFFFFFF && !(Atribs & FILE_ATTRIBUTE_DIRECTORY))
		return true;
	return false;
}

bool DirectoryExists(const char *Path) {
	DWORD Atribs = GetFileAttributes(Path);
	if (Atribs != 0xFFFFFFFF && (Atribs & FILE_ATTRIBUTE_DIRECTORY))
		return true;
	return false;
}

size_t GetFileSize(const char *Path) {
	FILE *Arquivo = fopen(Path, "r");
	int Size = 0;

	if (Arquivo != NULL) {
		fseek(Arquivo, 0, SEEK_END);
		Size = ftell(Arquivo);
		fclose(Arquivo);
	}

	return Size;
}