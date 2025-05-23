#include "file_system.h"

#include "fl_def.h"
#include "system/sys_fs.h"

static char* cwd_ptr = NULL;
static FileList list = { 0 };

void FileSystemInit() {
    SysFileListLoad(&list, cwd_ptr);
}

const char* FileSystemLoadCWD() {
    cwd_ptr = SysLoadCWD();
    return cwd_ptr;
}

const char* FileSystemGetCWD() {
    return cwd_ptr;
}

const FileList* FileSystemGetFileList() {
    return &list;
}

void FileSystemUpdateChoices(int choice) {
    if ((choice >= 0) && (choice < list.size)) {
        FileItem* item = &list.items[choice];
        if (item->type == IT_DIR) {
            SysUpdateChoices(choice, &list, item);
        }
    }
}
