#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "carte.h"
#include "erreur.h"
#include "input.h"
#include "affichage.h"
#include "tir.h"
#include "jeu.h"

/**
 * \file carte.c
 * \author Max Descomps (descomps@et.esiea.fr)
 * \author Dorian Creuze (creuze@et.esiea.fr)
 * \brief Fonctions liées au module carte
 * \version 0.2
 * \date 27/10/2022
 * \copyright Copyright (c) 2022
 */

static int cptSpawnMob = CPT_SPAWN_MOB;
static int nb_biomes = 4;
// A ocean, B montagne, C désert D plaines

static int hash[] = { 208,34,231,213,32,248,233,56,161,78,24,140,71,48,140,254,245,255,247,247,40,
					 185,248,251,245,28,124,204,204,76,36,1,107,28,234,163,202,224,245,128,167,204,
					 9,92,217,54,239,174,173,102,193,189,190,121,100,108,167,44,43,77,180,204,8,81,
					 70,223,11,38,24,254,210,210,177,32,81,195,243,125,8,169,112,32,97,53,195,13,
					 203,9,47,104,125,117,114,124,165,203,181,235,193,206,70,180,174,0,167,181,41,
					 164,30,116,127,198,245,146,87,224,149,206,57,4,192,210,65,210,129,240,178,105,
					 228,108,245,148,140,40,35,195,38,58,65,207,215,253,65,85,208,76,62,3,237,55,89,
					 232,50,217,64,244,157,199,121,252,90,17,212,203,149,152,140,187,234,177,73,174,
					 193,100,192,143,97,53,145,135,19,103,13,90,135,151,199,91,239,247,33,39,145,
					 101,120,99,3,186,86,99,41,237,203,111,79,220,135,158,42,30,154,120,67,87,167,
					 135,176,183,191,253,115,184,21,233,58,129,233,142,39,128,211,118,137,139,255,
					 114,20,218,113,154,27,127,246,250,1,8,198,250,209,92,222,173,21,88,102,219 };

const int VIEW_SIZE = (2 * VIEW_LENGTH + 1);

void collisionUpdate(carte_t* carte)
{
	int tailleCarte = carte->tailleCarte;
	char Affcase = 0;

	for (int i = 0; i < tailleCarte; i++)
	{
		for (int j = 0; j < tailleCarte; j++)
		{
			Affcase = carte->carre[i][j].Affcase;

			if (Affcase == 'W' || Affcase == 'D' || Affcase == '$'){
				carte->carre[i][j].acces = 0;
			}
			else{
				carte->carre[i][j].acces = 1;
			}
		}
	}
}

// creer le monde teste

void creerCarres(carte_t* carte)
{
	int tailleCarte = carte->tailleCarte;
	int i, j;

	// alloue le terrain
	carte->carre = (carre_t**)calloc(tailleCarte, sizeof(carre_t*));
	if (!(carte->carre) && tailleCarte != 0)
        erreur("Plus de mémoire", ERR_MEMOIRE);

	carre_t** carres = carte->carre;

	for (i = 0; i < tailleCarte; i++)
	{
		carres[i] = (carre_t*)calloc(tailleCarte, sizeof(carre_t));
		if (!carres[i])
        	erreur("Plus de mémoire", ERR_MEMOIRE);
	}

	// donne le type aux cases
	for (i = 0; i < tailleCarte; i++)
	{
		for (j = 0; j < tailleCarte; j++)
		{
			carres[i][j].acces = 1;
			carres[i][j].Affcase = '~';
			carres[i][j].couleur = SABLE;
			carres[i][j].entite = NULL;
			carres[i][j].visited = 0;
		}
	}
}

void detruireCarres(carte_t* carte){
	if (carte != NULL && carte->carre != NULL){
		for (int i = 0; i < carte->tailleCarte; i++)
		{
			if(carte->carre[i] != NULL){
				free(carte->carre[i]);
				carte->carre[i] = NULL;
			}
		}

		free(carte->carre);
		carte->carre = NULL;
	}
}

