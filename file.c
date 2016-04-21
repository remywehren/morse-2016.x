#include "test.h"

#define FILE_TAILLE 10

/** Espace de mémoire pour stoquer la file. */
static char file[FILE_TAILLE]; 

/**
 * Si il y a de la place dans la file, enfile un caractère.
 * @param c Le caractère.
 */
void fileEnfile(char c) {
    // À implémenter...
}

/**
 * Si la file n'est pas vide, défile un caractère.
 * @return Le caractère défilé, ou 0 si la file est vide.
 */
char fileDefile() {
    // À implémenter...
    return 0;
}

/**
 * Indique si la file est vide.
 */
char fileEstVide() {
    // À implémenter...
    return 0;
}

/**
 * Indique si la file est pleine.
 */
char fileEstPleine() {
    // À implémenter...
    return 0;
}

/**
 * Vide et réinitialise la file.
 */
void fileReinitialise() {
    // À implémenter...
}

#ifdef TEST
void testEnfileEtDefile() {
    fileReinitialise();
    
    testeEgaliteEntiers("FIL01", fileEstVide(), 255);    
    testeEgaliteEntiers("FIL02", fileDefile(), 0);
    testeEgaliteEntiers("FIL03", fileDefile(), 0);

    fileEnfile(10);
    fileEnfile(20);

    testeEgaliteEntiers("FIL04", fileEstVide(), 0);
    testeEgaliteEntiers("FIL05", fileDefile(), 10);
    testeEgaliteEntiers("FIL06", fileDefile(), 20);
    testeEgaliteEntiers("FIL07", fileEstVide(), 255);
    testeEgaliteEntiers("FIL08", fileDefile(), 0);
}

void testEnfileEtDefileBeaucoupDeCaracteres() {
    int n = 0;
    char c = 0;
    
    fileReinitialise();

    for (n = 0; n < FILE_TAILLE * 4; n++) {
        fileEnfile(c);
        if (testeEgaliteEntiers("FBC001", fileDefile(), c)) {
            return;
        }
        c++;
    }
}

void testDebordePuisRecupereLesCaracteres() {
    fileReinitialise();

    char c = 1;
    while(!fileEstPleine()) {
        fileEnfile(c++);
    }

    testeEgaliteEntiers("FDB001", fileDefile(), 1);
    testeEgaliteEntiers("FDB002", fileDefile(), 2);
    
    while(!fileEstVide()) {
        c = fileDefile();
    }
    fileEnfile(1);      // Ces caractères sont ignorés...
    fileEnfile(1);      // ... car la file est pleine.

    testeEgaliteEntiers("FDB003", c, FILE_TAILLE);
}

int testFile() {
    testEnfileEtDefile();
    testEnfileEtDefileBeaucoupDeCaracteres();
    testDebordePuisRecupereLesCaracteres();
}
#endif
