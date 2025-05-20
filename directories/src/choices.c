#include "choices.h"

#include <stdio.h>

#include "fl_def.h"

#define BLUE "\x1B[34m"
#define NORMAL_COLOR "\x1B[0m"

void ChoicesPrint(const FileList* list) {
    if (list == NULL) {
        perror("ERROR: NULL reference to list in 'ChoicesPrint'\n");
        return;
    }

    // print the list of directories and the exit command, directories are listed in BLUE, everything else is white

    puts("\t[e]xit");
    printf(NORMAL_COLOR);
    for (int i = 0; i < list->size; i++) {
        const FileItem* item = &list->items[i];
        const char* COLOR = item->type == IT_DIR ? BLUE : NORMAL_COLOR;
        printf("\t[%d]: %s%s%s\n", i, COLOR, item->name, NORMAL_COLOR);
    }
}

int ChoicesGetChoice() {
    int choice = getchar();
    while (getchar() != '\n') {}
    return choice;
}
