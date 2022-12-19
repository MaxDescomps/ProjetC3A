/**
 * \file carte.h
 * \author Max Descomps (descomps@et.esiea.fr)
 * \author Dorian Creuze (creuze@et.esiea.fr)
 * \brief Fichier contenant toutes les déclarations concernant la carte
 * \version 0.1
 * \date 29/09/2022
 * \copyright Copyright (c) 2022
 */

#pragma once

#include "mob.h"
#include "coffre.h"
#include "perso.h"

#define VIEW_LENGTH 12 /**<Longueur de la vue du personnage dans une direction */
#define MOB_ZONE 3 /**<Longueur de la zone de spawn des mobs après la zone visible du personnage*/
#define MAP_MIN_SIZE ((VIEW_LENGTH + MOB_ZONE) * 2 + 1) /**< Longueur et largeur minimum de la carte */
#define MAP_MAX_SIZE 500 /**<Longueur maximum d'un côté de la carte */
#define PADDING 1 /**<Ecart d'affichage entre le contenu et les bords de la fenêtre */
#define ADJUST 1 /**<Ajustement vers le haut de l'affichage complet dans le terminal */
#define ECCART_COFFRES 10 /**<Ecart entre les zones de spawn possibles des coffres */

extern const int VIEW_SIZE; /**<La longueur de la vue en jeu*/

//pour évolution future

// (E)léments (N)i (E)ntités (N)i (B)locs  c'est pour des objets fixes qui sont sur les cases mais ne sont pas les cases (exemples arbres)
// typedef enum
// {
//     ARBRE,
// 	CRAFT, //pour faire un potentiel système de crafting qui se ferait en intéraction avec l'élément
// 	SOIN, //pour un element qui soigne le personnage quand on intéragit avec lui
//     NB_ELEMENTINTERACTIF /**< Nombre de familles de mob*/
// } enumDesElementsInteractifs;

// typedef struct S_ElementsInteractifs
// {
// 	char Affcase;// caractère représentant l'élément
// 	char cachechar;// caractère caché par l'élément 
// 	int acces;// définit si le perso peut marche dessus ou non (je ne sais pas encore si je dois utiliser celui la ou remplacer celui de la case lorsque l'élément est sur la case)
// 	matiere_t couleur; // couleur du caratcère afficher
// 	enumDesElementsInteractifs EI; // EI pour element intéractif
// }elementInteractif;

/**
 * \brief Structure contenant les informations d'un carre de la carte
 * \author Dorian Creuze
 */
typedef struct Scarre
{
	char Affcase; /**< Caractère représentant le carré à afficher en jeu */
	matiere_t couleur; /**< Couleur du caractère affiché */
	int acces; /**< Définit si le perso peut marcher sur le carré */
	entite_t* entite; /**< Potentielle entité sur le carré*/
	// elementInteractif* EI; // pour une potentiel evolution avec element interactif posé sur la case (arbres ou autre)
	char biome; /**< Le biome dans auquel appartient le carré*/
	int y; /**< La hauteur du carré*/
	int visited; /**< Indique si le carré est connu du personnage*/
}carre_t;

/**
 * \brief Structure contenant les propiétées d'un biome
 * \author Dorian Creuze
 */
typedef struct SbiomeInfo
{
	char type; /**< Caractère représentant le type du biome */
	int x; /**< Taille du biome en nombre de lignes */
	int y; /**< Taille du biome en nombre de colonnes*/
}biomeInfo;

/**
 * \brief Structure contenant les informations de la carte
 * \author Max Descomps
 */
typedef struct Scarte{
	carre_t** carre; /**< Carres de la carte */
	int tailleCarte; /**< Longueur d'un côté de la carte */
}carte_t;

/**
 * \brief Structure contenant les informations d'un calque
 * \author Dorian Creuze
 */
struct calque
{
	int** v; /**<Valeurs du calque */
	int taille; /**<Taille du calque */
	float persistance; /**<Persistance du calque */
};

// elementInteractif* initElementInteractif(elementInteractif* EI);

/**
 * \brief Créé les carrés formant un terrain
 * \authors Dorian Creuze
 * \authors Max Descomps
 * \param carte La carte source contenant les carrés à créer
 */
void creerCarres(carte_t* carte);

/**
 * \brief Fait une copie des carrés d'une carte
 * \authors Dorian Creuze
 * \authors Max Descomps
 * \param carte La carte source contenant les carrés à copier
 * \return Les carrés copiés
 */
carre_t** copieCarres(carte_t* carte);

/**
 * \brief Génère un terrain aléatoire d'une taille donnée
 * \authors Max Descomps
 * \authors Dorian Creuze
 * \param carte Paramètre de sortie de la carte à créer
 */
void creerCarteAlea(carte_t* carte);

/**
 * \brief Gère le chargement d'une carte avant lancement de la partie
 * \authors Dorian Creuze
 * \authors Max Descomps
 * \param carte Paramètre de sortie de la carte chargée
 * \param perso Personnage chargé
 * \param listeCoffres La liste des coffres
 */
void chargerMonde(carte_t** carte, perso_t** perso, liste_t* listeCoffres);

/**
 * \brief Recharge une carte depuis un fichier de sauvegarde
 * \authors Max Descomps
 * \authors Dorian Creuze
 * \param chemin Chemin vers le fichier de sauvegarde
 * \param carte Instance de la carte rechargée
 * \param perso Instance de perso à parametrer
 */
void rechargerMonde(char* chemin, carte_t* carte, perso_t* perso);

/**
 * \brief Met à jour les collisions de toute la carte
 * \authors Max Descomps
 * \authors Dorian Creuze
 * \param carte Carte à mettre à jour
 */
