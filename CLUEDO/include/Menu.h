#ifndef MENU_H
#define MENU_H

#include "Sauvegarde.h"


class Menu
{
public:
    Menu();
    ~Menu();

    bool menu(std::vector <Joueur> &joueurs, std::vector <Carte> &cartes, std::vector <Carte> &cartes2, int &nb_joueurs,std::vector <Carte> &secret, int& tour, std::vector <Arme> &armes,std::vector <Lieu> &lieux,std::vector <Personnage> &personnages);
    void launch(std::vector <Joueur> &joueurs, std::vector <Carte> &cartes, std::vector <Carte> &cartes2, int &nb_joueurs,std::vector <Carte> &secret, int& tour, std::vector <Arme> &armes,std::vector <Lieu> &lieux,std::vector <Personnage> &personnages);
    int choix_nbj(FONT* broadway);
    void choix_couleur(Joueur& lejoueur, FONT* broadway, std::vector<bool>& pionschoisis);
    std::string saisie1joueur(FONT *broadway);
    char inscriptionConnexion(FONT *broadway);
    void animMelangeCarte(std::vector<Carte>& cartes, int& nb_joueurs, std::vector<Joueur>& joueurs);
    void cardInit(std::vector <Joueur> &joueurs, std::vector <Carte> &cartes, std::vector <Carte> &cartes2, int &nb_joueurs, std::vector <Arme> &armes,std::vector <Lieu> &lieux,std::vector <Personnage> &personnages);
    void distribCarte(std::vector <Carte> &cartes2,std::vector <Carte> &secret,std::vector <Joueur> &joueurs, int &nb_joueurs);
    std::vector<std::vector<char>> initPlateau() ;
    bool alreadyExist(std::vector<std::string> players, std::string nouveau);
};

#endif // MENU_H
