//#TODO A REVOIR
// Ajouter filtrage des entrees
//============================================================
// coder.c
//
// Gestion des codeurs
//
// Dépendance hardware:
//   - Dans config.h
//   
//        
//============================================================

/* Device header file */
#if defined(__dsPIC33E__)
#include <p33Exxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif


#include "../config.h"
#include "coder.h"



int g_coderOverFlowCount1; //nombre d'overflow du codeur 1
long g_totalValue1; //Somme du nombre de tour et de la valeur actuelle du codeur 1
int g_coderOverFlowCount2; //nombre d'overflow codeur 2
long g_totalValue2; //Somme du nombre de tour et de la valeur actuelle du codeur 2

long g_lastTotalValue2;
long g_lastTotalValue1;

//==========================================================
// Initialisation des codeurs
//========================================================== 
void initCoder( void )
{
    g_coderOverFlowCount1 = 0; //nombre de tour du codeur 1
    g_totalValue1 = 0; //Somme du nombre de tour et de la valeur actuelle du codeur 1
    g_coderOverFlowCount2 = 0; //nombre de tour du codeur 2
    g_totalValue2 = 0; //Somme du nombre de tour et de la valeur actuelle du codeur 2

    g_lastTotalValue2 = 0;
    g_lastTotalValue1 = 0;

    RPINR14bits.QEA1R = CODER1A_RP; //RP20
    RPINR14bits.QEB1R = CODER1B_RP; //RP21
    RPINR16bits.QEA2R = CODER2A_RP; //RP24
    RPINR16bits.QEB2R = CODER2B_RP; //RP25

    //REGISTER QEI1CON: QEI1 CONTROL REGISTER

    //INITIALISATION CODEUR 1

    QEI1CONbits.CNTERR = 0;  //Position count error has not occurred
    QEI1CONbits.QEISIDL = 0;	 //Continue module operation in Idle mode
    QEI1CONbits.UPDN = 0;
    QEI1CONbits.QEIM0 = 1;   //Quadrature Encoder Interface enabled (x4 mode) with position counter reset by match (MAXxCNT)
    QEI1CONbits.QEIM1 = 1;	
    QEI1CONbits.QEIM2 = 1;
    QEI1CONbits.SWPAB = 0;	//Phase A and Phase B inputs are not swapped
    QEI1CONbits.PCDOUT = 0;	//Position Counter Direction Status Output Disabled (Normal I/O pin operation)
    QEI1CONbits.TQGATE = 1;	//Timer gated time accumulation is enabled
    QEI1CONbits.TQCKPS1 = 1; //1:256 prescale value
    QEI1CONbits.TQCKPS0 = 1;
    QEI1CONbits.POSRES = 0;  //Index pulse does not reset position counter
    QEI1CONbits.TQCS = 0;		//Internal clock (tcy)


    //REGISTER DFLT1CON: DIGITAL FILTER CONTROL REGISTER

    DFLT1CONbits.IMV1 = 0;
    DFLT1CONbits.IMV0 = 0;
    DFLT1CONbits.CEID = 1;	//Interrupts due to count errors are disabled
    DFLT1CONbits.QEOUT = 0; 	//Digital filter outputs disabled (normal pin operation)
    DFLT1CONbits.QECK2 = 1;
    DFLT1CONbits.QECK1 = 1;	//111 = 1:256 Clock divide for QEAx/QEBx/INDXx
    DFLT1CONbits.QECK0 = 1;

    MAX1CNT =  0xFFFF;

    //REGISTER QEI2CON: QEI2 CONTROL REGISTER

    //INITIALISATION CODEUR 2

    QEI2CONbits.CNTERR = 0;  //Position count error has not occurred
    QEI2CONbits.QEISIDL = 0;	 //Continue module operation in Idle mode
    QEI2CONbits.UPDN = 0;
    QEI2CONbits.QEIM0 = 1;
    QEI2CONbits.QEIM1 = 1;	//Quadrature Encoder Interface enabled (x4 mode) with position counter reset by match (MAXxCNT)
    QEI2CONbits.QEIM2 = 1;
    QEI2CONbits.SWPAB = 0;	//Phase A and Phase B inputs are not swapped
    QEI2CONbits.PCDOUT = 0;	//Position Counter Direction Status Output Disabled (Normal I/O pin operation)
    QEI2CONbits.TQGATE = 1;	//Timer gated time accumulation is enabled
    QEI2CONbits.TQCKPS1 = 1; //1:256 prescale value
    QEI2CONbits.TQCKPS0 = 1;
    QEI2CONbits.POSRES = 0;  //Index pulse does not reset position counter
    QEI2CONbits.TQCS = 0;	//Internal clock (tcy)


    //REGISTER DFLT1CON: DIGITAL FILTER CONTROL REGISTER

    DFLT2CONbits.IMV1 = 0;
    DFLT2CONbits.IMV0 = 0;
    DFLT2CONbits.CEID = 1;	//Interrupts due to count errors are disabled
    DFLT2CONbits.QEOUT = 0; 	//Digital filter outputs disabled (normal pin operation)
    DFLT2CONbits.QECK2 = 1;
    DFLT2CONbits.QECK1 = 1;	//111 = 1:256 Clock divide for QEAx/QEBx/INDXx
    DFLT2CONbits.QECK0 = 1;

    MAX2CNT =  0xFFFF;

    //Interruption pour le comptage

    IEC3bits.QEI1IE = 1;
    IEC4bits.QEI2IE = 1;
    
    // pour initialisation de lastvalue...
    getDeltaValueCoder1();
    getDeltaValueCoder2();

}

