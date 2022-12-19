/**
 * \file coord.h
 * \author Max Descomps (descomps@et.esiea.fr)
 * \brief Fichier contenant les déclarations sur les coordonnées servant à résoudre un conflit d'inclusion mutuelle contenant un type énuméré non déclarable sous forme de prototype
 * \version 0.1
 * \date 02/10/2022
 * \copyright Copyright (c) 2022
 */

#pragma once

typedef struct perso_s perso_t; /**< Cette déclaration est là pour éviter un conflit d'inclusion mutuelle des fichiers coord.h et perso.h */
typedef struct Scarte carte_t; /**< Cette déclaration est là pour éviter un conflit d'inclusion mutuelle des fichiers coord.h et carte.h */

/**
 * \brief Direction
 */
typedef enum {
	HAUT, /**< Direction haut */
	DROITE, /**< Direction droite */
	BAS, /**< Direction bas */
	GAUCHE, /**< Direction gauche */
	NB_DIR, /**< Nombre de directions */
} direction_t; /**< Directions en jeu */

/**
 * \brief Structure de coordonnees d'un carre de la carte
 * \author Dorian Creuze
 */
typedef struct
{
	int row; /**< numéro de ligne */
	int col; /**< numéro de colonne */
}coord_t;

/**
 * \brief Créé des coordonnées
 * \author Max Descomps
 */
coord_t* creerCoord(void);

/**
 * \brief Désalloue l'espace attribué aux coordonnées
 * \author Max Descomps
 * \param coord Les coordonnées à détruire
 */
void detruireCoord(coord_t** coord);

/**
 * \brief Evalue si un carré est dans le champ de vision du perso
 * \author Max Descomps
 * \param i Le numéro de ligne du carre
 * \param j Le numéro de colonne du carre
 * \param perso Le perso
 * \return Un booléen
 */
int coordProche(int i, int j, perso_t* perso);

/**
 * \brief Donne des coordonnées aléatoires sur une carte
 * \author Max Descomps
 * \param carte La carte dont on veut des coordonnées aléatoires
 * \return Des coordonnées aléatoires sur la carte
 */
coord_t coordAlea(carte_t* carte);

/**
 * \brief Donne des coordonnées aléatoires d'un carré accessible sur une carte
 * \author Max Descomps
 * \param carte La carte dont on veut des coordonnées aléatoires
 * \return Des coordonnées aléatoires
 */
coord_t coordAleaAcces(carte_t* carte);

/**
 * \brief Vérifie si un carré existe
 * \author Max Descomps
 * \param coord Les coordonnées étudiés sur la carte
 * \param carte La carte étudiée
 * \return un booléen
 */
int coordExiste(coord_t* coord, carte_t* carte);

/**
 * \brief Vérifie si un carré est accessible
 * \author Max Descomps
 * \param carte La carte étudiée
 * \param coord Les coordonnées étudiés sur la carte
 * \return un booléen
 */
int coordAccessible(coord_t* coord, carte_t* carte);

/**
 * \brief Actualise une position selon un direction prise
 * \author Max Descomps
 * \param direction La direction prise
 * \param position Les coordonnées modifiées
 */
void actualiserCoord(direction_t direction, coord_t* position);

/**
 * \brief Renvoie les prochaines coordonnées que prendra un point
 * \author Max Descomps
 * \param direction La direction prise
 * \param position Les coordonnées du point
 * \return Instance nouvellement allouée des prochaines coordonnées du point
 */
coord_t* nextCoord(direction_t direction, coord_t* position);