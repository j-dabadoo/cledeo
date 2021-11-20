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
        void affichehypo(BITMAP* buffer, std::vector<Joueur>& joueurs, int& tour, int& nb_joueurs);
        void actionhypo(std::vector<Joueur>& joueurs, int& tour, int& nb_joueurs, BITMAP* buffer);
        std::string trouvlieu(Joueur lejoueur);
        void incluhypo(std::vector<Joueur>& joueurs, int& tour, Hypothese hypoaajt);
        void verifhypochezlejoueuraccuse(std::vector<Joueur>& joueurs, int accuse, std::string armeverif, std::string persoverif, std::string lieuverif, int tour);


    private:
        std::string m_lieu;
        std::string m_personnage;
        std::string m_arme;
        std::string m_jou;
};

#endif // HYPOTHESE_H


