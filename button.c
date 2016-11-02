//============================================================
// button.c
//============================================================

/* Device header file */
#if defined(__dsPIC33E__)
#include <p33Exxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif


#include "..\config.h"
#include "button.h"

//==========================================================
// Initialisation des boutons
//========================================================== 
void initButton(void)
{
  //Configuration des broches en entrée
#ifdef BUTTON0_TRI
  BUTTON0_TRI = 1;
#endif
#ifdef BUTTON1_TRI
  BUTTON1_TRI = 1;
#endif
#ifdef BUTTON2_TRI
  BUTTON2_TRI = 1;
#endif
#ifdef BUTTON3_TRI
  BUTTON3_TRI = 1;
#endif
#ifdef BUTTON4_TRI
  BUTTON4_TRI = 1;
#endif
#ifdef BUTTON5_TRI
  BUTTON5_TRI = 1;
#endif
#ifdef BUTTON6_TRI
  BUTTON6_TRI = 1;
#endif
#ifdef BUTTON7_TRI
  BUTTON7_TRI = 1;
#endif
}

//==========================================================
//Renvoie l'état du bouton 1 à 8 (0 ou 1)
//==========================================================
unsigned char getButton(int p_number)
{
  unsigned char l_value = 0;

  switch (p_number)
  {
    case 0:
#ifdef BUTTON0_TRI
      l_value = BUTTON0_PORT;
#endif
      break;
    case 1:
#ifdef BUTTON1_TRI
      l_value = BUTTON1_PORT;
#endif
      break;
    case 2:
#ifdef BUTTON2_TRI
      l_value = BUTTON2_PORT;
#endif
      break;
    case 3:
#ifdef BUTTON3_TRI
      l_value = BUTTON3_PORT;
#endif
      break;
    case 4:
#ifdef BUTTON4_TRI
      l_value = BUTTON4_PORT;
#endif
      break;
    case 5:
#ifdef BUTTON5_TRI
      l_value = BUTTON5_PORT;
#endif
      break;
    case 6:
#ifdef BUTTON6_TRI
      l_value = BUTTON6_PORT;
#endif
      break;
    case 7:
#ifdef BUTTON7_TRI
      l_value = BUTTON7_PORT;
#endif
      break;
  }
  return l_value;
}

//==========================================================
//Renvoie l'état du bouton de tous les boutons
//==========================================================
unsigned char getAllButton(void)
{
  unsigned char l_value = 0;

#ifdef BUTTON0_TRI
      l_value = BUTTON0_PORT;
#endif

#ifdef BUTTON1_TRI
      l_value |= (BUTTON1_PORT<<1);
#endif

#ifdef BUTTON2_TRI
      l_value |= (BUTTON2_PORT<<2);
#endif

#ifdef BUTTON3_TRI
      l_value |= (BUTTON3_PORT<<3);
#endif

#ifdef BUTTON4_TRI
      l_value |= (BUTTON4_PORT<<4);
#endif

#ifdef BUTTON5_TRI
      l_value |= (BUTTON5_PORT<<5);
#endif

#ifdef BUTTON6_TRI
      l_value |= (BUTTON6_PORT<<6);
#endif

#ifdef BUTTON7_TRI
      l_value |= (BUTTON7_PORT<<7);
#endif
      return l_value;
}

