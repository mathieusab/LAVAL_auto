/**
 * @file motor.h
 *
 * @version 1.0
 *
 * @brief Gestion de 2 moteurs.
 *
 * @details Permet d'asservir 2 moteurs avec des pas d'incrémentation.
 *
 * @b Dépendance:
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
 * @brief Met le moteur à la puissance demandée.
 *
 * @detail La puissance sera comprise entre MOTOR_MIN_POWER et MOTOR_MAX_POWER défini dans motor.h.
 *
 * @param p_power puissance du moteur voulu.
 *
 * @return Rien.
 */
void setPowerMotor1(float p_power);   

/**
 * @brief Met le moteur à la puissance demandée.
 *
 * @detail La puissance sera comprise entre MOTOR_MIN_POWER et MOTOR_MAX_POWER défini dans motor.h.
 *
 * @param p_power puissance du moteur voulu.
 *
 * @return Rien.
 */
void setPowerMotor2(float p_power);   

/**
 * @brief Définie la puissance à ateindre ainsi que le pas d'incrémentation du moteur 1.
 *
 * @param p_power puissance du moteur à ateindre.
 *        p_incc pas d'incrémentation.
 *
 * @return Rien.
 */
void setPowerAcc1(float p_power , unsigned int p_incc);

/**
 * @brief Définie la puissance à ateindre ainsi que le pas d'incrémentation du moteur 2.
 *
 * @param p_power puissance du moteur à ateindre.
 *        p_incc pas d'incrémentation.
 *
 * @return Rien.
 */
void setPowerAcc2(float p_power , unsigned int p_incc);

/**
 * @brief Initialise l'asservissement des moteurs.
 *
 * @detail Initialise les 2 moteurs à l'arrêt.
 *
 * @param Aucun.
 *
 * @return Rien.
 */
void initAsservMotor(void);

/**
 * @brief Met à jour la puissance des moteurs.
 *
 * @detail Ajoute l'incrément à la puissance actuelle et si l'asservissement est terminé, coupe les moteurs.
 *
 * @param Aucun.
 *
 * @return Rien.
 */
void powerAsservMotor(void);

/**
 * @brief Donne la puissance à ateindre du moteur 1.
 *
 * @param Aucun.
 *
 * @return La puissance à ateindre du moteur 1.
 */
float getPowerAsked1(void);

/**
 * @brief Donne la puissance à ateindre du moteur 2.
 *
 * @param Aucun.
 *
 * @return La puissance à ateindre du moteur 2.
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
