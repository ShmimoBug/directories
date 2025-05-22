#ifndef CHOICES
#define CHOICES

struct FileList;

void ChoicesInit();
void ChoicesPrint(const struct FileList* list, const char *cwd);
int ChoicesGetChoice();
void ChoicesDeInit();

#endif // CHOICES
