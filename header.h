#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include "Joueur.h"
#include "Carte.h"

///Prototypes de sspg
void allegroInit();

void cardInit(std::vector <Joueur> &joueurs, std::vector <Carte> &cartes, std::vector <Carte> &cartes2);

void distribCarte(std::vector <Carte> &cartes2,std::vector <Carte> &secret,std::vector <Joueur> &joueurs);

#endif // HEADER_H_INCLUDED
