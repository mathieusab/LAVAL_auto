//=============================================================
//  remoteData.c
//
//  Visualisation de donn�es � distance pour la mise au point
//  et la validation d'un programme.
//  
//  Possibilit� de processeur big endian ou little endian
//  ==>Commenter ou d�commenter la ligne ci-dessous en fonction!
//
// V1.0
//============================================================
#define LITTLE_ENDIAN    //si X86,DSPIC,...


#include "remoteData.h" 

//Envoi d'une trame au syst�me distant
//(fonction � impl�menter dans l'application � tester)
extern void writeDebugFrame(char * p_frame, int p_length);

//Trame pour envoi
static char g_sendFrame[MAX_FRAME_LENGTH];

//Pour r�ception
static unsigned char m_receiveFrameData[MAX_FRAME_LENGTH]; //Trame re�u
static union RemoteData m_receiveValue;



//==========================================================
//Compl�te la trame (caract�res start,stop et de contr�le)
//==========================================================
void buildFrame(unsigned char p_length,unsigned char l_control,char * p_frame)
{
	//Longueur des donn�es utiles
	g_sendFrame[1]=p_length;
	l_control=l_control^p_length;
	p_length++;

	//D�but de trame
	g_sendFrame[0]=FRAME_START;
	l_control=l_control ^'U';
	p_length++;

	//Caract�re de contr�le
	g_sendFrame[p_length]=l_control;
	p_length++;

	//Fin de trame
	g_sendFrame[p_length]=FRAME_STOP;
	p_length++;

	//Envoi la trame au syst�me distant
	//(fonction sp�cifique � l'application)
	writeDebugFrame(g_sendFrame, p_length);
}


//==========================================================
//  Envoi d'une variable de type "unsigned char"  (8 bits)
//==========================================================
void remoteDataU8(unsigned char p_varNumber, unsigned char p_value)
{
	unsigned char l_control=0; //Caract�re de contr�le de la trame
	unsigned char l_length=0; //longueur totale de la trame

	g_sendFrame[2]='D'; //Frame de type "data"
	l_control=l_control^'D';
	l_length++;

	g_sendFrame[3]=p_varNumber;
	l_control=l_control ^ p_varNumber;
	l_length++;

	g_sendFrame[4]=DATA_U8; //type 8 bits, non sign�
	l_control=l_control ^ '\x01';
	l_length++;

	g_sendFrame[5]='\x01';//longueur d'un char=1
	l_control=l_control ^ '\x01';
	l_length++;

	g_sendFrame[6]=p_value;//donn�e utile
	l_control=l_control ^ p_value;
	l_length++;

	//Construit et envoie la trame
	buildFrame(l_length,l_control,g_sendFrame);
}

//==========================================================
//  Envoi d'une variable de type "signed char"  (8 bits)
//==========================================================
void remoteDataS8(unsigned char p_varNumber, char p_value)
{
	unsigned char l_control=0; //Caract�re de contr�le de la trame
	unsigned char l_length=0; //longueur totale de la trame

	g_sendFrame[2]='D'; //Frame de type "data"
	l_control=l_control ^ 'D';
	l_length++;

	g_sendFrame[3]=p_varNumber;
	l_control=l_control ^ p_varNumber;
	l_length++;

	g_sendFrame[4]=DATA_S8; //type 8 bits, sign�
	l_control=l_control ^ '\x02';
	l_length++;

	g_sendFrame[5]='\x01';//longueur d'un char=1
	l_control=l_control ^ '\x01';
	l_length++;

	g_sendFrame[6]=p_value;////donn�e utile
	l_control=l_control ^ p_value;
	l_length++;

	//Construit et envoie la trame
	buildFrame(l_length,l_control,g_sendFrame);
}