void generationAlea(carte_t* carte)
{
	int tailleCarte = carte->tailleCarte;
	int cpt = 0;

	for (int i = 0; i < tailleCarte; i++)
	{
		for (int j = 0; j < tailleCarte; j++)
		{
			if ((rand() % 50 == 1)&&(cpt==0))
			{
				carte->carre[i][j].Affcase = '&';
				carte->carre[i][j].couleur = ROCHE;
				cpt++;
			}
		}
	}
}
void ile(carte_t* carte, int x, int y)
{
	int r = rand() % 5 + 2;
	carre_t** carre = carte->carre;

	for (int i = x - r; i < x + r; i++)
	{
		for (int j = y - r; j < y + r; j++)
		{
			if(pointExiste(carte, i, j)){

				if (((i < x + 2 + rand() % 2) && (i > x - 2 + rand() % 2) && (j > y - 4 - rand() % 2) && (j < y + 4 + rand() % 3))
				||  ((i < x + 4 + rand() % 3) && (i > x - 4 - rand() % 2) && (j > y - 2 + rand() % 2) && (j < y + 2 + rand() % 2))
				||	((i < x + 3 + rand() % 2) && (i > x - 3 + rand() % 2) && (j > y - 3 + rand() % 2) && (j < y + 3 + rand() % 2)))
				{
					carre[i][j].Affcase = '~';
					carre[i][j].couleur = SABLE;
				}
			}
		}
	}
}


void unLac(carte_t* carte, int x, int y)
{
	int r = rand() % 5 + 2;
	carre_t** carre = carte->carre;
	
	for (int i = x - r; i < x + r; i++)
	{
		for (int j = y - r; j < y + r; j++)
		{
			if(pointExiste(carte, i, j)){
				if (((i < x + 2 + rand() % 2) && (i > x - 2 + rand() % 2) && (j > y - 4 + rand() % 2) && (j < y + 4 + rand() % 2))
				||	((i < x + 4 + rand() % 2) && (i > x - 4 + rand() % 2) && (j > y - 2 + rand() % 2) && (j < y + 2 + rand() % 2))
				||	((i < x + 3 + rand() % 2) && (i > x - 3 + rand() % 2) && (j > y - 3 + rand() % 2) && (j < y + 3 + rand() % 2)))
				{
					carre[i][j].Affcase = 'W';
					carre[i][j].couleur = EAU;
					carre[i][j].acces = 0;
				}
			}
		}
	}
}

carre_t** ocean(carte_t* carte)
{
	int tailleCarte = carte->tailleCarte;
	int x, y;
	int a = rand() % 4;


	switch (a)
	{
	case 1:
		x = 0, y = 0;
		break;
	case 2:
		x = 0, y = tailleCarte;
		break;
	case 3:
		x = tailleCarte, y = 0;
		break;
	case 4:
		x = tailleCarte, y = tailleCarte;
		break;
	}
	int tailleOcean = rand() % (tailleCarte / 2 + tailleCarte / 4);
	if (tailleOcean < tailleCarte / 4)
		tailleOcean = tailleCarte / 4;
	int nb_ile = tailleOcean / 15;
	int cpt = 0;

	for (int i = x - tailleOcean; (i < x + tailleOcean) && (i < tailleCarte); i++)
	{
		if (i < 0)
			i = 0;
		for (int j = y - tailleOcean + rand() % 3; (j < y + tailleOcean + rand() % 3) && (j < tailleCarte); j++)
		{
			if (j < 0)
				j = 0;
			if ((rand() % 50 == 1) && (cpt <= nb_ile))
			{
				ile(carte, i, j);
				cpt++;
			}
			carte->carre[i][j].Affcase = 'W';
			carte->carre[i][j].couleur = EAU;
		}
	}
	for (int i = x - tailleOcean; (i < x + tailleOcean) && (i < tailleCarte); i++)
	{
		if (i < 0)
			i = 0;
		for (int j = y - tailleOcean; (j < y + tailleOcean + rand() % 3) && (j < tailleCarte); j++)
		{
			if (j < 0)
				j = 0;
			carte->carre[j][i].Affcase = 'W';
			carte->carre[j][i].couleur = EAU;
		}
	}
	ile(carte, tailleOcean / 2, tailleOcean / 2);

	return carte->carre;
}

