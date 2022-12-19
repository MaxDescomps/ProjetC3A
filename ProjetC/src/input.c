#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "input.h"

/**
 * \file input.c
 * \author Max Descomps (descomps@et.esiea.fr)
 * \brief Fonctions liées au module input
 * \version 0.2
 * \date 27/10/2022
 * \copyright Copyright (c) 2022
 */

void viderStdin(void)
{
    int c;
    do{
        c = getchar();
    } while (c != '\n' && c != EOF);
}

char* lireStr(char * buffer, int taille)
{
    char * result = fgets(buffer, taille, stdin);

    if (result != NULL)
    {
        char * lf = strchr(buffer, '\n'); /* On cherche le caractère '\n'. */

        if (lf != NULL) /* S'il est présent, ... */
            *lf = '\0'; /* ... on le supprime    */
        else
        {
            viderStdin(); /* On vide le buffer de l'entrée standard */
        }
    }
    return result;
}

char lireChar()
{
    char result;
    
    do{
        result = getchar();
    }while(result == '\n' || result == EOF);

    viderStdin(); /* On vide le buffer de l'entrée standard */

    return result;
}

int lireInt()
{
    char str[30];
    lireStr(str, 30);

    //empêche de saisir des caractères non numériques
    return atoi(str);
}