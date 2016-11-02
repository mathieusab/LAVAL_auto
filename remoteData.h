/**
 * @file remoteData.h
 * @author  FC
 * @version 1.0
 *
 * @brief Gestion de la communication avec un système distant.
 *
 * @details
 *
 *  Permet la visualisation de données à distance pour la mise au point
 *  et la validation d'un programme.
 *
 * @b Dépendance:
 *
 * Aucune.
 */


#define MAX_FRAME_LENGTH 255
#define FRAME_START 0x55  //'U'
#define FRAME_STOP  0x5A //'Z'

//Type des données acceptées
enum DataType { DATA_U8=1, DATA_S8, DATA_STRING, DATA_U16, 
				DATA_S16,DATA_U32, DATA_S32, DATA_FLOAT, DATA_DOUBLE};

enum FrameType { DATA_FRAME='D'};

union RemoteData
{
    unsigned char m_data[8];
    unsigned char m_valueU8;
    char m_valueS8;	
    unsigned short m_valueU16;
    short m_valueS16;	
    unsigned long m_valueU32;
    long m_valueS32;
    float m_valueFloat;
    double m_valueDouble;
}; 

typedef struct type{
   //évite l'erreur pour void remoteDataX(unsigned char p_varNumber, type p_value);
}type;

/**
 * @fn void remoteDataX(unsigned char p_varNumber, type p_value);
 *
 * @brief Envoi la ou les données au système distant.
 *
 * @detail Le X correspond au type de donnée à envoyer <br/>
 *                                                         <span style="margin-left:40px;"> U8 pour un caractère non signé int <br/> <span/>
 *                                                         <span style="margin-left:40px;"> S8 pour un caractère signé int <br/> <span/>
 *							   <span style="margin-left:40px;"> String pour une chaine de caractère <br/> <span/>
 *							   <span style="margin-left:40px;"> U16 pour un entier non signé <br/> <span/>
 *							   <span style="margin-left:40px;"> S16 pour un entier signé <br/>
 *							   <span style="margin-left:40px;"> U32 pour un entier long non signé <br/> <span/>
 *							   <span style="margin-left:40px;"> S32 pour un entier long signé <br/> <span/>
 *							   <span style="margin-left:40px;"> Float pour un nombre floatant <br/> <span/>
 *							   <span style="margin-left:40px;"> Double pour un nombre floatant double <br/> <br/> <span/>
 *
 * @param p_varNumber le numero de la variable.
 *
 * @param p_value la donnée de type:<br/> unsigned char si X = U8 <br/>
 *					   signed char si X = S8 <br/>
 *					   char* si X = String <br/>
 *					   unsigned int si X = U16 <br/>
 *					   signed int si X = S16 <br/>
 *					   unsigned long si X = U32 <br/>
 *					   signed long si X = S32 <br/>
 *					   float si X = Float <br/>
 *					   double si X = Double <br/>
 *
 * @return Rien.
 */
void remoteDataX(unsigned char p_varNumber, type p_value);

//Envoi de données au système distant
void remoteDataU8(unsigned char p_varNumber, unsigned char p_value);
void remoteDataS8(unsigned char p_varNumber, char p_value);
void remoteDataString(unsigned char p_varNumber, char *p_value); 
void remoteDataU16(unsigned char p_varNumber, unsigned short p_value);
void remoteDataS16(unsigned char p_varNumber, short p_value);
void remoteDataU32(unsigned char p_varNumber, unsigned long p_value);
void remoteDataS32(unsigned char p_varNumber, long p_value);
void remoteDataFloat(unsigned char p_varNumber, float p_value);
void remoteDataDouble(unsigned char p_varNumber, double p_value);


/**
 * @brief Traitement d'un caractère reçu.
 *
 * @param  p_receiveCar Caractère à traiter.
 *
 * @return 0 si OK <br/>
 *   <0 en cas d'erreur <br/>
 *        -1 ==> erreur de caractère de contrôle <br/>
 *        -2 ==> pas de caractère de fin de trame <br/>
 *   1 si nouvelle donnée reçue <br/>
 */
int remoteOnReceive(char p_receiveCar);

/**
 * @brief Donne le type de frame.
 *
 * @param  Rien.
 *
 * @return Le type de frame 'ex: 'D' => data frame.
 */
char remoteGetFrameType(void);

/**
 * @brief Donne le type de variable reçu.
 *
 * @param  Rien.
 *
 * @return Le type de variable reçu.
 */
char remoteGetDataType(void);

/**
 * @brief Donne le numero de variable reçu.
 *
 * @param  Rien.
 *
 * @return Le numero de variable reçu.<br/>
					DATA_U8 = 1 pour un caractère non signé char <br/>
					DATA_S8 = 2 pour un caractère signé char <br/>
					DATA_STRING = 3 pour une chaine de caractère <br/>
					DATA_U16 = 4 pour un entier non signé <br/>
					DATA_S16 = 5 pour un entier signé <br/>
					DATA_U32 = 6 pour un entier long non signé </br>
					DATA_S32 = 7 pour un entier long signé <br/>
					DATA_FLOAT = 8 pour un nombre floatant <br/>
					DATA_DOUBLE = 9 pour un nombre double <br/>
 */
unsigned char remoteGetDataNumber(void);

/**
 * @brief Lecture de la valeur reçue pour les types numériques.
 *
 * @param  Rien.
 *
 * @return La valeur reçu dans un union (contenant tout les types numériques).
 */
union RemoteData * remoteGetValue(void);

/**
 * @brief Lecture de la valeur reçue pour les chaines de caractères.
 *
 * @param  Rien.
 *
 * @return La chaine de caractères reçu.
 */
unsigned char * remoteGetString(void);





