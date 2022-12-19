/**
 * \file menu.h
 * \author Max Descomps (descomps@et.esiea.fr)
 * \brief Fichier contenant toutes les déclarations concernant les menus
 * \version 0.1
 * \date 30/09/2022
 * \copyright Copyright (c) 2022
 */

#pragma once

#include <ncurses.h>

extern int difficulty; /**<Niveau de difficulté du jeu */

/**
 * \brief Les difficultés
 */
typedef enum{
    FACILE, /**< Difficulté facile */
    NORMAL, /**< Difficulté normale */
    DIFFICILE, /**< Difficulté difficile */
    NB_DIFFICULTY /**< Nombre de difficultés */
} difficulty_t;

/**
 * \brief Choix de la carte à l'ouverture du jeu
 * \author Max Descomps
 * \return Taille strictement positive de la carte à créer ou zéro si carte à charger en sauvegarde
 */
int choixCarte(void);

/**
 * \brief Choix de la difficulté du jeu
 * \author Max Descomps
 */
void choixDifficulte(void);

/**
 * \brief Menu pause du jeu
 * \author Max Descomps
 * \param w Fenêtre de jeu ou s'affiche le menu pause
 * \param carte Carte de jeu
 * \param perso Le personnage en jeu
 * \param running Booléen indiquant si le jeu est en cours
 */
void menuPause(WINDOW* w, carte_t* carte, perso_t* perso, int* running);

/**
 * \brief Menu de mort du personnage
 * \author Max Descomps
 * \param tirs La liste des tirs
 * \param mobs La liste des mobs
 * \param coffres La liste des coffres
 * \param w Fenêtre de jeu ou s'affiche le menu de mort
 * \param carte Carte de jeu
 * \param perso Le personnage en jeu
 * \param running Booléen indiquant si le jeu est en cours
 */
void menuMort(liste_t* tirs, liste_t* mobs, liste_t* coffres, WINDOW* w, carte_t* carte, perso_t* perso, int* running);