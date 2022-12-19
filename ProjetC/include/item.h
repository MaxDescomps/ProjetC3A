/**
 * \file item.h
 * \author Max Descomps (descomps@et.esiea.fr)
 * \brief Fichier contenant toutes les déclarations concernant les items
 * \version 0.1
 * \date 22/10/2022
 * \copyright Copyright (c) 2022
 */

#pragma once

#include <ncurses.h>
#include "matiere.h"

/**
 * \brief Le type d'item
 */
typedef enum itemType_s{
    NOTYPE, /**< Type d'item null */
    BLOC, /**< Type d'item bloc */
    ARME, /**< Type d'item arme */
    CONSO, /**< Type d'item consommable */
}itemType_t;

/**
 * \brief Structure contenant les propiétées d'un item
 * \author Max Descomps
 */
typedef struct item_s{
    char affCase; /**< Caractère représentant le carré à afficher en jeu */
    matiere_t couleur; /**< Couleur du caractère affiché */
    int acces; /**< Définit si le perso peut marcher sur le carre */
}item_t;

/**
 * \brief Structure contenant les propiétées d'un consommable
 * \author Max Descomps
 */
typedef struct conso_s{
    char affCase; /**<Caractère d'affichage du consommable */
    matiere_t couleur; /**<Couleur d'affichage du consommable */
    int acces; /**<Collision du bloc contenant le consommable */
    int soin; /**<Soin engendré par l'utilisation du consommable */
}conso_t;

/**
 * \brief Structure contenant les propiétées d'une arme
 * \author Max Descomps
 */
typedef struct arme_s{
    char affCase; /**<Caractère d'affichage de l'arme */
    matiere_t couleur; /**<Couleur d'affichage de l'arme */
    int acces; /**<Collision du bloc contenant l'arme */
    int att; /**<Modification d'attaque engendrée par l'arme */
}arme_t;

/**
 * \brief Créé un item générique pour tests
 * \author Max Descomps
 * \return Instance nouvellement allouée d'un item
 */
item_t* creerItem(void);

/**
 * \brief Détruit un item
 * \author Max Descomps
 * \param item L'item à détruire
 */
void detruireItem(item_t** item);

/**
 * \brief Fonction de callback pour détruire un item
 * \author Max Descomps
 * \param item L'item à détruire
 */
void detruireItemCb(void* item);

/**
 * \brief Ajout d'item pour liste doublement chaînée
 * \author Max Descomps
 * \param item L'item à ajouter
 * \return L'item ajouté
 */
item_t* ajoutItem(item_t* item);

/**
 * \brief Fonction de callback d'ajout d'item pour liste doublement chaînée
 * \author Max Descomps
 * \param item L'item à ajouter
 * \return L'item ajouté
 */
void* ajoutItemCb(void* item);

/**
 * \brief Créé un consommable
 * \author Max Descomps
 * \return Instance nouvellement allouée d'un consommable
 */
conso_t* creerConso(void);

/**
 * \brief Affiche un item
 * \author Max Descomps
 * \param w La fenêtre d'affichage
 * \param item L'item à afficher
 */
void afficherItem(WINDOW* w, item_t* item);