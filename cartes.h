#define aff_joueur(i) printf("\033[0;33m\033[1m\033[5m\n\n\t\tJoueur %d \n\033[0m", i)
#define aff_dist(dist, i) printf("\033[0;44m\033[1m%s [%d]\033[0m ", dist, i)
#define aff_bonus(bonus, i) printf("\033[0;45m\033[1m%s [%d]\033[0m ", bonus, i)
#define aff_attq(attq, i) printf("\033[0;41m\033[1m%s [%d]\033[0m ", attq, i)
#define aff_rep(rep, i) printf("\033[0;42m\033[1m%s [%d]\033[0m ", rep, i)


enum Distances
{
   VINGT_CINQ = 0, CINQUANTE = 1, SOIXANTE_QUINZE = 2, CENT = 3, DEUX_CENT = 4
};


enum Bonus
{
   AS = 0, CITERNE = 1, INCREVABLE = 2, PRIORITAIRE = 3,
};


enum Attaques
{
   ACCIDENT = 0, PANNE_ESSENCE = 1, CREVAISON = 2, LIMITE_VITESSE = 3, FEU_ROUGE = 4
};


enum Parades
{
   REPARATION = 0, ESSENCE = 1, ROUE_SECOURS = 2, FIN_LIMITATION = 3, FEU_VERT = 4
};
