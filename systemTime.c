//============================================================
// systemTimer.c
//
// Gestion de la base de temps système de 1ms
//
// Dépendance hardware:
//   - Fréquence 1ms pour oscillateur 79.84MHz
//     ==> match_value et OpenTimer1(...T1_PS_x_x...)
//============================================================

/* Device header file */
#if defined(__dsPIC33E__)
#include <p33Exxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif
#include <timer.h>


#include <stdint.h>        /* Includes uint16_t definition */
#include <stdbool.h>       /* Includes true/false definition */


#include "systemTime.h"


extern void onSystemTimeMs(void);

unsigned long g_systemTime; //heure système (base 1/1000s)

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{
  WriteTimer1(0);
  g_systemTime++;
 
  onSystemTimeMs();

  IFS0bits.T1IF = 0; // Clear interrupt flag
}



//==========================================================
// Initialisation de la base de temps systeme (1/1000s)
//==========================================================

void initSystemTime(void)
{
  unsigned int l_match_value;

  g_systemTime = 0;

  /* Autorisation des interruption avec priorité 6 (faible) */
  ConfigIntTimer1(T1_INT_PRIOR_6 & T1_INT_ON);
  WriteTimer1(0);
  l_match_value = 39921; //Pour interruption toutes les 1ms (avec Tx_PS_1_1)
  OpenTimer1(T1_ON & T1_GATE_OFF & T1_IDLE_STOP &
             T1_PS_1_1 & T1_SYNC_EXT_OFF &
             T1_SOURCE_INT, l_match_value);
}

unsigned long getSystemTimeMs(void)
{
	unsigned long l_systemTime;

	//isole la fonction des interruptions du timer1 pour eviter les modifications pendant la copie.
	IEC0bits.T1IE = 0;//Timer1 Interrupt Disable

	l_systemTime = g_systemTime;//copie le temps syteme	

	IEC0bits.T1IE = 1;//Timer1 Interrupt Enable

	return l_systemTime;//renvoie le temps systeme
}

void wait(unsigned long int p_timeToWait)
{
    unsigned long int l_startTime;
    l_startTime = getSystemTimeMs();
    while((getSystemTimeMs() - l_startTime) <= p_timeToWait)
        ;
}