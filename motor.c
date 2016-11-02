//============================================================
// motor.c
//
// Gestion de 2 moteurs
//
// Dépendance hardware:
//   - Dans config.h
//   - Fréquence PWM: 9.74KHz (79.84MHz/2)/4096
//         Voir ==> P1TCON.PTCKPS,P2TCON.PTCKPS,P1TPER,P2TPER
//============================================================

/* Device header file */
#if defined(__dsPIC33E__)
#include <p33Exxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif


#include "../config.h"
#include "motor.h"
//#include "PID_assert.h"

//Variables globales pour la rampe d'accélération
float g_currentPower1, g_currentPower2, g_powerAsked1, g_powerAsked2;
int g_increment1, g_increment2;


//==========================================================
// Initialisation des sorties et des PWMs
//==========================================================   
void initMotor(void)
{
	
    g_currentPower1 = 0.0f;
    g_currentPower2 = 0.0f;
    g_powerAsked1 = 0.0f;
    g_powerAsked2 = 0.0f;
    g_increment1 = 0;	//incrément moteur1
    g_increment2 = 0;	//incrément moteur2


    //Configuration des broches en sorties et de l'état initial
    MOTOR1_TRI_PWM_L = 0;
    MOTOR1_TRI_PWM_H = 0;
    MOTOR2_TRI_PWM_L = 0;
    MOTOR2_TRI_PWM_H = 0;
    MOTOR1_PORT_PWM_L = 0;
    MOTOR1_PORT_PWM_H = 0;
    MOTOR2_PORT_PWM_L = 0;
    MOTOR2_PORT_PWM_H = 0;
    MOTOR_DISABLE_TRI = 0;
    MOTOR_DISABLE_PORT = 1; //Désactive les drivers des moteurs

    //Base de temps du registre PWM1
    P1TPER = 0xFFF; // ==>4096

    //Base de temps du registre PWM2
    P2TPER = 0xFFF; // ==>4096

    //Valeur du registre timer PWM1
    P1TMR =  0x0;

    //Valeur du registre timer PWM2
    P2TMR =  0x0;


    //P1DTCON1: DEAD-TIME CONTROL REGISTER 1
    //  ==>pas  de dead-time
    P1DTCON1bits.DTA = 0;  //Dead-Time Value for Dead-Time Unit A bits
    P1DTCON1bits.DTAPS = 0; //Clock period for Dead-Time Unit A is TCY
    P1DTCON1bits.DTB = 0; //Dead-Time Value for Dead-Time Unit B bits
    P1DTCON1bits.DTBPS = 0;  //Clock period for Dead-Time Unit B is TCY
    //
    //P2DTCON1: DEAD-TIME CONTROL REGISTER 1
    //  ==>pas  de dead-time
    P2DTCON1bits.DTA = 0;  //Dead-Time Value for Dead-Time Unit A bits
    P2DTCON1bits.DTAPS = 0; //Clock period for Dead-Time Unit A is TCY
    P2DTCON1bits.DTB = 0; //Dead-Time Value for Dead-Time Unit B bits
    P2DTCON1bits.DTBPS = 0;  //Clock period for Dead-Time Unit B is TCY
    //
    //P1DTCON2: DEAD-TIME CONTROL REGISTER 2
    //  1 ==> Dead time provided from Unit B
    //  0 ===> Dead time provided from Unit A
    P1DTCON2bits.DTS1A = 0;
    P1DTCON2bits.DTS2I = 0;
    P1DTCON2bits.DTS2A = 0;
    P1DTCON2bits.DTS3I = 0;
    P1DTCON2bits.DTS3A = 0;
    //
    //P2DTCON2: DEAD-TIME CONTROL REGISTER 2
    //  1 ==> Dead time provided from Unit B
    //  0 ===> Dead time provided from Unit A
    P2DTCON2bits.DTS1A = 0;
    P2DTCON2bits.DTS1I = 0;

    //
    // P1FLTACON: FAULT A CONTROL REGISTER
    //
    P1FLTACONbits.FAEN1 = 0;  //PWMxH1/PWMxL1 pin pair is not controlled by Fault Input A
    P1FLTACONbits.FAEN2 = 0;  // ""        ""         ""        ""          ""          ""
    P1FLTACONbits.FAEN3 = 0;  // ""        ""         ""        ""          ""          ""
    P1FLTACONbits.FLTAM = 0;  // The Fault A input pin latches all control pins to the programmed states in PxFLTACON<13:8>
    P1FLTACONbits.FAOV1H = 0; //The PWM output pin is driven inactive on an external Fault input event
    P1FLTACONbits.FAOV2H = 0; // ""        ""         ""        ""          ""          ""        ""
    P1FLTACONbits.FAOV3H = 0; // ""        ""         ""        ""          ""          ""        ""

    //PWM1CON1: PWM1 CONTROL REGISTER 1
    //   0 ==> PWMxx pin disabled, I/O pin becomes general purpose I/O
    //   1 ==> PWMxx pin is enabled for PWM output
    // => Les broches ne sont en sortie PWM que lorsque le moteur doit tourner
    PWM1CON1bits.PEN1L = 0;
    PWM1CON1bits.PEN2L = 0;
    PWM1CON1bits.PEN3L = 0;
    PWM1CON1bits.PEN1H = 0;
    PWM1CON1bits.PEN2H = 0;
    PWM1CON1bits.PEN3H = 0;
    // 1 ==> PWM I/O pin pair is in the Independent PWM Output mode
    // 0 ==> PWM I/O pin pair is in the Complementary Output mode
    PWM1CON1bits.PMOD1 = 1;
    PWM1CON1bits.PMOD2 = 1;
    PWM1CON1bits.PMOD3 = 1;
    //
    //PWM2CON1: PWM2 CONTROL REGISTER 1
    //   0 ==> PWMxx pin disabled, I/O pin becomes general purpose I/O
    //   1 ==> PWMxx pin is enabled for PWM output
    // => Les broches ne sont en sortie PWM que lorsque le moteur doit tourner
    PWM2CON1bits.PEN1L = 0;
    PWM2CON1bits.PEN1H = 0;
    // 1 ==> PWM I/O pin pair is in the Independent PWM Output mode
    // 0 ==> PWM I/O pin pair is in the Complementary Output mode
    PWM2CON1bits.PMOD1 = 1;

    //
    //PWM1CON2: PWM1 CONTROL REGISTER 2
    //
    PWM1CON2bits.UDIS = 0; //Updates from Duty Cycle and Period Buffer registers are enabled
    PWM1CON2bits.OSYNC = 0; //Output overrides via the PxOVDCON register occur on next TCY boundary
    PWM1CON2bits.IUE = 1; //Updates to the active PxDC registers are immediate
    PWM1CON2bits.SEVOPS = 0; //PWM Special Event Trigger Output Postscale (0 ==> 1:1 postscale)
    //
    //PWM1CON2: PWM2 CONTROL REGISTER 2
    //
    PWM2CON2bits.UDIS = 0; //Updates from Duty Cycle and Period Buffer registers are enabled
    PWM2CON2bits.OSYNC = 0; //Output overrides via the PxOVDCON register occur on next TCY boundary
    PWM2CON2bits.IUE = 1; //Updates to the active PxDC registers are immediate
    PWM2CON2bits.SEVOPS = 0; //PWM Special Event Trigger Output Postscale (0 ==> 1:1 postscale)

    //
    //P1TCON: PWM1 TIME BASE CONTROL REGISTER
    //
    P1TCONbits.PTMOD = 0b00; //PWM time base operates in a Free-Running mode
    P1TCONbits.PTCKPS = 0; //PWM time base input clock period is TCY (1:1 prescale)  (1:(N+1))
    P1TCONbits.PTOPS = 1; //PWM Time Base Output Postscale (1:2)   (1:(N+1))
    P1TCONbits.PTSIDL = 1; //PWM time base halts in CPU Idle mode
    P1TCONbits.PTEN = 1; //PWM Time Base Timer Enable
    //
    //P2TCON: PWM2 TIME BASE CONTROL REGISTER
    //
    P2TCONbits.PTMOD = 0b00; //PWM time base operates in a Free-Running mode
    P2TCONbits.PTCKPS = 0; //PWM time base input clock period is TCY (1:1 prescale)  (1:(N+1))
    P2TCONbits.PTOPS = 1; //PWM Time Base Output Postscale (1:2)   (1:(N+1))
    P2TCONbits.PTSIDL = 1; //PWM time base halts in CPU Idle mode
    P2TCONbits.PTEN = 1; //PWM Time Base Timer Enable

    MOTOR_DISABLE_PORT = 0; //Active les drivers des moteurs
}


