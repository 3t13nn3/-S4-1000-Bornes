#include "head.h"

/**Permet de tester toutes les conditions PARADE/MALUS**/
void test_malus_parade(jeu partie,tab_joueurs J){
	J->nos_joueurs[0].demarre = 1;
	J->nos_joueurs[0].distance = 200;
	carte tmp1,tmp2;
	tmp1.type = 2; //Attaque
	tmp2.type = 3; //Parade
	for(int i = 0; i< 5; i++){
		tmp1.sous_type = i;
		J->nos_joueurs[0].malus[0] = tmp1;
		for(int k = 0; k< 5; k++){
			tmp2.sous_type = k;
			printf("----------------\ntype1--> %d\nsous type1--> %d\ntype2--> %d\nsous type2--> %d\n\n",tmp1.type,tmp1.sous_type,tmp2.type,tmp2.sous_type);		
			int erreur = jouer_carte(partie, J, &J->nos_joueurs[0], tmp2, NULL, NULL);
			if(erreur!=1)
				printf("ERROR-> %d\n\n", erreur);
		}
	}
}

/**Autre implémentation de test_malus_parade**/
void test_malus_parade2(jeu partie, tab_joueurs J){
	int fourre;
	int joueur_fourre;
	int erreur = 1;
	
	J->nos_joueurs[0].demarre = 1;
	J->nos_joueurs[1].demarre = 1;
	
	for(int i = 0; i < 5; ++i){
		J->nos_joueurs[0].main[i].type = 2;
		J->nos_joueurs[0].main[i].sous_type = i;
		J->nos_joueurs[1].main[i].type = 3;
		J->nos_joueurs[1].main[i].sous_type = i;
	}
	
	for(int i = 0; i < 5; ++i){
		for(int j = 0; j < 2; ++j){
			printf("Joueur %d \t Carte %d - %d \t Malus %d\n", j+1, J->nos_joueurs[j].main[i].type, J->nos_joueurs[j].main[i].sous_type, J->nos_joueurs[j].malus[0].sous_type);
			erreur = jouer_carte(partie, J, &J->nos_joueurs[j], J->nos_joueurs[j].main[i], &fourre, &joueur_fourre);
			if (erreur <= 0){
				printf("ERROR %d", erreur);
				--j;
			}
		}
	}
}

/**Permet de tester toutes les conditions BONUS/MALUS**/
void test_bonus_malus(jeu partie, tab_joueurs J){
	int fourre;
	int joueur_fourre;
	int erreur = 1;
	
	J->nos_joueurs[0].demarre = 1;
	for(int i = 0; i < 4; ++i){
		J->nos_joueurs[0].bonus[i].type = 1;
		J->nos_joueurs[0].bonus[i].sous_type = 1;
	}
	
	for (int i = 0; i < 5; ++i){
		J->nos_joueurs[1].main[0].type = 2;
		J->nos_joueurs[1].main[0].sous_type = i;
		erreur = jouer_carte(partie, J, &J->nos_joueurs[1], J->nos_joueurs[1].main[0], &fourre, &joueur_fourre);
		if (erreur <= 0){
			printf("ERROR %d\n", erreur);
		}
	}
}

/**Permet de tester toutes les conditions par rapport a ce que l'on peut jouer en fonction de la distance**/
void test_distance(jeu partie,tab_joueurs J){
	J->nos_joueurs[0].demarre = 1;
	J->nos_joueurs[0].distance = 200;
	carte tmp;
	tmp.type = 0;
	int k = 4;
	for(int i = 0; i< 10; i++){
		tmp.sous_type = k;
		printf("----------------\ntype--> %d\nsous type--> %d\n\n",tmp.type,tmp.sous_type);
		int erreur = jouer_carte(partie, J, &J->nos_joueurs[0], tmp, NULL, NULL);
		printf("DISTANCE %d\n", J->nos_joueurs[0].distance);
		if(erreur!=1)
			printf("ERROR-> %d\n\n", erreur);
		if(i-1%2 == 0){
			k--;
		}
	}
}