//==========================================================
//  Envoi d'une variable de type "unsigned short" (16 bits)
//==========================================================
void remoteDataU16(unsigned char p_varNumber, unsigned short p_value)
{
	union RemoteData l_convert;
	unsigned char l_control=0; //Caract�re de contr�le de la trame
	unsigned char l_length=0; //longueur totale de la trame
	int i;

	l_convert.m_valueU16=p_value;

	g_sendFrame[2]='D'; //Frame de type "data"
	l_control=l_control ^ 'D';
	l_length++;

	g_sendFrame[3]=p_varNumber;
	l_control=l_control ^ p_varNumber;
	l_length++;

	g_sendFrame[4]=DATA_U16; //type 16 bits, non sign�
	l_control=l_control ^ '\x04';
	l_length++;

	g_sendFrame[5]='\x02';//longueur d'un char=1
	l_control=l_control ^ '\x02';
	l_length++;

	//donn�es utiles
	for(i=0; i<2;i++)//attention: envoi en big endian
	{
#ifdef LITTLE_ENDIAN
		g_sendFrame[7-i]=l_convert.m_data[i];
#else  //big endian
		g_sendFrame[6+i]=l_convert.m_data[i];
#endif
		l_control=l_control ^ l_convert.m_data[i];
		l_length++;
	}

	//Construit et envoie la trame
	buildFrame(l_length,l_control,g_sendFrame);
}

//==========================================================
//  Envoi d'une variable de type "signed short" (16 bits)
//==========================================================
void remoteDataS16(unsigned char p_varNumber, short p_value)
{
	unsigned char l_control=0; //Caract�re de contr�le de la trame
	unsigned char l_length=0; //longueur totale de la trame
	int i;
	union RemoteData l_convert;

	l_convert.m_valueS16=p_value;

	g_sendFrame[2]='D'; //Frame de type "data"
	l_control=l_control ^ 'D';
	l_length++;

	g_sendFrame[3]=p_varNumber;
	l_control=l_control ^ p_varNumber;
	l_length++;

	g_sendFrame[4]=DATA_S16; //type 16 bits, sign�
	l_control=l_control ^ '\x05';
	l_length++;

	g_sendFrame[5]='\x02';//longueur 
	l_control=l_control ^ '\x02';
	l_length++;


	//donn�es utiles
	for(i=0; i<2;i++)//attention: envoi en big endian
	{
#ifdef LITTLE_ENDIAN
		g_sendFrame[7-i]=l_convert.m_data[i];
#else  //big endian
		g_sendFrame[6+i]=l_convert.m_data[i];
#endif
		l_control=l_control ^ l_convert.m_data[i];
		l_length++;
	}

	//Construit et envoie la trame
	buildFrame(l_length,l_control,g_sendFrame);
}


//==========================================================
//  Envoi d'une variable de type "unsigned long" (32 bits)
//==========================================================
void remoteDataU32(unsigned char p_varNumber, unsigned long p_value)
{
	unsigned char l_control=0; //Caract�re de contr�le de la trame
	unsigned char l_length=0; //longueur totale de la trame
	int i;
	union RemoteData l_convert;

	l_convert.m_valueU32=p_value;

	g_sendFrame[2]='D'; //Frame de type "data"
	l_control=l_control ^ 'D';
	l_length++;

	g_sendFrame[3]=p_varNumber;
	l_control=l_control ^ p_varNumber;
	l_length++;

	g_sendFrame[4]=DATA_U32; //type 32 bits, non sign�
	l_control=l_control ^ '\x06';
	l_length++;

	g_sendFrame[5]='\x04';//longueur 
	l_control=l_control ^ '\x04';
	l_length++;

	//donn�es utiles
	for(i=0; i<4;i++)//attention: envoi en big endian
	{
#ifdef LITTLE_ENDIAN		
		g_sendFrame[9-i]=l_convert.m_data[i];
#else  //big endian
		g_sendFrame[6+i]=l_convert.m_data[i];
#endif
		l_control=l_control^l_convert.m_data[i];
		l_length++;
	}

	//Construit et envoie la trame
	buildFrame(l_length,l_control,g_sendFrame);
}

//==========================================================
//  Envoi d'une variable de type "signed long" (32 bits)
//==========================================================
void remoteDataS32(unsigned char p_varNumber, long p_value)
{
	unsigned char l_control=0; //Caract�re de contr�le de la trame
	unsigned char l_length=0; //longueur totale de la trame
	int i;
	union RemoteData l_convert;

	l_convert.m_valueS32=p_value;

	g_sendFrame[2]='D'; //Frame de type "data"
	l_control=l_control^'D';
	l_length++;

	g_sendFrame[3]=p_varNumber;
	l_control=l_control ^ p_varNumber;
	l_length++;

	g_sendFrame[4]=DATA_S32; //type 32 bits sign�
	l_control=l_control ^ '\x07';
	l_length++;

	g_sendFrame[5]='\x04';//longueur 
	l_control=l_control ^ '\x04';
	l_length++;

	//donn�es utiles
	for(i=0; i<4;i++)//attention: envoi en big endian
	{
#ifdef LITTLE_ENDIAN		
		g_sendFrame[9-i]=l_convert.m_data[i];
#else  //big endian
		g_sendFrame[6+i]=l_convert.m_data[i];
#endif
		l_control=l_control^l_convert.m_data[i];
		l_length++;
	}

	//Construit et envoie la trame
	buildFrame(l_length,l_control,g_sendFrame);
}

