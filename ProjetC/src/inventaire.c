#include <unistd.h>
#include <stdlib.h>
#include "perso.h"
#include "inventaire.h"
#include "erreur.h"

/**
 * \file inventaire.c
 * \author Max Descomps (descomps@et.esiea.fr)
 * \author Dorian Creuze (creuze@et.esiea.fr)
 * \brief Fonctions liées au module inventaire
 * \version 0.2
 * \date 27/10/2022
 * \copyright Copyright (c) 2022
 */

invCase_t* creerInvCase(){
	invCase_t* invCase = malloc(sizeof(invCase_t));

	if(!invCase)
		erreur("Erreur allocation case inventaire", ERR_MEMOIRE);

	invCase->item = malloc(sizeof(item_t));
	if(!invCase->item)
		erreur("Erreur allocation item", ERR_MEMOIRE);

	invCase->nb = 0;
	invCase->type = NOTYPE;

	return invCase;
}

void detruireInvCase(invCase_t** invCase){
	if(*invCase != NULL){
		free((*invCase)->item);

		free(*invCase);
		*invCase = NULL;
	}
}

inventaire_t* creerInv(){
	int i;
	inventaire_t* inventaire = malloc(sizeof(inventaire_t));

	if(!inventaire)
		erreur("Erreur allocation inventaire", ERR_MEMOIRE);

	inventaire->invCase = malloc(sizeof(invCase_t*) * MAX_ITEM_PERSO);
	if (!(inventaire->invCase))
        erreur("Plus de mémoire", ERR_MEMOIRE);

	for(i=0; i<MAX_ITEM_PERSO; i++){
		inventaire->invCase[i] = creerInvCase();
	}

	inventaire->nbItem = 0;
	inventaire->numCase = 0;

	return inventaire;
}

void detruireInv(inventaire_t** inventaire){
	if(*inventaire != NULL){
		int i;

		for(i=0; i<MAX_ITEM_PERSO; i++){
			detruireInvCase((*inventaire)->invCase + i);
		}

		free((*inventaire)->invCase);

		free(*inventaire);
		*inventaire = NULL;
	}
}

int ramasser(WINDOW* fenCoffre, WINDOW* fenInv, item_t* carre, perso_t* perso)
{
	int i;
	int input = -1;
	int actionFaite;
	inventaire_t* inventaire = perso->inventaire;

	//ouverture coffre
	if(((carre_t*)carre)->entite != NULL && carre->affCase == '$'){
		int dansCoffre = 1;
		coffre_t* coffre = (coffre_t*)(((carre_t*)carre)->entite);
		coffre->numCase = 0;

		do{
			wprintCoffre(fenCoffre, coffre); //affiche le coffre

			input = getch();

			if(input >= 0){
				actionFaite = 1;

				switch(input){
					case KEY_F(1) : inventaire->numCase = 0; break;
					case KEY_F(2) : inventaire->numCase = 1; break;
					case KEY_F(3) : inventaire->numCase = 2; break;
					case KEY_F(4) : inventaire->numCase = 3; break;
					case KEY_F(5) : inventaire->numCase = 4; break;
					case KEY_F(6) : inventaire->numCase = 5; break;
					case KEY_F(7) : inventaire->numCase = 6; break;
					case KEY_F(8) : inventaire->numCase = 7; break;
					case KEY_F(9) : inventaire->numCase = 8; break;
					case KEY_F(10) : inventaire->numCase = 9; break;
					default: actionFaite=0; break;
				}

				if(!actionFaite){
					actionFaite = 1;

					switch(input){
						case KEY_RIGHT:
							if(!listeVide(coffre->items)){
								(coffre->numCase)++;
								if(coffre->numCase >= coffre->items->nb_elem){
									coffre->numCase = 0;
								}
							}
						break;

						case KEY_LEFT:
							if(!listeVide(coffre->items)){
								(coffre->numCase)--;
								if(coffre->numCase < 0){
									coffre->numCase = (coffre->items->nb_elem)-1;
								}
							}
						break;

						case KEY_UP:
							if(!listeVide(coffre->items)){
								if(coffre->numCase >= 0 && coffre->numCase < coffre->items->nb_elem){
									enTete(coffre->items);
									for(i=0; i!=inventaire->numCase; i++){
										suivant(coffre->items);
									}

									item_t* item = valeurElt(coffre->items);

									//cherche l'item dans l'inventaire
									for(i=0; i < MAX_ITEM_PERSO; i++){
										if(inventaire->invCase[i]->nb != 0){
											if(inventaire->invCase[i]->item->affCase == item->affCase){
												break;
											}
										}
									}

									//recup si l'item est déjà dans l'inventaire
									if(i < MAX_ITEM_PERSO){
										(inventaire->invCase[i]->nb)++;
										oterElt(coffre->items);
									}

									else if(perso->inventaire->nbItem < MAX_ITEM_PERSO){

										//cherche un emplacement vide dans l'inventaire
										for(i=0; perso->inventaire->invCase[i]->nb != 0; i++);

										*(perso->inventaire->invCase[i]->item) = *item;
										perso->inventaire->invCase[i]->nb = 1;
										if(item->affCase == '+'){
											//limite d'implémentaion actuelle
											perso->inventaire->invCase[i]->type = CONSO;
										}
										(perso->inventaire->nbItem)++;

										oterElt(coffre->items);
									}
								}
							}
						break;
						default: actionFaite=0; break;
					}

					if(!actionFaite){
						switch(input){
							case 'e': dansCoffre = 0; break;
							default: break;
						}
					}
					else{
						wprintCoffre(fenCoffre, coffre);
						wprintInv(fenInv, inventaire);
					}
				}
				else{
					wprintInv(fenInv, inventaire);
				}
			}
			usleep(30);
		}while(dansCoffre);

		wclear(fenCoffre);
		wrefresh(fenCoffre);
	}

	//blocs récupérables
	else if(((carre_t*)carre)->entite == NULL && carre->affCase != 'X'){

		//recup si le bloc est déjà dans l'inventaire
		for(i=0; i < MAX_ITEM_PERSO; i++){
			if(perso->inventaire->invCase[i]->type == BLOC){
				if(perso->inventaire->invCase[i]->item->affCase == carre->affCase){
					(perso->inventaire->invCase[i]->nb)++;

					enlever((carre_t*)carre);
					return 1;
				}
			}
		}

		if(perso->inventaire->nbItem < MAX_ITEM_PERSO){
			int i;

			//cherche un emplacement vide dans l'inventaire
			for(i=0; perso->inventaire->invCase[i]->nb != 0; i++);

			*(perso->inventaire->invCase[i]->item) = *carre;
			perso->inventaire->invCase[i]->nb = 1;
			perso->inventaire->invCase[i]->type = BLOC;
			(perso->inventaire->nbItem)++;

			enlever((carre_t*)carre);

			return 1;
		}
	}
	
	return 0;
}

