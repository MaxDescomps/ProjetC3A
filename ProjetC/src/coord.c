#include <stdlib.h>
#include "coord.h"
#include "perso.h"
#include "erreur.h"

/**
 * \file coord.c
 * \author Max Descomps (descomps@et.esiea.fr)
 * \brief Fonctions liées au module coord
 * \version 0.2
 * \date 27/10/2022
 * \copyright Copyright (c) 2022
 */

coord_t* creerCoord(){
    coord_t* coord;

    coord = malloc(sizeof(coord));
	if (!coord)
        erreur("Plus de mémoire", ERR_MEMOIRE);

    coord->row = 0;
    coord->col = 0;

    return coord;
}

void detruireCoord(coord_t** coord){
    if((*coord != NULL)){
        free(*coord);
        (*coord) = NULL;
    }
}

int coordProche(int i, int j, perso_t* perso){
    int row = perso->position->row;
    int col = perso->position->col;

	//affichage carré
    // return ((i<= row && j <= col && i+VIEW_LENGTH >= row && j+VIEW_LENGTH >= col) ||
    //         (i >= row && j >= col && i-VIEW_LENGTH <= row && j-VIEW_LENGTH <= col) ||
    //         (i <= row && j >= col && i+VIEW_LENGTH >= row && j-VIEW_LENGTH <= col) ||
    //         (i >= row && j <= col && i-VIEW_LENGTH <= row && j+VIEW_LENGTH >= col));

	//affichage losange
	return((abs(row-i) + abs(col-j)) <= VIEW_LENGTH);
}

coord_t coordAlea(carte_t* carte){
	coord_t coord;

	coord.row = rand()%(carte->tailleCarte);
	coord.col = rand()%(carte->tailleCarte);

	return coord;
}

coord_t coordAleaAcces(carte_t* carte){
	coord_t coord;

	do{
		coord = coordAlea(carte);
	}
	while(!coordAccessible(&coord, carte));

	return coord;
}

int coordExiste(coord_t* coord, carte_t* carte){
	int tailleCarte = carte->tailleCarte;

	return (coord->row < tailleCarte && coord->col < tailleCarte && coord->row >= 0 && 
            coord->col >= 0);
}

int coordAccessible(coord_t* coord, carte_t* carte){
	return (coordExiste(coord, carte) && carte->carre[coord->row][coord->col].acces);
}

void actualiserCoord(direction_t direction, coord_t* position){
    switch(direction)
	{
		case BAS:
            (position->row)++;
			break;

		case DROITE:
			(position->col)++;
			break;

		case GAUCHE:
			(position->col)--;
			break;

		case HAUT:
			(position->row)--;
			break;
		default: break;
	}
}

coord_t* nextCoord(direction_t direction, coord_t* position){
	coord_t* coord = creerCoord();

	*coord = *position;

	switch(direction)
	{
		case BAS:
            (coord->row)++;
			break;

		case DROITE:
			(coord->col)++;
			break;

		case GAUCHE:
			(coord->col)--;
			break;

		case HAUT:
			(coord->row)--;
			break;
		default: break;
	}

	return coord;
}