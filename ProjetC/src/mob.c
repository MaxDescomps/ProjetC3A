#include <stdlib.h>
#include <unistd.h>
#include "mob.h"
#include "carte.h"
#include "erreur.h"

/**
 * \file mob.c
 * \author Max Descomps (descomps@et.esiea.fr)
 * \brief Fonctions liées au module mob
 * \version 0.2
 * \date 27/10/2022
 * \copyright Copyright (c) 2022
 */

const int MOB_CPT[NB_DIFFICULTY] = {PERSO_TICK*8, PERSO_TICK*6, PERSO_TICK*4};

void creerMob(mob_t** mob){
    (*mob) = (mob_t*)calloc(1, sizeof(mob_t));
	if (!*mob)
        erreur("Plus de mémoire", ERR_MEMOIRE);

	(*mob)->position = creerCoord();
	(*mob)->direction = HAUT;
	(*mob)->maxPdv = 10;
	(*mob)->pdv = 10;
	(*mob)->action = RIEN;
	(*mob)->hostile = 0;
	(*mob)->compteur = 0;
	(*mob)->cacheChar = 0;
	(*mob)->affCase = '!';
	(*mob)->typeEnt = ENT_MOB;
	(*mob)->couleur = PAISIBLE;
	(*mob)->cacheCouleur = BASE;
}

void detruireMob(mob_t** mob){
	if(*mob != NULL){
		detruireCoord(&((*mob)->position));
		
		free(*mob);
		*mob = NULL;
	}
}

void detruireMobCb(void* mob){
	detruireMob(mob);
}

mob_t* ajoutMob(mob_t* mob){
	return mob;
}

void* ajoutMobCb(void* mob){
	return ajoutMob(mob);
}

mob_t* spawnMobAlea(carte_t* carte, perso_t* perso){
    coord_t* coordP = perso->position;
	int signe = 1;
	mob_t* mob = NULL;

	creerMob(&mob);
    coord_t* coordM = mob->position;

	//spawn hors champ dans la MOB_ZONE
	do{
		//ligne
		if((coordP->row + VIEW_LENGTH + MOB_ZONE) >= carte->tailleCarte){ //evite un spawn hors carte
			coordM->row = coordP->row - (VIEW_LENGTH/2 + ((rand() % (MOB_ZONE + 1)) + 1)); //+1 pour ne pas être visible en cas d'imparité du nombre de cases
		}
		else if((coordP->row - VIEW_LENGTH - MOB_ZONE) < 0){
			coordM->row = coordP->row + VIEW_LENGTH/2 + ((rand() % (MOB_ZONE + 1)) + 1);
		}
		else{
			if(rand()%2){
				signe *= -1;
			}
			coordM->row = coordP->row + (VIEW_LENGTH/2 + ((rand() % (MOB_ZONE + 1)) + 1)) * signe;
		}

		//colonne
		if((coordP->col + VIEW_LENGTH + MOB_ZONE) >= carte->tailleCarte){ //evite un spawn hors carte
			coordM->col = coordP->col - (VIEW_LENGTH/2 + ((rand() % (MOB_ZONE + 1)) + 1));
		}
		else if((coordP->col - VIEW_LENGTH - MOB_ZONE) < 0){
			coordM->col = coordP->col + VIEW_LENGTH/2 + ((rand() % (MOB_ZONE + 1)) + 1);
		}
		else{
			if(rand()%2){
				signe *= -1;
			}
			coordM->col = coordP->col + (VIEW_LENGTH/2 + ((rand() % (MOB_ZONE + 1)) + 1)) * signe;
		}
	}while(!carte->carre[coordM->row][coordM->col].acces); //évite de spawn sur un obstacle

	carte->carre[coordM->row][coordM->col].entite = (entite_t*)mob;
	carte->carre[coordM->row][coordM->col].acces = 0;
	mob->cacheChar = carte->carre[coordM->row][coordM->col].Affcase;
	carte->carre[coordM->row][coordM->col].Affcase = mob->affCase;

	mob->cacheCouleur = carte->carre[coordM->row][coordM->col].couleur;
	carte->carre[coordM->row][coordM->col].couleur = mob->couleur;

	mob->famille = rand() % NB_FAMILLES;
	mob->maxPdv = 2;
	mob->pdv = 2;

	return mob;
}

void spawnListeMobs(carte_t* carte, liste_t* listeMobs, perso_t* perso){
	mob_t* mob = NULL;

	for(int i = 0; i < NB_MOB_MAX; i++){
		mob = spawnMobAlea(carte, perso);
		ajoutDroit(listeMobs, mob);
	}
}

int mobEstLoin(int i, int j, perso_t* perso){
	int row = perso->position->row;
    int col = perso->position->col;

	return((abs(row-i) + abs(col-j)) >= (VIEW_LENGTH + 10));
}

int mobVoitPerso(int i, int j, perso_t* perso){
	int row = perso->position->row;
    int col = perso->position->col;

	return((abs(row-i) + abs(col-j)) <= MOB_VIEW);
}

void mobRush(mob_t* mob, perso_t* perso){
	int dirRow = mob->position->row - perso->position->row;
	int dirCol = mob->position->col - perso->position->col;

	if(abs(dirRow) > abs(dirCol)){
		if(dirRow > 0){
			mob->direction = HAUT;
		}
		else if(dirRow < 0){
			mob->direction = BAS;
		}
	}
	else{
		if(dirCol > 0){
			mob->direction = GAUCHE;
		}
		else if(dirCol < 0){
			mob->direction = DROITE;
		}
	}
}

void bougerMob(direction_t direction, carte_t* carte, mob_t* mob, liste_t* listeTirs){

	//Gestion collision mob avec perso
	if(!bougerEntite(direction, carte, (entite_t*)mob, listeTirs)){
		coord_t* coordM = mob->position;
		coord_t* tempCoord = nextCoord(mob->direction, coordM);
		carre_t* tempCarre = (&carte->carre[tempCoord->row][tempCoord->col]);

		if(coordExiste(tempCoord, carte)){
			if((tempCarre->entite)){
				if(tempCarre->entite->typeEnt == ENT_PERSO){
					(tempCarre->entite->pdv)--;
				}
			}
		}

		detruireCoord(&tempCoord);
	}
}