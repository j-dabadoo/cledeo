#ifndef JOUEUR_H
#define JOUEUR_H

#include "Carte.h"

class Joueur
{
    public:
        Joueur();
        ~Joueur();

        std::string getNom()const;
        int getPosX()const;
        int getPosY()const;
        char getLoca()const;
        std::string getCouleurPion()const;
        BITMAP* getImagePion()const;
        std::map <std::string, bool> getHypo()const;
        std::vector<Carte> getCartes()const ;

        void setNom(std::string nom);
        void setPosX(int posX);
        void setPosY(int posY);
        void setLoca(char loca);
        void setCouleur(std::string couleur);
        void setLogo(BITMAP* logo);
        void setHypo(std::string nouvinfo);


        void add(Carte carte);
        void cardDisplay(BITMAP* page)const;
        void hypotheseinit();
        void infodisplay(BITMAP* page);
        void hypodisplay(BITMAP* page)const;
        void deplacement(BITMAP* page);

    private:
        std::string m_nom ;
        int m_posX ;
        int m_posY ;
        char m_loca;
        std::string m_couleurPion ;
        BITMAP* m_imagePion ;

        std::map <std::string, bool> m_hypothese ;
        std::vector <Carte> m_cartes ;

};

#endif // JOUEUR_H
