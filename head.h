#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "cartes.h"

//#define TEST
#define NB_CARTE 7
#define NB_CARTE_MALUS 2
#define NB_CARTE_BONUS 4
#define WIN_LIMIT 1000
#define ERROR_COUP_NON_VALIDE 0
#define ERROR_MALUS_IMPOSSIBLE -1
#define ERROR_200 -2
#define ERROR_1000 -3
#define COUP_FOURRE -4
#define ERROR_MALUS_MEME_JOUEUR -5
#define ERROR_LIMITE_DE_VITESSE -6

struct Carte{
	int type; //Type de la carte
	int sous_type; // Sous type de la carte
};
typedef struct Carte carte;

struct Joueur{
	int demarre;
	int distance;
	int tour;
	int deuxcent;
	carte malus[NB_CARTE_MALUS];
	carte bonus[NB_CARTE_BONUS];
	carte main[NB_CARTE];
};
typedef struct Joueur joueur;

struct Tab_Joueurs{
/*Tableau comportant nos joueurs*/
	int n;
	joueur * nos_joueurs;
};
typedef struct Tab_Joueurs * tab_joueurs;

struct Jeu{
/*Tableau comportant nos cartes*/
	int n;
	carte * deck;
};
typedef struct Jeu * jeu;

/*GAME.C*/
///Ajoute une Carte à la fin.
void push_back_carte(jeu, carte);
///Ajoute une Carte au début.
void push_front_carte(jeu, carte);
///Enlève la première carte.
carte pop_front_carte(jeu);
///Enlève la dernière carte.
carte pop_back_carte(jeu);
///Ajoute un Joueur à la fin.
void push_backJoueur(tab_joueurs, joueur);
///Mélange le Jeu::deck.
void shuffle_jeu(jeu *);
///Distribue les cartes de Jeu::deck.
void distribute(jeu,tab_joueurs);
///Vérifie si on à gagné.
int verif_win(joueur);

/*JOUERCARTE.C*/
///Permet de jouer une Carte.
int jouer_carte(jeu, tab_joueurs, joueur *, carte, int *, int *);
///Vérifie si le Joueur à démarré.
int demarrer(joueur *);
///Ajoute la distance à un Joueur.
int add_distance(joueur *, carte);
///Vérifie les Joueur::bonus.
int verif_bonus(joueur *, carte);
///Ajoute un bonus à un Joueur.
void add_bonus(joueur *, carte);
///Vérifie les Joueur::malus.
int verif_malus(joueur *, carte crt);
///Ajoute un malus à un Joueur.
void add_malus(joueur *, carte);
///Vérifie si le Joueur peut jouer une carte parade.
int verif_repare(joueur *, carte);
///Retire le malus du Joueur.
void repare(joueur *);
///Vérifie si un coup fourré peut être effectuer.
int verif_coup_fourre(joueur *, carte);
///Applique le coup fourré.
void coup_fourre(joueur *, carte);

/*INIT.C*/
///Initialise les Joueur(s) dans Tab_Joueur.
void init_joueurs(tab_joueurs);
///Initialise le jeu.
void init(jeu);
///Créer une nouvelle structure Jeu.
jeu new_jeu();
///Créer une nouvelle structure Tab_Joueur.
tab_joueurs new_tab_joueurs();

/*MEMORY.C*/
///Malloc simplifié.
void *my_malloc(unsigned int);
///Realloc simplifié.
void *my_realloc(void *, unsigned int);
///Réserve la mémoire pour le Jeu::deck.
void reserve_deck(jeu, int);
///Réserve la mémoire pour le Tab_Joueur.
void reserve_joueurs(tab_joueurs, int);

/*PLAYER.C*/
///Défosse une carte.
carte defosse(jeu, joueur*, int);

/*AFFICHAGE.C*/
///Affichage principal.
void affichage(tab_joueurs, int);
///Affichage de la main.
void affichage_main(tab_joueurs, int);
///Affichage des bonus.
void affichage_bonus(tab_joueurs, int);
///Affichages des malus.
void affichage_malus(tab_joueurs, int);

/*TEST.C*/
///Test qu'il n'y a pas de conflit entre Malus et Parade
void test_malus_parade(jeu, tab_joueurs);
///Test qu'il n'y a pas de conflit entre Malus et Parade
void test_malus_parade2(jeu, tab_joueurs);
///Test qu'il n'y a pas de conflit entre Malus et Bonus
void test_bonus_malus(jeu, tab_joueurs);
///Test les conditions de distances
void test_distance(jeu,tab_joueurs);

/*

Cartes KM |0|:
	-25 (10 unités) |0|
	-50 (10 unités) |1|
	-75 (10 unités) |2|
	-100 (12 unités) |3|
	-200 (4 unités) |4|

Cartes bonus (tout une seule fois) |1|:
	-As du Volant |0|
	-Camion citerne |1|
	-Increvable |2|
	-Prioritaire |3|

Cartes Attaque |2|:
	-Accident (3 unités) |0|
	-Panne d'essence (3 unités) |1|
	-Crevaison (3 unités) |2|
	-Limite de Vitesse (4 unités) |3|
	-Feu rouge (5 unités) |4|

Cartes Parades |3|:
	-Réparation (6 unités) |0|
	-Essence (6 unités) |1|
	-Roue de secours (6 unités) |2|
	-Fin de limitation (6 unités) |3|
	-Feu vert (14 unités) |4|

Première carte pour commencer est un feu vert.

Chaque debut de tour, on pioche une cartre.

Deck de 106 cartes.
Début du jeu, 6 cartes chacun.

*/
