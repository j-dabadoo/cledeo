#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include "Joueur.h"
#include "Carte.h"
#include "Hypothese.h"
#include "Sauvegarde.h"

///Initialistion allegro
void allegroInit();

///Initialisation des cartes
void cardInit(std::vector <Joueur> &joueurs, std::vector <Carte> &cartes, std::vector <Carte> &cartes2, int &nb_joueurs, std::vector <Arme> &armes,std::vector <Lieu> &lieux,std::vector <Personnage> &personnages);

///Distribution des cartes
void distribCarte(std::vector <Carte> &cartes2,std::vector <Carte> &secret,std::vector <Joueur> &joueurs, int &nb_joueurs);

///Destruction des bitmap
void destruction(std::vector<Carte> &cartes, BITMAP *plateau, std::vector<Joueur>& joueurs);

///1er menu : appuie sur play
void menu(std::vector <Joueur> &joueurs, std::vector <Carte> &cartes, std::vector <Carte> &cartes2, int &nb_joueurs,std::vector <Carte> &secret, int& tour, std::vector <Arme> &armes,std::vector <Lieu> &lieux,std::vector <Personnage> &personnages)
;
///2e menu : lancement du jeu (nouvelle partie, partie sauvegardée...)
void launch(std::vector <Joueur> &joueurs, std::vector <Carte> &cartes, std::vector <Carte> &cartes2, int &nb_joueurs,std::vector <Carte> &secret, int& tour, std::vector <Arme> &armes,std::vector <Lieu> &lieux,std::vector <Personnage> &personnages);

///3e menu : choix du nombre de joueurs (dans le cas ou on lance une nouvelle partie)
int choix_nbj();

///4e menu : choix du nom d'un joueur
std::string saisie1joueur(FONT *broadway);

///4e menu : choix de la couleur du pion du joueur
void choix_couleur(Joueur& lejoueur, FONT* broadway, std::vector<bool>& pionschoisis);

///Choix de l'inscription ou de la connexion
char inscriptionConnexion();

///Initialise la matrice du plateau
std::vector<std::vector<char>> initPlateau() ;

void tourParTour(int& tour, int& nb_joueurs, std::vector<Joueur>& joueurs) ;

int lancerDe(BITMAP *buffer, BITMAP *des) ;

void actualisation(BITMAP* buffer, BITMAP* plateau, std::vector<Joueur>& joueurs, int& tour, int& nb_joueurs, BITMAP *des, BITMAP* fond);

void affichehypo(BITMAP* buffer, std::vector<Joueur>& joueurs, int& tour);
std::string trouvlieu(Joueur lejoueur);
void actionhypo(int choixint, std::vector<Joueur>& joueurs, int& tour);
void incluhypo(std::vector<Joueur>& joueurs, int& tour, Hypothese hypoaajt);
void actionsBoutons(std::vector <Joueur>& joueurs, std::vector <Carte>& secret, int& tour, int& nb_joueurs, BITMAP* buffer, BITMAP *des, std::vector<Carte>& cartes, std::vector <Arme> &armes,std::vector <Lieu> &lieux,std::vector <Personnage> &personnages);

void animMelangeCarte(std::vector<Carte>& cartes, int& nb_joueurs, std::vector<Joueur>& joueurs);
bool casechance(BITMAP* plateau, std::vector<Joueur>& joueurs, int& tour, int nb_joueurs, BITMAP* buffer, std::vector<std::vector<char>> matrice, BITMAP* fond);

int accusationfinale(BITMAP* buffer, std::vector<Joueur> joueurs, std::vector <Carte> &secret, std::vector<Arme> armes, std::vector<Personnage> persos, std::vector<Lieu> lieux);
void disaccusationfinale(BITMAP* buffer, std::vector<Joueur> joueurs, std::vector <Carte> &secret, std::vector<Arme> armes, std::vector<Personnage> persos, std::vector<Lieu> lieux);

void zoom(BITMAP * buffer);

#endif // HEADER_H_INCLUDED