//==========================================================
// Définition de la commande du moteur 1
// power: (de MOTOR_MIN_POWER à MOTOR_MAX_POWER)   0 = arrêt
//==========================================================
void setPowerMotor1( float p_power )
{
    //Arrêt
    if ( p_power == 0 ) //Arrêt
    {
        // ==> PWM1L et PWM1H inactif
        MOTOR1_PWML = 0;
        MOTOR1_PWMH = 0;
        g_currentPower1 = p_power;
    }
    else if ( p_power < 0 )  //sens de rotation négatif
    {
        if (p_power < MOTOR_MIN_POWER)
        {
            p_power = MOTOR_MIN_POWER;
        }
         g_currentPower1 = p_power;
        //Passage en nombre positif
        p_power = -p_power;
        //Applique le rapport cyclique
        MOTOR1_DUTY_PWM_L = p_power;
        // ==> PWM1L actif
        MOTOR1_PWML = 1;
        MOTOR1_PWMH = 0;
    }
    else  //sens de rotation positif
    {
        if (p_power > MOTOR_MAX_POWER)
        {
            p_power = MOTOR_MAX_POWER;
        }
        g_currentPower1 = p_power;
        //Applique le rapport cyclique
        MOTOR1_DUTY_PWM_H = p_power;
        // ==> PWM1H actif
        MOTOR1_PWML = 0;
        MOTOR1_PWMH = 1;
    }
}


