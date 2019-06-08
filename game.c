#include "head.h"

/**
Fonction qui permet de distribuer 7 cartes à chaque joueurs. 
 **/
void distribute(jeu game, tab_joueurs players){
	int i,j;
	for(i = 0; i< players->n; i++){
		for(j = 0; j<NB_CARTE; j++){
			players->nos_joueurs[i].main[j]=pop_back_carte(game);
		}
	}
}

/**
Fonction qui permet d'ajouter un joueur à la liste des joueurs.
**/
void push_back_joueur(tab_joueurs j, joueur p){
	j->n++;
	j->nos_joueurs[j->n] = p;	
}

/**
Fonction qui permet d'ajouter une carte à la fin de la pioche.
 **/
void push_back_carte(jeu j, carte c){
	j->n++;
	j->deck[j->n] = c;
}

/**
Fonction qui permet d'ajouter une carte au début de la pioche.
 **/
void push_front_carte(jeu j, carte c){  
	int i;
	j->n++;
	for(i = j->n; i >= 0; i--)
		j->deck[i+1]=j->deck[i];
	j->deck[0] = c;
}

/**
Fonction qui retourne la dernière carte de la pioche et la retire du tas de carte.
**/
carte pop_back_carte(jeu j) {
  carte tmp;
  j->n--;
  if(j->n < 0) {
    fprintf(stderr , "--pop_back_carte-- Plus de cartes dans le paquet.\n");
    exit(-1);
  } 
  tmp = j->deck[j->n];
  return tmp;
}

/**
Fonction qui retourne la première carte de la pioche et la retire du tas de carte.
**/
carte pop_front_carte(jeu j){
	int i;
	carte tmp = j->deck[0];
	for(i = 0; i < j->n-1; i++)
		j->deck[i]=j->deck[i+1];
    j->n--; 
    return tmp;
}

/**
Fonction qui permet de mélanger aléatoirement le paquet de cartes. Le paquet de cartes obtenu constituera la pioche du jeu.
**/
void shuffle_jeu(jeu * j){
	srand(time(NULL));
    if((*j)->n > 1){
        int i;
        for (i = 0; i < (*j)->n - 1; i++){
        	int k = i + rand() / (RAND_MAX / ((*j)->n - i) + 1);
        	carte t =(*j)->deck[k];
	        (*j)->deck[k] = (*j)->deck[i];
	        (*j)->deck[i] = t;
        }
    }
}

/**
Fonction qui vérifie si la distance du joueur, passé en argument, a atteint 1000Km.
**/
int verif_win(joueur j){
	if(j.distance == 1000)
		return 1;
	else
		return 0;
}
