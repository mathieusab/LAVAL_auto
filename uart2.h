/**
 * @file uart2.h
 * @version 1.0
 *
 * @brief Gestion de l'uart2.

 * @details
 *
 * Initialisation et envoi de donn�e sur l'UART2.
 *
 * @b D�pendance:
 * cr�er le fichier <b>uart2Interrupt.h</b> et <b>uart2Interrupt.c</b> avec la fonction <b>void onUART2Receive(unsigned char p_receivedChar);</b> qui sera appel�e automatiquement � chaque r�ception d'un caract�re.
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
 * @brief Ecriture d'un carat�re sur l'UART2.
 *
 * @detail Reste bloqu� sur l'�criture si n�cessaire.
 *
 * @param p_data le caract�re � envoyer.
 *
 * @return Rien.
 */
void putcUART2(char p_data);

/**
 * @brief Ecriture d'un bloc de donn� sur l'UART2.
 *
 * @detail Reste bloqu� sur l'�criture si n�cessaire.
 *
 * @param *p_data chaine de caract�re � envoyer.
 * @param  p_length longueur de la chaine sans le caract�re de fin de chaine.
 *
 * @return Rien.
 */
void writeUART2(char *p_data, int p_length);




