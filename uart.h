#ifndef UART_H
#define	UART_H

/**
 * Initialise la sortie 1 de la EUSART.
 * Si le UP est à 1MHz, le "Virtual Terminal" dans Proteus
 * doit être configuré comme suit:
 * - 1200 bauds.
 * - Transmission 8 bits.
 * - Bit de stop activé.
 */
void initialiseUART1();

#endif

