#ifndef JOUEUR_H
#define JOUEUR_H

#include "Carte.h"

class Joueur
{
    public:
        Joueur();
        ~Joueur();

        void setnom(std::string nom);
        void setlogo(BITMAP* logo);
        void sethypot(std::string nouvinfo);
        void setcouleur(std::string couleur);
        void setposX(int posX);
        void setposY(int posY);
        void setloca(char loca);

        std::string getnom();
        BITMAP* getlogo();
        std::map <std::string, bool> gethypo();
        std::string getcouleur();
        int getposX();
        int getposY();
        char getloca();

        void add(Carte carte);
        void cardDisplay(BITMAP* page)const;
        void hypotheseinit();
        void infodisplay(BITMAP* page);
        void hypodisplay(BITMAP* page)const;
        void deplacement(BITMAP* plateau, BITMAP* page, std::vector<std::vector <char>> matrice);

    private:
        int m_posX ;
        int m_posY ;
        char m_loca;
        std::string m_couleurPion ;
        BITMAP* m_imagePion ;
        std::map <std::string, bool> m_hypothese ;
        std::vector <Carte> m_cartes ;
        std::string m_nom ;
};

std::vector<std::vector <char>> initplateau();


#endif // JOUEUR_H