carre_t** riviere(carte_t* carte, int x, int y)
{
	int taille = rand() % carte->tailleCarte;
	if (taille < 10)
		taille = 5;
	int largeur_max = rand() % carte->tailleCarte / 20;
	if (largeur_max < 1)
		largeur_max = 1;//si c'est égal à 0 on trace quand même une riviere de largeur 1
	int direction = rand() % 4;//détermine la direction dans laquelle la riviere s'en va

	switch (direction)
	{
	case 1:
		for (int i = 0; i < taille; i++)
		{
			carte->carre[x + i][y].Affcase = 'W';
			carte->carre[x + i][y].couleur = EAU;
			if (largeur_max > 0)
			{
				for (int j = y - largeur_max; j < y + largeur_max; j++)
				{
					if (j <= 0)
						j = 1;
					carte->carre[x + i][j].Affcase = 'W';
					carte->carre[x + i][j].couleur = EAU;
				}
			}
			if (rand() % 6 == 1)
			{
				y++;
			}
			if (rand() % 6 == 2)
			{
				y--;
			}
			if (y == 0)
			{
				return carte->carre;
			}
		}
		break;
	case 2:
		for (int i = 0; i < taille; i++)
		{
			carte->carre[x][y + i].Affcase = 'W';
			carte->carre[x][y + i].couleur = EAU;
			if (largeur_max > 0)
			{
				for (int j = x - largeur_max; j < x + largeur_max; j++)
				{
					if (j <= 0)
						j = 1;
					carte->carre[j][y + i].Affcase = 'W';
					carte->carre[j][y + i].couleur = EAU;
				}
			}
			if (rand() % 6 == 1)
			{
				x++;
			}
			if (rand() % 6 == 2)
			{
				x--;
			}
			if (x == 0)
			{
				return carte->carre;
			}
		}
		break;
	case 3:
		for (int i = 0; i < taille; i++)
		{
			carte->carre[x][y - i].Affcase = 'W';
			carte->carre[x][y - i].couleur = EAU;
			if (largeur_max > 0)
			{
				for (int j = x - largeur_max; j < x + largeur_max; j++)
				{
					if (j <= 0)
						j = 1;
					carte->carre[j][y - i].Affcase = 'W';
					carte->carre[j][y - i].couleur = EAU;
				}
			}
			if (rand() % 6 == 1)
			{
				x++;
			}
			if (rand() % 6 == 2)
			{
				x--;
			}
			if (x == 0)
			{
				return carte->carre;
			}
		}
		break;
	case 4:
		for (int i = 0; i < taille; i++)
		{
			carte->carre[x - i][y].Affcase = 'W';
			carte->carre[x - i][y].couleur = EAU;
			if (largeur_max > 0)
			{
				for (int j = y - largeur_max; j < y + largeur_max; j++)
				{
					if (j <= 0)
						j = 1;
					carte->carre[x - i][j].Affcase = 'W';
					carte->carre[x - i][j].couleur = EAU;
				}
			}
			if (rand() % 6 == 1)
			{
				y++;
			}
			if (rand() % 6 == 2)
			{
				y--;
			}
			if (y == 0)
			{
				return carte->carre;
			}
		}
		break;

	}
	return carte->carre;
}


int noise2(int x, int y, int rseed)
{
	int tmp = hash[(y + rseed) % 256];
	return hash[(tmp + x) % 256];
}

float lin_inter(float x, float y, float s)
{
	return x + s * (y - x);
}

float smooth_inter(float x, float y, float s)
{
	return lin_inter(x, y, s * s * (3 - 2 * s));
}

float noise2d(float x, float y, int rseed)
{
	int x_int = x;
	int y_int = y;
	float x_frac = x - x_int;
	float y_frac = y - y_int;
	int s = noise2(x_int, y_int, rseed);
	int t = noise2(x_int + 1, y_int, rseed);
	int u = noise2(x_int, y_int + 1, rseed);
	int v = noise2(x_int + 1, y_int + 1, rseed);
	float low = smooth_inter(s, t, x_frac);
	float high = smooth_inter(u, v, x_frac);
	return smooth_inter(low, high, y_frac);
}

float perlin2d(float x, float y, float freq, int depth, int rseed)
{
	float xa = x * freq;
	float ya = y * freq;
	float amp = 1.0;
	float fin = 0;
	float div = 0.0;

	int i;
	for (i = 0; i < depth; i++)
	{
		div += 256 * amp;
		fin += noise2d(xa, ya, rseed) * amp;
		amp /= 2;
		xa *= 2;
		ya *= 2;
	}

	return fin;
}

