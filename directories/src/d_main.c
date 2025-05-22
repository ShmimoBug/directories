#include "d_main.h"
#include "choices.h"
#include "file_system.h"

#include <stdio.h>

int DirectoriesMain(int argc, char* arv[]) {
    if (FileSystemLoadCWD() == NULL)
        return 1;

    FileSystemInit();

    while (1) {
        ChoicesPrint(FileSystemGetFileList(), FileSystemGetCWD());
        int choice = ChoicesGetChoice();
        if (choice <= -1) break;

        FileSystemUpdateChoices(choice);
    }

    return 0;
}