//==========================================================
// Définition de la commande du moteur 2
// power: (de MOTOR_MIN_POWER à MOTOR_MAX_POWER)   0 = arrêt
//==========================================================
void setPowerMotor2( float p_power )
{
    //Arrêt
    if ( p_power == 0 )   //Arrêt
    {
        // ==> PWM1L et PWM1H inactif
        MOTOR2_PWML = 0;
        MOTOR2_PWMH = 0;
        g_currentPower2 = p_power;
    }
    else if ( p_power < 0 )   //sens de rotation négatif
    {
        if (p_power < MOTOR_MIN_POWER)
        {
            p_power = MOTOR_MIN_POWER;
        }
        g_currentPower2 = p_power;
        //Passage en nombre positif
        p_power = -p_power;
        //Applique le rapport cyclique
        MOTOR2_DUTY_PWM_L = p_power;
        // ==> PWM1L actif
        MOTOR2_PWML = 1;
        MOTOR2_PWMH = 0;
    }
    else  //sens de rotation positif
    {
        if (p_power > MOTOR_MAX_POWER)
        {
            p_power = MOTOR_MAX_POWER;
        }
        g_currentPower2 = p_power;
        //Applique le rapport cyclique
        MOTOR2_DUTY_PWM_H = p_power;
        // ==> PWM1H actif
        MOTOR2_PWML = 0;
        MOTOR2_PWMH = 1;
    }
}


//==========================================================
// Consigne pour la rampe
// moteur 1
//==========================================================
void setPowerAcc1(float p_power, unsigned int p_incrementationStep)
{
    if(p_power > g_currentPower1)//p_power > 0.0f
    {
        g_powerAsked1 = p_power;
        g_increment1 = p_incrementationStep;
    }
    else
    {
        g_powerAsked1 = p_power;
        g_increment1 = -p_incrementationStep;
    }
}

//==========================================================
// Consigne pour la rampe
// moteur 2
//==========================================================
void setPowerAcc2(float p_power, unsigned int p_incrementationStep)
{
    if(p_power > g_currentPower2)//p_power > 0.0f
    {
        g_powerAsked2 = p_power;
        g_increment2 = p_incrementationStep;
    }
    else
    {
        g_powerAsked2 = p_power;
        g_increment2 = -p_incrementationStep;
    }
}

//==========================================================
// Initialise les moteurs à l'arrêt
//==========================================================
void initAsservMotor(void)
{
    setPowerMotor1(0.0f);
    setPowerMotor2(0.0f);
    g_currentPower1 = 0.0f;
    g_currentPower2 = 0.0f;
    g_increment2 = 0;
    g_increment1 = 0;
}

//==========================================================
// Définition de la rampe d'accélération
//==========================================================
void powerAsservMotor(void)
{

    if(g_increment1 != 0)
    {
        if(g_increment1 > 0.0f)// g_powerAsked1 > 0.0f
        {
            g_currentPower1 = g_currentPower1 + (float)g_increment1;

            if(g_currentPower1 > g_powerAsked1)
            {
                g_currentPower1 = g_powerAsked1;
                g_increment1 = 0;
            }
            setPowerMotor1(g_currentPower1);

        }
        else
        {
            g_currentPower1 = g_currentPower1 + (float)g_increment1;

            if(g_currentPower1 < g_powerAsked1)
            {
                g_currentPower1 = g_powerAsked1;
                g_increment1 = 0;
            }
            setPowerMotor1(g_currentPower1);
        }
    }
    
    if(g_increment2 != 0)
    {
        if(g_increment2 > 0.0f)//g_powerAsked2 > 0.0f
        {
            g_currentPower2 = g_currentPower2 + (float)g_increment2;

            if(g_currentPower2 > g_powerAsked2)
            {
                g_currentPower2 = g_powerAsked2;
                g_increment2 = 0;
            }
            setPowerMotor2(g_currentPower2);

        }
        else
        {
            g_currentPower2 = g_currentPower2 + (float)g_increment2;

            if(g_currentPower2 < g_powerAsked2)
            {
                g_currentPower2 = g_powerAsked2;
                g_increment2 = 0;
            }
            setPowerMotor2(g_currentPower2);
        }
    }
}

float getCurrentPower1(void)
{
    return g_currentPower1;
}

float getCurrentPower2(void)
{
    return g_currentPower2;
}

float getPowerAsked1(void)
{
    return g_powerAsked1;
}
float getPowerAsked2(void)
{
    return g_powerAsked2;
}