#include "file.h"
#include "test.h"
#include "morse.h"

#define MORSE_MAX_DUREE_POINT 10
#define MORSE_MIN_DUREE_PAUSE 30

/**
 * Appelée si la pioche morse à marqué un point.
 */
void morsePoint() {
    // À implémenter...
}

/**
 * Appelée si la pioche morse a marqué une ligne.
 */
void morseLigne() {
    // À implémenter...
}

/**
 * Rend le caractère ASCII correspondant à la séquence 
 * d'appels à morsePoint et morseLigne.
 * @return Le caractère ASCII. Un '?' si la séquence est inconnue.
 */
unsigned char morseDecodeSequence() {
    // À implémenter...
    return 0;
}

/**
 * Appelée si la pioche morse à marqué une pause.
 */
unsigned char morsePause() {
    // À implémenter...
    return 0;
}

/**
 * Réinitialise le décodeur morse.
 */
void morseReinitialise() {
    // À implémenter...
}

/**
 * Liste les caractères morse.
 */
typedef enum {
    CARACTERE_LIGNE = '-',
    CARACTERE_POINT = '.',
    CARACTERE_PAUSE = ' '
} CaractereMorse;

/**
 * Décrit les états possibles de la pioche morse.
 */
typedef enum {
    PIOCHE_LIBRE,
    PIOCHE_ENFONCEE
} EtatPiocheMorse;

/**
 * Reçoit la notification que la pioche a été enfoncée.
 */
void morseEnfoncePioche() {
    // À implémenter...
}

/**
 * Reçoit la notification que la pioche a été libéré.
 */
void morseLiberePioche() {
    // À implémenter...
}

/**
 * Est appelée régulièrement, toutes les 20 ms.
 */
void morseTicTac() {
    // À implémenter...
}

#ifdef TEST

