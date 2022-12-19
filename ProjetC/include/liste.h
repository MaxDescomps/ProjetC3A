/**
 * \file liste.h
 * \author Max Descomps (descomps@et.esiea.fr)
 * \brief Déclarations relatives au type de structure liste générique
 * \version 0.1
 * \date 09/10/2022
 * \copyright Copyright (c) 2022
 */

#pragma once

/**
 * \brief Définition dy type element : un élément d'une liste.
 * \author Max Descomps
 */
typedef struct element
{
    void *valeur; /**<La valeur de l'élément, un pointeur générique*/
    struct element *pred; /**<L'élément précédant*/
    struct element *succ; /**<L'élément suivant*/
} t_element;

/**
 * \brief Définition du type liste_t : une liste générique.
 * \author Max Descomps
 */
typedef struct liste{
    t_element *flag; /**<Le drapeau (1er élément)*/
    t_element *ec; /**<L'élément courant*/
    unsigned int nb_elem; /**<Le nombre d'élément dans la liste*/
    void * (*ajout)(void *); /**<Une fonction pour ajouter un élément dans la liste*/
    void (*del)(void *); /**<Une fonction pour retirer un élément de la liste*/
}liste_t;

/**
 * \brief Fonction qui permet de créer une liste.
 * \author Max Descomps
 *
 * On peut préciser des fonction pour l'insertion et la supprésion des objets.
 *
 * Mais on ne peut pas avoir une fonction d'insertion et aucune fonction de supprésion et vice-versa.
 *
 * Par défault la liste fonctionne par référencement, pour cela il suffit de ne pas fournir de fonctions dans l'appel de la fonction.
 *
 * On attend des éléments dynamiques dans la liste
 * 
 * \param fonction_ajout La fonction qui permet d'intertion des objets, NULL sinon
 * \param f_suppresion La fonction qui permet la suppresion des objets, NULL sinon
 * \return La liste qui vient d'être crée, NULL s'il y a eu une erreur
 */
extern liste_t *initListe(void *(*fonction_ajout)(void *), void (*f_suppresion)(void *));

/**
 * \brief Fonction booléenne qui permet de savoir si la liste est vide.
 * \author Max Descomps
 * 
 * \param to_verify La liste que l'on doit vérifier
 * \return Vrai si la liste est vide, faux sinon
 */
extern int listeVide(const liste_t * const to_verify);

/**
 * \brief Fonction booléenne qui permet de savoir si ll'on est actuellement hors de la liste.
 * \author Max Descomps
 * 
 * \param to_verify La liste que l'on doit vérifier
 * \return Vrai si on se trouve en dehors de la liste, faux sinon
 */
extern int horsListe(const liste_t * const to_verify);

/**
 * \brief Fonction qui permet de se placer en tête de la liste.
 * \author Max Descomps
 * 
 * \param mylist La liste dans laquelle on se déplace
 */
extern void enTete(liste_t *mylist);

/**
 * \brief Fonction qui permet de se placer en queue de la liste.
 * \author Max Descomps
 * 
 * \param mylist La liste dans laquelle on se déplace
 */
extern void enQueue(liste_t *mylist);

/**
 * \brief Fonction qui permet de passer à l'élément suivant dans la liste.
 * \author Max Descomps
 * 
 * \param mylist La liste dans laquelle on se déplace
 */
extern void suivant(liste_t *mylist);

/**
 * \brief Fonction qui permet de passer à l'élément suivant dans la liste.
 * \author Max Descomps
 * 
 * \param mylist La liste dans laquelle on se déplace
 */
extern void precedent(liste_t *mylist);

/**
 * \brief Fonction qui renvoie l'élément courant.
 * \author Max Descomps
 * 
 * \param mylist La liste dont on veut l'élément
 * \return L'élément que l'on convoite
 */
extern void * valeurElt(const liste_t *const mylist);

/**
 * \brief Fonction qui permet de modifier l'élément courant. 
 * \author Max Descomps
 * 
 * ATTENTION : si les élément sont placés dans la liste par référencement cela détruira l'élément précédent !
 * 
 * \param mylist La liste donc on veut modifier l'élément courant
 * \param v L'élément à mettre à la place de l'ancien
 */
extern void modifElt(liste_t *mylist, void *v);

/**
 * \brief Fonction qui permet de supprimer un élément de la liste.
 * \author Max Descomps
 *
 * ATTENTION : si les élements sont placés dans la liste par référencement cela détruira l'élément (ne pas y accéder après) !
 *
 * On attend des éléments dynamiques dans la liste.
 *
 * \param mylist La liste dont on veut oter l'éléement
 */
extern void oterElt(liste_t *mylist);

/**
 * \brief Fonction qui permet d'ajouter un élément à droite de l'élément courant.
 * \author Max Descomps
 * 
 * \param mylist La liste où on veut ajouter l'élément
 * \param v L'élément que l'on veut ajouter
 */
extern void ajoutDroit(liste_t *mylist, void *v);

/**
 * \brief Fonction qui permet d'ajouter un élément à gauche de l'élément courant.
 * \author Max Descomps
 *
 * \param mylist La liste où on veut ajouter l'élément
 * \param v L'élément que l'on veut ajouter
 */
extern void ajoutGauche(liste_t *mylist, void *v);

/**
 * \brief Fonction qui renvoie le nombre d'éléments dans la liste.
 * \author Max Descomps
 * 
 * \param mylist La liste dont on veut conaitre le nombre d'éléments
 * \return Le nombre d'élements dans la liste
 */
extern unsigned int tailleListe(const liste_t *const mylist);

/**
 * \brief Fonction qui supprimme tout les éléments de la liste. 
 * \author Max Descomps
 * 
 * ATTENTION : si les éléments sont insérés par référencement, ils seront tous détruits ! 
 * 
 * On attend des éléments dynamiques dans la liste.
 * 
 * \param mylist La liste que l'on veut vider
 */
extern void viderListe(liste_t *mylist);

/**
 * \brief Détruit une liste en détruisant tout ses éléménts.
 * \author Max Descomps
 * \param liste Adresse de la liste
 */
extern void detruireListe(liste_t ** liste);

/**
 * \brief Affiche une liste d'objets génériques.
 * \author Max Descomps 
 * \param liste Pointeur sur la liste
 */
void afficherListe(liste_t * liste);

/**
 * \brief Fonction qui permet de selectionner l'élément courant à partir d'un élément précis.
 * \author Max Descomps
 * 
 * \param liste La liste dans laquelle on veut faire la recherche
 * \param element L'élément que l'on veut rechercher
 * \param f_egalite Une fonction de comparaison qui renvoie vrai si les deux valeurs sont égales ou NULL si on veut comparer les adresses
 * \return Vrai si l'élément à été trouvé
 */
int chercherElement(liste_t *liste, void *element, int (*f_egalite)(void *, void *));