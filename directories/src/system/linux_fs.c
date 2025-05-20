#include "system/linux_fs.h"

#include <dirent.h>
#include <linux/limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "fl_def.h"

static char cwd[PATH_MAX];

char* LFSLoadCWD() {
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        return cwd;
    }

    perror("ERROR: Failed to load current working directory\n");
    return NULL;
}

static void LFSFileListAppend(FileList* list, struct dirent* dir, const char* ext) {
    if (dir->d_type == DT_DIR) {
        if (strcmp(dir->d_name, ".") == 0)
            return;

        FileItem* item = NULL;

        if (strcmp(dir->d_name, "..") == 0) {
            if (list->size > 0) {
                memmove(list->items + 1, list->items, sizeof(FileItem) * list->size);
                item = &list->items[0];
            }
        } else {
            item = &list->items[list->size];
        }

        strcpy(item->name, dir->d_name);
        item->type = IT_DIR;
        list->size++;
    } else {
        if ((ext == NULL) || (strstr(dir->d_name, ext) != NULL)) {
            FileItem* item = &list->items[list->size];
            strcpy(item->name, dir->d_name);
            item->type = IT_FILE;
            list->size++;
        }
    }
}

int LFSFileListLoad(FileList* list, const char* working_dir) {
    if (list == NULL || working_dir == NULL)
        return 1;

    list->size = 0;

    DIR* d;
    struct dirent* dir;
    d = opendir(working_dir);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            LFSFileListAppend(list, dir, NULL);
        }

        closedir(d);
    }

    return 0;
}

void LFSUpdateChoices(int choice, FileList* list, FileItem* item) {
    strcat(cwd, "/");
    strcat(cwd, item->name);
    LFSFileListLoad(list, cwd);
}