void testMorsePoint() {
    morseReinitialise();
    morsePoint();
    testeEgaliteChars("MPO", morseDecodeSequence(), 'E');
}
void testMorseLigne() {
    morseReinitialise();
    morseLigne();
    testeEgaliteChars("MLI", morseDecodeSequence(), 'T');
}
void testMorsePause() {
    morseReinitialise();
    morsePoint();
    morseLigne();
    testeEgaliteChars("MO-AA", morsePause(), 'A');
    morseLigne();
    morsePoint();
    morseLigne();
    testeEgaliteChars("MO-KK", morsePause(), 'K');
}
void testMorseDecodeLettreInconnue() {
    morseReinitialise();
    morsePoint();
    morseLigne();
    morsePoint();
    morseLigne();
    testeEgaliteChars("MO-IN", morsePause(), '?');
}
unsigned char testMorseDecode(const char *sequence) {
    unsigned char n = 0;

    morseReinitialise();
    do {
        switch(sequence[n++]) {
            case '-':
                morseLigne();
                break;
            case '.':
                morsePoint();
                break;
        }
    } while (sequence[n] != 0);
    
    return morsePause();
}
void testMorseDecodeToutAlphabet() {
    testeEgaliteChars("MO-A", testMorseDecode(".-"),    'A');
    testeEgaliteChars("MO-B", testMorseDecode("-..."),  'B');
    testeEgaliteChars("MO-C", testMorseDecode("-.-."),  'C');
    testeEgaliteChars("MO-D", testMorseDecode("-.."),   'D');
    testeEgaliteChars("MO-E", testMorseDecode("."),     'E');
    testeEgaliteChars("MO-F", testMorseDecode("..-."),  'F');
    testeEgaliteChars("MO-G", testMorseDecode("--."),   'G');
    testeEgaliteChars("MO-H", testMorseDecode("...."),  'H');
    testeEgaliteChars("MO-I", testMorseDecode(".."),    'I');
    testeEgaliteChars("MO-J", testMorseDecode(".---"),  'J');
    testeEgaliteChars("MO-K", testMorseDecode("-.-"),   'K');
    testeEgaliteChars("MO-L", testMorseDecode(".-.."),  'L');
    testeEgaliteChars("MO-M", testMorseDecode("--"),    'M');
    testeEgaliteChars("MO-N", testMorseDecode("-."),    'N');
    testeEgaliteChars("MO-O", testMorseDecode("---"),   'O');
    testeEgaliteChars("MO-P", testMorseDecode(".--."),  'P');
    testeEgaliteChars("MO-Q", testMorseDecode("--.-"),  'Q');
    testeEgaliteChars("MO-R", testMorseDecode(".-."),   'R');
    testeEgaliteChars("MO-S", testMorseDecode("..."),   'S');
    testeEgaliteChars("MO-T", testMorseDecode("-"),     'T');
    testeEgaliteChars("MO-U", testMorseDecode("..-"),   'U');
    testeEgaliteChars("MO-V", testMorseDecode("...-"),  'V');
    testeEgaliteChars("MO-X", testMorseDecode("-..-"),  'X');
    testeEgaliteChars("MO-Y", testMorseDecode("-.--"),  'Y');
    testeEgaliteChars("MO-Z", testMorseDecode("--.."),  'Z');

    testeEgaliteChars("MO-0", testMorseDecode("-----"), '0');
    testeEgaliteChars("MO-1", testMorseDecode(".----"), '1');
    testeEgaliteChars("MO-2", testMorseDecode("..---"), '2');
    testeEgaliteChars("MO-3", testMorseDecode("...--"), '3');
    testeEgaliteChars("MO-4", testMorseDecode("....-"), '4');
    testeEgaliteChars("MO-5", testMorseDecode("....."), '5');
    testeEgaliteChars("MO-6", testMorseDecode("-...."), '6');
    testeEgaliteChars("MO-7", testMorseDecode("--..."), '7');
    testeEgaliteChars("MO-8", testMorseDecode("---.."), '8');
    testeEgaliteChars("MO-9", testMorseDecode("----."), '9');
}
void attendTicTac(int nTicTac) {
    unsigned char n;
    for (n = 0; n < nTicTac; n++) {
        morseTicTac();
    }
}
void testMorseDetecteImpulsionsU() {
    morseReinitialise();
    fileReinitialise();
    
    morseEnfoncePioche();
    attendTicTac(1);
    morseLiberePioche();
    testeEgaliteChars("MDIU01", fileDefile(), CARACTERE_POINT);

    morseEnfoncePioche();
    attendTicTac(MORSE_MAX_DUREE_POINT);
    morseLiberePioche();
    testeEgaliteChars("MDIU02", fileDefile(), CARACTERE_POINT);

    attendTicTac(MORSE_MIN_DUREE_PAUSE - 1);
    
    morseEnfoncePioche();
    attendTicTac(MORSE_MAX_DUREE_POINT + 1);
    morseLiberePioche();
    testeEgaliteChars("MDIU03", fileDefile(), CARACTERE_LIGNE);

    attendTicTac(MORSE_MIN_DUREE_PAUSE);
    testeEgaliteChars("MDIU04", fileDefile(), CARACTERE_PAUSE);
    testeEgaliteChars("MDIU05", fileDefile(), 'U');
    testeEgaliteChars("MDIU06", fileDefile(), '\r');
    testeEgaliteChars("MDIU07", fileDefile(), '\n');
}
void testMorseDetecteImpulsionsET() {
    morseReinitialise();
    fileReinitialise();
    
    morseEnfoncePioche();
    attendTicTac(1);
    morseLiberePioche();
    testeEgaliteChars("MDIET01", fileDefile(), CARACTERE_POINT);

    attendTicTac(MORSE_MIN_DUREE_PAUSE);
    testeEgaliteChars("MDIET02", fileDefile(), CARACTERE_PAUSE);
    testeEgaliteChars("MDIET03", fileDefile(), 'E');
    testeEgaliteChars("MDIET04", fileDefile(), '\r');
    testeEgaliteChars("MDIET05", fileDefile(), '\n');

    morseEnfoncePioche();
    attendTicTac(MORSE_MAX_DUREE_POINT + 1);
    morseLiberePioche();
    testeEgaliteChars("MDIET06", fileDefile(), CARACTERE_LIGNE);

    attendTicTac(MORSE_MIN_DUREE_PAUSE);
    testeEgaliteChars("MDIET07", fileDefile(), CARACTERE_PAUSE);
    testeEgaliteChars("MDIET08", fileDefile(), 'T');
    testeEgaliteChars("MDIET09", fileDefile(), '\r');
    testeEgaliteChars("MDIET10", fileDefile(), '\n');
    
    attendTicTac(MORSE_MIN_DUREE_PAUSE);
    testeEgaliteEntiers("MDIET11", fileEstVide(), 255);
    attendTicTac(MORSE_MIN_DUREE_PAUSE * 2);
    testeEgaliteEntiers("MDIET12", fileEstVide(), 255);
}
void testMorseIgnorePauseInitiale() {
    morseReinitialise();
    fileReinitialise();

    attendTicTac(MORSE_MIN_DUREE_PAUSE);
    testeEgaliteEntiers("IPI01", fileEstVide(), 255);
    attendTicTac(MORSE_MIN_DUREE_PAUSE);
    testeEgaliteEntiers("IPI02", fileEstVide(), 255);
}

void testMorse() {
    testMorsePoint();
    testMorseLigne();
    testMorsePause();

    testMorseDecodeLettreInconnue();
    testMorseDecodeToutAlphabet();
    
    testMorseDetecteImpulsionsU();
    testMorseDetecteImpulsionsET();    
    testMorseIgnorePauseInitiale();
}

#endif