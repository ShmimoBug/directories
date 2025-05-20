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
    if (list == NULL || dir == NULL)
        return;

    if (dir->d_type == DT_DIR) {
        // don't add 'current directory' to list, no need
        if (strcmp(dir->d_name, ".") == 0)
            return;

        FileItem* item = NULL;

        // if the added directory is the 'parent directory', put it at the front of the list
        if (strcmp(dir->d_name, "..") == 0) {
            if (list->size > 0) {
                // move the list over by one, set new item to be the first member in the list
                memmove(list->items + 1, list->items, sizeof(FileItem) * list->size);
                item = &list->items[0];
            }
        } else {
            // if the item is just a regular directory, append to the end of the list
            item = &list->items[list->size];
        }

        strcpy(item->name, dir->d_name);
        item->type = IT_DIR;
        list->size++;
    } else {
        // if the item is a file, check if the user wants to filter for specific file extensions
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

    if (strcmp(working_dir, "/home") == 0)
        return 1;

    list->size = 0;

    DIR* d;
    struct dirent* dir;
    d = opendir(working_dir);
    if (d == NULL) {
        fprintf(stderr, "ERROR: Failed to load directory [%s]\n", working_dir);
        return 1;
    }

    if (d) {
        while ((dir = readdir(d)) != NULL) {
            LFSFileListAppend(list, dir, NULL);
        }

        closedir(d);
    }

    return 0;
}

void LFSUpdateChoices(int choice, FileList* list, FileItem* item) {
    if (choice == 0) {
        char* new_end = strrchr(cwd, '/');
        *new_end = 0;
        if (strcmp(cwd, "/home") == 0) {
            *new_end = '/';
            puts("Cannot go further");
        }
    } else {
        strcat(cwd, "/");
        strcat(cwd, item->name);
    }

    LFSFileListLoad(list, cwd);
}
