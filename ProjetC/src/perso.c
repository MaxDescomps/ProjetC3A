#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "perso.h"
#include "erreur.h"
#include "input.h"
#include "tir.h"

/**
 * \file perso.c
 * \author Max Descomps (descomps@et.esiea.fr)
 * \author Dorian Creuze (creuze@et.esiea.fr)
 * \brief Fonctions liées au module perso
 * \version 0.2
 * \date 27/10/2022
 * \copyright Copyright (c) 2022
 */

char affPerso[NB_DIR] = {'^','>','v','<'};

void actualiserPlaceEcran(direction_t direction, carte_t* carte, perso_t* perso){
	coord_t* coordEcran = perso->placeEcran;
	coord_t* coordP = perso->position;
	int tailleCarte = carte->tailleCarte;
	perso->direction = direction;

	switch(direction)
	{
		case BAS:
			if(coordP->row - VIEW_LENGTH < 0){ //voit hors haut
				(coordEcran->row)++;
			}
			else if(coordP->row + VIEW_LENGTH >= (tailleCarte-1)){ //voit bord bas
				(coordEcran->row)++;
			}
			break;

		case DROITE:
			if(coordP->col - VIEW_LENGTH < 0){ //voit hors gauche
				(coordEcran->col)++;
			}
			else if(coordP->col + VIEW_LENGTH >= (tailleCarte-1)){ //voit bord droite
				(coordEcran->col)++;
			}
			break;

		case GAUCHE:
			if(coordP->col - VIEW_LENGTH <= 0){ //voit bord gauche
				(coordEcran->col)--;
			}
			else if(coordP->col + VIEW_LENGTH >= tailleCarte){ //voit hors droite
				(coordEcran->col)--;
			}
			break;

		case HAUT:
			if(coordP->row - VIEW_LENGTH <= 0){ //voit bord haut
				(coordEcran->row)--;
			}
			else if(coordP->row + VIEW_LENGTH >= tailleCarte){ //voit hors bas
				(coordEcran->row)--;
			}
			break;
		
		default: break;
	}
}

void bougerPerso(direction_t direction, carte_t* carte, perso_t* perso, liste_t* listeTirs)
{
	perso->affCase = affPerso[direction];

	if(bougerEntite(direction, carte, (entite_t*)perso, listeTirs)){
		actualiserPlaceEcran(direction, carte, perso);
	}
	else{ //collision
		coord_t* coordP = perso->position;
		carre_t* carreP = (&carte->carre[coordP->row][coordP->col]);

		coord_t* tempCoord = nextCoord(perso->direction, coordP);
		carre_t* tempCarre = (&carte->carre[tempCoord->row][tempCoord->col]);
		

		if(coordExiste(tempCoord, carte)){
			if((tempCarre->entite)){
				if(tempCarre->entite->typeEnt == ENT_TIR){
					collisionVivantTir((entite_t*)perso, carte, listeTirs, tempCarre);
					actualiserPlaceEcran(direction, carte, perso); //actualise le focus
				}
				else{
					carreP->Affcase = perso->affCase; //actualise l'affichage du perso
					carreP->couleur = perso->couleur; //actualise l'affichage du perso
				}
			}
		}
		else{
			carreP->Affcase = perso->affCase; //actualise l'affichage du perso
			carreP->couleur = perso->couleur; //actualise l'affichage du perso
		}
		detruireCoord(&tempCoord);
	}
}

void enlever(carre_t* carre)
{
	carre->Affcase = 'X';
	carre->couleur = TERRE;
	carre->acces = 1;

	return;
}

void gestionXP(perso_t* perso)
{
	while(perso->xp >= XP_LIMIT){
		(perso->xp) -= XP_LIMIT;
		(perso->niveau)++;
		(perso->attaque)++;
		(perso->defense)++;
		(perso->maxPdv)++;
		perso->pdv = perso->maxPdv;
	}
}