// génération de biome et de hauteur
carre_t** generationBiome(carte_t* carte, int taille, int rseed, liste_t* listeCoffres)
{
	int cptBiome = taille / 20;
 	biomeInfo* tab = (biomeInfo*)calloc(taille / 10, sizeof(biomeInfo));
	if (!tab)
        erreur("Generation biome plus de mémoire", ERR_MEMOIRE);

 	if (cptBiome < 2)
 		cptBiome = 2;

 	//cette boucle donne aux biomes une position sur la carte
 	for (int i = 0; i < cptBiome; i++)
 	{
 		tab[i].type = 65 + (i % nb_biomes);
 		tab[i].x = rand() % taille;
 		tab[i].y = rand() % taille;
 	}

 	//cette boucle donne une hauteur à la carte grâce à l'algo du bruit de perlin
 	//et elle change cette hauteur en fonction du biome, ce que vous trouvez sur la carte change aussi en fonction du biome
 	for (int i = 0; i < taille; i++)
 	{
 		for (int j = 0; j < taille; j++)
 		{
 			char nearest = '.';
 			int dist = 10000;
 			for (int z = 0; z < cptBiome; z++)
 			{
 				int xdiff = tab[z].x - i;
 				int ydiff = tab[z].y - j;

 				int cdist = xdiff * xdiff + ydiff * ydiff;

 				if (cdist < dist)
				{
 					nearest = tab[z].type;
 					dist = cdist;
 				}
 			}
 			carte->carre[i][j].biome = nearest;
 			carte->carre[i][j].y = perlin2d(i, j, 0.1, 6, 0);
 			switch (carte->carre[i][j].biome)
			{//&~WDeEmMS-
 			case 'A':
 				carte->carre[i][j].y = carte->carre[i][j].y - 70;
 				if (carte->carre[i][j].y > 240){
 					carte->carre[i][j].Affcase = '&';
 					carte->carre[i][j].couleur = TERRE;
				}
 				if (carte->carre[i][j].y < 240){
 					carte->carre[i][j].Affcase = '~';
 					carte->carre[i][j].couleur = SABLE;
				}
				if (carte->carre[i][j].y < 200){
 					carte->carre[i][j].Affcase = 'W';
 					carte->carre[i][j].couleur = EAU;
					carte->carre[i][j].acces=0;
				}
 				if (carte->carre[i][j].y < 130){
 					carte->carre[i][j].Affcase = 'D';
 					carte->carre[i][j].couleur = EAU;
					carte->carre[i][j].acces=0;
				}
				if (rand() % 500 == 1)
 				 	ile(carte, i, j);
				break;
 			case 'B':
 				carte->carre[i][j].y = carte->carre[i][j].y + 70;
 				if (carte->carre[i][j].y < 240){
 					carte->carre[i][j].Affcase = 'e';
 					carte->carre[i][j].couleur = PLANTE;
				}
				if (carte->carre[i][j].y > 240){
 					carte->carre[i][j].Affcase = 'E';
 					carte->carre[i][j].couleur = HERBE;
				}
				if (carte->carre[i][j].y > 300){
 					carte->carre[i][j].Affcase = '&';
 					carte->carre[i][j].couleur = TERRE;
				}
 				if (carte->carre[i][j].y > 360){
 					carte->carre[i][j].Affcase = 'm';
 					carte->carre[i][j].couleur = ROCHE;
				}
 				if (carte->carre[i][j].y > 400){
 					carte->carre[i][j].Affcase = 'M';
 					carte->carre[i][j].couleur = ROCHE;
				}
				if (carte->carre[i][j].y > 430){
 					carte->carre[i][j].Affcase = 'S';
 					carte->carre[i][j].couleur = BASE;
				}
				
				//pour évolution future

				// if((rand()%10==1)&&(carte->carre[i][j].Affcase=='e'))
				// {
				// 	elementInteractif* EI=NULL;
				// 	EI=initElementInteractif(EI);
				// 	if(EI)
				// 	{
				// 	carte->carre[i][j].EI=EI;
				// 	carte->carre[i][j].EI->EI=ARBRE;
				// 	carte->carre[i][j].EI->Affcase='T';
				// 	carte->carre[i][j].EI->cachechar='e';
				// 	carte->carre[i][j].Affcase='T';
				// 	carte->carre[i][j].couleur=HOSTILE;  // temporaire
				// 	carte->carre[i][j].EI->cachechar=carte->carre[i][j].Affcase;
				// 	}
				// }
				
 				break;
 			case 'C':
				if (carte->carre[i][j].y < 230)
					carte->carre[i][j].y = carte->carre[i][j].y + 20;
				if (carte->carre[i][j].y > 270)
 					carte->carre[i][j].y = carte->carre[i][j].y - 20;
 				if ((carte->carre[i][j].y > 230) && (carte->carre[i][j].y < 270) && (carte->carre[i][j].Affcase != 'W')){
 					carte->carre[i][j].Affcase = '~';
 					carte->carre[i][j].couleur = SABLE;
				}
				if ((carte->carre[i][j].y <= 200) && (carte->carre[i][j].Affcase != 'W')){
 					carte->carre[i][j].Affcase = '-';
 					carte->carre[i][j].couleur = SABLE;
				}
 				if (rand() % 500 == 1)
 				 	unLac(carte, i, j);
 				break;
 			case 'D':
 				if (carte->carre[i][j].y < 230)
 					carte->carre[i][j].y = carte->carre[i][j].y + 20;
 				if (carte->carre[i][j].y > 270)
 					carte->carre[i][j].y = carte->carre[i][j].y - 20;
 				if ((carte->carre[i][j].y >= 210) && (carte->carre[i][j].y < 280) && (carte->carre[i][j].Affcase != 'W')){
 					carte->carre[i][j].Affcase = 'E';
 					carte->carre[i][j].couleur = HERBE;
				}
 				if ((carte->carre[i][j].y >= 280) && (carte->carre[i][j].Affcase != 'W')){
					carte->carre[i][j].Affcase = '&';
 					carte->carre[i][j].couleur = TERRE;
				}
 				if ((carte->carre[i][j].y < 210) && (carte->carre[i][j].Affcase != 'W')){
					carte->carre[i][j].Affcase = 'e';
 					carte->carre[i][j].couleur = PLANTE;
				}
 				if (rand() % 500 == 1)
					unLac(carte, i, j);
 				break;
 			}
 		}
 	}

	//génération coffres
	int ci=0;
	int cj=0;
	coffre_t* coffre = NULL;
	item_t* item = NULL;

	for(int i=ECCART_COFFRES; i< (carte->tailleCarte) - ECCART_COFFRES; i+=ECCART_COFFRES){
		for(int j=ECCART_COFFRES; j<(carte->tailleCarte) - ECCART_COFFRES; j+=ECCART_COFFRES){
			if(carte->carre[i][j].acces){
				if(rand()%2){

					//création coffre
					ci = i - (rand()%ECCART_COFFRES);
					cj = j - (rand()%ECCART_COFFRES);

					coffre = creerCoffre(listeCoffres);
					ajoutDroit(listeCoffres, coffre);

					//création items du coffre
					for(int w=0; w<MAX_LOOT_COFFRE; w++){
						if(1){
						item = (item_t*)creerConso();
						ajoutDroit(coffre->items, item);
						}
					}

					carte->carre[ci][cj].entite = (entite_t*)coffre;
					carte->carre[ci][cj].Affcase = '$';
					carte->carre[ci][cj].acces = 0;
					carte->carre[ci][cj].couleur = TERRE;
				}
			}
		}
	}

	collisionUpdate(carte);
	
	free(tab);

 	return carte->carre;
}

