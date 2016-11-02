//============================================================
// uart1.c
//
// Gestion de l'uart1
//
// Dépendance hardware:
//              FCY
//============================================================

/* Device header file */
#if defined(__dsPIC33E__)
	#include <p33Exxxx.h>
#elif defined(__dsPIC33F__)
	#include <p33Fxxxx.h>
#endif

#include "..\config.h"
#include "uart1.h"


//Fonction appelée à chaque reception d'un caractère en interruption
extern void onUART1Receive(unsigned char p_receivedChar);



void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void)
{
  char l_receivedChar;
  int l_error; //code de l'erreur de reception

  IFS0bits.U1RXIF = 0;

  while(U1STAbits.URXDA) //tant que des donnees sont disponibles
  {
    l_error = 0;

    if (U1STAbits.FERR == 1)
    {
      l_error = 1; //Framing error
    }
    if (U1STAbits.PERR == 1)
    {
      l_error = 2; //Parity error
    }

    l_receivedChar = U1RXREG;

    if (l_error==0)
    {
      // ==> utilisation de receivedChar (GESTION DE LA RECEPTION)
       onUART1Receive(l_receivedChar);
     }
  }

	 /* must clear the overrun error to keep uart receiving */
	 if(U1STAbits.OERR == 1) U1STAbits.OERR = 0;
}


//Initialise l'UART1 en interruption
void initUART1(long p_baudRate)
{

//Définition des pattes programmables
//==================================================

 UART1_TX_RP = 0b00011; //U1TX
 RPINR18bits.U1RXR = UART1_RX_RP;

//==================================================

  U1BRG = (((FCY / p_baudRate) / 16.0) + 0.5 - 1); // BAUD Rate Setting
												 //+0.5 pour arrondir au plus proche

  U1MODEbits.STSEL = 0; // 1 Stop bit
  U1MODEbits.PDSEL = 0b00; // No Parity, 8 data bits
  U1MODEbits.BRGH = 0; // BRG generates 16 clocks per bit period
					   //(16x baud clock, Standard mode)
// U1MODEbits.BRG =1;
  
  U1MODEbits.URXINV = 0; //UxRX Idle state is ?1?
  U1MODEbits.ABAUD = 0; // Auto-Baud Disabled
  U1MODEbits.LPBACK = 0; //Loopback mode is disabled
  U1MODEbits.WAKE = 0; //No wake-up enabled
  U1MODEbits.UEN = 0b00; //UxTX and UxRX pins are enabled and used;
						 //UxCTS and UxRTS/BCLK pins controlled by port latches
  U1MODEbits.RTSMD = 0; //UxRTS pin in Flow Control mode
  U1MODEbits.IREN = 0; //IrDA encoder and decoder disabled
  U1MODEbits.USIDL = 0; //Continue module operation in Idle mode


  //Mettre impérativement cette ligne avant initialisation de U1STA
  //U1STAbits.UTXEN non pris en compte dans le cas contraire
  U1MODEbits.UARTEN = 1; // Enable UART

  U1STAbits.OERR = 0; //Clearing a previously set OERR bit
  U1STAbits.ADDEN = 0; //Address Detect mode disabled
  U1STAbits.URXISEL = 0b00;	 //Interrupt is set when any character is received and
							 //transferred from the UxRSR to the receive buffer.
							 //Receive buffer has one or more characters
  U1STAbits.UTXBRK = 0; //Sync Break transmission disabled or completed
  U1STAbits.UTXINV = 0; //UxTX Idle state is ?1?
  U1STAbits.UTXISEL0 = 0; //Interrupt when a character is transferred to the Transmit
  U1STAbits.UTXISEL1 = 0; //Shift register (this implies there is at least one
                          //character open in the transmit buffer

  IEC0bits.U1TXIE = 0; // Disable UART TX Interrupt
  IEC0bits.U1RXIE = 1; // Enable UART RX Interrupt
  U1STAbits.UTXEN = 1; // Enable UART TX

}


//=========================================================
//Ecriture d'un caratère sur l'UART
//!!!Reste bloqué sur l'écriture si nécessaire
//=========================================================


void putcUART1(char p_data)
{
  while (U1STAbits.UTXBF); //Attente du buffer vide
  U1TXREG = p_data;
}

//===========================================================
//Ecriture d'un bloc de donné sur l'UART
//!!!Reste bloqué sur l'écriture si nécessaire
//============================================================


void writeUART1(char *p_data, int p_length)
{
  char * l_ptr;
  int l_cpt;

  l_ptr = p_data;
  l_cpt = 0;
  while (l_cpt < p_length) //Pour le nombre d'octet à transmettre
  {
    while (U1STAbits.UTXBF); //Attente du buffer vide
    U1TXREG = *l_ptr; //Envoi  d'un octet
    l_ptr++; //pointe sur octet suivant
    l_cpt++;
  }
}