void wprintInv(WINDOW* w, inventaire_t* inventaire)
{
	int i;

	wmove(w, PADDING, PADDING*2);
	box(w,0,0);

	for(i=0; i<MAX_ITEM_PERSO; i++){
		if(inventaire->invCase[i]->nb){
			if(inventaire->numCase == i){
				wattron(w, A_STANDOUT);
			}
			wattron(w, COLOR_PAIR(inventaire->invCase[i]->item->couleur));
			wprintw(w, "%c", inventaire->invCase[i]->item->affCase);
			wattroff(w, COLOR_PAIR(inventaire->invCase[i]->item->couleur));
			if(inventaire->numCase == i){
				wattroff(w, A_STANDOUT);
			}
			wprintw(w, " ");
		}
		else{
			wprintw(w, "  ");
		}
	}
	wnoutrefresh(w); //préparation pour refresh centralisé des fenêtres
}

int utiliserItem(perso_t* perso, carre_t* carre)
{
	inventaire_t* inventaire = perso->inventaire;

	if(inventaire->invCase[inventaire->numCase]->type == BLOC){
		if(carre->acces == 1)
		{
			//gestion inventaire
			(inventaire->invCase[inventaire->numCase]->nb)--;

			if(inventaire->invCase[inventaire->numCase]->nb == 0){
				inventaire->invCase[inventaire->numCase]->type = NOTYPE;
			}

			//changement carte
			carre_t* carreInv = (carre_t*)inventaire->invCase[inventaire->numCase]->item;

			carre->Affcase = carreInv->Affcase;
			carre->couleur = carreInv->couleur;
			carre->acces = carreInv->acces;

			return 1;
		}
	}
	else if(inventaire->invCase[inventaire->numCase]->type == CONSO){
		(perso->pdv)++; //limite implémentation actuelle faute de temps (items copiés au lieu de référencés)
		if(perso->pdv > perso->maxPdv){
			perso->pdv = perso->maxPdv;
		}

		//gestion inventaire
		(inventaire->invCase[inventaire->numCase]->nb)--;

		if(inventaire->invCase[inventaire->numCase]->nb == 0){
			inventaire->invCase[inventaire->numCase]->type = NOTYPE;
		}
	}

	return 0;
}