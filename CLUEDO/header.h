#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include "Joueur.h"
#include "Carte.h"

///Initialistion allegro
void allegroInit();

///Initialisation des cartes
void cardInit(std::vector <Joueur> &joueurs, std::vector <Carte> &cartes, std::vector <Carte> &cartes2);

///Distribution des cartes
void distribCarte(std::vector <Carte> &cartes2,std::vector <Carte> &secret,std::vector <Joueur> &joueurs);

///Destruction des bitmap
void destruction(std::vector<Carte> &cartes);

///1er menu : appuie sur play
void menu();

///2e menu : choix du nombre de joueurs
int choix_nbj();

///3e menu : lancement du jeu (nouvelle partie, partie sauvegardée...)
void launch();

#endif // HEADER_H_INCLUDED
