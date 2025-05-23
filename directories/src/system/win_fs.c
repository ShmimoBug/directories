#include "system/win_fs.h"

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "fl_def.h"

static char cwd[MAX_PATH];

char* WFSLoadCWD() {
	if (GetCurrentDirectory(sizeof(cwd), cwd) != 0) {
		return cwd;
	}

	return NULL;
}

static void WFSFileListAppend(FileList* list, const WIN32_FIND_DATA* fdFile, const char* ext) {
	if (list == NULL || fdFile == NULL) return;

	if (strcmp(fdFile->cFileName, ".") == 0) return;

	if (fdFile->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
		FileItem* item = &list->items[list->size];

		if (strcmp(fdFile->cFileName, "..") == 0) {
			if (list->size > 0) {
				memmove(list->items + 1, list->items, sizeof(FileItem) * list->size);
				item = &list->items[0];
			}
		}

		strcpy(item->name, fdFile->cFileName);
		item->type = IT_DIR;
		list->size++;
	}
	else {
		if ((ext == NULL) || (strstr(fdFile->cFileName, ext) != NULL)) {
			FileItem* item = &list->items[list->size];
			strcpy(item->name, fdFile->cFileName);
			item->type = IT_FILE;
			list->size++;
		}
	}
}

int WFSFileListLoad(FileList* list, const char* working_dir) {
	if (list == NULL || working_dir == NULL) return -1;
	
	list->size = 0;

	WIN32_FIND_DATA fdFile;
	HANDLE hFind = NULL;

	char sPath[MAX_PATH];
	sprintf(sPath, "%s\\*.*", working_dir);

	if ((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE) {
		printf("Path not found: [%s]\n", working_dir);
		return -1;
	}

	do {
		WFSFileListAppend(list, &fdFile, NULL);
	} while (FindNextFile(hFind, &fdFile));
	FindClose(hFind);
	return 0;
}

void WFSUpdateChoices(int choice, FileList* list, FileItem* item) {
	if (choice == 0) {
		char* new_end = strrchr(cwd, '\\');
		*new_end = 0;

		if (strlen(cwd) <= 2) {
			*new_end = '\\';
			puts("Cannot go further");
		}
	}
	else {
		strcat(cwd, "\\");
		strcat(cwd, item->name);
	}

	WFSFileListLoad(list, cwd);
}