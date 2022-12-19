/**
 * \file jeu.h
 * \author Max Descomps (descomps@et.esiea.fr)
 * \brief Fichier contenant toutes les déclarations concernant le jeu
 * \version 0.1
 * \date 25/10/2022
 * \copyright Copyright (c) 2022
 */

#pragma once

#include "carte.h"
#include "perso.h"

#define SAVE_DIR "saves/" /**<Repertoire des sauvegardes */

/**
 * \brief Gère la mémoire pour quitter la partie
 * \authors Max Descomps
 * \param tirs La liste des tirs
 * \param mobs La liste des mobs
 * \param coffres La liste des coffres
 * \param perso Le personnage en jeu
 * \param carte La carte de jeu
 * \param plateau La fenêtre d'affichage du jeu
 * \param stats La fenêtre d'affichage des statistiques du personnage
 * \param cartePerso La fenêtre d'affichage de la minicarte du personnage
 * \param inv La fenêtre d'affichage de l'inventaire
 */
void quitterJeu(liste_t** tirs, liste_t** mobs, liste_t** coffres, perso_t** perso, carte_t** carte, WINDOW* plateau, 
WINDOW* stats, WINDOW* cartePerso, WINDOW* inv);

/**
 * \brief Détruit les éléments ponctuels d'une partie en vue de la recharger
 * \authors Max Descomps
 * \param tirs La liste des tirs
 * \param mobs La liste des mobs
 * \param coffres La liste des coffres
 */
void nettoyerJeu(liste_t* tirs, liste_t* mobs, liste_t* coffres);

/**
 * \brief Sauvegarde la partie
 * \authors Dorian Creuze
 * \authors Max Descomps
 * \param carte La carte à sauvegarder
 * \param perso Le perso sur la carte
 * \return Un code de sortie entier
 */
int sauvegarde(carte_t* carte, perso_t* perso);