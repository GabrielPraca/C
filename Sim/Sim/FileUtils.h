#ifndef FileUtils_H
#define FileUtils_H

bool FileExists(const char *Path);
bool DirectoryExists(const char *Path);
size_t GetFileSize(const char *Path);

#endif