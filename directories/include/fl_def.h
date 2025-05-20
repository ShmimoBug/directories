#ifndef FL_DEF
#define FL_DEF

#define MAX_NAME 128
#define MAX_ITEM 256

typedef enum ItemType {
    IT_DIR = 0,
    IT_FILE
} ItemType;

typedef struct FileItem {
    char name[MAX_NAME];
    ItemType type;
} FileItem;

typedef struct FileList {
    FileItem items[MAX_ITEM];
    int size;
} FileList;

#endif // FL_DEF
