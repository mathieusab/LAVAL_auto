/**
 * @file systemTime.h
 * @author  FC
 * @version 1.0
 *
 * @brief Gestion de la base de temps système.
 *
 *
 * @b Dépendance:
 *
 * aucune
 */




/**
 * @brief Initialise le temps systeme.
 *
 * @param  Rien.
 *
 * @return Rien.
 */
void initSystemTime(void); //Initialisation de la base de temps systeme (1/100s)

/**
 * @brief Lecture du temps système en ms.
 *
 * @param  Rien.
 *
 * @return Le temps système en ms.
 */
unsigned long getSystemTimeMs(void);


/**
 * @brief Attend pendant une periode donnée (en ms).
 *
 * @param  Temps à attendre en ms.
 *
 * @return Attend pendant une période donnée.
 */
void wait(unsigned long int p_timeToWait);