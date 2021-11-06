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

int Carte::getId()const {return m_id ;}
int Carte::getPosX()const{return m_posX;}
int Carte::getPosY()const{return m_posY;}
std::string Carte::getNom()const {return m_nom ;}
BITMAP* Carte::getImage()const{return m_image;}
std::string Carte::getType()const {return m_type;}



/// /////// ///
/// SETTERS ///
/// /////// ///

void Carte::setId(int id) {m_id=id;}
void Carte::setPosX(int x) {m_posX=x;}
void Carte::setPosY(int y) {m_posY=y;}
void Carte::setNom(std::string nom) {m_nom=nom;}
void Carte::setType(std::string type) {m_type=type;}




/// ///////////////////// ///
/// AFFICHAGE D'UNE CARTE ///
/// ///////////////////// ///

void Carte::display(BITMAP* buffer)const
{
    blit(getImage(), buffer, 0, 0, getPosX(), getPosY(), getImage()->w, getImage()->h);
}


