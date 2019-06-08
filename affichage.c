#include "head.h"

/** Affiche les différentes infos de tout les joueurs. **/
void affichage(tab_joueurs j, int num_joueur){
	for(int i = 0; i < j->n; ++i){
		if (i == num_joueur)
			continue;
		printf("- Joueur %d \tDistance: %d\tBonus: ", i + 1, j->nos_joueurs[i].distance);
		affichage_bonus(j, i);
		printf("\tMalus: ");
		affichage_malus(j, i);
		printf("\n");
		
	}
	aff_joueur(num_joueur + 1);
	printf("\033[0;33m\033[1m------------------------------------------\n\n");
	printf("Distance : %d \t Bonus : ", j->nos_joueurs[num_joueur].distance);
    affichage_bonus(j, num_joueur);

    printf("\tMalus : ");
    affichage_malus(j, num_joueur);

    printf("\n\n\033[0m");
    affichage_main(j, num_joueur);
	printf("\n\n");
}

/** Affiche les bonus du joueur. **/
void affichage_bonus(tab_joueurs j, int num_joueur){
	for(int i = 0; i < NB_CARTE_BONUS; ++i){
		if (j->nos_joueurs[num_joueur].bonus[i].type == 1){
			switch(j->nos_joueurs[num_joueur].malus[i].sous_type){
				case AS:
					printf("As du Volant ");
					break;
				case CITERNE:
					printf("Camion citerne ");
					break;
				case INCREVABLE:
					printf("Increvable ");
					break;
				case PRIORITAIRE:
					printf("Prioritaire ");
					break;
				default:
					break;
			}
		}
	}
}

/** Affiche les malus du joueur. **/
void affichage_malus(tab_joueurs j, int num_joueur){
    for(int i = 0; i < NB_CARTE_MALUS; ++i){
        if (j->nos_joueurs[num_joueur].malus[i].type == 2){
            switch(j->nos_joueurs[num_joueur].malus[i].sous_type){
                case ACCIDENT:
                    printf("Accident ");
                    break;
                case PANNE_ESSENCE:
                    printf("Panne d'essence ");
                    break;
                case CREVAISON:
                    printf("Crevaison ");
                    break;
                case LIMITE_VITESSE:
                    printf("Limite de Vitesse ");
                    break;
                case FEU_ROUGE:
                    printf("Feu rouge ");
                    break;
                default:
                    break;
            }
	    }
    }
}

/** Affiche la main du joueur. **/
void affichage_main(tab_joueurs j, int num_joueur){
    for(int i = 0; i < NB_CARTE; ++i){
		if (j->nos_joueurs[num_joueur].main[i].type == 0){
            printf("| ");
			switch(j->nos_joueurs[num_joueur].main[i].sous_type){
				case VINGT_CINQ:
					aff_dist("25 ", i+1);
					break;
				case CINQUANTE:
					aff_dist("50 ", i+1);
					break;
				case SOIXANTE_QUINZE:
					aff_dist("75 ", i+1);
					break;
				case CENT:
					aff_dist("100 ", i+1);
					break;
                case DEUX_CENT:
					aff_dist("200 ", i+1);
                    break;
				default:
					break;
			}
		}

		if (j->nos_joueurs[num_joueur].main[i].type == 1){
            printf("\033[1m|\033[0m ");
			switch(j->nos_joueurs[num_joueur].main[i].sous_type){
				case AS:
					aff_bonus("As du Volant", i+1);
					break;
				case CITERNE:
					aff_bonus("Camion citerne", i+1);
					break;
				case INCREVABLE:
					aff_bonus("Increvable", i+1);
					break;
				case PRIORITAIRE:
					aff_bonus("Prioritaire", i+1);
					break;
				default:
					break;
			}
		}

        if (j->nos_joueurs[num_joueur].main[i].type == 2){
            printf("| ");
			switch(j->nos_joueurs[num_joueur].main[i].sous_type){
				case ACCIDENT:
					aff_attq("Accident", i+1);
					break;
				case PANNE_ESSENCE:
					aff_attq("Panne d'essence", i+1);
					break;
				case CREVAISON:
					aff_attq("Crevaison", i+1);
					break;
				case LIMITE_VITESSE:
					aff_attq("Limite de Vitesse", i+1);
					break;
                case FEU_ROUGE:
                    aff_attq("Feu rouge", i+1);
                    break;
				default:
					break;
			}
		}
        if (j->nos_joueurs[num_joueur].main[i].type == 3){
            printf("| ");
			switch(j->nos_joueurs[num_joueur].main[i].sous_type){
				case REPARATION:
					aff_rep("Reparation", i+1);
					break;
				case ESSENCE:
					aff_rep("Essence", i+1);
					break;
				case ROUE_SECOURS:
					aff_rep("Roue de secours", i+1);
					break;
				case FIN_LIMITATION:
					aff_rep("Fin de limitation", i+1);
					break;
                case FEU_VERT:
                    aff_rep("Feu vert", i+1);
                    break;
				default:
					break;
			}
		}
	}
	printf("\033[1m|\033[0m");
}
