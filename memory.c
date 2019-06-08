#include "head.h"

/**
Fonction qui permet d'allouer de l'espace mémoire à un pointeur selon une taille passée en argument. 
 **/
void *my_malloc(unsigned int size) {
    void *p;
    p = malloc(size);
    if(p == NULL) {
       fprintf(stderr , "Erreur : impossible d’allouer la memoire\n");
       exit(-1);
    }
    return p;
}

/**
Fonction qui permet de réallouer de l'espace mémoire à un pointeur passé en argument selon une nouvelle taille.
**/
void *my_realloc(void *p, unsigned int size) {
    p = realloc(p, size);
    if(p == NULL) {
        fprintf(stderr , "Erreur : impossible de reallouer la memoire\n");
        exit(-1);
    }
    return p;
}

/**
Fonction qui permet de réallouer de l'espace mémoire au pointeur qui représente le tas de carte de la pioche et d'affecter une nouvelle taille à la variable qui représente le nombre de carte totale.
**/
void reserve_deck(jeu j , int newcap){ 
    j->deck = my_realloc(j->deck, newcap * sizeof(carte));//On double la capacité
    j->n = newcap;
}

/**
Fonction qui permet de réallouer de l'espace mémoire au pointeur qui représente le tableau de joueurs et d'affecter une nouvelle taille à la variable qui représente le nombre totale de joueur.
 **/
void reserve_joueurs(tab_joueurs j , int newcap){ 
    j->nos_joueurs = my_realloc(j->nos_joueurs, newcap * sizeof(joueur));
    j->n = newcap;
}
