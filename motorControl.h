/**
 * @file mototControl.h
 *
 * @version 1.0
 *
 * @brief Asservissement des moteurs.
 *
 * @details Permet de déplacer le robot selon une position en x et y donnée par rapport à sa position actuelle.
 *
 * @b Dépendance:
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
 * @brief Initialise la position et l'orientation de départ.
 *
 * @param p_x0cm position en x de départ (en cm).
 * @param p_y0cm position en y de départ (en cm).
 * @param p_teta0Radian orientation de départ (en radian).
 *
 * @return Rien.
 */
void initMotorControl(float p_x0Cm, float p_y0Cm, float p_teta0Radian);

/*
 * @brief Initialise l'orientation du robot à atteindre et la distance à parcourir.
 *
 * @param p_orientation angle à parcourir.
 * @param p_distance distance à parcourir.
 *
 * @return Rien.
 */
void setOrientationDistanceAsked(long p_orientation, long p_distance);

/*
 * @brief Dit si l'asservissement est terminé ou non.
 *
 * @param Aucun.
 *
 * @return 1 si l'asservissement est fini 0 sinon.
 */
int isMotorControlFinished(void);

/*
 * @brief Déplace le robot vers le point (x,y).
 *
 * @param p_x coordonnée x de la position du robot à atteindre.
 * @param p_y coordonnée y de la position du robot à atteindre.
 *
 * @return Rien.
 */
void goTo(float p_x, float p_y);

/*
 * @brief Gère le déplacements du robot, arrêt, tourne ou avance.
 *
 * @param Aucun.
 *
 * @return Rien.
 */
void motorControl();

/*
 * @brief Donne la distance à parcourir en pas codeur.
 *
 * @param Aucun.
 *
 * @return Distance à parcourir.
 */
long getDistanceAsked(void);

/*
 * @brief Donne l'angle absolu à parcourir en pas codeur.
 *
 * @param Aucun.
 *
 * @return L'angle absolu à parcourir.
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