void resetCoder( void )
{
    //génère une interruption d'overflow pour reset le compteur
    POS1CNT =  0x0000;
    POS2CNT =  0x0000;
    
    g_coderOverFlowCount1 = 0; //nombre de tour du codeur 1
    g_totalValue1 = 0; //Somme du nombre de tour et de la valeur actuelle du codeur 1
    g_coderOverFlowCount2 = 0; //nombre de tour du codeur 2
    g_totalValue2 = 0; //Somme du nombre de tour et de la valeur actuelle du codeur 2

    g_lastTotalValue2 = 0;
    g_lastTotalValue1 = 0;

}

void __attribute__((interrupt, no_auto_psv)) _QEI1Interrupt(void)
{
    //test le bit de poids fort pour avoir un temps de réaction maximal
    if ((POS1CNT & 0x8000) == 0)
        g_coderOverFlowCount1++;
    else
        g_coderOverFlowCount1--;

    IFS3bits.QEI1IF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _QEI2Interrupt(void)
{
    if ((POS2CNT & 0x8000) == 0)
        g_coderOverFlowCount2++;
    else
        g_coderOverFlowCount2--;

    IFS4bits.QEI2IF = 0;
}

long getCoder1( void )
{
    long l_instantRotation1 = 0L;//32bits
        l_instantRotation1 = POS1CNT;//POS1CNT = 16bits

    return l_instantRotation1;
}

long getCoder2( void )
{
    long l_instantRotation2 = 0L;
        l_instantRotation2 = POS2CNT;

    return l_instantRotation2;
}

long getTotalValueCoder1( void )
{
    g_totalValue1 = POS1CNT + (((long)g_coderOverFlowCount1) << 16);

    return g_totalValue1;
}

long getTotalValueCoder2( void )
{
    g_totalValue2 = POS2CNT + (((long)g_coderOverFlowCount2) << 16);

    return g_totalValue2;
}

long getDeltaValueCoder1( void )
{
    long l_delta1 = 0;		//Valeur que l'on va calculer puis retourner
    long l_valeurcodeur1 = 0;		//Valeur que l'on mesure en temps IRL

    l_valeurcodeur1 = POS1CNT + (((long)g_coderOverFlowCount1) << 16);
    l_delta1 = (l_valeurcodeur1 - g_lastTotalValue1);
    g_lastTotalValue1 = l_valeurcodeur1;

    return l_delta1;
}

long getDeltaValueCoder2( void )
{
    long l_delta2 = 0;		//Valeur que l'on va calculer puis retourner
    long l_valeurcodeur2 = 0;		//Valeur que l'on mesure en temps IRL

    l_valeurcodeur2 = POS2CNT + (((long)g_coderOverFlowCount2) << 16);
    l_delta2 = (l_valeurcodeur2 - g_lastTotalValue2);
    g_lastTotalValue2 = l_valeurcodeur2;

    return l_delta2;
}

