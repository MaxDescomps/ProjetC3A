#include <stdlib.h>
#include "coffre.h"
#include "erreur.h"
#include "carte.h"

/**
 * \file coffre.c
 * \author Max Descomps (descomps@et.esiea.fr)
 * \brief Fonctions liées au module coffre
 * \version 0.2
 * \date 27/10/2022
 * \copyright Copyright (c) 2022
 */

coffre_t* creerCoffre(liste_t* listeCoffres){
    coffre_t* coffre = (coffre_t*)calloc(1, sizeof(coffre_t));

	if (!coffre)
        erreur("creerCoffre: Plus de mémoire", ERR_MEMOIRE);

	coffre->position = creerCoord();
	coffre->direction = HAUT;
	coffre->pdv = 10;
	coffre->cacheChar = 'X';
	coffre->affCase = '$';
	coffre->typeEnt = ENT_COFFRE;
	coffre->couleur = TERRE;
	coffre->cacheCouleur = BASE;
	coffre->numCase = 0;

    coffre->items = initListe(ajoutItemCb, detruireItemCb);

	return coffre;
}

void detruireCoffre(coffre_t** coffre){
	if(*coffre != NULL){
		detruireCoord(&((*coffre)->position));
	    detruireListe(&((*coffre)->items));
		
		free(*coffre);
		*coffre = NULL;
	}
}

void detruireCoffreCb(void* coffre){
	detruireCoffre(coffre);
}

coffre_t* ajoutCoffre(coffre_t* coffre){
	return coffre;
}

void* ajoutCoffreCb(void* coffre){
	return ajoutCoffre(coffre);
}

void wprintCoffre(WINDOW* w, coffre_t* coffre){
	liste_t* items = coffre->items;
	int i;

	box(w,0,0);
	wmove(w, PADDING, PADDING*2);

	enTete(items);

	for(i=0; !horsListe(items); i++){
		if(coffre->numCase == i){
			wattron(w, A_STANDOUT);
		}
		afficherItem(w, valeurElt(items));
		if(coffre->numCase == i){
			wattroff(w, A_STANDOUT);
		}
		wprintw(w, " ");
		
		suivant(items);
	}

	while(i < MAX_ITEMS_COFFRE){
		wprintw(w, "  ");
		i++;
	}

	wrefresh(w);
}