void collisionUpdate(carte_t* carte);

/**
 * \brief Génère une carte basique aléatoirement
 * \authors Max Descomps
 * \authors Dorian Creuze
 * \param carte Carte à générer
 */
void generationAlea(carte_t* carte);

/**
 * \brief Génère un lac autour d'un premier point d'eau
 * \author Dorian Creuze
 * \param carte La carte sur laquelle on veut générer un lac
 * \param x Coordonnée du premier point d'eau
 * \param y Coordonnée du premier point d'eau
 */
void unLac(carte_t* carte, int x, int y);

/**
 * \brief Génère une ile
 * \author Dorian Creuze
 * \param carte La carte sur laquelle on veut générer une ile
 * \param x Coordonnée du point autour duquel on place l'ile
 * \param y Coordonnée du point autour duquel on place l'ile
 */
void ile(carte_t* carte, int x, int y);

/**
 * \brief Génère une rivière en partant d'un point
 * \author Dorian Creuze
 * \param carte La carte sur laquelle on veut générer une rivière
 * \param x Coordonnée du départ de la rivière
 * \param y Coordonnée du départ de la rivière
 */
carre_t** riviere(carte_t* carte, int x, int y);

/**
 * \brief Génère un océan sur un bord de la carte
 * \author Dorian Creuze
 * \param carte La carte sur laquelle on veut générer un ocean
 */
carre_t** ocean(carte_t* carte);

/**
 * \brief Génère des biomes et de la hauteur
 * \author Dorian Creuze
 * \param carte La carte sur laquelle on veut générer les biomes et la hauteur
 * \param taille Taille de la carte
 * \param rseed Graîne pour la génération aléatoire de la carte
 * \param listeCoffres Liste des coffres
 */
carre_t** generationBiome(carte_t* carte, int taille, int rseed, liste_t* listeCoffres);

/**
 * \brief Désalloue l'espace attribué à la carte
 * \author Max Descomps
 * \param carte La carte à detruire
 */
void detruireCarte(carte_t** carte);

/**
 * \brief Initialise une carte
 * \author Max Descomps
 * \param carte La carte à initialiser
 */
void initCarte(carte_t** carte);

/**
 * \brief Désalloue l'espace attribué aux carrés de la carte
 * \author Max Descomps
 * \param carte La carte contenant les carrés à détruire
 */
void detruireCarres(carte_t* carte);

/**
 * \brief Actualise l'état du jeu et des éléments de chaque liste
 * \author Max Descomps
 * \param listeTirs La liste des tirs
 * \param carte La carte du monde à actualiser
 * \param listeMobs La liste des mobs
 * \param perso Le personnage en jeu
 */
void actualiserMonde(liste_t* listeTirs, carte_t* carte, liste_t* listeMobs, perso_t* perso);

/**
 * \brief Affiche les carrés visités sur la minicarte du perso
 * \author Max Descomps
 * \param w La fenêtre d'affichage
 * \param carte La carte du monde
 * \param perso Le personnage en jeu
 * \param maxRow Le nombre de lignes maximum de l'écran
 * \param maxCol Le nombre de colonnes maximum de l'écran
 */
void voirCarte(WINDOW* w, carte_t* carte, perso_t* perso, int maxRow, int maxCol);

/**
 * \brief Evalue si une case contient de l'eau
 * \author Max Descomps
 * \param affCase L'affichage de la case
 * \return un booléen
 */
int estAffEau(char affCase);

/**
 * \brief Evalue si un point existe sur la carte
 * \author Max Descomps
 * \param carte La carte étudiée
 * \param row Le numéro de ligne
 * \param col Le numéro de colonne
 * \return un booléen
 */
int pointExiste(carte_t* carte, int row, int col);

/**
 * \brief Génère un entier aléatoire
 * \author Dorian Creuze
 * \param x Coordonnée du carré sur lequel on travail
 * \param y Coordonnée du carré sur lequel on travail
 * \param rseed Graîne pour randomisation
 * \return Un entier aléatoire
 */
int noise2(int x, int y, int rseed);

/**
 * \brief Recherche une valeur intermédiaire en fonction des coordonnées sur lesquelles on travail
 * \author Dorian Creuze
 * \param x Coordonnée du carré sur lequel on travail
 * \param y Coordonnée du carré sur lequel on travail
 * \param s Décalage
 * \return Un flottant
 */
float lin_inter(float x, float y, float s);

/**
 * \brief Recherche une valeur intermédiaire en fonction des coordonnées sur lesquelles on travail
 * \author Dorian Creuze
 * \param x Coordonnée du carré sur lequel on travail
 * \param y Coordonnée du carré sur lequel on travail
 * \param s Décalage
 * \return Un flottant
 */
float smooth_inter(float x, float y, float s);

/**
 * \brief Travail de randomisation sur un carré
 * \author Dorian Creuze
 * \param x Coordonnée du carré sur lequel on travail
 * \param y Coordonnée du carré sur lequel on travail
 * \param rseed Graîne de randomisation
 * \return Un flottant
 */
float noise2d(float x, float y, int rseed);

/**
 * \brief Génération de hauteur aléatoire avec l'algorithme du bruit de Perlin
 * \author Dorian Creuze
 * \param x Coordonnée du carré sur lequel on travail
 * \param y Coordonnée du carré sur lequel on travail
 * \param freq Taille des zones
 * \param depth Profondeur des variations
 * \param rseed Graîne de randomisation
 * \return Un flottant
 */
float perlin2d(float x, float y, float freq, int depth, int rseed);