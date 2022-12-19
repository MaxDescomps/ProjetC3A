/**
 * \file input.h
 * \author Max Descomps (descomps@et.esiea.fr)
 * \brief Fichier contenant toutes les déclarations concernant l'entrée sécurisée de données par l'utilisateur
 * \version 0.2
 * \date 1/10/2022
 * \copyright Copyright (c) 2022
 */

#pragma once

/**
 * \brief Vide le buffer de l'entrée standard
 * \author Max Descomps
 */
void viderStdin(void);

/**
 * \brief Lit une chaîne de caractères sur l'entrée standard de manière sécurisée
 * \author Max Descomps
 * \param buffer Enregistrement de la chaîne lue
 * \param taille Nombre maximum de caractères lus
 * \return La chaîne de caractères lue
 */
char* lireStr(char * buffer, int taille);

/**
 * \brief Lit un caractère sur l'entrée standard de manière sécurisée
 * \author Max Descomps
 * \return Le caractère lu
 */
char lireChar(void);

/**
 * \brief Lit un entier sur l'entrée standard de manière sécurisée
 * \author Max Descomps
 * \return L'entier lu ou zero si la valeur est incorrecte
 */
int lireInt(void);