void rechargerMonde(char* chemin, carte_t* carte, perso_t* perso)
{
	FILE* sauvegarde;
	int tailleCarte = 0;
	char c = 0;
	char savePath[80];

	strcpy(savePath, SAVE_DIR);
	strcat(savePath, chemin);
	
	sauvegarde = fopen(savePath, "r");

	if (sauvegarde == NULL)
	{
		printf("Impossible de lire le fichier carte %s\n", chemin);
	}
	else
	{
		//calcul tailleCarte (longueur d'une ligne)
		while (fscanf(sauvegarde, "%c", &c) == 1 && c != '\n')
		{
			tailleCarte++;
		}
		rewind(sauvegarde);

		if(tailleCarte == 0){
			printf("fichier de sauvegarde vide\n");
			return;
		}

		carte->tailleCarte = tailleCarte;
		creerCarres(carte);
		
		//lecture de l'affichage des carrés
		//&~WDeEmMS-
		matiere_t* couleur = NULL;

		for (int i = 0; i < tailleCarte; i++)
		{
			for (int j = 0; j < tailleCarte; j++)
			{
				fscanf(sauvegarde, "%c", &c);
				carte->carre[i][j].Affcase = c;

				couleur = &(carte->carre[i][j].couleur);

				switch(c){
					case 'e': *couleur = PLANTE; break;
					case 'E': *couleur = HERBE; break;
					case '&': *couleur = TERRE; break;
					case '~':
					case '-': *couleur = SABLE; break;
					case 'W':
					case 'D': *couleur = EAU; break;
					case 'S': *couleur = BASE; break;
					case 'm':
					case 'M': *couleur = ROCHE; break;
					case '^':
					case '<':
					case 'v':
					case '>': *couleur = PERSO; break;
					case 'X': *couleur = TERRE; break;
					default: *couleur = BASE; break;
				}
			}
			fscanf(sauvegarde, "%*c");
		}
		c = 0;

		fscanf(sauvegarde, "%c%c%*c", &(perso->cacheChar), (char*)&(perso->cacheCouleur));

		int row = 0;

		fscanf(sauvegarde, "%c", &c);

		while (c != '\n')
		{
			row = row * 10;
			row = row+c - 48;
			fscanf(sauvegarde, "%c", &c);
		}
		int col = 0;

		fscanf(sauvegarde, "%c", &c);
		while (c != '\n')
		{
			col = col * 10;
			col = col + c - 48;
			fscanf(sauvegarde, "%c", &c);
		}
		//niveau
		fscanf(sauvegarde, "%c", &c);
		int niveau=0;
		while(c!='\n')
		{
			niveau=niveau*10;
			niveau=niveau+c-48;
			fscanf(sauvegarde, "%c", &c);
		}
		//pdv
		fscanf(sauvegarde, "%c", &c);
		int pdv=0;
		while(c!='\n')
		{
			pdv=pdv*10;
			pdv=pdv+c-48;
			fscanf(sauvegarde, "%c", &c);
		}
		//xp
		fscanf(sauvegarde, "%c", &c);
		int xp=0;
		while(c!='\n')
		{
			xp=xp*10;
			xp=xp+c-48;
			fscanf(sauvegarde, "%c", &c);
		}
		

		perso->xp=xp;
		perso->pdv=pdv;
		perso->niveau=niveau;
		perso->position->row = row;
		perso->position->col = col;
		collisionUpdate(carte);

		fclose(sauvegarde);
	}
}

