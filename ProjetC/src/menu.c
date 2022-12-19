#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "jeu.h"
#include "input.h"
#include "menu.h"

#define NB_TEXT_PAUSE 4
#define NB_TEXT_MORT 2

/**
 * \file menu.c
 * \author Max Descomps (descomps@et.esiea.fr)
 * \brief Fonctions liées au module menu
 * \version 0.2
 * \date 27/10/2022
 * \copyright Copyright (c) 2022
 */

int difficulty;

int choixCarte()
{
	char c = 0;
	int size = 0;

	printf("Voulez-vous creer une carte ou en reprendre une (entrez C ou R): ");
	do{
		c = lireChar();

		if((c != 'C') && (c != 'R')){
			printf("Choix invalide (C ou R): ");
        }
	}while((c != 'C') && (c != 'R'));
	
	if (c == 'C'){ //creation carte
        printf("Entrez la taille de la carte: ");
        do{
			size = lireInt();

            if(size < MAP_MIN_SIZE){
                printf("La taille de la carte doit etre superieure a %d: ", MAP_MIN_SIZE-1);
            }

			else if(size > MAP_MAX_SIZE){
                printf("La taille de la carte doit etre inferieure a %d: ", MAP_MAX_SIZE+1);
            }
        }while((size < MAP_MIN_SIZE) || (size > MAP_MAX_SIZE));
    }
	
	return size;
}

void choixDifficulte(){
	int input;
	
	printf("Entrez le niveau de difficulte:\n1) Facile\n2) Normal\n3) Difficile\n\n -->");
        do{
			input = lireInt();

            if(input < 1){
                printf("Le niveau de difficulte doit etre superieur a 0: ");
            }
			else if(input > 3){
                printf("Le niveau de difficulte doit etre inferieur a 4: ");
            }
        }while((input < 1) || (input > 3));

	difficulty = input-1;
}

void menuPause(WINDOW* w, carte_t* carte, perso_t* perso, int* running){
	char options[NB_TEXT_PAUSE][30] = {"Resume", "Save&Quit", "Save", "Quit"};
	int i, txtlen, row, col;
	int surligne = 0;
	int pause = 1;

	wclear(w);

	getmaxyx(w, row, col);

	while(pause){
		//contrôle du surlignage
		if(surligne >= NB_TEXT_PAUSE){
			surligne = 0;
		}
		else if(surligne < 0){
			surligne = NB_TEXT_PAUSE - 1;
		}

		//affichage
		box(w, 0, 0);

		for(i=0; i < NB_TEXT_PAUSE; i++){
			txtlen = strlen(options[i]);

			if(surligne == i){
				wattron(w, A_STANDOUT);
			}

			mvwprintw(w, (row / NB_TEXT_PAUSE * (i+1)) - (row / (2*NB_TEXT_PAUSE)) , (col-txtlen)/2, "%s", options[i]);

			if(surligne == i){
				wattroff(w, A_STANDOUT);
			}
		}
		wrefresh(w);

		int input=-1;

		do{
			input = getch();
			usleep(20); //limite utilisation processeur
		}while(input < 0);

		switch(input){
			case 'z':
			case KEY_UP: surligne--; break;
			case 's':
			case KEY_DOWN: surligne++; break;
			case '\n':
			case KEY_ENTER:
				switch(surligne){
					case 0: pause = 0; break;
					case 1: sauvegarde(carte, perso); *running = 0; pause = 0; break;
					case 2: sauvegarde(carte, perso); break;
					case 3: *running = 0; pause = 0; break;
					default: break;
				}
				break;
			case 'p': pause = 0; wclear(w); break;
			default: break;
		}
	}
	wclear(w);
}

void menuMort(liste_t* tirs, liste_t* mobs, liste_t* coffres, WINDOW* w, carte_t* carte, perso_t* perso, int* running){
	char options[NB_TEXT_MORT][30] = {"Last Save", "Quit"};
	int i, txtlen, row, col;
	int surligne = 0;
	int noChoice = 1;

	wclear(w);

	getmaxyx(w, row, col);

	char* txtMort = "GAME OVER";
	txtlen = strlen(txtMort);
	mvwprintw(w, 1 , (col-txtlen)/2, "%s", txtMort);

	while(noChoice){
		//contrôle du surlignage
		if(surligne >= NB_TEXT_MORT){
			surligne = 0;
		}
		else if(surligne < 0){
			surligne = NB_TEXT_MORT - 1;
		}

		//affichage
		box(w, 0, 0);

		for(i=0; i < NB_TEXT_MORT; i++){
			txtlen = strlen(options[i]);

			if(surligne == i){
				wattron(w, A_STANDOUT);
			}

			mvwprintw(w, (row / NB_TEXT_MORT * (i+1)) - (row / (2*NB_TEXT_MORT)) , (col-txtlen)/2, "%s", options[i]);

			if(surligne == i){
				wattroff(w, A_STANDOUT);
			}
		}
		wrefresh(w);
		
		int input=-1;

		do{
			input = getch();
			usleep(20); //limite utilisation processeur
		}while(input < 0);

		switch(input){
			case 'z':
			case KEY_UP: surligne--; break;
			case 's':
			case KEY_DOWN: surligne++; break;
			case '\n':
			case KEY_ENTER:
				switch(surligne){
					case 0: detruireCarres(carte); nettoyerJeu(tirs, mobs, coffres); rechargerMonde(perso->nom, carte, perso); noChoice = 0; break;
					case 1: *running = 0; noChoice = 0; break;
					default: break;
				}
				break;
			default: break;
		}
	}
	wclear(w);
}