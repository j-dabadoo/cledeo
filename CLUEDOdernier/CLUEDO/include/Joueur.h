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
        int getDeplacement()const;
        char getLoca()const;
        std::string getCouleurPion()const;
        BITMAP* getImagePion()const;
        BITMAP* getLogoHypo()const;
        std::map <std::string, bool> getHypo()const;
        std::vector<Carte> getCartes()const ;

        void setNom(std::string nom);
        void setPosX(int posX);
        void setPosY(int posY);
        void setDeplacement(int nb_depl);
        void setLoca(char loca);
        void setCouleur(std::string couleur);
        void setImagePion(BITMAP* logo);
        void setHypo(std::string nouvinfo);
        void setLogoHypo(BITMAP* logohypo);


        void add(Carte carte);
        void cardDisplay(BITMAP* buffer)const;
        void hypotheseInit();
        void infoDisplay(BITMAP* buffer);
        void hypoDisplay(BITMAP* buffer)const;
        void deplacement(BITMAP* plateau, BITMAP* buffer, std::vector<std::vector <char>> &matrice);

    private:
        std::string m_nom ;
        int m_posX ;
        int m_posY ;
        int m_deplacement;
        char m_loca;
        std::string m_couleurPion ;
        BITMAP* m_imagePion ;
        BITMAP* m_logohypo;

        std::map <std::string, bool> m_hypothese ;
        std::vector <Carte> m_cartes ;

};

#endif // JOUEUR_H
