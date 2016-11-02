//============================================================
// servoOut.c
//
// Gestion de servomoteurs de modelisme
//
// Dépendance hardware:
//              FCY
//============================================================

#if defined(__dsPIC33E__)
#include <p33Exxxx.h>
#endif
#if defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include "..\config.h"
#include "servoOut.h"



#define PRESCALER               8
#define SCALE_FOR_PWM_OUT(p_value) (int)((((long)(FCY*3/2))+((long)((FCY)/1800)*(p_value)))/(1000*PRESCALER))
#define	DELAY_INTERRUPT_SERVO   20000/2


int g_servoOut[MAX_SERVO] ;/** tableau avec les durées pour chaques servos. 10000 ==> 1ms  à 25000 ==> 2.5ms*/
int g_outputNum = 0;/* servo en cours d'utilisation */
int g_stopMode = 0;


void __attribute__((__interrupt__,__no_auto_psv__)) _T4Interrupt(void);


// initialise les servomoteurs
void initServoOut( void )					
{
    int i;

    for (i = 0 ; i < MAX_SERVO ; i++)
        setServoOutX( i, 0);                    // on initialise chaque case du tableau à la valeur initiale 0 : correpsond à la position médianne du servo


    T4CON = 0b1000000000000000;                 // initialisation du timer4, sans prescaler
    T4CONbits.TCKPS = 1;			// prescaler diviseur par 8 (voir doc technique)
    _T4IP = 7;                                  // interruption de priorité 7, priorité max
    _T4IE = 0;                                  // bit d'activation pour les interruptions du timer4, desactif ici



    //on met toutes les sorties tristates a 0 (output) : on "active" toutes les sorties
    #ifdef  SERVOUT0_TRI
      SERVOUT0_TRI = 0;
      SERVOUT0_PORT = 0;
    #endif
    #ifdef  SERVOUT1_TRI
      SERVOUT1_TRI = 0;
      SERVOUT1_PORT = 0;
    #endif
    #ifdef  SERVOUT2_TRI
      SERVOUT2_TRI = 0;
      SERVOUT2_PORT = 0;
    #endif
    #ifdef  SERVOUT3_TRI
      SERVOUT3_TRI = 0;
      SERVOUT3_PORT = 0;
    #endif
    #ifdef  SERVOUT4_TRI
      SERVOUT4_TRI = 0;
      SERVOUT4_PORT = 0;
    #endif
    #ifdef  SERVOUT5_TRI
      SERVOUT5_TRI = 0;
      SERVOUT5_PORT = 0;
    #endif
    #ifdef  SERVOUT6_TRI
      SERVOUT6_TRI = 0;
      SERVOUT6_PORT = 0;
    #endif
    #ifdef  SERVOUT7_TRI
      SERVOUT7_TRI = 0;
      SERVOUT7_PORT = 0;
    #endif
    #ifdef  SERVOUT8_TRI
      SERVOUT8_TRI = 0;
      SERVOUT8_PORT = 0;
    #endif
	
}


//démarre les interruptions en vue de remplir les servomoteurs
void startServoOut( void )
{
    g_outputNum = 0;                    // on commencera par traiter le servo 1 (voir switch dans la routine T4)
    PR4 = SCALE_FOR_PWM_OUT(0);		// initialise le  servomoteur à 0°
    TMR4 = 0 ;
    _T4IF = 0 ;                         // l'interuption va être traite : on remet le flag a 0
    _T4IE = 1 ;                         // autorise les interuption provenant du timer4
                                        // les interruptions
}


#if (RECORD_FREE_STACK_SPACE == 1)
    extern unsigned int maxstack ;
#endif



