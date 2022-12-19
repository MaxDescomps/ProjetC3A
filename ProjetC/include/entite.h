/**
 * \file entite.h
 * \author Max Descomps (descomps@et.esiea.fr)
 * \brief Fichier contenant toutes les déclarations communes aux entités
 * \version 0.1
 * \date 6/10/2022
 * \copyright Copyright (c) 2022
 */

#pragma once

#include "coord.h"
#include "liste.h"
#include "matiere.h"

typedef struct Scarre carre_t;  /**< Cette déclaration est là pour éviter un conflit d'inclusion mutuelle des fichiers entite.h et carte.h */

/**
 * \brief Le type d'entité
 */
typedef enum{
	ENT_MOB, /**< type d'entité des mobs */
	ENT_PERSO, /**< type d'entité des persos */
	ENT_TIR, /**< type d'entité des tirs */
	ENT_COFFRE, /**< type d'entité des coffres */
}typeEntite;

/**
 * \brief Le type d'action
 */
typedef enum {
	RIEN, /**< Aucune action */
	ATTAQUE /**< Action d'attaque */
} action_t; /**< Action du personnage en cours*/

/**
 * \brief Structure contenant les propiétées d'une entité
 * \author Max Descomps
 */
typedef struct{
	coord_t* position; /**< Position de l'entité sur la carte */
	direction_t direction; /**< Direction de l'entité */
	char cacheChar; /**< Caractère caché par celui de l'entité */
	char affCase; /**< Caractère d'affichage de l'entité */
	int pdv; /**< Résistance de l'entité avant d'être détruite */
	typeEntite typeEnt; /**< Type de l'entité */
	matiere_t couleur; /**< Couleur de l'entité */
	matiere_t cacheCouleur; /**< Couleur du caractère caché par l'entité */
} entite_t;

/**
 * \brief Déplace une entité
 * \author Max Descomps
 * \param direction La direction du déplacement
 * \param carte La carte ou l'entité se déplace
 * \param entite L'entité qui se déplace
 * \param listeTirs La liste des tirs
 * \return 1 si l'entité à pu se déplacer, 0 sinon
 */
int bougerEntite(direction_t direction, carte_t* carte, entite_t* entite, liste_t* listeTirs);

/**
 * \brief Gère une entité vivante qui fonce sur un tire
 * \author Max Descomps
 * \param entite L'entité qui fonce sur le tir
 * \param carte La carte ou se produit la collision
 * \param listeTirs La liste des tirs
 * \param carreTir Le carré ou se trouve le tir
 */
void fonceSurTir(entite_t* entite, carte_t* carte, liste_t* listeTirs, carre_t* carreTir);