#include <stdlib.h>
#include <math.h>

#include "../config.h"

#include "motorControl.h"
#include "odometry.h"
#include "motor.h"
#include "coder.h"

#include "systemTime.h"
#include "remoteData.h"


long g_orientationAsked, g_distanceAsked;
stateMotorControl g_stateMotorControl;
rotation g_rotationDirection;

void initMotorControl(float p_x0Cm, float p_y0Cm, float p_teta0Radian)
{
    resetCoder();
    initOdometry (p_x0Cm, p_y0Cm, p_teta0Radian);
    g_orientationAsked = 0;
    g_distanceAsked = 0;
    g_stateMotorControl = STOP;
    g_rotationDirection = RIGHT;
}

//Initialise l'angle et la distance à parcourir en pas
void setOrientationDistanceAsked(long p_orientation, long p_distance)
{
    g_distanceAsked = p_distance;
    g_orientationAsked = p_orientation;
    initDeltaDistance();
    initDeltaOrientation();
    g_stateMotorControl = TURN;
}

//Retourne 1 si l'asservissement est fini
int isMotorControlFinished(void)
{
    if(g_stateMotorControl == STOP)
        return 1;
    else 
        return 0;
}

void goTo(float p_x, float p_y)
{
    long l_orientation;
    long l_distance;
    float l_dx;
    float l_dy;
    float l_x;
    float l_y;
    float l_orientationRadian;
    float l_dtetaRadian;
    float l_orientationCurrent;
    unsigned long time = getSystemTimeMs();

    getPositionCm(&l_x, &l_y);
    l_dx = p_x - l_x;
    l_dy = p_y - l_y;

    //calcul de la distance
    l_distance = sqrt((l_dx * l_dx) + (l_dy * l_dy)) * COEF_CM_TO_STEP;
    
    //évite la division par 0 dans l'arc tangente
    if(l_dx < 0.00001 && l_dx > -0.00001)
    {
        if(l_dy > 0.0f)
            l_orientationRadian = PI / 2;
        else
            l_orientationRadian = -PI / 2;
    }
    else
        l_orientationRadian = atan(l_dy / l_dx);
    
    //ajuste l'angle par rapport à un cercle trigo de 0:2PI
    if(l_dy < 0.0f && l_dx >= 0.0f)
        l_orientationRadian += 2.0f * PI;
    else if(l_dx < 0.0f)
        l_orientationRadian += PI;


    l_orientationCurrent = getOrientationRadian();//angle compris entre 0 et 2PI


    l_dtetaRadian = l_orientationCurrent - l_orientationRadian;

    //reajuste l'angle (le plus court)
    if(l_dtetaRadian < (-1.0f * PI))
        l_dtetaRadian += 2.0f * PI;
    else if(l_dtetaRadian > PI)
        l_dtetaRadian -= 2.0f * PI;

    //choix du sens de rotation le plus court
    if(l_dtetaRadian < PI && l_dtetaRadian >= 0.0)
        g_rotationDirection = RIGHT;
    else
        g_rotationDirection = LEFT;

    l_orientation = labs(l_dtetaRadian * COEF_RADIAN_TO_STEP);

    //envoie des paramètres d'asservissement et asservissement
    setOrientationDistanceAsked(l_orientation, l_distance);
    while(isMotorControlFinished() == 0)//tant que l'asservissement n'est pas fini
    {
        //traitement si besoin est
        if((getSystemTimeMs() - time) >= 100)
        {
            time = getSystemTimeMs();
            remoteDataFloat(99 , l_distance / (float)COEF_CM_TO_STEP);
            remoteDataFloat(2, l_orientationCurrent);
            remoteDataFloat(3, l_x);
            remoteDataFloat(4, l_y);
            remoteDataFloat(10, l_dtetaRadian);
        }
    }

}

//asservi le robot pour réaliser le déplacement
void motorControl()
{    
    switch(g_stateMotorControl)
    {
    case STOP:
        initAsservMotor(); //on éteint les moteurs
        break;
    case TURN:
        if(getDeltaOrientation() < g_orientationAsked)//on a pas ateint l'orientation voulue on continue de tourner
        {
            if(g_rotationDirection == RIGHT)//tourne à droite
            {
                setPowerMotor1(2500.0f);
                setPowerMotor2(-2500.0f);
            }
            else //tourne à gauche
            {
                setPowerMotor1(-2500.0f);
                setPowerMotor2(2500.0f);
            }
        }
        else //sinon on passe à la distance
             g_stateMotorControl = FORWARD;//après avoir tourné on avance
        break;
    case FORWARD:
        if(getDeltaDistance() < g_distanceAsked)//si on a PAS parcouru la distance on avance
        {
            setPowerMotor1(2500.0f);
            setPowerMotor2(2500.0f);
        }
        else
        {
            initAsservMotor();
            g_stateMotorControl = STOP;//après avoir avancé on s'arrête
        }
        break;
    }
}

long getDistanceAsked(void)
{
    return g_distanceAsked;
}

long getOrientationAsked(void)
{
    return g_orientationAsked;
}

rotation getRotationDirection(void)
{
    return g_rotationDirection;
}