void creerPerso(perso_t** perso)
{
	(*perso) = (perso_t*)calloc(1, sizeof(perso_t));
	if (!*perso)
        erreur("Plus de mémoire", ERR_MEMOIRE);

	(*perso)->nom = malloc(sizeof(char) * (MAX_TAILLE_NOM+1));
	if (!((*perso)->nom))
        erreur("Plus de mémoire", ERR_MEMOIRE);

	(*perso)->maxPdv = 10;
	(*perso)->pdv = 10;
	(*perso)->cacheChar = 0;
	(*perso)->attaque=5;
	(*perso)->defense=5;
	(*perso)->affCase = '^';
	(*perso)->action = RIEN;
	(*perso)->direction = HAUT;
	(*perso)->position = creerCoord();
	(*perso)->placeEcran = creerCoord();
	(*perso)->inventaire = creerInv();
	(*perso)->typeEnt = ENT_PERSO;
	(*perso)->couleur = PERSO;
	(*perso)->cacheCouleur = BASE;
	(*perso)->niveau = 1;
	(*perso)->xp = 0;
	(*perso)->porteeBase = TIR_PORTEE_BASE - 1;
}

void actionUtiliser(carte_t* carte, perso_t* perso)
{
	coord_t* coordP = perso->position;

	switch (perso->direction)
	{
		case HAUT:
			if(directionExiste(HAUT, carte, coordP)){
				utiliserItem(perso, (carte->carre[coordP->row-1] + (coordP->col)));
			}
			break;

		case DROITE:
			if(directionExiste(DROITE, carte, coordP)){
				utiliserItem(perso, (carte->carre[coordP->row] + (coordP->col+1)));
			}
			break;

		case BAS:
			if(directionExiste(BAS, carte, coordP)){
				utiliserItem(perso, (carte->carre[coordP->row+1] + (coordP->col)));
			}
			break;

		case GAUCHE:
			if(directionExiste(GAUCHE, carte, coordP)){
				utiliserItem(perso, (carte->carre[coordP->row] + (coordP->col - 1)));
			}
			break;
		default: break;
	}
}

void actionRamasser(WINDOW* fenCoffre, WINDOW* fenInv, carte_t* carte, perso_t* perso)
{
	coord_t* coordP = perso->position;

	switch (perso->direction)
	{
	case HAUT:
		if(directionExiste(HAUT, carte, coordP)){
			ramasser(fenCoffre, fenInv, (item_t*)(carte->carre[coordP->row-1] + (coordP->col)), perso);
		}
		break;

	case DROITE:
		if(directionExiste(DROITE, carte, coordP)){
			ramasser(fenCoffre, fenInv, (item_t*)(carte->carre[coordP->row] + (coordP->col+1)), perso);
		}
		break;

	case BAS:
		if(directionExiste(BAS, carte, coordP)){
			ramasser(fenCoffre, fenInv, (item_t*)(carte->carre[coordP->row+1] + (coordP->col)), perso);
		}
		break;

	case GAUCHE:
		if(directionExiste(GAUCHE, carte, coordP)){
			ramasser(fenCoffre, fenInv, (item_t*)(carte->carre[coordP->row] + (coordP->col - 1)), perso);
		}
		break;
	
	default: break;
	}
}

void detruirePerso(perso_t** perso){
	if(*perso != NULL){
		detruireInv(&((*perso)->inventaire));
		detruireCoord(&((*perso)->position));
		detruireCoord(&((*perso)->placeEcran));

		free((*perso)->nom);
		
		free(*perso);
		*perso = NULL;
	}
}

int directionExiste(direction_t direction, carte_t* carte, coord_t* position){
	int row = position->row;
	int col = position->col;
	int tailleCarte = carte->tailleCarte;

	switch(direction){
		case HAUT:
			return ((row > 0));
		case DROITE:
			return ((col < tailleCarte - 1));
		case BAS:
			return ((row < tailleCarte - 1));
		case GAUCHE:
			return ((col > 0));
		default:
			printf("Direction inconnue\n");
			break;
	}
	return 0;
}

int directionPossible(direction_t direction, carte_t* carte, coord_t* position){
	int row = position->row;
	int col = position->col;
	carre_t** carre = carte->carre;
	int tailleCarte = carte->tailleCarte;

	switch(direction){
		case HAUT:
			return ((row > 0) && (carre[row-1][col].acces == 1));
		case DROITE:
			return ((col < tailleCarte - 1) && (carre[row][col+1].acces == 1));
		case BAS:
			return ((row < tailleCarte - 1) && (carre[row+1][col].acces == 1));
		case GAUCHE:
			return ((col > 0) && (carre[row][col-1].acces == 1));
		default: break;
	}
	return 0;
}