//==========================================================
//  Envoi d'une variable de type "signed float"
//==========================================================
void remoteDataFloat(unsigned char p_varNumber, float p_value)
{
	unsigned char l_control=0; //Caract�re de contr�le de la trame
	unsigned char l_length=0; //longueur totale de la trame
	int i;

	union RemoteData l_convert;
	l_convert.m_valueFloat=p_value;

	g_sendFrame[2]='D'; //Frame de type "data"
	l_control=l_control ^ 'D';
	l_length++;

	g_sendFrame[3]=p_varNumber;
	l_control=l_control ^ p_varNumber;
	l_length++;

	g_sendFrame[4]=DATA_FLOAT; //type float
	l_control=l_control ^ '\x08';
	l_length++;

	g_sendFrame[5]='\x04';//longueur 
	l_control=l_control ^ '\x04';
	l_length++;

	//donn�es utiles
	for(i=0; i<4;i++)//attention: envoi en big endian
	{
#ifdef LITTLE_ENDIAN		
		g_sendFrame[9-i]=l_convert.m_data[i];
#else  //big endian
		g_sendFrame[6+i]=l_convert.m_data[i];
#endif
		l_control=l_control^l_convert.m_data[i];
		l_length++;
	}

	//Construit et envoie la trame
	buildFrame(l_length,l_control,g_sendFrame);

}

//==========================================================
//  Envoi d'une variable de type "signed double"
//==========================================================
void remoteDataDouble(unsigned char p_varNumber, double p_value)
{
	unsigned char l_control=0; //Caract�re de contr�le de la trame
	unsigned char l_length=0; //longueur totale de la trame
	int i;

	union RemoteData l_convert;
	l_convert.m_valueDouble=p_value;

	g_sendFrame[2]='D'; //Frame de type "data"
	l_control=l_control ^ 'D';
	l_length++;

	g_sendFrame[3]=p_varNumber;
	l_control=l_control ^ p_varNumber;
	l_length++;

	g_sendFrame[4]=DATA_DOUBLE; //type double
	l_control=l_control ^ '\x09';
	l_length++;

	g_sendFrame[5]='\x08';//longueur 
	l_control=l_control ^ '\x08';
	l_length++;

	//donn�es utiles
	for(i=0; i<8;i++)//attention: envoi en big endian
	{
#ifdef LITTLE_ENDIAN
		g_sendFrame[13-i]=l_convert.m_data[i];
#else  //big endian
		g_sendFrame[6+i]=l_convert.m_data[i];
#endif
		l_control=l_control ^ l_convert.m_data[i];
		l_length++;
	}

	//Construit et envoie la trame
	buildFrame(l_length,l_control,g_sendFrame);
}

//==========================================================
//  Envoi d'une variable de type "chaine de carat�res"
//    !!! chaine termin�e obligatoirement par un '\0'
//==========================================================
void remoteDataString(int p_varNumber, char *p_value)
{
	unsigned char l_control=0; //Caract�re de contr�le de la trame
	unsigned char l_length=0; //longueur totale de la chaine ou de la trame

	//donn�es utiles
	while(l_length< (MAX_FRAME_LENGTH-10))
	{
		g_sendFrame[6+l_length]=*p_value; //copie un caract�re
		l_control=l_control ^ *p_value; 
		l_length++;  //incr�mente la longueur de la chaine de donn�e 
		if (*p_value=='\0') break; //Fin de la chaine � transmettre
		p_value++;
	}

	g_sendFrame[5]=l_length;//longueur de la chaine de caract�res
	l_control=l_control ^ l_length;
	l_length++;

	g_sendFrame[2]='D'; //Frame de type "data"
	l_control=l_control ^ 'D';
	l_length++;

	g_sendFrame[3]=p_varNumber;
	l_control=l_control^ p_varNumber;
	l_length++;

	g_sendFrame[4]=DATA_STRING; //type chaine de caract�res
	l_control=l_control ^ '\x03';
	l_length++;

	//Construit et envoie la trame
	buildFrame(l_length,l_control,g_sendFrame);
}


