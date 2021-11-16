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
        void affichehypo(BITMAP* page, std::vector<Joueur>& joueurs, int& tour);
        void actionhypo(int choixint, std::vector<Joueur>& joueurs, int& tour);
        std::string trouvlieu(Joueur lejoueur);
        void incluhypo(std::vector<Joueur>& joueurs, int& tour, Hypothese hypoaajt);

    private:
        std::string m_lieu;
        std::string m_personnage;
        std::string m_arme;
        std::string m_jou;
};

#endif // HYPOTHESE_H
