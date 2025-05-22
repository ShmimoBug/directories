#ifndef FILE_SYSTEM
#define FILE_SYSTEM

#include <stddef.h>

void FileSystemInit();
const char* FileSystemLoadCWD();
const char* FileSystemGetCWD();
const struct FileList* FileSystemGetFileList();
void FileSystemUpdateChoices(int choice);
void FileSystemDeInit();

#endif // FILE_SYSTEM
