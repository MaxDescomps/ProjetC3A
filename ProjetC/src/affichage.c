#include <string.h>
#include "erreur.h"
#include "affichage.h"

/**
 * \file affichage.c
 * \author Max Descomps (descomps@et.esiea.fr)
 * \brief Fonctions liées au module affichage
 * \version 0.2
 * \date 27/10/2022
 * \copyright Copyright (c) 2022
 */

void initColor(){
    if(!has_colors())
	{
		erreur("Le terminal ne supporte pas les couleurs", ERR_NCURSES);
	}

	start_color();
	init_color(COLOR_TURQUOISE, 0,1000,1000);
	init_color(COLOR_MARRON, 1000,500,250);
	init_color(COLOR_JAUNE, 1000,1000,200);
	init_color(COLOR_VERT, 500,1000,250);
	init_color(COLOR_ROSE, 1000,300,500);

	init_pair(BASE, -1, -1); //-1 représente la couleur normalement affichée par le terminal
	init_pair(PLANTE, COLOR_VERT, -1);
	init_pair(HERBE, COLOR_GREEN, -1);
	init_pair(ROCHE, COLOR_YELLOW, -1);
	init_pair(EAU, COLOR_BLUE, -1);
	init_pair(SABLE, COLOR_JAUNE, -1);
	init_pair(PERSO, COLOR_ROSE, -1);
	init_pair(PAISIBLE, COLOR_TURQUOISE, -1);
	init_pair(HOSTILE, COLOR_RED, -1);
	init_pair(TIR, COLOR_ROSE, -1);
	init_pair(TERRE, COLOR_MARRON, -1);
	init_pair(C_CONSO, COLOR_MAGENTA, -1);
}

void wprintwCarte(WINDOW* w, carte_t* carte, perso_t* perso)
{
	int tailleCarte = carte->tailleCarte;
	coord_t* coordP = perso->position;
	int i, j;
	int k; //sauvegarde valeur initiale de j
	int cptX; //nombre de lignes affichées
	int cptY; //nombre de colonnes affichées

	box(w, 0, 0);

	//réglage du focus sur le perso
	//lignes
	if((coordP->row - VIEW_LENGTH) > 0){ //pas en bord carte au début
		if(coordP->row + VIEW_LENGTH >= (tailleCarte-1)){ //en bord de carte à la fin
			i = tailleCarte - VIEW_SIZE;
		}
		else{ //pas en bord de carte à la fin
			i = coordP->row - VIEW_LENGTH;
		}
	}
	else{ //en bord carte au début
		i = 0;
	}

	//colonnes
	if((coordP->col - VIEW_LENGTH) > 0){ //pas en bord carte au début
		if(coordP->col + VIEW_LENGTH >= (tailleCarte-1)){ //en bord de carte à la fin
			k = tailleCarte - VIEW_SIZE;
		}
		else{ //pas en bord de carte à la fin
			k = coordP->col - VIEW_LENGTH;
		}
	}
	else{ //en bord carte au début
		k = 0;
	}

	//affichage carte
	for (cptX = 0; cptX < VIEW_SIZE; i++, cptX++)
	{
		wmove(w, PADDING + cptX, PADDING*2); //place l'image dans la fenêtre
		for (j = k, cptY = 0; cptY < VIEW_SIZE; j++, cptY++)
		{
			if(coordProche(i, j, perso)){ //si dans champ de vision
					carte->carre[i][j].visited = 1;
					
					wattron(w, COLOR_PAIR(carte->carre[i][j].couleur));
					wprintw(w, "%c ", carte->carre[i][j].Affcase);
					wattroff(w, COLOR_PAIR(carte->carre[i][j].couleur));
			}
			else{
				wprintw(w, "  "); //sinon masquer carré
			}
		}
	}
	wnoutrefresh(w); //préparation pour refresh centralisé des fenêtres
}

void wprintStats(WINDOW* w, perso_t* perso, int colMax){
	box(w, 0, 0);
	char classe[6] = "HUMAIN";

	mvwprintw(w, PADDING, PADDING*2, "%s", perso->nom);
	wprintw(w, "	lvl:%i", perso->niveau);
	wmove(w, PADDING, colMax - strlen(classe));
	wprintw(w, "%s", classe);

	wmove(w, PADDING+1, PADDING*2);
	wprintw(w, "PDV [");
	for(int i=0; i<perso->maxPdv; i++){
		if(i < perso->pdv){
			wprintw(w, "#");
		}
		else{
			wprintw(w, " ");
		}
	}
	wprintw(w, "]");

	wmove(w, PADDING+2, PADDING*2);
	wprintw(w, "XP [");
	for(int i=0; i<XP_LIMIT; i++){
		if(i < perso->xp){
			wprintw(w, "*");
		}
		else{
			wprintw(w, " ");
		}
	}
	wprintw(w, "]");


	wnoutrefresh(w); //préparation pour refresh centralisé des fenêtres
}