//évolution future
// elementInteractif* initElementInteractif(elementInteractif* EI)
// {
// 	EI=(elementInteractif*)calloc(1, sizeof(elementInteractif));
// 	if(!EI)
// 		return NULL;

// 	EI->acces=1;
// 	return EI;
// }

void creerCarteAlea(carte_t* carte)
{
	int tailleCarte = carte->tailleCarte;
	int i, j;
	int cpt=0;
	int row=0, col=0;

	// alloue la carte
	carte->carre = (carre_t**)calloc(tailleCarte, sizeof(carre_t*));
	if (!carte->carre)
        erreur("Plus de mémoire", ERR_MEMOIRE);

	carre_t** carres = carte->carre;

	for (i = 0; i < tailleCarte; i++)
	{
		carres[i] = (carre_t*)calloc(tailleCarte, sizeof(carre_t));
		if (!carres[i])
        	erreur("Plus de mémoire", ERR_MEMOIRE);
	}

	// donne le type aux cases sauf a la derniere qui est faite a part
	// mettre taille-1 te faisait ignorer la dernière ligne et colonne de la carte
	for (i = 0; i < tailleCarte; i++)
	{
		for (j = 0; j < tailleCarte; j++)
		{
			carres[i][j].acces = 1;

			if (carres[i][j].Affcase != '&') {
				if (rand() % 10 == 5)
				{
					carres[i][j].Affcase = '&';
				}
				else
				{
					carres[i][j].Affcase = '~';
				}
			}
		}
	}
	for (i = 0; i < tailleCarte-1; i++)
	{
		for (j = 0; j < tailleCarte-1; j++)
		{
			// 50% de chance de voir un bloc different
			if (carres[i][j].Affcase == '&')
			{
				if (rand() % (2) == 1)
				{
					carres[i + 1][j].Affcase = '&';
					carres[i][j + 1].Affcase = '&';
				}
			}

			//generation rivière
			if ((rand() % 200 == 1) && (cpt == 0) && (i > 5) && (j > 5))
			{
				carres[i][j].Affcase = 'W';
				carres[i][j].acces = 0;
				row = i;
				col = j;
				cpt++;
			}
			else if ((j > col + 6) && (j < col + 12) && (i < row + 25))
			{
				if (rand() % 2 == 1)
				{
					carres[i][j].Affcase = 'W';
					carres[i][j].acces = 0;
				}
			}
			else if ((j > col + 6) && (j < col + 12) && (i < row + 25))
			{
				if (rand() % 2 == 1)
				{
					carres[i][j].Affcase = 'W';
					carres[i][j].acces = 0;
				}
			}
			else if ((j > col + 4) && (j < col + 14) && (i < row + 30))
			{
				if (rand() % 5 == 1)
				{
					carres[i][j].Affcase = 'W';
					carres[i][j].acces = 0;
				}
			}
		}
	}

	//derniere case
	carres[tailleCarte-1][tailleCarte-1].acces = 1;
	carres[tailleCarte-1][tailleCarte-1].Affcase = '~';
}

