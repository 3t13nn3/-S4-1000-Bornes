#include "head.h"

/***********************************/
/*			 PIMP MY GAME		   */
/*		                           */	        			
/*		     .-'""""""'-.          */
/*		   /              \        */
/*		 /                  \      */
/*		+--------------------+     */
/*		|                    |     */
/*		|        1000        |     */
/*		|       BORNES       |     */
/*		|                    |     */
/*		|                    |     */
/*		|                    |     */
/*		+--------------------+     */
/*		                           */
/***********************************/

/** Contient la boucle la principale. **/
int main(){
	int win = 0;
	int erreur = 2;
	int coup = -1;
	int fourre;
	int joueur_fourre;
	int nb_joueurs = 0;
	int tour_joueur = 0;
	jeu partie = new_jeu();
	tab_joueurs J = new_tab_joueurs();
	reserve_deck(partie,106);
	
	#ifdef TEST
		nb_joueurs = 2;
	#else
		while(nb_joueurs < 2 || nb_joueurs > 8){
			system("clear");
			printf("Combien de joueurs pour cette partie ?: ");
			scanf("%d",&nb_joueurs);
		}
	#endif
	
	reserve_joueurs(J,nb_joueurs);
	init(partie);
	shuffle_jeu(&partie);

	init_joueurs(J);

	#ifdef TEST
		printf("\n---test_malus_parade---\n");
		test_malus_parade(partie, J);
		printf("\n---test_malus_parade2---\n");
		test_malus_parade2(partie,J);
		printf("\n---test_bonus_malus---\n");
		test_bonus_malus(partie, J);
		printf("\n---test_distance---\n");
		test_distance(partie,J);
		exit(0);
	#endif

	distribute(partie,J);	

	while(!win){
		if(partie->n == 0){
			//system("clear");
			int tmp = 0, i_tmp = 0, i;
			for(i=0; i< J->n; i++){
				if(J->nos_joueurs[i].distance > tmp){
					tmp = J->nos_joueurs[i].distance;
					i_tmp = i;
				}
			}
			printf("\033[0;32m\033[1mIl n'y a plus de carte, le Joueur %d est ke meilleur avec une distance de %d.\033[0m\n\n", i_tmp, J->nos_joueurs[i_tmp].distance);
			break;
		}
		while(coup < 0 || coup >= NB_CARTE +1){
			system("clear");
			if(erreur == ERROR_COUP_NON_VALIDE){
				printf("\033[0;31m\033[1m/!\\Vous ne pouvez pas jouer cette carte./!\\\033[0m\n\n");
				erreur=1;
			}
			else if(erreur == ERROR_MALUS_IMPOSSIBLE){
				printf("\033[0;31m\033[1m/!\\Vous ne pouvez pas mettre de malus a ce joueur./!\\\033[0m\n\n");
				erreur=1;
			}
			else if(erreur == ERROR_200){
				printf("\033[0;31m\033[1m/!\\Vous ne pouvez pas mettre plus de deux 200./!\\\033[0m\n\n");
				erreur=1;
			}
			else if(erreur == ERROR_1000){
				printf("\033[0;31m\033[1m/!\\Vous ne pouvez pas depasser 1000 bornes./!\\\033[0m\n\n");
				erreur=1;
			}
			else if(erreur == COUP_FOURRE){
				printf("\033[0;35m\033[1m/!\\COUP FOURRÉ/!\\\033[0m\n\n");
				erreur=1;
			}
			else if(erreur == ERROR_MALUS_MEME_JOUEUR){
				printf("\033[0;31m\033[1m/!\\Impossible de se mettre un malus sois même./!\\\033[0m\n\n");
				erreur=1;
			}
			else if(erreur == ERROR_LIMITE_DE_VITESSE){
				printf("\033[0;31m\033[1m/!\\Limitation de vitesse (25 ou 50 uniquement)./!\\\033[0m\n\n");
				erreur=1;
			}
			else
				printf("\n\n");
			affichage(J, tour_joueur % nb_joueurs);
			printf("Quel carte voulez vous jouer ? (0 pour defosser) ");
			scanf("%d",&coup);
		}
		if(coup == 0){
			int a;
			printf("De quelle carte voulez vous vous defosser ? ");
			scanf("%d", &a);
			defosse(partie,&J->nos_joueurs[tour_joueur % nb_joueurs], a-1);
			tour_joueur++;
		}
		else{
			erreur = jouer_carte(partie, J, &J->nos_joueurs[tour_joueur % nb_joueurs], J->nos_joueurs[tour_joueur % nb_joueurs].main[coup-1], &fourre, &joueur_fourre);
			if(partie->n > 0 && erreur == 1){
				if(defosse(partie, &J->nos_joueurs[tour_joueur % nb_joueurs], coup-1).type != 1){//si la carte est pas un bonus
					win = verif_win(J->nos_joueurs[tour_joueur % nb_joueurs]);
					if(!win)
						tour_joueur++;
				}
			}
			else if(partie->n > 0 && erreur == COUP_FOURRE){
				defosse(partie, &J->nos_joueurs[joueur_fourre], fourre);
				if(defosse(partie, &J->nos_joueurs[tour_joueur % nb_joueurs], coup-1).type != 1){//si la carte est pas un bonus
					win = verif_win(J->nos_joueurs[tour_joueur % nb_joueurs]);
					if(!win)
						tour_joueur+=joueur_fourre-1;
				}
			}
		}
		printf("\n");
		coup = -1;
	}
	system("clear");
	printf("\033[0;32m\033[1mBravo, le joueur %d à gagné !\n\n", (tour_joueur % nb_joueurs)+1);
	for(int i=0; i< J->n; i++){
		printf("Joueur %d : %dkm\n", i + 1, J->nos_joueurs[i].distance );
	}
	return 0;
}
