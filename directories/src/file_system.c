#include "file_system.h"

#include "fl_def.h"

#ifdef __linux__
#include "system/linux_fs.h"
#endif

#ifdef _WIN32
#include "system/win_fs.h"
#endif

static char* cwd_ptr = NULL;
static FileList list = { 0 };

void FileSystemInit() {
#ifdef __linux__
    LFSFileListLoad(&list, cwd_ptr);
#endif
#ifdef _WIN32
    WFSFileListLoad(&list, cwd_ptr);
#endif
}

const char* FileSystemLoadCWD() {
#ifdef __linux__
    cwd_ptr = LFSLoadCWD();
#endif
#ifdef _WIN32
    cwd_ptr = WFSLoadCWD();
#endif
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
#ifdef __linux__
            LFSUpdateChoices(choice, &list, item);
#endif
#ifdef _WIN32
            WFSUpdateChoices(choice, &list, item);
#endif
        }
    }
}
