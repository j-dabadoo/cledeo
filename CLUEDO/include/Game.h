#ifndef GAME_H
#define GAME_H

#include "Menu.h"

class Game
{
public:
    Game();
    ~Game();

    void jeu() ;

    void allegroInit();

    void destruction(std::vector<Carte> &cartes, BITMAP *plateau, std::vector<Joueur>& joueurs);

    void tourParTour(int& tour, int& nb_joueurs, std::vector<Joueur>& joueurs) ;

    int lancerDe(BITMAP *buffer, BITMAP *des, FONT* broadway) ;

    void actualisation(BITMAP* buffer, BITMAP* plateau, std::vector<Joueur>& joueurs, int& tour, int& nb_joueurs,
                       BITMAP *des, BITMAP* fond, FONT* broadway);

    void zoom(BITMAP * buffer);

    bool casechance(BITMAP* plateau, std::vector<Joueur>& joueurs, int& tour, int nb_joueurs, BITMAP* buffer,
                    std::vector<std::vector<char>> matrice, BITMAP* fond, BITMAP* des, FONT* broadway);

    void actionsBoutons(std::vector <Joueur>& joueurs, std::vector <Carte>& secret, int& tour, int& nb_joueurs, BITMAP* buffer,
            BITMAP *des, std::vector<Carte>& cartes, std::vector <Arme> &armes,std::vector <Lieu> &lieux,
            std::vector <Personnage> &personnages, bool& quitter, FONT* broadway);



private:
    int nb_joueurs, tour = 0 ;
    bool quitter=false;
    Sauvegarde save ;
    Menu menu ;

    std::vector <Carte> cartes ; ///non mélangées
    std::vector <Arme> armes;
    std::vector <Lieu> lieux;
    std::vector <Personnage> personnages;

    std::vector <Carte> cartes2 ;///Mélangées
    std::vector <Carte> secret ;///Pochette secrète de 3 cartes
    std::vector <Joueur> joueurs;///Ensemble des joueurs
    std:: vector <std::vector <char>> matrice = menu.initPlateau(); ///Matrice du plateau
};

#endif // GAME_H
