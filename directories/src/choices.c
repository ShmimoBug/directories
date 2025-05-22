#include "choices.h"

#include <stdio.h>
#include <string.h>

#include "fl_def.h"

#define BLUE "\x1B[34m"
#define NORMAL_COLOR "\x1B[0m"

static char in_buffer[8] = "\0";

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
    while ((in_buffer[0] != 'e') && (in_buffer[0] != 'E')) {
        if (fgets(in_buffer, sizeof(in_buffer), stdin)) {
            int choice = 0;
            int result = sscanf(in_buffer, "%d", &choice);
            if (result == EOF) {
                perror("ERROR: Failed to receive data from input buffer.");
            } else if (result == 0) {
                puts("Invalid input, try again!");
                if (strcspn(in_buffer, "\n") >= 7) {
                    while (fgetc(stdin) != '\n');
                }
            } else {
                return choice;
            }
        }
    }

    return -1; // ready to exit
}
