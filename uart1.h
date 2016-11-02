/**
 * @file uart1.h
 * @version 1.0
 *
 * @brief Gestion de l'uart1.

 * @details
 *
 * Initialisation et envoi de donnée sur l'UART1.
 *
 * @b Dépendance:
 * créer le fichier <b>uart1Interrupt.h</b> et <b>uart1Interrupt.c</b> avec la fonction <b>void onUART1Receive(unsigned char p_receivedChar);</b> qui sera appelée automatiquement à chaque réception d'un caractère.
 * Fichier: config.h
 *
 * hardware: FCY
 */

/**
 * @brief Initialise l'UART1 en interruption.
 *
 * @param p_baudRate valeur du bauderate pour cadencer l'UART1.
 *
 * @return Rien.
 */
void initUART1(long p_baudRate);

/**
 * @brief Ecriture d'un caratère sur l'UART1.
 *
 * @detail Reste bloqué sur l'écriture si nécessaire.
 *
 * @param p_data le caractère à envoyer.
 *
 * @return Rien.
 */
void putcUART1(char p_data);

/**
 * @brief Ecriture d'un bloc de donné sur l'UART1.
 *
 * @detail Reste bloqué sur l'écriture si nécessaire.
 *
 * @param *p_data chaine de caractère à envoyer.
 * @param  p_length longueur de la chaine sans le caractère de fin de chaine.
 *
 * @return Rien.
 */
void writeUART1(char *p_data, int p_length);