void placerPerso(carte_t* carte, perso_t* perso, coord_t* coord){
	int tailleCarte = carte->tailleCarte;
	coord_t* coordP = perso->position;
	coord_t* coordEcran = perso->placeEcran;
	
	if(coordAccessible(coord, carte)){
		*(perso->position) = *coord;

		//carré affichage perso ligne
		if((coordP->row - VIEW_LENGTH) <= 0){ //bord de carte début
			coordEcran->row = coordP->row;
		}
		else if(coordP->row + VIEW_LENGTH >= tailleCarte){ //bord de carte fin
			coordEcran->row = (VIEW_SIZE-1) - (tailleCarte-1 - (coordP->row)); //flag a revoir
		}
		else{
			coordEcran->row = VIEW_LENGTH;
		}
		
		//carré affichage perso colonne
		if((coordP->col - VIEW_LENGTH) <= 0){ //bord de carte début
			coordEcran->col = coordP->col;
		}
		else if(coordP->col + VIEW_LENGTH >= tailleCarte){ //bord de carte fin
			coordEcran->col = (VIEW_SIZE-1) - (tailleCarte-1 - (coordP->col));
		}
		else{
			coordEcran->col = VIEW_LENGTH;
		}

	carte->carre[coordP->row][coordP->col].entite = (entite_t*)perso;
	carte->carre[coordP->row][coordP->col].acces = 0;
	perso->cacheChar = carte->carre[coordP->row][coordP->col].Affcase;
	carte->carre[coordP->row][coordP->col].Affcase = perso->affCase;

	perso->cacheCouleur = carte->carre[coordP->row][coordP->col].couleur;
	carte->carre[coordP->row][coordP->col].couleur = perso->couleur;
	}
}

void spawnPerso(carte_t* carte, perso_t* perso, coord_t* coord){
	statPerso(perso);
	
	placerPerso(carte, perso, coord);
}

int voitHorsCarte(carte_t* carte, perso_t* perso){
	coord_t* coordP = perso->position;
	int tailleCarte = carte->tailleCarte;

	return (((coordP->row - VIEW_LENGTH) < 0) || (coordP->row + VIEW_LENGTH >= tailleCarte) || 
		    ((coordP->col - VIEW_LENGTH) < 0) || (coordP->col + VIEW_LENGTH >= tailleCarte));
}

int voitBordCarte(carte_t* carte, perso_t* perso){
	coord_t* coordP = perso->position;
	int tailleCarte = carte->tailleCarte;

	return (((coordP->row - VIEW_LENGTH) <= 0) || (coordP->row + VIEW_LENGTH >= tailleCarte-1) || 
		    ((coordP->col - VIEW_LENGTH) <= 0) || (coordP->col + VIEW_LENGTH >= tailleCarte-1));
}

void statPerso(perso_t *perso){
	printf("Nom de votre personnage: ");
	lireStr(perso->nom, MAX_TAILLE_NOM);
	perso->nom = realloc(perso->nom, sizeof(char)* strlen(perso->nom) + 1);
	if (!(perso->nom))
        erreur("Plus de mémoire", ERR_MEMOIRE);
}

void checkMort(liste_t* tirs, liste_t* mobs, liste_t* coffres, WINDOW* plateau, carte_t* carte, perso_t* perso, int* running){
	if(perso->pdv <= 0){
		menuMort(tirs, mobs, coffres, plateau, carte, perso, running);
		// *running = 0;
	}
}

void gestionPerso(liste_t* tirs, liste_t* mobs, liste_t* coffres, WINDOW* plateau, carte_t* carte, perso_t* perso, int* running){
	checkMort(tirs, mobs, coffres, plateau, carte, perso, running);
}

void persoTire(perso_t* perso, direction_t direction, carte_t* carte, liste_t* listeTirs, int* stopTir){
	perso->direction = direction;
	perso->affCase = affPerso[direction];
	carte->carre[perso->position->row][perso->position->col].Affcase=affPerso[direction];

	tirer(carte, listeTirs, (entite_t* )perso);
	*stopTir = TIR_RATE;
}