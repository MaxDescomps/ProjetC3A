#include <stdlib.h>
#include <stdio.h>
#include "liste.h"
#include "erreur.h"

/**
 * \file liste.c
 * \author Max Descomps (descomps@et.esiea.fr)
 * \brief Fonctions relatives au type de structure liste générique
 * \version 0.1
 * \date 09/10/2022
 * \copyright Copyright (c) 2022
 */

liste_t * initListe(void *(*fonction_ajout)(void *), void (*fonction_suppresion)(void *)){
    if(fonction_ajout == NULL)
        if(fonction_suppresion != NULL)
            return NULL;
    if(fonction_suppresion == NULL)
        if(fonction_ajout != NULL)
            return NULL;

    liste_t *new = malloc(sizeof(liste_t));
    if (!(new))
        erreur("Plus de mémoire", ERR_MEMOIRE);

    new->flag = malloc(sizeof(t_element));
    if (!(new->flag))
        erreur("Plus de mémoire", ERR_MEMOIRE);

    new->flag->pred = new->flag;
    new->flag->succ = new->flag;
    new->ec = new->flag;
    new->nb_elem = 0;
    new->ajout = fonction_ajout;
    new->del = fonction_suppresion;

    return new;
}

int horsListe(const liste_t * const liste) {
    return liste->ec == liste->flag;
}

int listeVide(const liste_t * const liste) {
    return (liste->flag->pred == liste->flag);
}

void enQueue(liste_t *liste){
    if (!listeVide(liste))
        liste->ec = liste->flag->pred;
}

void enTete(liste_t *liste){
    if (!listeVide(liste))
        liste->ec = liste->flag->succ;
}

void precedent(liste_t *liste){
    if (!horsListe(liste))
        liste->ec = liste->ec->pred;
}

void suivant(liste_t *liste){
    if (!horsListe(liste))
        liste->ec = liste->ec->succ;
}

void * valeurElt(const liste_t * const liste){
    if (!horsListe(liste))
        return (liste->ec->valeur);

    return NULL;
}

void modifElt(liste_t *liste, void * v)
{
    if (!horsListe(liste)){
            if(liste->del == NULL){
                // free(liste->ec->valeur); elem static
                liste->ec->valeur = v;
            }
            else{
                liste->del(&liste->ec->valeur);
                liste->ajout(liste->ec->valeur);
            }
    }
        else
            liste->ec->valeur = liste->ajout(v);
}

void oterElt(liste_t *liste){
    t_element *t;

    if (!horsListe(liste))
    {
        t = liste->ec;
        suivant(liste);
        liste->ec->pred = t->pred;
        t->pred->succ = liste->ec;
        if(liste->del != NULL){
            liste->del(&t->valeur);
        }
        (liste->nb_elem)--;

        free(t);
    }
}

void ajoutDroit(liste_t *liste, void * v){
    t_element *t;

    t = malloc(sizeof(t_element));
    if (!t)
        erreur("Plus de mémoire", ERR_MEMOIRE);

    if(liste->ajout == NULL){
        t->valeur = v;
    }
    else
        t->valeur = liste->ajout(v);

    t->pred = liste->ec;
    t->succ = liste->ec->succ;
    (liste->ec->succ)->pred = t;
    liste->ec->succ = t;
    liste->ec = t;
    (liste->nb_elem)++;
}

void ajoutGauche(liste_t *liste, void * v){
    t_element *t;

    t = malloc(sizeof(t_element));
    if (!t)
        erreur("Plus de mémoire", ERR_MEMOIRE);

    if (liste->ajout == NULL)
        t->valeur = v;
    else
        t->valeur = liste->ajout(v);
    t->succ = liste->ec;
    t->pred = liste->ec->pred;
    (liste->ec->pred)->succ = t;
    liste->ec->pred = t;
    liste->ec = t;
    (liste->nb_elem)++;
}

unsigned int tailleListe(const liste_t * const liste){
    return liste->nb_elem;
}

void viderListe(liste_t *liste){

    enTete(liste);
    while(!horsListe(liste)){
        oterElt(liste);
    }
}

void detruireListe(liste_t ** liste){

    if(!(*liste))
        return;

    viderListe(*liste);

    free((*liste)->flag);

    free(*liste);
    *liste = NULL;
}

int chercherElement(liste_t * liste, void * element, int (*f_egalite)(void *, void *)){
    
    if(listeVide(liste))
        return 0;

    enTete(liste);

    while(!horsListe(liste)){
        if(f_egalite == NULL){
            if(valeurElt(liste) == element)
                return 1;
        }
        else{
            if(f_egalite(valeurElt(liste), element))
                return 1;
        }

        suivant(liste);
    }

    return 0;
}