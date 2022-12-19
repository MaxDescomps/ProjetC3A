#include <stdlib.h>
#include "tir.h"
#include "erreur.h"

/**
 * \file tir.c
 * \author Max Descomps (descomps@et.esiea.fr)
 * \brief Fonctions liées au module tir
 * \version 0.2
 * \date 27/10/2022
 * \copyright Copyright (c) 2022
 */

tir_t* creerTir(entite_t* entite, carte_t* carte){
	tir_t* tir = malloc(sizeof(tir_t));
	if (!tir)
        erreur("Plus de mémoire", ERR_MEMOIRE);

	tir->position = nextCoord(entite->direction, entite->position);
	coord_t* coordT = tir->position;
	carre_t* carreT = &carte->carre[coordT->row][coordT->col];

	if(coordAccessible(coordT, carte)){
		tir->direction = entite->direction;
		tir->compteur = TIR_TICK;
		if(entite->typeEnt == ENT_PERSO){
			perso_t* perso = (perso_t*)entite;
			tir->portee = perso->porteeBase + perso->niveau - 1;
		}
		else{
			tir->portee = TIR_PORTEE_BASE - 1;
		}
		tir->affCase = '*';
		tir->typeEnt = ENT_TIR;

		tir->couleur = TIR;
		tir->cacheCouleur = BASE;

		carreT->entite = (entite_t*)tir;
		carreT->acces = 0;
		tir->cacheChar = carreT->Affcase;
		carreT->Affcase = tir->affCase;

		tir->cacheCouleur = carreT->couleur;
		carreT->couleur = tir->couleur;
	}
	//tir à bout portant
	else{
		if(coordExiste(coordT, carte)){
			if(carreT->entite){
				if(carreT->entite->typeEnt != ENT_TIR){
					(carreT->entite->pdv)--;
				}
			}
		}
		
		detruireTir(&tir);
		return NULL;
	}

	return tir;
}

void detruireTir(tir_t** tir){
	detruireCoord(&((*tir)->position));

	free(*tir);
	(*tir) = NULL;
}
void detruireTirCb(void* tir){
	detruireTir(tir);
}

tir_t* ajoutTir(tir_t* tir){
	return tir;
}

void* ajoutTirCb(void* tir){
	return ajoutTir(tir);
}

void tirer(carte_t* carte, liste_t* listeTirs, entite_t* entite){
	tir_t* tir = creerTir(entite, carte);

	if(tir){ //Si le tir ne s'est pas détruit à bout portant
		ajoutDroit(listeTirs, tir);
	}
}

void collisionVivantTir(entite_t* entite, carte_t* carte, liste_t* listeTirs, carre_t* carreTir){
    coord_t* coordE = entite->position;
	carre_t* carreE = &carte->carre[coordE->row][coordE->col];
    
	//avancer entité sur tir
	carreE->Affcase = entite->cacheChar;
	carreE->couleur = entite->cacheCouleur;
	carreE->acces = 1;
	carreE->entite = NULL;


	actualiserCoord(entite->direction, coordE);
	carreTir->Affcase = entite->affCase;
	carreTir->couleur = entite->couleur;
	entite->cacheChar = carreTir->entite->cacheChar;

	//detruire tir
	chercherElement(listeTirs, carreTir->entite, NULL);
	oterElt(listeTirs);

	//calcul des dommages
	(entite->pdv)--;
}

int collisionTirEntite(carte_t* carte, coord_t* coordColli, tir_t* tir){
	carre_t* carreTir = &carte->carre[tir->position->row][tir->position->col];
	carre_t* carreColli = NULL;

	carreTir->Affcase = tir->cacheChar;
	carreTir->couleur = tir->cacheCouleur;
	carreTir->acces = 1;
	carreTir->entite = NULL;

	if(coordExiste(coordColli, carte)){
		carreColli = &carte->carre[coordColli->row][coordColli->col];

		if(carreColli->entite){
			if(carreColli->entite->typeEnt == ENT_MOB || carreColli->entite->typeEnt == ENT_PERSO){
				(carreColli->entite->pdv)--;
			}
			return 1; //si collision entité
		}
	}

	return 0; //collision mur/tir/horsmap
	//pas de destruction dans cette fonction /!/
}