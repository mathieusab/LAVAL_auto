//============================================================
// Odometry.c
//
// Gestion de l'odom�trie
//
// D�pendance hardware:
//   - Dans config.h
//   
//        
//============================================================

#include <math.h>
#include <stdlib.h> 
#include "../config.h"
#include "Odometry.h"
#include "coder.h"

/********* D�finition des variables globales ******************************
***************************************************************************/

//variables d'angle en pas
long g_orientCurrent;//orientation actuelle
long g_orientInit;//orientation de d�part
long g_orientPrev;//orientation pr�c�dente
long g_landmarkOrientation;//rep�re orientation pour le delta

//variables de distance en pas
long g_leftCurrent;//d�placement gauche
long g_rightCurrent;//d�placement droit
long g_distanceCovered; //distance parcourue
long g_distancePrevCovered;//distance pr�c�dente parcourue
long g_deltaDistanceCovered;//delta distance parcourue entre le rep�re et la distance actuelle(valeur absolue)
long g_landmarkDistance;//rep�re distance (pour calculer le delta)

//variables de position
float g_xCm;//position en cm
float g_yCm; 

double g_xStep;//position en pas
double g_yStep;


/************ Conditions initiales ***************************************************
Fonction appel�e 1 fois au d�but du programme qui initialise les variables orientation,
x, y et de distances parcourues en fonction de la position du robot au d�part
**************************************************************************************/
void initOdometry (float x0Cm, float y0Cm, float teta0Radian)
{ 
    g_xCm = x0Cm;
    g_yCm = y0Cm;

    g_xStep = g_xCm * COEF_CM_TO_STEP;
    g_yStep = g_yCm * COEF_CM_TO_STEP;

    g_orientCurrent = teta0Radian * COEF_RADIAN_TO_STEP;
    g_orientInit = teta0Radian * COEF_RADIAN_TO_STEP;
    g_orientPrev = teta0Radian * COEF_RADIAN_TO_STEP;
    g_landmarkOrientation = 0;

    g_leftCurrent = 0;
    g_rightCurrent = 0;
    g_distanceCovered = 0;
    g_distancePrevCovered = 0;
    g_deltaDistanceCovered = 0;
    g_landmarkDistance = 0;

}

/************ Calcul de x et y ******************************************************
Cette fonction r�cup�re les 2 variables globales gauche et droite et actualise les
valeurs de x et y. Le calcul de g_xCm et g_yCm peut �tre fait en dehors de la fonction
*************************************************************************************/
void calculPosition (void)
{
    long l_deltaOrientStep;
    long l_orientMoyStep;
    float l_orientMoyRadian;
    float l_deltaOrientRadian;
    double l_dxStep;
    double l_dyStep;

    g_leftCurrent = getTotalValueCoder1();
    g_rightCurrent = getTotalValueCoder2();

    // Correspondance avec notation du document th�orique
    g_distanceCovered = ( g_rightCurrent + g_leftCurrent ) / 2; // distance en pas parcourue � tn
    g_orientCurrent = g_orientInit + ( g_rightCurrent - g_leftCurrent ); //correspond � l'angle en pas 
    g_deltaDistanceCovered = g_distanceCovered - g_distancePrevCovered; // correspond � la distance parcourue en pas
    l_deltaOrientStep = g_orientCurrent - g_orientPrev; // correspond au delta de l'angle en pas
    l_orientMoyStep = ( g_orientCurrent + g_orientPrev ) / 2; // correspond au delta moyen en pas
    l_deltaOrientRadian = l_deltaOrientStep / COEF_RADIAN_TO_STEP; // correspond au delta de l'angle en radian
    l_orientMoyRadian = l_orientMoyStep / COEF_RADIAN_TO_STEP; // correspond � l'angle moyen en radian


    l_dxStep = g_deltaDistanceCovered *  cos(l_orientMoyRadian);
    l_dyStep = g_deltaDistanceCovered *  sin(l_orientMoyRadian);

    g_xStep = g_xStep + l_dxStep; // valeurs exprim�es en nombre de pas incr�mentaux
    g_yStep = g_yStep + l_dyStep;

    //Conversion des x et y en cm
    g_xCm = ( g_xStep / COEF_CM_TO_STEP );
    g_yCm = ( g_yStep / COEF_CM_TO_STEP );

    g_orientPrev = g_orientCurrent; // actualisation de delta-1
    g_distancePrevCovered = g_distanceCovered; //actualisation de la distance curviligne parcourue par le centre de l'axe


}

// Renvoi les positions de x et y en cm
//=======================================================================================
void getPositionCm(float *x, float *y)
{
    *x = g_xCm;
    *y = g_yCm;
}

// Renvoi les positions de x et y en pas
//=======================================================================================
void getPositionStep(double *x, double *y)
{
    *x = g_xStep;
    *y = g_yStep;
}

// Initialise la distance de d�part pour le calcul du delta
//=======================================================================================
void initDeltaDistance(void)
{
    g_landmarkDistance = g_distanceCovered;
}

// Retourne la distance absolue entre la distance actuelle et le rep�re en pas
//=======================================================================================
long getDeltaDistance(void)
{
    return labs(g_distanceCovered - g_landmarkDistance);
}

// Initialise l'orientation de d�part pour le calcul du delta
//=======================================================================================
void initDeltaOrientation(void)
{
    g_landmarkOrientation = g_orientCurrent;
}

// Retourne l'angle absolue entre l'orientation actuelle et le rep�re en pas
//=======================================================================================
long getDeltaOrientation(void)
{
    return labs(g_orientCurrent - g_landmarkOrientation);
}

// Retourne la distance parcourue depuis le d�but en pas
//=======================================================================================
long getDistanceStep(void)
{
    return g_distanceCovered;
}

// Retourne la distance parcourue depuis le d�but en cm
//=======================================================================================
float getDistanceCm(void)
{
    return g_distanceCovered / COEF_CM_TO_STEP;
}

// Retourne l'orientation en pas
//=======================================================================================
long getOrientationStep(void)
{
    return g_orientCurrent;
}

// Retourne l'orientation en radian compris entre 0 et 2 PI
//=======================================================================================
float getOrientationRadian(void)
{
    float l_orientationCurrent;

    l_orientationCurrent = g_orientCurrent / COEF_RADIAN_TO_STEP;
    //remet l'angle entre -PI et PI
    while(l_orientationCurrent > PI)
        l_orientationCurrent -= 2.0f * PI;
    while(l_orientationCurrent < -PI)
        l_orientationCurrent += 2.0f * PI;
    //remet l'angle entre 0 et 2PI
    if(l_orientationCurrent < 0.0f)
        l_orientationCurrent += 2.0f * PI;
    
    return l_orientationCurrent;
}
