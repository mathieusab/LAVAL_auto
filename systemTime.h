/**
 * @file systemTime.h
 * @author  FC
 * @version 1.0
 *
 * @brief Gestion de la base de temps syst�me.
 *
 *
 * @b D�pendance:
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
 * @brief Lecture du temps syst�me en ms.
 *
 * @param  Rien.
 *
 * @return Le temps syst�me en ms.
 */
unsigned long getSystemTimeMs(void);


/**
 * @brief Attend pendant une periode donn�e (en ms).
 *
 * @param  Temps � attendre en ms.
 *
 * @return Attend pendant une p�riode donn�e.
 */
void wait(unsigned long int p_timeToWait);