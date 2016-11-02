/**
 * @file remoteData.h
 * @author  FC
 * @version 1.0
 *
 * @brief Gestion de la communication avec un syst�me distant.
 *
 * @details
 *
 *  Permet la visualisation de donn�es � distance pour la mise au point
 *  et la validation d'un programme.
 *
 * @b D�pendance:
 *
 * Aucune.
 */


#define MAX_FRAME_LENGTH 255
#define FRAME_START 0x55  //'U'
#define FRAME_STOP  0x5A //'Z'

//Type des donn�es accept�es
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
   //�vite l'erreur pour void remoteDataX(unsigned char p_varNumber, type p_value);
}type;

/**
 * @fn void remoteDataX(unsigned char p_varNumber, type p_value);
 *
 * @brief Envoi la ou les donn�es au syst�me distant.
 *
 * @detail Le X correspond au type de donn�e � envoyer <br/>
 *                                                         <span style="margin-left:40px;"> U8 pour un caract�re non sign� int <br/> <span/>
 *                                                         <span style="margin-left:40px;"> S8 pour un caract�re sign� int <br/> <span/>
 *							   <span style="margin-left:40px;"> String pour une chaine de caract�re <br/> <span/>
 *							   <span style="margin-left:40px;"> U16 pour un entier non sign� <br/> <span/>
 *							   <span style="margin-left:40px;"> S16 pour un entier sign� <br/>
 *							   <span style="margin-left:40px;"> U32 pour un entier long non sign� <br/> <span/>
 *							   <span style="margin-left:40px;"> S32 pour un entier long sign� <br/> <span/>
 *							   <span style="margin-left:40px;"> Float pour un nombre floatant <br/> <span/>
 *							   <span style="margin-left:40px;"> Double pour un nombre floatant double <br/> <br/> <span/>
 *
 * @param p_varNumber le numero de la variable.
 *
 * @param p_value la donn�e de type:<br/> unsigned char si X = U8 <br/>
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

//Envoi de donn�es au syst�me distant
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
 * @brief Traitement d'un caract�re re�u.
 *
 * @param  p_receiveCar Caract�re � traiter.
 *
 * @return 0 si OK <br/>
 *   <0 en cas d'erreur <br/>
 *        -1 ==> erreur de caract�re de contr�le <br/>
 *        -2 ==> pas de caract�re de fin de trame <br/>
 *   1 si nouvelle donn�e re�ue <br/>
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
 * @brief Donne le type de variable re�u.
 *
 * @param  Rien.
 *
 * @return Le type de variable re�u.
 */
char remoteGetDataType(void);

/**
 * @brief Donne le numero de variable re�u.
 *
 * @param  Rien.
 *
 * @return Le numero de variable re�u.<br/>
					DATA_U8 = 1 pour un caract�re non sign� char <br/>
					DATA_S8 = 2 pour un caract�re sign� char <br/>
					DATA_STRING = 3 pour une chaine de caract�re <br/>
					DATA_U16 = 4 pour un entier non sign� <br/>
					DATA_S16 = 5 pour un entier sign� <br/>
					DATA_U32 = 6 pour un entier long non sign� </br>
					DATA_S32 = 7 pour un entier long sign� <br/>
					DATA_FLOAT = 8 pour un nombre floatant <br/>
					DATA_DOUBLE = 9 pour un nombre double <br/>
 */
unsigned char remoteGetDataNumber(void);

/**
 * @brief Lecture de la valeur re�ue pour les types num�riques.
 *
 * @param  Rien.
 *
 * @return La valeur re�u dans un union (contenant tout les types num�riques).
 */
union RemoteData * remoteGetValue(void);

/**
 * @brief Lecture de la valeur re�ue pour les chaines de caract�res.
 *
 * @param  Rien.
 *
 * @return La chaine de caract�res re�u.
 */
unsigned char * remoteGetString(void);





