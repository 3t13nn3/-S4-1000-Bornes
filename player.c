#include "head.h"

/** Défausse une carte de la Joueur::main du joueur. **/
carte defosse(jeu game, joueur * p, int idxCarte){
	carte tmp = p->main[idxCarte];
	p->main[idxCarte] = pop_back_carte(game);
	return tmp;
}
