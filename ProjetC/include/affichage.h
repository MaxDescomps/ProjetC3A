/**
 * \file affichage.h
 * \author Max Descomps (descomps@et.esiea.fr)
 * \brief Fichier contenant les déclarations des fonctions d'affichage
 * \version 0.1
 * \date 4/10/2022
 * \copyright Copyright (c) 2022
 */

#pragma once

#include "perso.h"

#define COLOR_TURQUOISE 8 /**<Couleur custom turquoise */
#define COLOR_MARRON 9 /**<Couleur custom marron */
#define COLOR_JAUNE 10 /**<Couleur custom jaune */
#define COLOR_VERT 11 /**<Couleur custom vert */
#define COLOR_ROSE 12 /**<Couleur custom rose */

#define STATS_SIZE 4 /**<Hauteur de la fenêtre des stats sans padding*/
#define INV_SIZE 1 /**<Hauteur de la fenêtre de l'inventaire sans padding*/

/**
 * \brief Initialise les couleurs pour l'affichage
 * \authors Max Descomps
 */
void initColor(void);

/**
 * \brief Affiche le jeu sur la sortie ncurses
 * \authors Dorian Creuze
 * \authors Max Descomps
 * \param w fenêtre d'affichage
 * \param carte La carte à afficher
 * \param perso Le personnage sur la carte
 */
void wprintwCarte(WINDOW* w, carte_t* carte, perso_t* perso);

/**
 * \brief Affiche les statistiques personnage sur la sortie ncurses
 * \authors Max Descomps
 * \param w fenêtre d'affichage
 * \param perso Le personnage étudié
 * \param colMax La largeur de la fenêtre
 */
void wprintStats(WINDOW* w, perso_t* perso, int colMax);