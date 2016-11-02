/**
 * @file led.h
 * @author  FC
 * @version 1.0
 *
 * @brief Gestion des leds.

 * @details
 *
 * Gestion de 1 à 8 leds (maximum).
 *
 * @b Dépendance:
 *
 * Fichier: config.h
 */
#include "..\config.h"

/**
 * @brief Allume ou éteint une led.
 *
 * @details X Correspond au numero de la led.
 *
 * @param State 0 Pour éteindre la led, 1 pour l'allumer.
 *
 * @return Rien.
 *
 */
//void setLedX(bool state);

/**
 * @brief Donne l'état de la led.
 *
 * @details X Correspond au numero de la led.
 *
 * @param Aucun.
 *
 * @return 0 si la led est éteinte, 1 sinon.
 *
 */
//bool getLedX();

/**
 * @brief Initialise la gestion de la led.
 *
 * @details X Correspond au numero de la led.
 *
 * @param Aucun.
 *
 * @return Rien.
 *
 */
void initLedX();

//Si 1 led
#ifdef LED0_TRI
#define setLed0(state) LED0_PORT_OUT=!(state)
#define getLed0()  (!LED0_PORT_IN)
#define initLed0() LED0_TRI=0;setLed0(0)
#endif

//Si 2 leds
#ifdef LED1_TRI 
#define setLed1(state) LED1_PORT_OUT=!(state) 
#define getLed1()  (!LED1_PORT_IN) 
#define initLed1() LED1_TRI=0;setLed1(0) 
#endif

//Si 3 leds
#ifdef LED2_TRI
#define setLed2(state) LED2_PORT_OUT=!(state)
#define getLed2()  (!LED2_PORT_IN)
#define initLed2() LED2_TRI=0;setLed2(0)
#endif

//Si 4 leds
#ifdef LED3_TRI
#define setLed3(state) LED3_PORT_OUT=!(state)
#define getLed3()  (!LED3_PORT_IN)
#define initLed3() LED3_TRI=0;setLed3(0)
#endif

//Si 5 leds
#ifdef LED4_TRI
#define setLed4(state) LED4_PORT_OUT=!(state)
#define getLed4()  (!LED4_PORT_IN)
#define initLed4() LED4_TRI=0;setLed4(0)
#endif

//Si 6 leds
#ifdef LED5_TRI
#define setLed5(state) LED5_PORT_OUT=!(state)
#define getLed5()  (!LED5_PORT_IN)
#define initLed5() LED5_TRI=0;setLed5(0)
#endif

//Si 7 leds
#ifdef LED6_TRI
#define setLed6(state) LED6_PORT_OUT=!(state)
#define getLed6()  (!LED6_PORT_IN)
#define initLed6() LED6_TRI=0;setLed6(0)
#endif

//Si 8 leds
#ifdef LED7_TRI
#define setLed7(state) LED7_PORT_OUT=!(state)
#define getLed7()  (!LED7_PORT_IN)
#define initLed7() LED7_TRI=0;setLed7(0)
#endif




