#include <dirent.h>
#include <limits.h>
#include <linux/limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "d_main.h"

int main(int argc, char* argv[]) {
    return DirectoriesMain(argc, argv);
}
/*
#define NORMAL_COLOR "\x1B[0m"
#define BLUE "\x1B[34m"
#define ITEM_MAX 64

typedef enum FileType {
    FT_DIR = 0,
    FT_REG
} FileType;

typedef struct FileItem {
    char name[PATH_MAX];
    FileType type;
} FileItem;

typedef struct FileList {
    FileItem items[ITEM_MAX];
    size_t num_items;
} FileList;

void FileListAppend(FileList* list, struct dirent* dir, const char* ext) {
    // check if directory is a file or a directory
    if (dir->d_type == DT_DIR) {
        // if directory, don't add 'current' directory, doesn't do anything
        if (strcmp(dir->d_name, ".") == 0)
            return;

        FileItem* item = NULL;

        // if the directory is the parent directory, move it to the front of the list
        if (strcmp(dir->d_name, "..") == 0) {
            if (list->num_items > 0) {
                // move list forward one, make space at beginning for parent directory
                memmove(list->items + 1, list->items, sizeof(FileItem) * list->num_items);
                item = &list->items[0];
            }
        } else {
            // else, just append directory to end of list
            item = &list->items[list->num_items];
        }

        strcpy(item->name, dir->d_name);
        item->type = FT_DIR;

        list->num_items++;
    } else {
        // if item is a file, check if looking for certain file extension, append to end of list
        if ((ext == NULL) || (strstr(dir->d_name, ext) != NULL)) {
            FileItem* item = &list->items[list->num_items];
            sprintf(item->name, "%s", dir->d_name);
            item->type = FT_REG;
            list->num_items++;
        }
    }
}

// given a working directory, load all the files and directories within it
void FileListLoad(FileList* list, const char* working_dir) {
    list->num_items = 0;

    DIR* d;
    struct dirent* dir;
    d = opendir(working_dir);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            FileListAppend(list, dir, NULL);
        }

        closedir(d);
    }
}

// print current directory contents as well as exit command
void ChoicesPrint(const FileList* list) {
    puts("\t[e]xit");
    printf(NORMAL_COLOR);
    for (size_t i = 0; i < list->num_items; i++) {
        const FileItem* item = &list->items[i];
        const char* COLOR = item->type == FT_DIR ? BLUE : NORMAL_COLOR;
        printf("\t[%zu]: %s%s%s\n", i, COLOR, item->name, NORMAL_COLOR);
    }
    printf(NORMAL_COLOR);
}



int program(int argc, char* argv[]) {
    // get current working directory of the program at startup
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s\n", cwd);
    } else {
        perror("getcwd() error");
        return 1;
    }

    // load file list from cwd
    FileList list = { 0 };
    FileListLoad(&list, cwd);
    int choice = 0;
    while (1) {
        // update user choice and load new directories if requested
        ChoicesPrint(&list);
        choice = getchar();
        if ((choice == 'e') || (choice == 'E'))
            break;

        choice -= 48;
        if ((choice >= 0) && (choice < list.num_items)) {
            FileItem* item = &list.items[choice];
            if (item->type == FT_DIR) {
                strcat(cwd, "/");
                strcat(cwd, item->name);
                FileListLoad(&list, cwd);
            }
        }
        while (getchar() != '\n')
            ;
    }
    return 0;
}*/
