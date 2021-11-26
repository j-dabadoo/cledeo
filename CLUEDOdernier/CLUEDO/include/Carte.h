#ifndef CARTE_H
#define CARTE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include <allegro.h>
#include <conio.h>
#include <time.h>
#include <math.h>

#define NB_CARTE 24



class Carte
{
public:
    Carte();
    Carte(int id, std::string nom, BITMAP* image, std::string type, int posX, int posY);
    Carte(std::string nom, BITMAP* image, std::string type);
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

    void display(BITMAP* buffer)const;


protected:
    std::string m_nom ;
    BITMAP * m_image ;
    std::string m_type;


private:
    int m_id ;
    int m_posX;
    int m_posY;
};


class Arme: public Carte
{
public:
    Arme(std::string nom, BITMAP* image, std::string type);
};


class Lieu: public Carte
{
public:
    Lieu(std::string nom, BITMAP* image, std::string type);
};


class Personnage: public Carte
{
public:
    Personnage(std::string nom, BITMAP* image, std::string type);
};


#endif // CARTE_H
