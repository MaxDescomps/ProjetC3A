/**
 * \file erreur.h
 * \author Max Descomps (descomps@et.esiea.fr)
 * \brief Fichier contenant toutes les déclarations concernant les erreurs
 * \version 0.1
 * \date 1/10/2022
 * \copyright Copyright (c) 2022
 */

#pragma once

/**
 * \brief L'énumération des codes d'erreur du programme
 */
typedef enum{
    AUCUNE_ERREUR, /**< Aucune erreur */
    ERR_MEMOIRE,   /**< Erreur d'allocation mémoire */
    ERR_FICHIER,   /**< Erreur de fichier (écriture ou lecture impossible) */
    ERR_FCT,       /**< Erreur de fonction (bon déroulement compromis) */
    ERR_NCURSES    /**< Ncurses mal supporté */
} erreur_t;


/**
 * \brief Gère les erreurs et quitte le programme
 * \author Max Descomps
 * \param err_msg Le message d'erreur personnalisable
 * \param err_code Le code d'erreur spécifique
 */
void erreur(char* err_msg, erreur_t err_code);