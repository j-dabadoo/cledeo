#include "Carte.h"

/// //////////////////////////// ///
/// CONSTRUCTEURS / DESTRUCTEURS ///
/// //////////////////////////// ///

Carte::Carte()
{
    m_id=0;
    m_nom="vide";
    m_image=NULL;
    m_type="vide";
}

Carte::Carte(int id, std::string nom, BITMAP* image, std::string type)
{
    m_id = id ;
    m_nom = nom ;
    m_image = image ;
    m_type = type ;
}

Carte::~Carte() {}


/// /////// ///
/// GETTERS ///
/// /////// ///

std::string Carte::getNom()const {return m_nom ;}
int Carte::getId()const {return m_id ;}
std::string Carte::getType()const {return m_type;}
BITMAP* Carte::getImage()const{return m_image;}


/// /////// ///
/// SETTERS ///
/// /////// ///

void Carte::setId(int id) {m_id=id;}
void Carte::setType(std::string type) {m_type=type;}
void Carte::setNom(std::string nom) {m_nom=nom;}



/// ///////////////////// ///
/// AFFICHAGE D'UNE CARTE ///
/// ///////////////////// ///

void Carte::display(BITMAP* buffer)const
{
    //std::cout <<"Carte :"<<std::endl<<getId()<<std::endl<<getNom()<<std::endl
    //          <<getType()<<std::endl<<std::endl;
    blit(m_image, buffer, 0, 0, m_posX, m_posY, SCREEN_W, SCREEN_H);
}


