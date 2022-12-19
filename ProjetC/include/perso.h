/**
 * \file perso.h
 * \author Max Descomps (descomps@et.esiea.fr)
 * \author Dorian Creuze (creuze@et.esiea.fr)
 * \brief Fichier contenant toutes les déclarations concernant le personnage
 * \version 0.1
 * \date 29/09/2022
 * \copyright Copyright (c) 2022
 */

#pragma once

#include "inventaire.h"
#include "carte.h"

#define PERSO_TICK 500 /**<Delai de mouvement du personnage */
#define XP_LIMIT 10 /**<Experience pour monter de niveau */
#define MAX_ITEM_PERSO 10 /**<Taille de l'inventaire du personnage */
#define MAX_TAILLE_NOM 100 /**<Taille maximum du nom du personnage */

typedef struct Scarte carte_t;  /**< Cette déclaration est là pour éviter un conflit d'inclusion mutuelle des fichiers perso.h et carte.h */

/**
 * \brief Structure contenant les informations sur le personnage
 * 
 * \author Descomps Max
 * \author Creuze Dorian
 */
typedef struct perso_s
{
	coord_t* position; /**< Coordonnées du personnage sur la carte*/
	direction_t direction; /**< Direction du personnage*/
	char cacheChar; /**< Caractère de la carte caché par le personnage*/
	char affCase; /**< Caractère d'affichage du personnage */
	int pdv; /**< Les points de vie actuels du personnage */
	typeEntite typeEnt; /**< Type d'entité du personnage */
	matiere_t couleur; /**< Couleur du personnage */
	matiere_t cacheCouleur; /**< Couleur du caractère caché par le personnage */
	int maxPdv; /**< Le nombre de Pv maximum du personnage */
	int attaque; /**< L'attaque du personnage */
	int defense; /**< La défense du personnage */
	char* nom; /**< Le nom du personnage */
	action_t action; /**< Action du personnage*/
	coord_t* placeEcran; /**< Coordonnées du personnage sur l'écran*/
	inventaire_t* inventaire; /**< Inventaire du personnage*/
	int niveau; /**< Niveau du personnage*/
	int xp; /**< Expérience du personnage*/
	int porteeBase; /**< Portée de base du personnage*/
}perso_t;

/**
 * \brief Déplace le personnage sur la carte
 * \authors Max Descomps
 * \authors Dorian Creuze
 * \param direction La direction prise par le personnage
 * \param carte La carte sur laquelle se déplace le personnage
 * \param perso Le personnage qui se déplace
 * \param listeTirs La liste des tirs
 */
void bougerPerso(direction_t direction, carte_t* carte, perso_t* perso, liste_t* listeTirs);

/**
 * \brief Vérifie l'expérience et augmente le niveau du personnage si nécessaire
 * \authors Dorian Creuze
 * \authors Max Descomps
 * \param perso Le personnage dont on vérifie l'expérience
 */
void gestionXP(perso_t* perso);

/**
 * \brief Enlève un carré de la carte
 * \authors Dorian Creuze
 * \authors Max Descomps
 * \param carre Le carré à enlever
 */
void enlever(carre_t* carre);

/**
 * \brief Utilise un item de l'inventaire du personnage
 * \authors Dorian Creuze
 * \authors Max Descomps
 * \param carte La carte sur laquelle on utilise un item
 * \param perso Le personnage qui utilise un item
 */
void actionUtiliser(carte_t* carte, perso_t* perso);

/**
 * \brief Le personnage tente de ramasser
 * \authors Dorian Creuze
 * \authors Max Descomps
 * \param fenCoffre La fenêtre d'affichage des coffres
 * \param fenInv La fenêtre d'affichage de l'inventaire
 * \param carte La carte sur laquelle le personnage ramasse
 * \param perso Le personnage qui ramasse
 */
void actionRamasser(WINDOW* fenCoffre, WINDOW* fenInv, carte_t* carte, perso_t* perso);

/**
 * \brief Créé un personnage
 * \authors Max Descomps
 * \authors Dorian Creuze
 * \param perso Le personnage à créer
 */
