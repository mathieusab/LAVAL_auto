/**
 * @file button.h
 * @author  FC
 * @version 1.0
 *
 * @brief Gestion des boutons.

 * @details
 *
 * Gestion de 1 à 8 boutons (maximum).
 *
 * @b Dépendance:
 *
 * Fichier: config.h
 */

/**
 * @brief Initialise les boutons de 0 à 7.
 *
 * @param Aucun.
 *
 * @return Rien.
 */
void initButton( void );


/**
 * @brief Donne l'état du bouton.
 *
 * @param p_number Numero du bouton (de 0 à 7).
 *
 * @return L'état du bouton (1 si utilisé 0 sinon).
 */
unsigned char getButton  (int p_number );

/**
 * @brief Donne l'état de tout les boutons.
 *
 * @param Aucun.
 *
 * @return Renvoi l'état des 8 boutons avec le bit le plus faible qui est associé au 1er bouton.
 */
unsigned char getAllButton(void);