//fonction d'interruption du timer4
//temps max pour traiter tout les servos : 20ms soit 10 servo
void __attribute__((__interrupt__,__no_auto_psv__)) _T4Interrupt(void)
{

	static int l_delay = 0;
        
	//on traite chaque servomoteur l'un après l'autre
	switch ( g_outputNum )
        {
	
#ifdef  SERVOUT0_PORT                                    //si le servo1 existe
        case 0:                                         //numéro du servo en cours de traitement
                PR4 = g_servoOut[g_outputNum];            //fixe le délai voulu au servomoteur n°g_outputNum
                SERVOUT0_PORT = 1;                       //deverrouille le "loquet" (latch) pemettant l'envoie de PR4 au servo
                l_delay = g_servoOut[g_outputNum];
                g_outputNum++;                          // on passe au servo suivant qui sera traité lors de la prochaine interruption (toutes les 2 ms)
                break ;
#endif
			
#ifdef  SERVOUT1_PORT
        case 1:
                SERVOUT0_PORT = 0;
                PR4 = g_servoOut[g_outputNum];
                SERVOUT1_PORT = 1;
                l_delay += g_servoOut[g_outputNum];
                g_outputNum++;
                break ;
#endif
			
#ifdef  SERVOUT2_PORT
        case 2:
                SERVOUT1_PORT = 0;
                PR4 = g_servoOut[g_outputNum];
                SERVOUT2_PORT = 1;
                l_delay += g_servoOut[g_outputNum];
                g_outputNum++;
                break ;
#endif
			
#ifdef  SERVOUT3_PORT
        case 3:
                SERVOUT2_PORT = 0;
                PR4 = g_servoOut[g_outputNum];
                SERVOUT3_PORT = 1;
                l_delay += g_servoOut[g_outputNum];
                g_outputNum++;
                break ;
#endif
			
#ifdef  SERVOUT4_PORT
        case 4:
                SERVOUT3_PORT = 0;
                PR4 = g_servoOut[g_outputNum];
                SERVOUT4_PORT = 1;
                l_delay += g_servoOut[g_outputNum];
                g_outputNum++;
                break ;
#endif
			
#ifdef  SERVOUT5_PORT
        case 5:
                SERVOUT4_PORT = 0;
                PR4 = g_servoOut[g_outputNum];
                SERVOUT5_PORT = 1;
                l_delay += g_servoOut[g_outputNum];
                g_outputNum++;
                break ;
#endif
			
#ifdef  SERVOUT6_PORT
        case 6:
                SERVOUT5_PORT = 0;
                PR4 = g_servoOut[g_outputNum];
                SERVOUT6_PORT = 1;
                l_delay += g_servoOut[g_outputNum];
                g_outputNum++;
                break ;
#endif
			
			
#ifdef  SERVOUT7_PORT
        case 7:
                SERVOUT6_PORT = 0;
                PR4 = g_servoOut[g_outputNum];
                SERVOUT7_PORT = 1;
                l_delay += g_servoOut[g_outputNum];
                g_outputNum++;
                break ;
#endif
			
			
#ifdef  SERVOUT8_PORT
        case 8:
                SERVOUT7_PORT = 0;
                PR4 = g_servoOut[g_outputNum];
                SERVOUT8_PORT = 1;
                l_delay += g_servoOut[g_outputNum];
                g_outputNum++;
                break ;
#endif

        default:
                if(g_stopMode == 1)  _T4IE = 0 ;                  // n'autorise plus momentanemement une interuption du timer4
                PR4 = DELAY_INTERRUPT_SERVO - l_delay;
                g_outputNum = 0;                                  //on recommence au premier servo
                l_delay = 0;

//n'autorise plus les sorties du dernier servomoteur défini
#if   defined(SERVOUT8_PORT)
    SERVOUT8_PORT = 0 ;
#elif defined(SERVOUT7_PORT)
    SERVOUT7_PORT = 0 ;
#elif defined(SERVOUT6_PORT)
    SERVOUT6_PORT = 0 ;
#elif defined(SERVOUT5_PORT)
    SERVOUT5_PORT = 0 ;
#elif defined(SERVOUT4_PORT)
    SERVOUT4_PORT = 0 ;
#elif defined(SERVOUT3_PORT)
    SERVOUT3_PORT = 0 ;
#elif defined(SERVOUT2_PORT)
    SERVOUT2_PORT = 0 ;
#elif defined(SERVOUT1_PORT)
    SERVOUT1_PORT = 0 ;
#elif defined(SERVOUT0_PORT)
    SERVOUT0_PORT = 0 ;
#endif
     break ;
	}
	TMR4=0;							
	_T4IF = 0 ;// efface l'interuption
        
	
#if (RECORD_FREE_STACK_SPACE == 1)

	unsigned int l_stack = WREG15;
	if ( l_stack > maxstack )
	{
		maxstack = l_stack;
	}
#endif
	return;
}




void setServoOutX(int p_numServo, int p_value)
{
    g_servoOut[p_numServo] =  SCALE_FOR_PWM_OUT(p_value);
}



void stopServoOut(void)
{
    g_stopMode = 1;
}



