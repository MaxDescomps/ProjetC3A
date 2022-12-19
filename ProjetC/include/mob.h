/**
 * \file mob.h
 * \author Max Descomps (descomps@et.esiea.fr)
 * \brief Fichier contenant toutes les déclarations concernant les mobs
 * \version 0.1
 * \date 06/10/2022
 * \copyright Copyright (c) 2022
 */

#pragma once

#include "entite.h"
#include "menu.h"

#define NB_MOB_MAX 5 /**<Nombre de mobs maximum en jeu */
#define CPT_SPAWN_MOB 1000 /**<Delai de respawn des mobs */
#define MOB_VIEW 7 /**<Distance de détection du joueur par les mobs */

extern const int MOB_CPT[NB_DIFFICULTY]; /**<Niveaux de difficulté du jeu */

/**
 * \brief Les familles de mobs
 */
typedef enum{
    MAGE, /**< Reste à distance et tire des projectils*/
    KAMIKAZE, /**< Fonce sur le personnage et explose*/
    NB_FAMILLES /**< Nombre de familles de mob*/
} famille_t;

/**
 * \brief Structure contenant les propiétées d'un mob
 * \author Max Descomps
 */
typedef struct{
    coord_t* position; /**< Position du mob sur la carte */
	direction_t direction; /**< Direction du mob */
	char cacheChar; /**< Caractère caché par celui du mob */
	char affCase; /**< Caractère d'affichage du mob */
	int pdv; /**< Résistance du mob avant d'être détruit */
	typeEntite typeEnt; /**< Type d'entité du mob */
	matiere_t couleur; /**< Couleur du mob */
	matiere_t cacheCouleur; /**< Couleur du caractère caché par le mob */
    int maxPdv; /**< Nombre de points de vie maximum du mob */
    famille_t famille; /**< Famille du mob */
    // coord_t* placeEcran; /**< Place du mob à l'écran */ enlever?
    action_t action; /**< Action du mob */
    int hostile; /**< Etat hostile du mob */
    int compteur; /**< Compteur pour appliquer un dellai au mob */
} mob_t;

/**
 * \brief Créé un mob
 * \author Max Descomps
 * \param mob Le mob à créer
 */
void creerMob(mob_t** mob);

/**
 * \brief Détruit un mob
 * \author Max Descomps
 * \param mob Le mob à détruire
 */
void detruireMob(mob_t** mob);

/**
 * \brief Fonction de callback pour désallouer l'espace attribué au mob
 * \author Max Descomps
 * \param mob Le mob à détruire
 */
void detruireMobCb(void* mob);

/**
 * \brief Fonction d'ajout de mob pour liste
 * \author Max Descomps
 * \param mob Le mob à ajouter
 * \return Un mob
 */
mob_t* ajoutMob(mob_t* mob);

/**
 * \brief Fonction de callback d'ajout de mob pour liste
 * \author Max Descomps
 * \param mob Le mob à ajouter
 * \return Un pointeur void sur le mob
 */
void* ajoutMobCb(void* mob);

/**
 * \brief Fait apparaitre un mob sur la carte aléatoirement proche du personnage
 * \author Max Descomps
 * \param carte La carte sur laquelle faire apparaitre un mob
 * \param perso Le perso autour duquel faire apparaitre un mob
 * \return Le mob apparu
 */
mob_t* spawnMobAlea(carte_t* carte, perso_t* perso);

/**
 * \brief Fait apparaitre un maximum de mobs sur la carte aléatoirement proche du personnage
 * \author Max Descomps
 * \param carte La carte sur laquelle faire apparaitre un mob
 * \param listeMobs La liste des mobs
 * \param perso Le perso autour duquel faire apparaitre un mob
 */
void spawnListeMobs(carte_t* carte, liste_t* listeMobs, perso_t* perso);

/**
 * \brief Fait bouger un mob
 * \author Max Descomps
 * \param direction La direction prise par le mob
 * \param carte La carte sur laquelle le mob se déplace
 * \param mob Le mob qui se déplace
 * \param listeTirs La liste des tirs
 */
void bougerMob(direction_t direction, carte_t* carte, mob_t* mob, liste_t* listeTirs);

/**
 * \brief Fait bouger un mob vers le personnage
 * \author Max Descomps
 * \param mob Le mob qui se déplace
 * \param perso Le personnage vers lequel le personnage se déplace
 */
void mobRush(mob_t* mob, perso_t* perso);

/**
 * \brief Evalue si un mob détecte le personnage
 * \author Max Descomps
 * \param i Le numéro de ligne du mob
 * \param j Le numéro de colonne du mob
 * \param perso Le personnage que le mob peut détecter
 * \return un booléen
 */
int mobVoitPerso(int i, int j, perso_t* perso); //refaire avec les coord du mob?

/**
 * \brief Evalue si un mob est assez loin du personnage pour être détruit
 * \author Max Descomps
 * \param i Le numéro de ligne du carre
 * \param j Le numéro de colonne du carre
 * \param perso Le perso
 * \return Un booléen
 */
int mobEstLoin(int i, int j, perso_t* perso); //refaire avec les coord du mob?