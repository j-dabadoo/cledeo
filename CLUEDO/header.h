#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include "Joueur.h"
#include "Carte.h"

///Initialistion allegro
void allegroInit();

///Initialisation des cartes
void cardInit(std::vector <Joueur> &joueurs, std::vector <Carte> &cartes, std::vector <Carte> &cartes2, int &nb_joueurs);

///Distribution des cartes
void distribCarte(std::vector <Carte> &cartes2,std::vector <Carte> &secret,std::vector <Joueur> &joueurs, int &nb_joueurs);

///Destruction des bitmap
void destruction(std::vector<Carte> &cartes);

///1er menu : appuie sur play
int menu(std::vector <Joueur> &joueurs, std::vector <Carte> &cartes, std::vector <Carte> &cartes2, int &nb_joueurs,std::vector <Carte> &secret);

///2e menu : lancement du jeu (nouvelle partie, partie sauvegardée...)
int launch(std::vector <Joueur> &joueurs, std::vector <Carte> &cartes, std::vector <Carte> &cartes2, int &nb_joueurs,std::vector <Carte> &secret);

///3e menu : choix du nombre de joueurs (dans le cas ou on lance une nouvelle partie)
int choix_nbj();

///4e menu : choix de la couleur du pion du joueur
void choix_couleur(Joueur& lejoueur);

///Initialise la matrice du plateau
std::vector<std::vector<char>> initPlateau() ;


#endif // HEADER_H_INCLUDED
