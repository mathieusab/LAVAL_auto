/**
 * @file motor.h
 *
 * @version 1.0
 *
 * @brief Gestion de 2 moteurs.
 *
 * @details Permet d'asservir 2 moteurs avec des pas d'incr�mentation.
 *
 * @b D�pendance:
 * 
 * Fichier: config.h
 */

#define MOTOR_MAX_POWER +8191.0f
#define MOTOR_MIN_POWER -8191.0f

/**
 * @brief Initialise les 2 moteurs avec leurs PWM.
 *
 * @param Aucun.
 *
 * @return Rien.
 */
void initMotor(void);

/**
 * @brief Met le moteur � la puissance demand�e.
 *
 * @detail La puissance sera comprise entre MOTOR_MIN_POWER et MOTOR_MAX_POWER d�fini dans motor.h.
 *
 * @param p_power puissance du moteur voulu.
 *
 * @return Rien.
 */
void setPowerMotor1(float p_power);   

/**
 * @brief Met le moteur � la puissance demand�e.
 *
 * @detail La puissance sera comprise entre MOTOR_MIN_POWER et MOTOR_MAX_POWER d�fini dans motor.h.
 *
 * @param p_power puissance du moteur voulu.
 *
 * @return Rien.
 */
void setPowerMotor2(float p_power);   

/**
 * @brief D�finie la puissance � ateindre ainsi que le pas d'incr�mentation du moteur 1.
 *
 * @param p_power puissance du moteur � ateindre.
 *        p_incc pas d'incr�mentation.
 *
 * @return Rien.
 */
void setPowerAcc1(float p_power , unsigned int p_incc);

/**
 * @brief D�finie la puissance � ateindre ainsi que le pas d'incr�mentation du moteur 2.
 *
 * @param p_power puissance du moteur � ateindre.
 *        p_incc pas d'incr�mentation.
 *
 * @return Rien.
 */
void setPowerAcc2(float p_power , unsigned int p_incc);

/**
 * @brief Initialise l'asservissement des moteurs.
 *
 * @detail Initialise les 2 moteurs � l'arr�t.
 *
 * @param Aucun.
 *
 * @return Rien.
 */
void initAsservMotor(void);

/**
 * @brief Met � jour la puissance des moteurs.
 *
 * @detail Ajoute l'incr�ment � la puissance actuelle et si l'asservissement est termin�, coupe les moteurs.
 *
 * @param Aucun.
 *
 * @return Rien.
 */
void powerAsservMotor(void);

/**
 * @brief Donne la puissance � ateindre du moteur 1.
 *
 * @param Aucun.
 *
 * @return La puissance � ateindre du moteur 1.
 */
float getPowerAsked1(void);

/**
 * @brief Donne la puissance � ateindre du moteur 2.
 *
 * @param Aucun.
 *
 * @return La puissance � ateindre du moteur 2.
 */
float getPowerAsked2(void);

/**
 * @brief Donne la puissance actuelle du moteur 1.
 *
 * @param Aucun.
 *
 * @return Puissance du moteur 1.
 */
float getCurrentPower1(void);

/**
 * @brief Donne la puissance actuelle du moteur 2.
 *
 * @param Aucun.
 *
 * @return Puissance du moteur 2.
 */
float getCurrentPower2(void);
