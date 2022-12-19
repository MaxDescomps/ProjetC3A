/**
 * \file matiere.h
 * \author Max Descomps (descomps@et.esiea.fr)
 * \brief Fichier contenant les déclarations des matières
 * \version 0.1
 * \date 18/10/2022
 * \copyright Copyright (c) 2022
 */

#pragma once

/**
 * \brief L'énumération des codes couleurs
 */
typedef enum {
    BASE,     /**< Aucune couleur ajoutée */
    HERBE,    /**< Couleur de l'herbe */
    PLANTE,    /**< Couleur d'une plante */
    ROCHE,    /**< Couleur de la roche */
    EAU,      /**< Couleur de l'eau */
    SABLE,    /**< Couleur du sable */
    PAISIBLE, /**< Couleur des Paisibles */
    HOSTILE,  /**< Couleur des hostiles */
    PERSO,    /**< Couleur du perso */
    TIR,      /**< Couleur des tirs */
    TERRE,    /**< Couleur de la terre */
    C_CONSO,    /**< Couleur d'un consommable */
} matiere_t;