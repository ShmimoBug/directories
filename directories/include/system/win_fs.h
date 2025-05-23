#ifndef WIN_FS
#define WIN_FS

struct FileList;
struct FileItem;

char* WFSLoadCWD();

int WFSFileListLoad(struct FileList* list, const char* working_dir);
void WFSUpdateChoices(int choice, struct FileList* list, struct FileItem* item);

#endif // WIN_FS