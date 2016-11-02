/**
 * @file coder.h
 *
 * @version 1.0
 *
 * @brief Gestion des codeurs.
 *
 * @details Permet de r�cuperer le d�placement des 2 moteurs.
 *
 * @b D�pendance:
 *
 * Fichier: config.h
 */

/**
 * @brief Initialise 2 codeurs.
 *
 * @param Aucun.
 *
 * @return Rien.
 */
void initCoder( void );

/**
 * @brief Reset 2 codeurs.
 *
 * @detail Remet � z�ro les valeurs de 2 codeurs.
 *
 * @param Aucun.
 *
 * @return Rien.
 */
void resetCoder( void );

/**
 * @brief Donne la valeur actuelle du codeur 1.
 *
 * @param Aucun.
 *
 * @return La valeur actuelle du codeur 1.
 */
long getCoder1( void );

/**
 * @brief Donne la valeur actuelle du codeur 2.
 *
 * @param Aucun.
 *
 * @return La valeur actuelle du codeur 2.
 */
long getCoder2( void );

/**
 * @brief Donne la valeur totale du codeur 1.
 *
 * @detail Valeur totale = valeur actuelle + nombre de tours d�j� effectu�s par le codeur 1.
 *
 * @param Aucun.
 *
 * @return La valeur totale du codeur 1.
 */
long getTotalValueCoder1( void );

/**
 * @brief Donne la valeur totale du codeur 2.
 *
 * @detail Valeur totale = valeur actuelle + nombre de tours d�j� effectu�s par le codeur 2.
 *
 * @param Aucun.
 *
 * @return La valeur totale du codeur 2.
 */
long getTotalValueCoder2( void );

/**
 * @brief Donne le nombre de "tops" du codeur 1 entre 2 appels de fonction.
 *
 * @param Aucun.
 *
 * @return Le nombre de "tops" du codeur 1 entre 2 appels de fonction.
 */
long getDeltaValueCoder1( void );

/**
 * @brief Donne le nombre de "tops" du codeur 2 entre 2 appels de fonction.
 *
 * @param Aucun.
 *
 * @return Le nombre de "tops" du codeur 2 entre 2 appels de fonction.
 */
long getDeltaValueCoder2( void ); 

