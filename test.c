#include <xc.h>
#include <stdio.h>
#include "uart.h"

#ifdef TEST

/** Nombre de tests en erreur depuis l'initialisation des tests. */
static int testsEnErreur = 0;

void initialiseTests() {
    initialiseUART1();
    testsEnErreur = 0;
    printf("\r\nLancement des tests...\r\n");
}

unsigned char testeEgaliteEntiers(const char *testId, int valeurObtenue, int valeurAttendue) {
    if (valeurObtenue != valeurAttendue) {
        printf("%s: Valeur obtenue %d - Valeur attendue %d\r\n", testId, valeurObtenue, valeurAttendue);
        testsEnErreur++;
        return 255;
    }
    return 0;
}

unsigned char testeEgaliteChars(const char *testId, char valeurObtenue, char valeurAttendue) {
    if (valeurObtenue != valeurAttendue) {
        printf("%s: Valeur obtenue <%c> - Valeur attendue <%c>\r\n", testId, valeurObtenue, valeurAttendue);
        testsEnErreur++;
        return 255;
    }
    return 0;
}

void finaliseTests() {
    printf("%d tests en erreur\r\n", testsEnErreur);    
}

#endif
