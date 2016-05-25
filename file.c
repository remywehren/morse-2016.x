#include "test.h"



#define FILE_TAILLE 10

/** Espace de mémoire pour gérer la file. */
static char file[FILE_TAILLE];
static char in, out, overflow;

/**
 * Indique si la file est pleine.
 */
char fileEstPleine() {
    return (overflow == 255) ? 255 : 0; // file est pleine : file pas pleine
}
     
 /**
 * Indique si la file est vide.
 */
char fileEstVide() {
    return ((out == in) && (overflow == 0)) ? 255 : 0; // file est vide : file pas vide
}

/**
 * Si il y a de la place dans la file, enfile un caractère.
 * @param c Le caractère.
 */
void fileEnfile(char c) {
    if (!fileEstPleine()) {
        file[in] = c;
        overflow = (in == FILE_TAILLE-1) ? 255 : 0;   // overflow : pas overflow
        in++;
        if (in > FILE_TAILLE - 1){
            in = 0;
        }
    }
}

/**
 * Si la file n'est pas vide, défile un caractère.
 * @return Le caractère défilé, ou 0 si la file est vide.
 */
char fileDefile() {
    char c;
    if(!fileEstVide()) {
        c = file[out];
        out++;
        if (out > FILE_TAILLE - 1) {
            out = 0;
        }
        if (overflow == 255) {
            overflow = 0;
        }
        return c;
    }
    return 0;
}
/**
 * Vide et réinitialise la file.
 */
void fileReinitialise() {
    int i;
    for (i = 0 ; i < FILE_TAILLE ; i++) {
        file[i] = 0;
    }
    // Réinitalise la file
    in = 0;
    out = 0;
    overflow = 0;
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

    testeEgaliteEntiers("FDB003", c, FILE_TAILLE);
}

int testFile() {
    testEnfileEtDefile();
    testEnfileEtDefileBeaucoupDeCaracteres();
    testDebordePuisRecupereLesCaracteres();
}
#endif
