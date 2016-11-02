
/**
 * @file servoOut.h 
 *
 * @author  @b ESIEA
 *
 * @version 3.0
 *
 * @brief Gestion de servomoteurs de modelisme
 *
 * @b D�pendance: config.h
 *   
*/


 /**
 *@brief initServoOut : initialise les servomoteurs
 *
 *@param none
 *
 *@return none
 */ 

void initServoOut( void );	

 /**
 *@brief startServoOut : entame la proc�dure d'interruption T4
 *
 *@param none
 *
 *@return none
 */ 

void startServoOut( void );


 /**
 *@brief setServoOut : fixe une valeur a un servo
 *
 *p_num Servo valeur du servomoteur de 0 � N
 *p_value  angle allant de -90� a 90�
 * (unit� en 1/10 degr� donc de -900 � +900)
 *
 *@return none
 */ 

void setServoOutX(int p_numServo, int p_value);


 /**
 *@brief stopServoOut : mode stop d'un servomoteur
 *
 *@return none
 */ 

void stopServoOut(void);
