/**
 * \file inventaire.h
 * \author Max Descomps (descomps@et.esiea.fr)
 * \author Dorian Creuze (creuze@et.esiea.fr)
 * \brief Fichier contenant toutes les déclarations concernant l'inventaire
 * \version 2.0
 * \date 20/10/2022
 * \copyright Copyright (c) 2022
 */

#pragma once

#include "item.h"

typedef struct Scarre carre_t;  /**< Cette déclaration est là pour éviter un conflit d'inclusion mutuelle des fichiers inventaire.h et carte.h */
typedef struct perso_s perso_t;  /**< Cette déclaration est là pour éviter un conflit d'inclusion mutuelle des fichiers inventaire.h et perso.h */

/**
 * \brief Structure contenant les propiétées d'une case d'inventaire
 * \author Max Descomps
 */
typedef struct{
    itemType_t type; /**<Type d'item contenu par la case d'inventaire */
    int nb; /**<Nombre d'items contenu par la case d'inventaire */
    item_t* item; /**<Item contenu par la case d'inventaire */
}invCase_t;

/**
 * \brief Structure contenant les propiétées d'un inventaire
 * \author Max Descomps
 */
typedef struct{
    invCase_t** invCase; /**<Cases d'inventaire*/
    int nbItem; /**<Nombre de cases d'inventaires occupées*/
    int numCase; /**<Case active de l'inventaire*/
}inventaire_t;

/**
 * \brief Créé une case d'inventaire
 * \author Max Descomps
 * \return Instance nouvellement allouée d'une case d'inventaire
 */
invCase_t* creerInvCase(void);

/**
 * \brief Détruit une case d'inventaire
 * \author Max Descomps
 * \param invCase La case d'inventaire à détruire
 */
void detruireInvCase(invCase_t** invCase);

/**
 * \brief Créé un inventaire
 * \author Max Descomps
 * \return Instance nouvellement allouée d'un inventaire
 */
inventaire_t* creerInv(void);

/**
 * \brief Détruit un inventaire
 * \author Max Descomps
 * \param inventaire L'inventaire à détruire
 */
void detruireInv(inventaire_t** inventaire);

/**
 * \brief Ramasse un item et le met dans l'inventaire
 * \author Max Descomps
 * \param fenCoffre La fenêtre d'affichage des coffres
 * \param fenInv La fenêtre d'affichage de l'inventaire
 * \param carre Le carré sur lequel on ramasse
 * \param perso Le personnage qui ramasse
 * \return Un booléen: 1 si on a récupéré un bloc, sinon 0
 */
int ramasser(WINDOW* fenCoffre, WINDOW* fenInv, item_t* carre, perso_t* perso);

/**
 * \brief Affiche un inventaire
 * \author Max Descomps
 * \param w La fenêtre d'affichage de l'inventaire
 * \param inventaire L'inventaire à afficher
 */
void wprintInv(WINDOW* w, inventaire_t* inventaire);

/**
 * \brief Utilise un item de l'inventaire
 * \author Max Descomps
 * \param perso Le personnage qui utilise un item
 * \param carre Le carré ou utiliser un item
 * \return Un booléen: 1 si on a posé un bloc, sinon 0
 */
int utiliserItem(perso_t* perso, carre_t* carre);