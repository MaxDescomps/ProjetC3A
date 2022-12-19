/**
 * \file coffre.h
 * \author Max Descomps (descomps@et.esiea.fr)
 * \brief Fichier contenant toutes les déclarations communes aux coffres
 * \version 0.1
 * \date 22/10/2022
 * \copyright Copyright (c) 2022
 */

#pragma once

#include <ncurses.h>
#include "entite.h"

#define MAX_ITEMS_COFFRE 3 /**<Nombre maximum d'items contenus dans un coffre */
#define MAX_LOOT_COFFRE 2 /**<Nombre maximum de loot de base contenu dans un coffre */

/**
 * \brief Structure contenant les propiétées d'un coffre
 * \author Max Descomps
 */
typedef struct{
    coord_t* position; /**< Position du coffre sur la carte */
	direction_t direction; /**< Direction du coffre */
	char cacheChar; /**< Caractère caché par celui du coffre */
	char affCase; /**< Caractère d'affichage du coffre */
	int pdv; /**< Résistance du coffre avant de casser */
	typeEntite typeEnt; /**< Type d'entité liée au coffre */
	matiere_t couleur; /**< Couleur du coffre */
	matiere_t cacheCouleur; /**< Couleur du caractère caché par le coffre */
    liste_t* items; /**< Liste des items du coffre */
	int numCase; /**< Numéro de l'item actif du coffre */
} coffre_t;

/**
 * \brief Créé un coffre
 * \author Max Descomps
 * \param listeCoffres La liste des coffres
 * \return Instance nouvellement allouée de coffre
 */
coffre_t* creerCoffre(liste_t* listeCoffres);

/**
 * \brief Détruit un coffre
 * \author Max Descomps
 * \param coffre Le coffre à détruire
 */
void detruireCoffre(coffre_t** coffre);

/**
 * \brief Fonction de callback pour détruire un coffre
 * \author Max Descomps
 * \param coffre Le coffre à détruire
 */
void detruireCoffreCb(void* coffre);

/**
 * \brief Ajout de coffre pour liste doublement chaînée
 * \author Max Descomps
 * \param coffre Le coffre à ajouter
 * \return Le coffre ajouté
 */
coffre_t* ajoutCoffre(coffre_t* coffre);

/**
 * \brief Fonction de callback pour ajout de coffre pour liste doublement chaînée
 * \author Max Descomps
 * \param coffre Le coffre à ajouter
 * \return Le coffre ajouté
 */
void* ajoutCoffreCb(void* coffre);

/**
 * \brief Affiche le contenu d'un coffre
 * \author Max Descomps
 * \param w La fenêtre d'affichage
 * \param coffre Le coffre à afficher
 */
void wprintCoffre(WINDOW* w, coffre_t* coffre);