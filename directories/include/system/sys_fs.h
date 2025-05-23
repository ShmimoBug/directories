#ifndef SYS_FS
#define SYS_FS

struct FileList;
struct FileItem;

char* SysLoadCWD();
int SysFileListLoad(struct FileList *list, const char *working_dir);
void SysUpdateChoices(int choice, struct FileList *list, struct FileItem *item);

#endif // SYS_FS
