//============================================================
// uart2.c
//
// Gestion de l'uart2
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
#include "uart2.h"


//Fonction appelée à chaque reception d'un caractère en interruption
extern void onUART2Receive(unsigned char p_receivedChar);



void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void)
{
  char l_receivedChar;
  int l_error; //code de l'erreur de reception

  IFS1bits.U2RXIF = 0;

  while(U2STAbits.URXDA) //tant que des donnees sont disponibles
  {
    l_error = 0;
    
    if(U2STAbits.FERR == 1)
    {
      l_error = 1; //Framing error
    }
    if (U2STAbits.PERR == 1)
    {
      l_error = 2; //Parity error
    }

    l_receivedChar = U2RXREG;

    if (l_error == 0)
    {
      // ==> utilisation de receivedChar (GESTION DE LA RECEPTION)
       onUART2Receive(l_receivedChar);
     }
  }

	/* must clear the overrun error to keep uart receiving */
	if(U2STAbits.OERR == 1)	 U2STAbits.OERR = 0;
}


//Initialise l'UART2 en interruption
void initUART2(long p_baudRate)
{

//Définition des pattes programmables
//==================================================

UART2_TX_RP = 0b00101; //U2TX
RPINR19bits.U2RXR = UART2_RX_RP;

//==================================================

U2BRG = (((FCY/p_baudRate)/16.0) +0.5 - 1); // BAUD Rate Setting
                                          //+0.5 pour arrondir au plus proche
U2MODEbits.STSEL = 0; // 1 Stop bit
U2MODEbits.PDSEL = 0b00; // No Parity, 8 data bits
U2MODEbits.BRGH = 0; // BRG generates 16 clocks per bit period
                     //(16x baud clock, Standard mode)
U2MODEbits.URXINV = 0; //UxRX Idle state is ?1?
U2MODEbits.ABAUD = 0; // Auto-Baud Disabled
U2MODEbits.LPBACK = 0; //Loopback mode is disabled
U2MODEbits.WAKE = 0; //No wake-up enabled
U2MODEbits.UEN = 0b00; //UxTX and UxRX pins are enabled and used;
                     //UxCTS and UxRTS/BCLK pins controlled by port latches
U2MODEbits.RTSMD = 0; //UxRTS pin in Flow Control mode
U2MODEbits.IREN = 0; //IrDA encoder and decoder disabled
U2MODEbits.USIDL = 0; //Continue module operation in Idle mode

//Mettre impérativement cette ligne avant initialisation de U1STA
//U1STAbits.UTXEN non pris en compte dans le cas contraire
U2MODEbits.UARTEN = 1; // Enable UART

U2STAbits.OERR = 0; //Clearing a previously set OERR bit
U2STAbits.ADDEN = 0; //Address Detect mode disabled
U2STAbits.URXISEL = 0b00;//Interrupt is set when any character is received and 
                       //transferred from the UxRSR to the receive buffer.
                       //Receive buffer has one or more characters
U2STAbits.UTXBRK = 0;  //Sync Break transmission disabled or completed
U2STAbits.UTXINV = 0; //UxTX Idle state is ?1?
U2STAbits.UTXISEL0 = 0; //Interrupt when a character is transferred to the Transmit
U2STAbits.UTXISEL1 = 0;//Shift register (this implies there is at least one
                      //character open in the transmit buffer
 

IEC1bits.U2TXIE = 0; // Disable UART TX Interrupt
IEC1bits.U2RXIE = 1; // Enable UART RX Interrupt
U2STAbits.UTXEN = 1; // Enable UART TX

}

//=========================================================
//Ecriture d'un caratère sur l'UART
//!!!Reste bloqué sur l'écriture si nécessaire
//=========================================================


void putcUART2(char p_data)
{
  while(U2STAbits.UTXBF); //Attente du buffer vide
  U2TXREG = p_data;
}


//===========================================================
//Ecriture d'un bloc de donné sur l'UART
//!!!Reste bloqué sur l'écriture si nécessaire
//============================================================


void writeUART2(char *p_data, int p_length)
{
  char * l_ptr;
  int l_cpt;

  l_ptr = p_data;
  l_cpt = 0;
  while(l_cpt < p_length) //Pour le nombre d'octet à transmettre
  {
    while(U2STAbits.UTXBF); //Attente du buffer vide
    U2TXREG = *l_ptr; //Envoi  d'un octet
    l_ptr++; //pointe sur octet suivant
    l_cpt++;
  }
}
