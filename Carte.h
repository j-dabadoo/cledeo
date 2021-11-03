#ifndef CARTE_H
#define CARTE_H

#include <iostream>
#include <vector>
#include <map>

#include <allegro.h>
#include <conio.h>
#include <time.h>
#include <fstream>

#define NB_CARTE 24
#define NB_JOUEUR 4

#define HAUT 72
#define BAS 80
#define GAUCHE 75
#define DROITE 77


class Carte
{
    public:
        Carte();
        Carte(int id, std::string nom, BITMAP* image, std::string type);
        ~Carte();

        void setId(int id);
        void setNom(std::string nom);
        void setImage(BITMAP* image);
        void setType(std::string type);

        int getId()const;
        std::string getNom()const;
        BITMAP* getImage()const;
        std::string getType()const;

        void display(BITMAP* page)const;

    private:
        int m_id ;
        int m_posX;
        int m_posY;
        std::string m_nom ;
        BITMAP * m_image ;
        std::string m_type;
};




#endif // CARTE_H
