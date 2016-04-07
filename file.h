#ifndef FILE_H
#define	FILE_H

void fileEnfile(char c);
char fileDefile();
char fileEstVide();
char fileEstPleine();
void fileReinitialise();

#ifdef TEST
int testFile();
#endif

#endif
