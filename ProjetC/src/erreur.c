#include <stdio.h>
#include <stdlib.h>
#include "erreur.h"

/**
 * \file erreur.c
 * \author Max Descomps (descomps@et.esiea.fr)
 * \brief Fonctions liées au module erreur
 * \version 0.2
 * \date 27/10/2022
 * \copyright Copyright (c) 2022
 */

void erreur(char* err_msg, erreur_t err_code){
    printf("%s\nCode erreur: %d\n", err_msg, err_code);

    exit(err_code);
}