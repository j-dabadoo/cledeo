#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

#include "Joueur.h"


class Sauvegarde
{
    public:
        Sauvegarde();
        ~Sauvegarde();

        void writeAll(std::vector <Joueur>& joueurs, int& tour, std::vector <Carte> &secret);
        void readAll(std::vector <Joueur>& joueurs, int& nb_joueurs, int& tour, std::vector <Carte> &secret);
        void readNBJ(int& nb_joueurs);
        void scoreDisplay() ;
        void saveScore(std::vector <Joueur>& joueurs) ;
        void saveNewCompte(std::string& nom, std::string& mdp);
        bool connexionValide(std::string& nom, std::string& mdp);
        void readComptes();
        bool alreadyExist(std::string& nom) ;
        template <typename T>
        void ajoutVec(std::vector <T>& cartes, T newCarte);
        template <typename A>
        void recupBitmap(std::vector <A>& cartes, std::vector <Carte>& paquet);
};

#endif // SAUVEGARDE_H
