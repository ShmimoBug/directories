#ifndef LINUX_FS
#define LINUX_FS

struct FileList;
struct FileItem;

char* LFSLoadCWD();

int LFSFileListLoad(struct FileList* list, const char* working_dir);
void LFSUpdateChoices(int choice, struct FileList* list, struct FileItem* item);

#endif // LINUX_FS
