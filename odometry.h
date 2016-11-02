/**
 * @file odometry.h
 *
 * @version 1.0
 *
 * @brief Calcule la position , l'orientation et le déplacement du robot par rapport aux codeurs.
 *
 * @b Dépendance:
 *
 * Fichier: config.h et coder.h
 */

/**
 * @brief Initialise l'odometrie par rapport à la position et l'orientation données en paramètre.
 *
 * @param x0cm position en x du robot en cm.
 *        y0cm position en y du robot en cm.
 *        teta0radian orientation du robot en radian.
 *
 * @return Rien.
 */
void initOdometry (float x0Cm, float y0Cm, float teta0Radian);

/**
 * @brief Calul la position et le déplacement du robot.
 *
 * @detail Fonction appelée en interruption toutes les 5 ms.
 *
 * @param Aucun.
 *
 * @return Rien.
 */
void calculPosition (void);

/**
 * @brief Donne la position en cm.
 *
 * @detail La position est inscrite dans les float passés par adresse.
 *
 * @param *x pointeur sur le float qui recevera la position en x. <br/>
 * @param *y pointeur sur le float qui recevera la position en y.
 *
 * @return Rien.
 */
void getPositionCm(float *x, float *y);

/**
 * @brief Donne la position en pas codeur.
 *
 * @detail La position est inscrite dans les float passés par adresse.
 *
 * @param *x pointeur sur le float qui recevera la position en x. <br/>
 * @param *y pointeur sur le float qui recevera la position en y.
 *
 * @return Rien.
 */
void getPositionStep(double *x, double *y);

/**
 * @brief Donne la distance parcourue par le robot depuis le debut en pas codeur.
 *
 * @param Aucun.
 *
 * @return Distance parcourue en pas codeur.
 */
long getDistanceStep(void);

/**
 * @brief Donne la distance parcourue par le robot depuis le debut en cm.
 *
 * @param Aucun.
 *
 * @return Distance parcourue en cm.
 */
float getDistanceCm(void);

/**
 * @brief Donne l'orientation actuelle en pas codeur.
 *
 * @param Aucun.
 *
 * @return Orientation actuelle en pas codeur.
 */
long getOrientationStep(void);

/**
 * @brief Donne l'orientation actuelle en radian compris entre 0 et 2 PI.
 *
 * @param Aucun.
 *
 * @return Orientation actuelle en radian.
 */
float getOrientationRadian(void);

/**
 * @brief Initialise la distance de départ pour le calcul du delta en pas codeur.
 *
 * @param Aucun.
 *
 * @return Rien.
 */
void initDeltaDistance(void);

/**
 * @brief Calcul un déplacement entre la distance actuelle et le repère en pas.
 *
 * @detail Le repère est fixé à 0 dans initOdometry()
 *         et peut être réinitialisé à la distance actuelle avec initDeltaDistance(void).
 *
 * @param Aucun.
 *
 * @return Distance absolue parcourue entre le repère fixé et maintenant en pas.
 */
long getDeltaDistance(void);

/**
 * @brief Initialise l'orientation de départ pour le calcul du delta en pas codeur.
 *
 * @param Aucun.
 *
 * @return Rien.
 */
void initDeltaOrientation(void);

/**
 * @brief Calcul l'angle entre l'orientation actuelle et le repère en pas.
 *
 * @detail Le repère est fixé à 0 dans initOdometry()
 *         et peut être réinitialisé à l'orientation actuelle avec initDeltaOrientation(void).
 *
 * @param Aucun.
 *
 * @return Angle absolue parcourue entre le repère fixé et maintenant en pas.
 */
long getDeltaOrientation(void);