carre_t** copieCarres(carte_t* carte)
{
	int tailleCarte = carte->tailleCarte;
	carre_t** copie;

	copie = (carre_t**)calloc(tailleCarte, sizeof(carre_t*));
	if (!copie)
        erreur("Plus de mémoire", ERR_MEMOIRE);

	for (int i = 0; i < tailleCarte; i++)
	{
		copie[i] = (carre_t*)calloc(tailleCarte, sizeof(carre_t));
		if (!copie[i])
        	erreur("Plus de mémoire", ERR_MEMOIRE);
	}

	for (int i = 0; i < tailleCarte; i++)
	{
		for (int j = 0; j < tailleCarte; j++)
		{
			copie[i][j] = carte->carre[i][j];
		}
	}
	return copie;
}

void initCarte(carte_t** carte){
	*carte = malloc(sizeof(carte_t));
	if (!(*carte))
        erreur("Plus de mémoire", ERR_MEMOIRE);
		
	(*carte)->carre = NULL;
	(*carte)->tailleCarte = 0;
}

void chargerMonde(carte_t** carte, perso_t** perso, liste_t* listeCoffres){
	int tailleCarte;
	
	initCarte(carte);

	creerPerso(perso);
	
	while((*carte)->carre == NULL){ //gere une erreur de chargement de la carte
		tailleCarte = choixCarte();

		if(tailleCarte) //nouvelle carte
		{
			(*carte)->tailleCarte = tailleCarte;
			
			//nouveau terrain
			creerCarres(*carte);

			// generationAlea(*carte);
			generationBiome((*carte), tailleCarte, rand() % 3000, listeCoffres);
			
			//nouveau personnage
			coord_t coordP = coordAleaAcces(*carte);
			spawnPerso(*carte, *perso, &coordP);

			//sauvegarde après première création
			sauvegarde(*carte, *perso);
		}

		else //charger carte depuis sauvegarde
		{
			char c=2;
			FILE* saveList = fopen("liste.txt", "r");

			if(saveList){
				rewind(saveList);
				for(int i=0; i<10; i++)
				{
					fscanf(saveList, "%c", &c);
					printf("%c", c);
				}
				fclose(saveList);
				printf("\nnom du fichier de sauvegarde de la carte: ");
				lireStr((*perso)->nom, 100);
				rechargerMonde((*perso)->nom, *carte, *perso);
			}

			if((*carte)->carre == NULL){
				printf("Retour au menu de choix de carte\n\n");
			}
		}
	}
}

void detruireCarte(carte_t** carte){
	if(*carte != NULL){
		detruireCarres(*carte);

		free(*carte);
		*carte = NULL;
	}
}