//==========================================================
//Traitement d'un caract�re re�u
// Retourne:
//   0 si OK
//   <0 en cas d'erreur 
//        -1 ==> erreur de caract�re de contr�le
//        -2 ==> pas de caract�re de fin de trame
//   1 si nouvelle donn�e re�ue
//==========================================================
int remoteOnReceive(char p_receiveCar)
{
	static int m_receiveState=0; //Etat de la machine de r�ception
	static int l_control=0;//calcul du caract�re de contr�le
	static int m_dataLength=0; //Longueur de la frame data � recevoir
	static int m_receiveLength=0; //Nombre de caract�res re�us dans m_receiveFrameData
	int l_ret=0;//Code de retour de la fonction

	switch( m_receiveState)
	{
	case 0: 
		if(p_receiveCar==FRAME_START)
		{
			l_control=FRAME_START;
			m_receiveState=1;
		}
		break;
	case 1: 
		//Longueur de la frame data 
		m_dataLength=p_receiveCar;	
		l_control=l_control^m_dataLength;
		m_receiveLength=0; //init longueur data re�u
		m_receiveState=2;
		break;
	case 2: 
		//Reception de la data
			m_receiveFrameData[m_receiveLength]=p_receiveCar;
			l_control=l_control^p_receiveCar;
			m_receiveLength++;

			if(m_receiveLength>=m_dataLength)
			{
				//Fin de la data
				m_receiveState=3;
			}

		break;
	case 3: 
		//V�rification du caract�re de contr�le
		if(p_receiveCar==l_control)
		{
			// Pas d'erreur
			m_receiveState=4;
		}
		else
		{
			//Erreur de contr�le
			m_receiveState=0; //R�initialise la r�ception
			l_ret=-1; //Trame erron�e (pb de caract�re de contr�le)
		}
		break;
	case 4: 
		//Caract�re de fin de trame
		if(p_receiveCar==FRAME_STOP)
		{
			l_ret=1; //Trame compl�te re�u (nouvelle donn�e)
			m_receiveState=0; //R�initialise la r�ception
		}
		else
		{
			//Erreur de r�ception 
			m_receiveState=0; //R�initialise la r�ception
			l_ret=-2; //Pas de caract�re de fin de trame
		}
		break;
	}
        
	return l_ret;
}


//==========================================================
// Lecture du type de frame 'ex: 'D' => data frame
//==========================================================
char remoteGetFrameType(void)
{
	return m_receiveFrameData[0]; 
}


//==========================================================
// Lecture du num�ro de variable re�u pour une "data frame"
//==========================================================
unsigned char remoteGetDataNumber(void)
{
	return m_receiveFrameData[1]; 
}


//==========================================================
// Lecture du type de donn�e re�u (voir enum DataType)
//==========================================================
char remoteGetDataType(void)
{
	return m_receiveFrameData[2]; 
}


//==========================================================
// Lecture de la valeur re�ue pour les types num�riques
//==========================================================
union RemoteData * remoteGetValue(void)
{
	int l_length;
	unsigned char* l_src;
	unsigned char* l_dst;
	int i;

	switch(m_receiveFrameData[2]) //suivant le type de donn�e
	{
		//Donn�e de 8 bits
	case DATA_U8:
	case DATA_S8:
		l_length=1;
		break;
		
		//Donn�e de 16 bits
	case DATA_U16: 
	case DATA_S16:
		l_length=2;
		break;
		
		//Donn�e de 32 bits
	case DATA_U32:
	case DATA_S32:
	case DATA_FLOAT:
		l_length=4;
		break;
		
		//Donn�e de 64  bits
	case DATA_DOUBLE:
		l_length=8;
		break;
	}

	//copie des donn�es utiles
	l_dst=&m_receiveValue.m_data[0];
#ifdef LITTLE_ENDIAN
	l_src=&m_receiveFrameData[3]+l_length;
#else
	l_src=&m_receiveFrameData[4];
#endif
	for(i=0; i<l_length;i++)//attention: reception en "big endian"
	{
		*l_dst=*l_src;
		l_dst++;
#ifdef LITTLE_ENDIAN
		l_src--;
#else  //big endian
		l_src++;
#endif
	}
	return &m_receiveValue; 
}

//==========================================================
// Lecture de la valeur re�ue pour les chaines de caract�res
//==========================================================
unsigned char * remoteGetString(void)
{
	return &m_receiveFrameData[4];
}