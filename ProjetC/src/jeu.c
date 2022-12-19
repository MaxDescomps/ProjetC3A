#include <stdlib.h>
#include <string.h> 
#include "jeu.h"

/**
 * \file jeu.c
 * \author Max Descomps (descomps@et.esiea.fr)
 * \brief Fonctions liées au module jeu
 * \version 0.2
 * \date 27/10/2022
 * \copyright Copyright (c) 2022
 */

void quitterJeu(liste_t** tirs, liste_t** mobs, liste_t** coffres, perso_t** perso, carte_t** carte, WINDOW* plateau, 
WINDOW* stats, WINDOW* cartePerso, WINDOW* inv){
    detruireListe(tirs);
	detruireListe(mobs);
	detruireListe(coffres);

	detruirePerso(perso);
	detruireCarte(carte);

	delwin(plateau); //désalloue la fenêtre de jeu
	delwin(stats); //désalloue la fenêtre de statistiques
	delwin(cartePerso); //désalloue la fenêtre de la carte du personnage
	delwin(inv); //désalloue la fenêtre de l'inventaire du personnage
	endwin(); //désalloue la base de ncurses
}

void nettoyerJeu(liste_t* tirs, liste_t* mobs, liste_t* coffres){
    viderListe(tirs);
	viderListe(mobs);
	viderListe(coffres);
}

int sauvegarde(carte_t* carte, perso_t* perso)
{
	FILE* saveList;
	int tailleCarte = carte->tailleCarte;
	saveList=fopen("liste.txt", "a+");
	int i, j;
	
	if(saveList==NULL)
	{
		printf("\nimpossible d'ecrire le fichier liste\n");
		return EXIT_FAILURE; 
	}
	
	char saveName[MAX_TAILLE_NOM];
	int saveExiste = 0;

	while(fscanf(saveList, "%s", saveName) == 1){
		if(!strcmp(saveName, perso->nom)){
			saveExiste = 1;
			break;
		}
	}

	if(!saveExiste){
		fseek(saveList, 0, SEEK_END);
		fprintf(saveList, "%s", perso->nom);
		fprintf(saveList, "\n");
	}
	
	fclose(saveList);

	FILE* sauvegarde;
	char path[80];
	strcpy(path, SAVE_DIR);
	strcat(path, perso->nom);
	
	sauvegarde = fopen(path, "w");

	if (sauvegarde == NULL)
	{
		printf("\nimpossible d'ecrire le fichier de sauvegarde\n");
		return EXIT_FAILURE;
	}
	else
	{
		for (i = 0; i < tailleCarte; i++){
			for (j = 0; j < tailleCarte; j++){

				if(carte->carre[i][j].entite){
					if(carte->carre[i][j].entite->typeEnt == ENT_PERSO){
						fprintf(sauvegarde, "%c", carte->carre[i][j].entite->affCase);
					}
					else{
						fprintf(sauvegarde, "%c", carte->carre[i][j].entite->cacheChar);
					}
				}
				else{
					fprintf(sauvegarde, "%c", carte->carre[i][j].Affcase);
				}
			}
			fprintf(sauvegarde, "\n");
		}

		fprintf(sauvegarde, "%c%c\n%d\n%d\n%d\n%d\n%d\n", perso->cacheChar, perso->cacheCouleur, perso->position->row,
				perso->position->col, perso->niveau, perso->pdv, perso->xp);

		

		fclose(sauvegarde);

		return 0;
	}
}