void actualiserMonde(liste_t* listeTirs, carte_t* carte, liste_t* listeMobs, perso_t* perso){
	tir_t* tir = NULL;
	carre_t* carreTir = NULL;
	coord_t* coordTemp = NULL;
	mob_t* mob = NULL;

	//mobs
	//spawn
	if(listeMobs->nb_elem < NB_MOB_MAX){
		if(cptSpawnMob){
			cptSpawnMob--;
		}
		else{
			mob = spawnMobAlea(carte, perso);
			ajoutDroit(listeMobs, mob);

			cptSpawnMob = CPT_SPAWN_MOB;
		}
	}

	//evolution
	enTete(listeMobs);
	while(!horsListe(listeMobs)){
		mob = valeurElt(listeMobs);

		if((mob->pdv) > 0){
			if(!mob->compteur){

				if(!mob->hostile){
					if((mobVoitPerso(mob->position->row, mob->position->col, perso)) && (difficulty!=0)){
						mob->hostile = 1;
						mob->couleur = HOSTILE;
						mobRush(mob, perso);
					}
					else{
						mob->direction = rand()%NB_DIR; //Le mob avance au hasard
					}
				}

				else{
					mobRush(mob, perso);
				}
				
				bougerMob(mob->direction, carte, mob, listeTirs);

				mob->compteur = MOB_CPT[difficulty];
			}
			else{
				(mob->compteur)--;
			}
			if(mobEstLoin(mob->position->row, mob->position->col, perso)){ //unspawn mob
				carre_t* carreM = &(carte->carre[mob->position->row][mob->position->col]);
			
				carreM->entite = NULL;
				carreM->acces = 1;
				carreM->Affcase = mob->cacheChar;
				carreM->couleur = mob->cacheCouleur;

				oterElt(listeMobs);
			}
		}
		else{ //Mort du mob

			carre_t* carreM = &(carte->carre[mob->position->row][mob->position->col]);
			
			carreM->entite = NULL;
			carreM->acces = 1;
			carreM->Affcase = mob->cacheChar;
			carreM->couleur = mob->cacheCouleur;
			(perso->xp)++;
			gestionXP(perso);

			oterElt(listeMobs);
		}
		suivant(listeMobs);
	}

	//tirs
	enTete(listeTirs);
	while(!horsListe(listeTirs)){
		tir = valeurElt(listeTirs);
		carreTir = (&carte->carre[tir->position->row][tir->position->col]);

		if(!tir->compteur){ //la cadance de tir permet au tir d'avancer
			if(tir->portee){ //le tire n'a pas atteint sa limite de portée
				if(!bougerEntite(tir->direction, carte, (entite_t*)tir, listeTirs)){ //collision
					coordTemp = nextCoord(tir->direction, tir->position);

					collisionTirEntite(carte, coordTemp, tir);

					oterElt(listeTirs);

					free(coordTemp);
				}
				else{ //le tir avance
					(tir->portee)--;
					tir->compteur = TIR_TICK;

					suivant(listeTirs);
				}
			}
			else{ //le tir a atteint sa limite de portée
				carreTir->Affcase = tir->cacheChar;
				carreTir->couleur = tir->cacheCouleur;
				carreTir->acces = 1;
				carreTir->entite = NULL;

				oterElt(listeTirs);
			}
		}
		else{//le tire ne progresse pas encore
			(tir->compteur)--;

			suivant(listeTirs);
		}
	}
}

void voirCarte(WINDOW* w, carte_t* carte, perso_t* perso, int maxRow, int maxCol){
	int cptX = 0;
	int cptY = 0;
	int i = perso->position->row - (maxRow/2);
	int j;
	int k = perso->position->col - (maxCol/4);

	wclear(w);

	box(w,0,0);

	//affichage carte
	for (cptX = 0; (cptX < maxRow - 2) && (i < carte->tailleCarte); cptX++, i++)
	{
		wmove(w, PADDING + cptX, PADDING*2); //place l'image dans la fenêtre
		for (j = k, cptY = 0; (cptY < maxCol/2 - 2) && (j < carte->tailleCarte); cptY++, j++)
		{
			if(i >= 0 && j >= 0){
				if(carte->carre[i][j].visited){
					if(carte->carre[i][j].entite){
						if(carte->carre[i][j].entite->typeEnt != ENT_PERSO){
							wattron(w, COLOR_PAIR(carte->carre[i][j].entite->cacheCouleur));
							wprintw(w, "%c ", carte->carre[i][j].entite->cacheChar);
							wattroff(w, COLOR_PAIR(carte->carre[i][j].entite->cacheCouleur));
						}
						else{
							wattron(w, COLOR_PAIR(carte->carre[i][j].couleur));
							wprintw(w, "%c ", carte->carre[i][j].Affcase);
							wattroff(w, COLOR_PAIR(carte->carre[i][j].couleur));
						}
					}
					else{
						wattron(w, COLOR_PAIR(carte->carre[i][j].couleur));
						wprintw(w, "%c ", carte->carre[i][j].Affcase);
						wattroff(w, COLOR_PAIR(carte->carre[i][j].couleur));
					}
				}
				else{
					wprintw(w, "  ");
				}
			}
			else{
				wprintw(w, "  ");
			}
		}
	}

	wrefresh(w);

	while(getch() != 'm'){
		usleep(30);
	}

	clear();
}

int estAffEau(char affCase){
	return (affCase == 'W' || affCase == 'D');
}

int pointExiste(carte_t* carte, int row, int col){
	int tailleCarte = carte->tailleCarte;

	return (row >= 0 && row < tailleCarte && col >= 0 && col < tailleCarte);
}