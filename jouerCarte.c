#include "head.h"

/** Permet de jouer la carte choisis. **/
int jouer_carte(jeu game, tab_joueurs tabJ, joueur * j, carte crt, int * index_fourre, int* joueur_fourre){
	int a, m;
	switch(crt.type){
		case 0:
			m = demarrer(j);
			if (m == 1){
				if(add_distance(j, crt) == 1)
					return 1;
				else if(add_distance(j, crt) == 0)
					return ERROR_200;
				else if(add_distance(j, crt) == 3)
					return ERROR_LIMITE_DE_VITESSE;
				else if(add_distance(j, crt) == 4)
					return ERROR_COUP_NON_VALIDE;
				else
					return ERROR_1000;
			}else{
				return ERROR_COUP_NON_VALIDE;
			}
		case 1:
			add_bonus(j, crt);
			return 1;
		case 2:
			while(1){
				printf("A quel joueur voulez-vous la poser ? ");
				scanf("%d", &a);
				if(&tabJ->nos_joueurs[a-1] == j)
					return ERROR_MALUS_MEME_JOUEUR;
				m = verif_malus(&tabJ->nos_joueurs[a-1], crt);
				*index_fourre = verif_coup_fourre(&tabJ->nos_joueurs[a-1], crt);
				printf("index %d\n",*index_fourre);
				if (m == 0){
					if(!verif_bonus(&tabJ->nos_joueurs[a-1],crt)){
						if(*index_fourre != -1){
							coup_fourre(&tabJ->nos_joueurs[a-1],crt);
							*joueur_fourre = a - 1;
							return COUP_FOURRE;
						}
						else{
							add_malus(&tabJ->nos_joueurs[a-1], crt);
							return 1;
						}
					}
					else
						return ERROR_MALUS_IMPOSSIBLE;
				}else{
					return ERROR_MALUS_IMPOSSIBLE;
				}
			}
		case 3:
			m = verif_repare(j, crt);
			if (m == 1){
				repare(j);
				return 1;
			}else if (m == 2){
				j->demarre = 1;
				return 1;
			}else{
				return ERROR_COUP_NON_VALIDE;
			}
		default:
			break;
	}
	return ERROR_COUP_NON_VALIDE;
}

/** Vérifie si le joueur a déjà démarrer ( feu vert ) ou non. **/
int demarrer(joueur * j){
	if (j->demarre == 1){
		return 1;
	}
	return 0;
}

/*int add_distance(joueur * j, carte crt){
	switch(crt.sous_type){
		case 0:
			for(int i = 0; i<NB_CARTE_MALUS; i++){
				if(j->malus[i].type == 2 &&
				  (j->malus[i].sous_type == 0 || j->malus[i].sous_type == 1 || j->malus[i].sous_type == 2 || j->malus[i].sous_type == 4))
					return 4;
			}
			j->distance += 25;
			break;
		case 1:
			for(int i = 0; i<NB_CARTE_MALUS; i++){
				if(j->malus[i].type == 2 &&
				  (j->malus[i].sous_type == 0 || j->malus[i].sous_type == 1 || j->malus[i].sous_type == 2 || j->malus[i].sous_type == 4))
					return 4;
			}
			if(j->distance + 50 <=WIN_LIMIT){
				j->distance += 50;
			}
			else
				return 2;
			break;
		case 2:
			if(j->distance + 75 <=WIN_LIMIT){
				for(int i = 0; i<NB_CARTE_MALUS; i++){
					if(j->malus[i].type == 2 &&
					  (j->malus[i].sous_type == 0 || j->malus[i].sous_type == 1 || j->malus[i].sous_type == 2 || j->malus[i].sous_type == 4))
						return 4;
					if(j->malus[i].type == 2 && j->malus[i].sous_type == 3)
						return 3;
				}
				j->distance += 75;
			}
			else
				return 2;
			break;
		case 3:
			if(j->distance + 100 <=WIN_LIMIT){
				for(int i = 0; i<NB_CARTE_MALUS; i++){
					if(j->malus[i].type == 2 &&
					  (j->malus[i].sous_type == 0 || j->malus[i].sous_type == 1 || j->malus[i].sous_type == 2 || j->malus[i].sous_type == 4))
						return 4;
					if(j->malus[i].type == 2 && j->malus[i].sous_type == 3)
						return 3;
				}
				j->distance += 100;
			}
			else
				return 2;
			break;
		case 4:
			if(j->distance + 200 <=WIN_LIMIT){
				for(int i = 0; i<NB_CARTE_MALUS; i++){
					if(j->malus[i].type == 2 &&
					  (j->malus[i].sous_type == 0 || j->malus[i].sous_type == 1 || j->malus[i].sous_type == 2 || j->malus[i].sous_type == 4))
						return 4;
					if(j->malus[i].type == 2 && j->malus[i].sous_type == 3)
						return 3;
				}
				if(j->deuxcent < 2){
					j->distance += 200;
					j->deuxcent++;
				}
				else
					return 0;
			}
			else
				return 2;
			break;
		default:
			break;
	}
	return 1;
}*/

