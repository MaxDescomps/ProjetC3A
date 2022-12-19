#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "erreur.h"
#include "affichage.h"
#include "tir.h"
#include "jeu.h"

/**
 * \file main.c
 * \author Max Descomps (descomps@et.esiea.fr)
 * \brief Programme principal du jeu
 * \version 0.2
 * \date 27/10/2022
 * \copyright Copyright (c) 2022
 */

int main(int argc, char** argv)
{
	carte_t* carte = NULL;
	perso_t* perso = NULL;
	int running = 1;
	int input = 0;
	int compteur = 0;
	WINDOW* plateau;
	WINDOW* stats;
	WINDOW* inv;
	WINDOW* cartePerso;
	WINDOW* coffre;
	int row, col;
	liste_t* listeTirs = initListe(ajoutTirCb, detruireTirCb);
	liste_t* listeMobs = initListe(ajoutMobCb, detruireMobCb);
	liste_t* listeCoffres = initListe(ajoutCoffreCb, detruireCoffreCb);
	int stopTir = 0;
	int actionFaite = 1;
	int errRessolution = 0;

	srand(time(NULL)); //graîne aléatoire

	//doit etre avant ncurses pour stdio
	chargerMonde(&carte, &perso, listeCoffres);
	choixDifficulte();

	//ncurses
	initscr();             // initialise librairie ncurses
	use_default_colors();  // connait les couleurs par défaut du terminal
	clear();			   // nettoie l'écran
	refresh();			   // affiche l'écran nettoyé
	raw();   	           // renvoie les touches préssées mais pas les signaux
	noecho();              // n'affiche pas les input à l'écran
	keypad(stdscr, TRUE);  // ajoute les touches spéciales
	timeout(0);            // getch() non bloquant
	curs_set(0);           // rend le curseur invisible
	initColor();
	
	getmaxyx(stdscr,row,col);

	int rowPlateau = (row-VIEW_SIZE)/2 - ADJUST;
	int colPlateau = col/2 - VIEW_SIZE;
	int hPlateau = VIEW_SIZE + (PADDING*2);
	int largPlateau = (2 * VIEW_SIZE) + (PADDING*4) -1; //largeur des fenêtres (-1 car le dernier padding suit un espace)
	int largInv = 2*MAX_ITEM_PERSO + PADDING*4 - 1;
	int hInv = INV_SIZE + (PADDING*2);
	int hStats = STATS_SIZE + (PADDING*2);

	if(row < (hPlateau+rowPlateau + 2*hInv + 2) || col < largPlateau + 2){
		running = 0;
		errRessolution = 1;
	}

	// Création des fenêtres des interfaces
  	plateau = newwin(hPlateau, largPlateau, rowPlateau, colPlateau);
  	stats = newwin(hStats, largPlateau, rowPlateau - hStats, colPlateau);
  	inv = newwin(hInv, largInv, rowPlateau + hPlateau, colPlateau + (largPlateau - largInv)/2);
  	coffre = newwin(hInv, largInv, rowPlateau + hPlateau + hInv, colPlateau + (largPlateau - largInv)/2);
  	cartePerso = newwin(row-1, col-3, 1, 2);

	//spawn des mobs
	spawnListeMobs(carte, listeMobs, perso);

	//affiche l'inventaire du perso
	wprintInv(inv, perso->inventaire);

	//Boucle principale de jeu
	while(running){

		//affichage
		wprintwCarte(plateau, carte, perso); //affiche la carte
		wprintStats(stats, perso, largPlateau - 2); //affiche les stats du perso

		doupdate(); //refresh centralisé des fenêtres
		
		//ticks interactions perso
		if(compteur){
			compteur--;
		}

		//tick tirs perso
		if (stopTir){
			stopTir--;
		}
		
		input = getch();

		if(input >= 0){

			//actions sur le personnage
			actionFaite = 1;
			if(!compteur){
				
				switch(input){
					case 'z': bougerPerso(HAUT, carte, perso, listeTirs); compteur=PERSO_TICK; break;
					case 'd': bougerPerso(DROITE, carte, perso, listeTirs); compteur=PERSO_TICK; break;
					case 's': bougerPerso(BAS, carte, perso, listeTirs); compteur=PERSO_TICK; break;
					case 'q': bougerPerso(GAUCHE, carte, perso, listeTirs); compteur=PERSO_TICK; break;
					case 'e': actionRamasser(coffre, inv, carte, perso); break;
					case 'f': actionUtiliser(carte, perso); break;
					default: actionFaite=0; break;
				}
			}

			//actions sur le jeu
			if(!actionFaite){
				actionFaite = 1;

				switch(input){
					case 'p': menuPause(plateau, carte, perso, &running); break;
					case 'n' : running = 0; break;
					case 'm' : voirCarte(cartePerso, carte, perso, row-1, col-3); break;
					case KEY_F(1) : perso->inventaire->numCase = 0; break;
					case KEY_F(2) : perso->inventaire->numCase = 1; break;
					case KEY_F(3) : perso->inventaire->numCase = 2; break;
					case KEY_F(4) : perso->inventaire->numCase = 3; break;
					case KEY_F(5) : perso->inventaire->numCase = 4; break;
					case KEY_F(6) : perso->inventaire->numCase = 5; break;
					case KEY_F(7) : perso->inventaire->numCase = 6; break;
					case KEY_F(8) : perso->inventaire->numCase = 7; break;
					case KEY_F(9) : perso->inventaire->numCase = 8; break;
					case KEY_F(10) : perso->inventaire->numCase = 9; break;
					default: actionFaite=0; break;
				}
			}

			if(actionFaite){
				wprintInv(inv, perso->inventaire); //affiche l'inventaire du perso
			}

			//actions sur les tirs
			else if(!stopTir){
				switch(input){
					case KEY_LEFT: persoTire(perso, GAUCHE, carte, listeTirs, &stopTir); break;
					case KEY_UP: persoTire(perso, HAUT, carte, listeTirs, &stopTir); break;
					case KEY_DOWN: persoTire(perso, BAS, carte, listeTirs, &stopTir); break;
					case KEY_RIGHT: persoTire(perso, DROITE, carte, listeTirs, &stopTir); break;
					default: break;
				}
			}
		}

		actualiserMonde(listeTirs, carte, listeMobs, perso); //actualise l'environnement du perso

		//mise à jour personnage
		gestionPerso(listeTirs, listeMobs, listeCoffres, plateau, carte, perso, &running);

		//limite utilisation processeur
		usleep(10);
	}

	quitterJeu(&listeTirs, &listeMobs, &listeCoffres, &perso, &carte, plateau, stats, cartePerso, inv);

	if(errRessolution){
		printf("\n\n----- Résolution du terminal insuffisante pour lancer le jeu, veuillez l'agrandir -----\n\n");
	}

	return 0;
}