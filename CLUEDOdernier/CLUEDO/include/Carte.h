#ifndef CARTE_H
#define CARTE_H

#include <iostream>
#include <vector>
#include <map>

#include <allegro.h>
#include <conio.h>
#include <time.h>

#define NB_CARTE 24



class Carte
{
    public:
        Carte();
        Carte(int id, std::string nom, BITMAP* image, std::string type);
        ~Carte();

        int getId()const;
        int getPosX()const;
        int getPosY()const;
        std::string getNom()const;
        BITMAP* getImage()const;
        std::string getType()const;


        void setId(int id);
        void setPosX(int x);
        void setPosY(int y);
        void setNom(std::string nom);
        void setImage(BITMAP* image);
        void setType(std::string type);

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
