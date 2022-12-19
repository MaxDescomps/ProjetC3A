#include <stdlib.h>
#include "item.h"
#include "erreur.h"

/**
 * \file item.c
 * \author Max Descomps (descomps@et.esiea.fr)
 * \brief Fonctions liées au module item
 * \version 0.2
 * \date 27/10/2022
 * \copyright Copyright (c) 2022
 */

//fonction de test de création type abstrait
item_t* creerItem(){

    item_t* item = (item_t*)calloc(1, sizeof(item_t));
	if (!item)
        erreur("Plus de mémoire", ERR_MEMOIRE);

	item->affCase = 'X';
	item->couleur = BASE;
	item->acces = 1;

    return item;
}

conso_t* creerConso(){
	conso_t* conso = (conso_t*)calloc(1, sizeof(conso_t));
	if (!conso)
        erreur("Plus de mémoire", ERR_MEMOIRE);

	conso->affCase = '+';
	conso->couleur = C_CONSO;
	conso->acces = 1;
	conso->soin = 1;

    return conso;
}

void detruireItem(item_t** item){
    free(*item);
    *item = NULL;
}

void detruireItemCb(void* item){
	detruireItem(item);
}

item_t* ajoutItem(item_t* item){
	return item;
}

void* ajoutItemCb(void* item){
	return ajoutItem(item);
}

void afficherItem(WINDOW* w, item_t* item){
	wattron(w, COLOR_PAIR(item->couleur));
	wprintw(w, "%c", item->affCase);
	wattroff(w, COLOR_PAIR(item->couleur));
}