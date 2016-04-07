#ifndef MORSE_H
#define	MORSE_H

/**
 * Reçoit la notification que l'actuateur a été enfoncé.
 */
void morseEnfoncePioche();

/**
 * Reçoit la notification que l'actuateur a été libéré.
 */
void morseLiberePioche();

/**
 * Est appelée régulièrement, toutes les 20 ms.
 */
void morseTicTac();

/**
 * Réinitialise la machine morse.
 */
void morseReinitialise();

#ifdef TEST
void testMorse();
#endif

#endif
