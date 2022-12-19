#include "entite.h"
#include "perso.h"

/**
 * \file entite.c
 * \author Max Descomps (descomps@et.esiea.fr)
 * \brief Fonctions relatives au type de structure entite
 * \version 0.1
 * \date 09/10/2022
 * \copyright Copyright (c) 2022
 */

int bougerEntite(direction_t direction, carte_t* carte, entite_t* entite, liste_t* listeTirs){
    coord_t* coordE = entite->position;
    entite->direction = direction;
    carre_t* carre = (&carte->carre[coordE->row][coordE->col]);

    if (directionPossible(direction, carte, coordE)){

        carre->Affcase = entite->cacheChar; //remet le caractère initial
        carre->couleur = entite->cacheCouleur; //remet la couleur initiale
        
        carre->acces = 1;
        carre->entite = NULL;

		actualiserCoord(direction, coordE);

        carre = (&carte->carre[coordE->row][coordE->col]); //actualise le carré de l'entité

        entite->cacheChar = carre->Affcase; //enregistre l'ancien caractère
        carre->Affcase = entite->affCase; //met le caractère de l'entité par dessus
        entite->cacheCouleur = carre->couleur; //enregistre l'ancienne couleur
        carre->couleur = entite->couleur; //met la couleur de l'entité par dessus

        carre->acces = 0;
        carre->entite = entite;

        return 1; //pas de collision
	}
    else{
        return 0; //collision
    }
}