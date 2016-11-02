/**
 * @file button.h
 * @author  FC
 * @version 1.0
 *
 * @brief Gestion des boutons.

 * @details
 *
 * Gestion de 1 � 8 boutons (maximum).
 *
 * @b D�pendance:
 *
 * Fichier: config.h
 */

/**
 * @brief Initialise les boutons de 0 � 7.
 *
 * @param Aucun.
 *
 * @return Rien.
 */
void initButton( void );


/**
 * @brief Donne l'�tat du bouton.
 *
 * @param p_number Numero du bouton (de 0 � 7).
 *
 * @return L'�tat du bouton (1 si utilis� 0 sinon).
 */
unsigned char getButton  (int p_number );

/**
 * @brief Donne l'�tat de tout les boutons.
 *
 * @param Aucun.
 *
 * @return Renvoi l'�tat des 8 boutons avec le bit le plus faible qui est associ� au 1er bouton.
 */
unsigned char getAllButton(void);