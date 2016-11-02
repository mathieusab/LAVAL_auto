/**
 * @file mototControl.h
 *
 * @version 1.0
 *
 * @brief Asservissement des moteurs.
 *
 * @details Permet de d�placer le robot selon une position en x et y donn�e par rapport � sa position actuelle.
 *
 * @b D�pendance:
 *
 * Fichier: config.h
 *          motor.h
 *          odometry.h
 */

typedef enum {  STOP,
                TURN,
                FORWARD
             } stateMotorControl;

typedef enum { RIGHT,
               LEFT
	     } rotation;

/*
 * @brief Initialise la position et l'orientation de d�part.
 *
 * @param p_x0cm position en x de d�part (en cm).
 * @param p_y0cm position en y de d�part (en cm).
 * @param p_teta0Radian orientation de d�part (en radian).
 *
 * @return Rien.
 */
void initMotorControl(float p_x0Cm, float p_y0Cm, float p_teta0Radian);

/*
 * @brief Initialise l'orientation du robot � atteindre et la distance � parcourir.
 *
 * @param p_orientation angle � parcourir.
 * @param p_distance distance � parcourir.
 *
 * @return Rien.
 */
void setOrientationDistanceAsked(long p_orientation, long p_distance);

/*
 * @brief Dit si l'asservissement est termin� ou non.
 *
 * @param Aucun.
 *
 * @return 1 si l'asservissement est fini 0 sinon.
 */
int isMotorControlFinished(void);

/*
 * @brief D�place le robot vers le point (x,y).
 *
 * @param p_x coordonn�e x de la position du robot � atteindre.
 * @param p_y coordonn�e y de la position du robot � atteindre.
 *
 * @return Rien.
 */
void goTo(float p_x, float p_y);

/*
 * @brief G�re le d�placements du robot, arr�t, tourne ou avance.
 *
 * @param Aucun.
 *
 * @return Rien.
 */
void motorControl();

/*
 * @brief Donne la distance � parcourir en pas codeur.
 *
 * @param Aucun.
 *
 * @return Distance � parcourir.
 */
long getDistanceAsked(void);

/*
 * @brief Donne l'angle absolu � parcourir en pas codeur.
 *
 * @param Aucun.
 *
 * @return L'angle absolu � parcourir.
 */
long getOrientationAsked(void);

/*
 * @brief Donne le sens de rotation du robot.
 *
 * @param Aucun.
 *
 * @return Sens de rotation du robot (RIGHT ou LEFT).
 */
rotation getRotationDirection(void);