/** Ajoute la distance au jouer en vérifiant si la carte peut être joué. **/
int add_distance(joueur * j, carte crt){
		int d;
		for(int i = 0; i<NB_CARTE_MALUS; i++){
			if(j->malus[i].type == 2 && 
				(j->malus[i].sous_type == 0 || j->malus[i].sous_type == 1 || j->malus[i].sous_type == 2 || j->malus[i].sous_type == 4))
				return 4;
			if(j->malus[i].type == 2 && j->malus[i].sous_type == 3)
				if (25 * (crt.sous_type + 1) > 50)
					return 3;
		}
		d = j->distance + 25 * (crt.sous_type + 1);
		if(d <= WIN_LIMIT){
			if((25 * (crt.sous_type + 1)) == 125){
				if (j->deuxcent < 2){
					j->distance = d;
					j->deuxcent++;
					j->distance += 200;
					return 1;
				}
				else{
					return 0;
				}
			}
			else
				j->distance = d;
		}
		else
			return 2;
	return 1;
}

/** Vérifie si le joueur possède une carte bonus. **/
int verif_bonus(joueur * j, carte crt){
	for (int i = 0; i < NB_CARTE_BONUS; ++i){
		if(j->bonus[i].sous_type == crt.sous_type)
			return 1;
	}
	return 0;
}

/** Ajoute une carte bonus au joueur. **/
void add_bonus(joueur * j, carte crt){
	int i;
	for(i = 0; i < NB_CARTE_BONUS; ++i){
		if(j->bonus[i].type == -1)
			break;
	}
	j->bonus[i] = crt;
	
	if (j->malus[0].sous_type == crt.sous_type)
		repare(j);
	if (crt.sous_type == 3 && j->malus[0].sous_type == 4)
		repare(j);
	if(j->distance + 100 <= WIN_LIMIT){
		j->distance+=100;
	}
}

/** Vérifie si le joueur possède un malus. **/
int verif_malus(joueur * j, carte crt){
	if (j->demarre == 1){
		if (j->malus[0].type != -1)
        	return 1;
   		return 0;
	}
	if (crt.sous_type == 3){
		if (j->malus[1].type != -1)
			return 1;
		return 0;
	}
	return 1;
}

/** Ajoute une carte malus à un joueur. **/
void add_malus(joueur * j, carte crt){
	j->malus[0] = crt;
}

/** Vérifie si le joueur peut jouer une carte réparation correspondant au malus. **/
int verif_repare(joueur * j, carte crt){
	for (int i = 0; i < NB_CARTE_MALUS; ++i){
		if(j->malus[i].sous_type == crt.sous_type)
			return 1;
	}
	if(j->demarre == 0 && crt.sous_type == 4)
		return 2;
	return 0;
}

/** Retire le malus du joueur. **/
void repare(joueur * j){
	carte tmp;
	tmp.type = -1;
	tmp.sous_type = -1;

	j->malus[0] = tmp;
}

/** Vérifie si un coup fourré peut être effectué. **/
int verif_coup_fourre(joueur * j, carte crt){
	for(int i = 0; i < NB_CARTE; ++i){
		if (j->main[i].type == 1 && j->main[i].sous_type == crt.sous_type)
			return i;
	}
	return -1;
}

/** Effectue le coup fourré. **/
void coup_fourre(joueur * j, carte crt){
	int i;
	for (i = 0; i < NB_CARTE; ++i){
		if (j->main[i].type == 1 && j->main[i].sous_type == crt.sous_type)
			break;
	}
	add_bonus(j, j->main[i]);
	if(j->distance + 300 <= WIN_LIMIT){
		j->distance+=300;
	}
}