void creerPerso(perso_t** perso);

/**
 * \brief Désalloue l'espace attribué au personnage
 * \author Max Descomps
 * \param perso Le personnage à détruire
 */
void detruirePerso(perso_t** perso);

/**
 * \brief Vérifie si le prochain carré dans une direction est accessible
 * \author Max Descomps
 * \param direction La direction choisie
 * \param carte La carte étudiée
 * \param position La position de référence
 * \return Un booléen
 */
int directionPossible(direction_t direction, carte_t* carte, coord_t* position);

/**
 * \brief Vérifie si le prochain carré dans une direction existe
 * \author Max Descomps
 * \param direction La direction choisie
 * \param carte La carte étudiée
 * \param position La position d'origine
 * \return Un booléen
 */
int directionExiste(direction_t direction, carte_t* carte, coord_t* position);

/**
 * \brief Génère le personnage dans le jeu pour la première fois (placement et demande du nom)
 * \author Max Descomps
 * \param carte La carte sur laquelle évolue le personnage
 * \param perso Le personnage à faire apparaître
 * \param coord Les coordonnées du personnage quand il apparaît
 */
void spawnPerso(carte_t* carte, perso_t* perso, coord_t* coord);

/**
 * \brief Place le personnage sur un carré s'il est accessible
 * \author Max Descomps
 * \param carte La carte sur laquelle placer le personnage
 * \param perso Le personnage à placer
 * \param coord Les coordonnées ou placer personnage
 */
void placerPerso(carte_t* carte, perso_t* perso, coord_t* coord);

/**
 * \brief Indique si le personnage voit hors de la carte
 * \author Max Descomps
 * \param carte La carte sur laquelle évolue le personnage
 * \param perso Le personnage étudié
 * \return Un booléen
 */
int voitHorsCarte(carte_t* carte, perso_t* perso);

/**
 * \brief Indique si le personnage voit le bord de la carte
 * \author Max Descomps
 * \param carte La carte sur laquelle évolue le personnage
 * \param perso Le personnage étudié
 * \return Un booléen
 */
int voitBordCarte(carte_t* carte, perso_t* perso);

/**
 * \brief Paramètre un nouveau personnage
 * \author Max Descomps
 * \param perso Le personnage à paramétrer
 */
void statPerso(perso_t *perso);

/**
 * \brief Modifie la place du personnage dans la fenêtre de jeu
 * \author Max Descomps
 * \param direction La direction prise par le personnage
 * \param carte La carte ou se trouve le personnage
 * \param perso Le personnage qui se déplace
 */
void actualiserPlaceEcran(direction_t direction, carte_t* carte, perso_t* perso);

/**
 * \brief Gère la mort du personnage
 * \author Max Descomps
 * \param tirs La liste des tirs
 * \param mobs La liste des mobs
 * \param coffres La liste des coffres
 * \param plateau La fenêtre d'affichage du jeu
 * \param carte La carte
 * \param perso Le personnage à gérer
 * \param running L'état du jeu
 */
void checkMort(liste_t* tirs, liste_t* mobs, liste_t* coffres, WINDOW* plateau, carte_t* carte, perso_t* perso, int* running);

/**
 * \brief Gère le personnage
 * \author Max Descomps
 * \param tirs La liste des tirs
 * \param mobs La liste des mobs
 * \param coffres La liste des coffres
 * \param plateau La fenêtre d'affichage du jeu
 * \param carte La carte
 * \param perso Le personnage
 * \param running L'état du jeu
 */
void gestionPerso(liste_t* tirs, liste_t* mobs, liste_t* coffres, WINDOW* plateau, carte_t* carte, perso_t* perso, int* running);

/**
 * \brief Gère un tir du personnage
 * \author Max Descomps
 * \param perso Le personnage
 * \param direction La direction du tir
 * \param carte La carte ou se trouve le personnage
 * \param listeTirs La liste des tirs
 * \param stopTir Le compteur avant le prochain tir
 */
void persoTire(perso_t* perso, direction_t direction, carte_t* carte, liste_t* listeTirs, int* stopTir);