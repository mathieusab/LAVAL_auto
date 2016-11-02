/**
 * @file uart2.h
 * @version 1.0
 *
 * @brief Gestion de l'uart2.

 * @details
 *
 * Initialisation et envoi de donnée sur l'UART2.
 *
 * @b Dépendance:
 * créer le fichier <b>uart2Interrupt.h</b> et <b>uart2Interrupt.c</b> avec la fonction <b>void onUART2Receive(unsigned char p_receivedChar);</b> qui sera appelée automatiquement à chaque réception d'un caractère.
 * Fichier: config.h
 *
 * hardware: FCY
 */

/**
 * @brief Initialise l'UART2 en interruption.
 *
 * @param p_baudRate valeur du bauderate pour cadencer l'UART2.
 *
 * @return Rien.
 */
void initUART2(long p_baudRate);

/**
 * @brief Ecriture d'un caratère sur l'UART2.
 *
 * @detail Reste bloqué sur l'écriture si nécessaire.
 *
 * @param p_data le caractère à envoyer.
 *
 * @return Rien.
 */
void putcUART2(char p_data);

/**
 * @brief Ecriture d'un bloc de donné sur l'UART2.
 *
 * @detail Reste bloqué sur l'écriture si nécessaire.
 *
 * @param *p_data chaine de caractère à envoyer.
 * @param  p_length longueur de la chaine sans le caractère de fin de chaine.
 *
 * @return Rien.
 */
void writeUART2(char *p_data, int p_length);




