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
        int getScore()const;
        std::string getCouleurPion()const;
        BITMAP* getImagePion()const;
        BITMAP* getLogoHypo()const;
        std::map <std::string, bool> getHypo()const;
        std::vector<Carte> getCartes() ;
        bool getFin()const;

        void setNom(std::string nom);
        void setPosX(int posX);
        void setPosY(int posY);
        void setDeplacement(int nb_depl);
        void setLoca(char loca);
        void setScore(int score);
        void setCouleur(std::string couleur);
        void setImagePion(BITMAP* logo);
        void setHypo(std::string nouvinfo);
        void setHypo(std::string nouvinfo, bool etat);
        void setLogoHypo(BITMAP* logohypo);
        void setCartes(std::vector <Carte> cartes);
        void setFin(bool fin);


        void add(Carte carte);
        void cardDisplay(BITMAP* buffer);
        void hypotheseInit();
        void infoDisplay(BITMAP* buffer);
        void hypoDisplay(BITMAP* buffer)const;
        void cardRecovery(std::vector <Carte>& cartes);
        void pawnRecovery();
        void deplacement(BITMAP* buffer, std::vector<std::vector <char>> &matrice);
        void deplacementChance(BITMAP* buffer, std::vector<std::vector <char>> &matrice);


    private:
        std::string m_nom ;
        int m_posX ;
        int m_posY ;
        int m_deplacement;
        char m_loca;
        int m_score;
        std::string m_couleurPion ;
        BITMAP* m_imagePion ;
        BITMAP* m_logohypo;
        bool m_fin ;

        std::map <std::string, bool> m_hypothese ;
        std::vector <Carte> m_cartes ;

};

#endif // JOUEUR_H
