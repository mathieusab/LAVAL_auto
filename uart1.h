/**
 * @file uart1.h
 * @version 1.0
 *
 * @brief Gestion de l'uart1.

 * @details
 *
 * Initialisation et envoi de donn�e sur l'UART1.
 *
 * @b D�pendance:
 * cr�er le fichier <b>uart1Interrupt.h</b> et <b>uart1Interrupt.c</b> avec la fonction <b>void onUART1Receive(unsigned char p_receivedChar);</b> qui sera appel�e automatiquement � chaque r�ception d'un caract�re.
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
 * @brief Ecriture d'un carat�re sur l'UART1.
 *
 * @detail Reste bloqu� sur l'�criture si n�cessaire.
 *
 * @param p_data le caract�re � envoyer.
 *
 * @return Rien.
 */
void putcUART1(char p_data);

/**
 * @brief Ecriture d'un bloc de donn� sur l'UART1.
 *
 * @detail Reste bloqu� sur l'�criture si n�cessaire.
 *
 * @param *p_data chaine de caract�re � envoyer.
 * @param  p_length longueur de la chaine sans le caract�re de fin de chaine.
 *
 * @return Rien.
 */
void writeUART1(char *p_data, int p_length);

