#ifndef HYPOTHESE_H
#define HYPOTHESE_H

#include "Joueur.h"

class Hypothese
{
    public:
        Hypothese();
        ~Hypothese();

        ///getters
        std::string getLieu();
        std::string getPersonnage();
        std::string getArme();
        std::string getJou();

        ///setters
        void setLieu(std::string lieu);
        void setPersonnage(std::string personnage);
        void setArme(std::string arme);
        void setJou(std::string jou);

        ///autres
        void displayHypo();
        void affichehypo(BITMAP* buffer, std::vector<Joueur>& joueurs, int& tour, int& nb_joueurs, std::vector<Carte>& cartes, std::vector <Arme> &armes,std::vector <Lieu> &lieux,std::vector <Personnage> &personnages);
        void actionhypo(std::vector<Joueur>& joueurs, int& tour, int& nb_joueurs, BITMAP* buffer, std::vector<Carte>& cartes, std::vector <Arme> &armes,std::vector <Lieu> &lieux,std::vector <Personnage> &personnages, BITMAP *des);
        std::string trouvelieu(Joueur lejoueur);
        void verifhypochezlejoueuraccuse(std::vector<Joueur>& joueurs, int accuse, std::string armeverif, std::string persoverif, std::string lieuverif, int tour, BITMAP* buffer);
        void incluhypo(std::vector<Joueur>& joueurs, int& tour, Hypothese hypoaajt, BITMAP* buffer);
        int accusationfinale(BITMAP* buffer, std::vector<Joueur> joueurs, std::vector <Carte> &secret, std::vector<Arme> armes, std::vector<Personnage> persos, std::vector<Lieu> lieux);
        void disaccusationfinale(BITMAP* buffer, std::vector<Joueur> joueurs, std::vector <Carte> &secret, std::vector<Arme> armes, std::vector<Personnage> persos, std::vector<Lieu> lieux);


    private:
        std::string m_lieu;
        std::string m_personnage;
        std::string m_arme;
        std::string m_jou;
};

#endif // HYPOTHESE_H
