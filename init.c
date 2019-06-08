#include "head.h"

/**Alloue la place pour une structure Jeu * (jeu). Il faut absolument 
allouer cette structure avant de reserver la place pour notre Jeu::deck 
de cartes avec la fonction 'reserve_deck()'**/
jeu new_jeu(){ 
	jeu j = my_malloc(sizeof(jeu));
    j->deck = my_malloc(sizeof(carte));
    j->n = 0;
    return j;
}

/**Alloue la place pour une structure Tab_Joueurs * (tab_joueurs). Il faut absolument allouer cette structure avant de reserver la place pour notre tableau de joueurs avec la fonction 'reserve_joueurs()'**/
tab_joueurs new_tab_joueurs(){
	tab_joueurs j = my_malloc(sizeof(tab_joueurs));

    j->nos_joueurs = my_malloc(sizeof(joueur));
    j->n = 0;
    return j;
}

/**Initialise tout les Joueur(s) de notre Tab_Joueurs * (tab_joueurs).
Nous initialisons tout les champs à 0, sauf Carte::type && Carte::sous_type à -1.**/
void init_joueurs(tab_joueurs j){
	carte tmp;
	tmp.type = -1;
	tmp.sous_type = -1;
	for(int i = 0; i < j->n; ++i){
		j->nos_joueurs[i].distance = 0;
		j->nos_joueurs[i].demarre = 0;
		j->nos_joueurs[i].tour = 0;
		j->nos_joueurs[i].deuxcent = 0;
		
		for (int k = 0; k < NB_CARTE_BONUS; ++k){
			j->nos_joueurs[i].bonus[k] = tmp;
		}
		for (int k = 0; k < NB_CARTE_MALUS; ++k){
			j->nos_joueurs[i].malus[k] = tmp;
		} 
	}
}

/**Rempli notre Jeu::deck de Carte(s) avec toutes les cartes dont nous avont besoins, selon leurs types.
Il y en a 106, toutes cartes confondus.**/
void init(jeu mon_jeu){
	int i;
	carte tmp;
	i = 0;

	/*Carte km*/
	tmp.type = 0;
	// 25 km
	tmp.sous_type = 0;
	while(i < 30){
		if(i == 10 ||i == 20)
			tmp.sous_type++;
		mon_jeu->deck[i] = tmp;
		++i;
	}
	tmp.sous_type = 3;
	while(i < 42){
		mon_jeu->deck[i] = tmp;
		++i;
	}
	tmp.sous_type = 4;
	while(i < 46){
		mon_jeu->deck[i] = tmp;
		++i;
	}
	/*FIN--Carte km*/

	/*Carte Bonus*/
	tmp.type++;
	tmp.sous_type = 0;
	while(i < 50){
		mon_jeu->deck[i] = tmp;
		tmp.sous_type++;
		++i;
	}
	/*FIN--Carte Bonus*/

	/*Carte Attaque*/
	tmp.type++;
	tmp.sous_type = 0;
	while(i < 59){
		if(i == 53 || i == 56)
			tmp.sous_type++;
		mon_jeu->deck[i] = tmp;
		++i;
	}
	tmp.sous_type++;
	while(i < 63){
		mon_jeu->deck[i] = tmp;
		++i;
	}
	tmp.sous_type++;
	while(i < 68){
		mon_jeu->deck[i] = tmp;
		++i;
	}
	/*FIN--Carte Attaque*/

	/*Carte Parade*/
	tmp.type++;
	tmp.sous_type = 0;
	while(i < 92){
		if(i == 74 || i == 80 || i == 86)
			tmp.sous_type++;
		mon_jeu->deck[i] = tmp;
		++i;
	}
	tmp.sous_type++;
	while(i < 106){
		mon_jeu->deck[i] = tmp;
		++i;
	}
	/*FIN--Carte Parade*/

}