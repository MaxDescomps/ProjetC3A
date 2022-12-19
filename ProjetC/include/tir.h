/**
 * \file tir.h
 * \author Max Descomps (descomps@et.esiea.fr)
 * \brief Fichier contenant toutes les déclarations concernant le tir
 * \version 0.1
 * \date 09/10/2022
 * \copyright Copyright (c) 2022
 */

#pragma once

#include "carte.h"

#define TIR_PORTEE_BASE 4 /**<Portée de base des tirs */
#define TIR_TICK 800 /**<Delai de progression des tirs (traveltime) */
#define TIR_RATE (2 * TIR_TICK) /**<Cadence de tir de base */

/**
 * \brief Structure contenant les informations sur un tir
 * \author Descomps Max
 */
typedef struct{
	coord_t* position; /**< Position du tir sur la carte */
	direction_t direction; /**< Direction du tir */
	char cacheChar; /**< Caractère caché par celui du tir */
	char affCase; /**< Caractère d'affichage du tir */
	int portee; /**< Portée du tir */
	typeEntite typeEnt; /**< Type d'entité du tir */
	matiere_t couleur; /**< Couleur du tir */
	matiere_t cacheCouleur; /**< Couleur du caractère caché par le tir */
	int compteur; /**< Compteur servant de delai de progression du tir */
}tir_t;

/**
 * \brief Créé un tir
 * \authors Max Descomps
 * \param entite L'entité qui tire
 * \param carte La carte ou l'entité tire
 * \return Le tir créé
 */
tir_t* creerTir(entite_t* entite, carte_t* carte);

/**
 * \brief Désalloue l'espace attribué au tir
 * \author Max Descomps
 * \param tir Le tir à détruire
 */
void detruireTir(tir_t** tir);

/**
 * \brief Fonction de callback pour désallouer l'espace attribué au tir
 * \author Max Descomps
 * \param tir L'adresse du pointeur sur le tir à détruire
 */
void detruireTirCb(void* tir);

/**
 * \brief Fonction d'ajout de tir pour liste
 * \author Max Descomps
 * \param tir Le tir à ajouter
 * \return Un tir
 */
tir_t* ajoutTir(tir_t* tir);

/**
 * \brief Fonction de callback d'ajout de tir pour liste
 * \author Max Descomps
 * \param tir Le tir à ajouter
 * \return Un pointeur void sur le tir
 */
void* ajoutTirCb(void* tir);

/**
 * \brief Génère le tir d'une entité
 * \author Max Descomps
 * \param carte La carte depuis laquelle on tire
 * \param listeTirs La liste des tirs
 * \param entite L'entité qui tire
 */
void tirer(carte_t* carte, liste_t* listeTirs, entite_t* entite);

/**
 * \brief Gère une entité vivante qui fonce sur un tir
 * \author Max Descomps
 * \param entite L'éntité qui fonce sur le tir
 * \param carte La carte ou se produit la collision
 * \param listeTirs La liste des tirs
 * \param carreTir Le carre ou se trouve le tir
 */
void collisionVivantTir(entite_t* entite, carte_t* carte, liste_t* listeTirs, carre_t* carreTir);

/**
 * \brief Gère un tir qui fonce sur une entité
 * \author Max Descomps
 * \param carte La carte contenant le tir
 * \param coordColli Les coordonnées de la collision
 * \param tir Le tir en collision
 * \return un booléen indiquant si le tir à heurté une entité
 */
int collisionTirEntite(carte_t* carte, coord_t* coordColli, tir_t* tir);