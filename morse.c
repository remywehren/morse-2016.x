#include "file.h"
#include "test.h"
#include "morse.h"

#define MORSE_MAX_DUREE_POINT 10
#define MORSE_MIN_DUREE_PAUSE 30

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

// Déclaration variable pioche. */
    EtatPiocheMorse pioche;

// Déclaration de la variable lignePointPause. */
    CaractereMorse lignePointPause;

// Défifnition du caratère selon la séquence. */
    static char caractereMorse;
    
// Déclaration de la variable n. */
    long ni;

/**
 * Réinitialise le décodeur morse.
 */
void morseReinitialise() {
    caractereMorse = 0;
    ni = 0;
    pioche = PIOCHE_LIBRE;
}

/**
 * Appelée si la pioche morse à marqué un point.
 */
void morsePoint() {
    switch(caractereMorse) {
        case 0 : caractereMorse = 'E'; break;
        case 'A' : caractereMorse = 'R'; break;
        case 'B' : caractereMorse = '6'; break;
        case 'C' : caractereMorse = '?'; break;
        case 'D' : caractereMorse = 'B'; break;
        case 'E' : caractereMorse = 'I'; break;
        case 'F' : caractereMorse = '?'; break;
        case 'G' : caractereMorse = 'Z'; break;
        case 'H' : caractereMorse = '5'; break;
        case 'I' : caractereMorse = 'S'; break;
        case 'J' : caractereMorse = '?'; break;
        case 'K' : caractereMorse = 'C'; break;
        case 'L' : caractereMorse = '?'; break;
        case 'M' : caractereMorse = 'G'; break;
        case 'N' : caractereMorse = 'D'; break;
        case 'O' : caractereMorse = 'o'; break;     // o
        case 'P' : caractereMorse = '?'; break;
        case 'Q' : caractereMorse = '?'; break;
        case 'R' : caractereMorse = 'L'; break;
        case 'S' : caractereMorse = 'H'; break;
        case 'T' : caractereMorse = 'N'; break;
        case 'U' : caractereMorse = 'F'; break;
        case 'V' : caractereMorse = '?'; break;
        case 'W' : caractereMorse = 'P'; break;
        case 'X' : caractereMorse = '/'; break;
        case 'Y' : caractereMorse = '?'; break;
        case 'Z' : caractereMorse = '7'; break;
        case 'u' : caractereMorse = '?'; break;
        case 'r' : caractereMorse = '+'; break;     // e -> +
        case 'o' : caractereMorse = '8'; break;     // o -> 8
        case '#' : caractereMorse = '9'; break;     // # -> 9
        }       
}
/**
 * Appelée si la pioche morse a marqué une ligne.
 */
void morseLigne() {
    switch(caractereMorse) {
        case 0 : caractereMorse = 'T'; break;
        case 'A' : caractereMorse = 'W'; break;
        case 'B' : caractereMorse = '='; break;
        case 'C' : caractereMorse = '?'; break;
        case 'D' : caractereMorse = 'X'; break;
        case 'E' : caractereMorse = 'A'; break;
        case 'F' : caractereMorse = '?'; break;
        case 'G' : caractereMorse = 'Q'; break;
        case 'H' : caractereMorse = '4'; break;
        case 'I' : caractereMorse = 'U'; break;
        case 'J' : caractereMorse = '1'; break;
        case 'K' : caractereMorse = 'Y'; break;
        case 'L' : caractereMorse = 'L'; break;
        case 'M' : caractereMorse = 'O'; break;
        case 'N' : caractereMorse = 'K'; break;
        case 'O' : caractereMorse = '#'; break;         // O -> #
        case 'P' : caractereMorse = '?'; break;
        case 'Q' : caractereMorse = '?'; break;
        case 'R' : caractereMorse = 'r'; break;
        case 'S' : caractereMorse = 'V'; break;
        case 'T' : caractereMorse = 'M'; break;
        case 'U' : caractereMorse = 'u'; break;         // U -> u
        case 'V' : caractereMorse = '3'; break;
        case 'W' : caractereMorse = 'J'; break;
        case 'X' : caractereMorse = '?'; break;
        case 'Y' : caractereMorse = '?'; break;
        case 'Z' : caractereMorse = '?'; break;
        case 'u' : caractereMorse = '2'; break;     // u -> 2
        case 'r' : caractereMorse = '?'; break;
        case 'o' : caractereMorse = '?'; break;
        case '#' : caractereMorse = '0'; break;     // # -> 0
    }
}

/**
 * Rend le caractère ASCII correspondant à la séquence 
 * d'appels à morsePoint et morseLigne.
 * @return Le caractère ASCII. Un '?' si la séquence est inconnue.
 */
unsigned char morseDecodeSequence() {
    while (lignePointPause != CARACTERE_PAUSE) {
        if ((caractereMorse >= 'A') && (caractereMorse >= 'Z')) {
            return caractereMorse;
        }
        else if ((caractereMorse >= '0') && (caractereMorse >= '9')) {
            return caractereMorse;
        }
        else if (caractereMorse == '+' || caractereMorse == '=' || caractereMorse == '/') {
            return caractereMorse;
        }
        //else if (caractereMorse == 'u' || caractereMorse == 'r' || caractereMorse == 'o'|| caractereMorse == '#') {
        //    return '?';
        //}
        else {
            return '?';
        }
    }
    return 0;
}

/**
 * Appelée si la pioche morse à marqué une pause.
 */
unsigned char morsePause() {
    static char charTemp;
    charTemp = caractereMorse;
    if (charTemp == 'u' || charTemp == 'r' || charTemp == 'o'|| charTemp == '#') {
            charTemp = '?';
        }
    caractereMorse = 0;
    return charTemp;
}

/**
 * Reçoit la notification que la pioche a été enfoncée.
 */
void morseEnfoncePioche() {
    pioche = PIOCHE_ENFONCEE;
    ni = 0;
}

/**
 * Reçoit la notification que la pioche a été libéré.
 */
void morseLiberePioche() {
    pioche = PIOCHE_LIBRE;
    if (ni > MORSE_MAX_DUREE_POINT) {
        morseLigne();
        fileEnfile(CARACTERE_LIGNE);
    }
    else if (ni <= MORSE_MAX_DUREE_POINT) {
        morsePoint();
        fileEnfile(CARACTERE_POINT);
    }
    ni = 0;
}

/**
 * Est appelée régulièrement, toutes les 20 ms.
 */
void morseTicTac() {
    
    switch (pioche) {
        case (PIOCHE_LIBRE) :
            ni++;
            if (ni >= MORSE_MIN_DUREE_PAUSE) {
                fileEnfile(CARACTERE_PAUSE);
                fileEnfile(morsePause());
                fileEnfile('\r');
                fileEnfile('\n');
                break; 
            }
            break;
        case (PIOCHE_ENFONCEE) : ni++; break;
        }  
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