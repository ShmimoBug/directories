#include "d_main.h"
#include "choices.h"
#include "file_system.h"

#define ASCII_TO_INT 48

int DirectoriesMain(int argc, char* arv[]) {
    if (FileSystemLoadCWD() == NULL)
        return 1;

    FileSystemInit();

    while (1) {
        ChoicesPrint(FileSystemGetFileList());
        int choice = ChoicesGetChoice();
        if (choice == 'e' || choice == 'E')
            break;

        choice -= ASCII_TO_INT;
        FileSystemUpdateChoices(choice);
    }

    return 0;
}
