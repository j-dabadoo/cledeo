#include "Joueur.h"

/// ////////////////////////// ///
/// CONSTRUCTEUR / DESTRUCTEUR ///
/// ////////////////////////// ///
Joueur::Joueur()
{
    m_loca='D' ;
    m_deplacement = 0;
}

Joueur::~Joueur()
{}


/// /////// ///
/// GETTERS ///
/// /////// ///

std::string Joueur::getNom()const
{
    return m_nom;
}
int Joueur::getPosX()const
{
    return m_posX;
}
int Joueur::getPosY()const
{
    return m_posY;
}
int Joueur::getDeplacement()const
{
    return m_deplacement;
}
char Joueur::getLoca()const
{
    return m_loca;
}
std::string Joueur::getCouleurPion()const
{
    return m_couleurPion;
}
BITMAP* Joueur::getImagePion()const
{
    return m_imagePion ;
}
std::map <std::string, bool> Joueur::getHypo()const
{
    return m_hypothese;
}
std::vector<Carte> Joueur::getCartes()const
{
    return m_cartes ;
}


/// /////// ///
/// SETTERS ///
/// /////// ///

void Joueur::setNom(std::string nom)
{
    m_nom=nom;
}
void Joueur::setPosX(int posX)
{
    m_posX=posX;
}
void Joueur::setPosY(int posY)
{
    m_posY=posY;
}
void Joueur::setDeplacement(int nb_depl)
{
    m_deplacement=nb_depl;
}
void Joueur::setLoca(char loca)
{
    m_loca=loca;
}
void Joueur::setCouleur(std::string couleur)
{
    m_couleurPion=couleur;
}
void Joueur::setImagePion(BITMAP* logo)
{
    m_imagePion=logo;
}
void Joueur::setHypo(std::string nouvinfo)
{
    m_hypothese[nouvinfo]=true;
}



/// ///////////////////////////////////////// ///
/// AJOUT D'UNE CARTE DANS LE JEU D'UN JOUEUR ///
/// ///////////////////////////////////////// ///

void Joueur::add(Carte carte)
{
    m_cartes.push_back(carte);
}


/// //////////////////////////////// ///
/// AFFICHAGE DES CARTES D'UN JOUEUR ///
/// //////////////////////////////// ///

void Joueur::cardDisplay(BITMAP* buffer)const
{
    int i=0 ;

    for(auto& carte : getCartes())
    {
        carte.setPosX(700+70*i);
        carte.setPosY(300);
        carte.display(buffer);
        i++;
    }
}



/// ////////// ///
/// HYPOTHÈSES ///
/// ////////// ///

void Joueur::hypotheseInit()
{
    std::string inter;
    std::vector <Carte> ::iterator it;

    inter = "Sabre";
    it=m_cartes.begin();
    while(it!=m_cartes.end() && inter==it->getNom())
    {
        it++;
    }
    if(inter==it->getNom())
        m_hypothese[inter]=true;
    else m_hypothese[inter]=false;

    inter = "Pistolet";
    it=m_cartes.begin();
    while(it!=m_cartes.end() && inter==it->getNom())
    {
        it++;
    }
    if(inter==it->getNom())
        m_hypothese[inter]=true;
    else m_hypothese[inter]=false;

    inter = "Poudre a canon";
    it=m_cartes.begin();
    while(it!=m_cartes.end() && inter==it->getNom())
    {
        it++;
    }
    if(inter==it->getNom())
        m_hypothese[inter]=true;
    else m_hypothese[inter]=false;

    inter = "Cle";
    it=m_cartes.begin();
    while(it!=m_cartes.end() && inter==it->getNom())
    {
        it++;
    }
    if(inter==it->getNom())
        m_hypothese[inter]=true;
    else m_hypothese[inter]=false;

    inter = "Tire bouchon";
    it=m_cartes.begin();
    while(it!=m_cartes.end() && inter==it->getNom())
    {
        it++;
    }
    if(inter==it->getNom())
        m_hypothese[inter]=true;
    else m_hypothese[inter]=false;

    inter = "Canon";
    it=m_cartes.begin();
    while(it!=m_cartes.end() && inter==it->getNom())
    {
        it++;
    }
    if(inter==it->getNom())
        m_hypothese[inter]=true;
    else m_hypothese[inter]=false;

    inter = "Will Turner";
    it=m_cartes.begin();
    while(it!=m_cartes.end() && inter==it->getNom())
    {
        it++;
    }
    if(inter==it->getNom())
        m_hypothese[inter]=true;
    else m_hypothese[inter]=false;

    inter = "Bill Turner";
    it=m_cartes.begin();
    while(it!=m_cartes.end() && inter==it->getNom())
    {
        it++;
    }
    if(inter==it->getNom())
        m_hypothese[inter]=true;
    else m_hypothese[inter]=false;

    inter = "Jack Sparrow";
    it=m_cartes.begin();
    while(it!=m_cartes.end() && inter==it->getNom())
    {
        it++;
    }
    if(inter==it->getNom())
        m_hypothese[inter]=true;
    else m_hypothese[inter]=false;

    inter = "Barbossa";
    it=m_cartes.begin();
    while(it!=m_cartes.end() && inter==it->getNom())
    {
        it++;
    }
    if(inter==it->getNom())
        m_hypothese[inter]=true;
    else m_hypothese[inter]=false;

    inter = "Elizabeth Swann";
    it=m_cartes.begin();
    while(it!=m_cartes.end() && inter==it->getNom())
    {
        it++;
    }
    if(inter==it->getNom())
        m_hypothese[inter]=true;
    else m_hypothese[inter]=false;

    inter = "Davy Jones";
    it=m_cartes.begin();
    while(it!=m_cartes.end() && inter==it->getNom())
    {
        it++;
    }
    if(inter==it->getNom())
        m_hypothese[inter]=true;
    else m_hypothese[inter]=false;

    inter = "Calypso";
    it=m_cartes.begin();
    while(it!=m_cartes.end() && inter==it->getNom())
    {
        it++;
    }
    if(inter==it->getNom())
        m_hypothese[inter]=true;
    else m_hypothese[inter]=false;

    inter = "James Norrington";
    it=m_cartes.begin();
    while(it!=m_cartes.end() && inter==it->getNom())
    {
        it++;
    }
    if(inter==it->getNom())
        m_hypothese[inter]=true;
    else m_hypothese[inter]=false;

    inter = "Barbe Noire";
    it=m_cartes.begin();
    while(it!=m_cartes.end() && inter==it->getNom())
    {
        it++;
    }
    if(inter==it->getNom())
        m_hypothese[inter]=true;
    else m_hypothese[inter]=false;

    inter = "Tortuga";
    it=m_cartes.begin();
    while(it!=m_cartes.end() && inter==it->getNom())
    {
        it++;
    }
    if(inter==it->getNom())
        m_hypothese[inter]=true;
    else m_hypothese[inter]=false;

    inter = "Port Royal";
    it=m_cartes.begin();
    while(it!=m_cartes.end() && inter==it->getNom())
    {
        it++;
    }
    if(inter==it->getNom())
        m_hypothese[inter]=true;
    else m_hypothese[inter]=false;

    inter = "Ile de la Muerta";
    it=m_cartes.begin();
    while(it!=m_cartes.end() && inter==it->getNom())
    {
        it++;
    }
    if(inter==it->getNom())
        m_hypothese[inter]=true;
    else m_hypothese[inter]=false;

    inter = "Ile au rhum";
    it=m_cartes.begin();
    while(it!=m_cartes.end() && inter==it->getNom())
    {
        it++;
    }
    if(inter==it->getNom())
        m_hypothese[inter]=true;
    else m_hypothese[inter]=false;

    inter = "Hollandais Volant";
    it=m_cartes.begin();
    while(it!=m_cartes.end() && inter==it->getNom())
    {
        it++;
    }
    if(inter==it->getNom())
        m_hypothese[inter]=true;
    else m_hypothese[inter]=false;

    inter = "Ile des 4 vents";
    it=m_cartes.begin();
    while(it!=m_cartes.end() && inter==it->getNom())
    {
        it++;
    }
    if(inter==it->getNom())
        m_hypothese[inter]=true;
    else m_hypothese[inter]=false;

    inter = "HMS Intrepide";
    it=m_cartes.begin();
    while(it!=m_cartes.end() && inter==it->getNom())
    {
        it++;
    }
    if(inter==it->getNom())
        m_hypothese[inter]=true;
    else m_hypothese[inter]=false;

    inter = "Triangle des Bermudes";
    it=m_cartes.begin();
    while(it!=m_cartes.end() && inter==it->getNom())
    {
        it++;
    }
    if(inter==it->getNom())
        m_hypothese[inter]=true;
    else m_hypothese[inter]=false;

    inter = "Black Pearl";
    it=m_cartes.begin();
    while(it!=m_cartes.end() && inter==it->getNom())
    {
        it++;
    }
    if(inter==it->getNom())
        m_hypothese[inter]=true;
    else m_hypothese[inter]=false;
}


void Joueur::infoDisplay(BITMAP* buffer)
{
    textprintf_ex(buffer, font, 660, 450, makecol(255, 255, 255), -1, "Joueur : ");
    textprintf_ex(buffer, font, 730, 450, makecol(255, 255, 255), -1,"%s", getNom().c_str());
    masked_blit(m_imagePion, buffer, 0,0, 610, 430, SCREEN_W, SCREEN_H);
    cardDisplay(buffer);
    blit(buffer, screen, 0, 0,0,0, SCREEN_W, SCREEN_H);
}


/// ////////////////////////////////// ///
/// AFFICHAGE DES HYPOTHÈSES DU JOUEUR ///
/// ////////////////////////////////// ///

void Joueur::hypoDisplay(BITMAP* buffer) const
{
    int i=0;
    for(const auto& it : getHypo())
    {
        textprintf_ex(buffer, font, 20, (10+25*i), makecol(0,0,0), -1, "%s", it.first.c_str());
        if(it.second==true)
            rectfill(buffer, 370, (5+25*i), 385, (20+25*i), makecol(0,0,0));
        else rect(buffer, 370, (5+25*i), 385, (20+25*i), makecol(0,0,0));
        i++;
    }
}


/// ///////////////////// ///
/// DEPLACEMENT DES PIONS ///
/// ///////////////////// ///

void Joueur::deplacement(BITMAP* plateau, BITMAP* buffer, std::vector<std::vector <char>> &matrice)
{
    int nb_depl, locaX, locaY;
    char pos;

    ///Lancement de dé
    //nb_depl=(rand()%(6))+1;
    nb_depl = getDeplacement();

    if(nb_depl>0 && keypressed())
    {
        ///Effacer la buffer precedante
        //clear_bitmap(buffer);

        ///Selon où se trouve le joueur
        switch(m_loca)
        {
        ///Le joueur est dans une salle
        case '0':
            ///initialiation de la localistion actuelle
            locaX=m_posX;
            locaY=m_posY;

            ///Haut
            if(key[KEY_UP])
            {
                ///Recherche de la case suivante
                if(locaY-1>=0)
                    locaY--;
                pos = matrice[locaY][locaX];

                ///La case suivante est dans la salle
                if(m_posY-1 > 0 && pos=='0')
                {
                    m_posY--;
                    m_loca=pos;
                }
                ///La case suivante est une porte de salle
                else if(m_posY-1 > 0 && pos=='7')
                {
                    m_posY-=1;
                    m_loca=pos;
                }
                ///La case suivante est un mur (1 ou 8 pour mur de salle)
                else
                    textprintf_ex(buffer, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
            }
            ///Bas
            else if(key[KEY_DOWN])
            {

                ///Recherche de la case suivante
                if(locaY+1<=25)
                    locaY++;
                pos = matrice[locaY][locaX];

                ///La case suivante est dans la salle
                if(m_posY+1 <26 && pos=='0')
                {
                    m_posY++;
                    m_loca=pos;
                }
                ///La case suivante est la porte de la salle
                else if(m_posY+1 <26 && pos=='7')
                {
                    m_posY+=1;
                    m_loca=pos;
                }
                ///La case suivante est un mur (1 ou 8 pour mur de salle)
                else
                    textprintf_ex(buffer, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
            }
            ///Gauche
            else if(key[KEY_LEFT])
            {
                ///Recherche de la case suivante
                if(locaX-1>=0)
                    locaX--;
                pos = matrice[locaY][locaX];

                ///La case suivante est dans la salle
                if(m_posX-1 > 0 && pos=='0')
                {
                    m_posX--;
                    m_loca=pos;
                }
                ///La case suivante est la porte de la salle
                else if(m_posX-1 > 0 && pos=='7')
                {
                    m_posX-=1;
                    m_loca=pos;
                }
                ///La case suivante est un mur (1 ou 8 pour mur de salle)
                else
                    textprintf_ex(buffer, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
            }
            ///Droite
            else if(key[KEY_RIGHT])
            {
                ///Recherche de la case suivante
                if(locaX+1<=25)
                    locaX++;
                pos = matrice[locaY][locaX];

                ///La case suivante est dans la sallecc
                if(m_posX+1 < 26 && pos=='0')
                {
                    m_posX++;
                    m_loca=pos;
                }
                ///La case suivante est la porte de la salle
                else if(m_posX+1 <26 && pos=='7')
                {
                    m_posX+=1;
                    m_loca=pos;
                }
                ///La case suivante est un mur (1 ou 8 pour mur de salle)
                else
                    textprintf_ex(buffer, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");

            }
break;

        ///Le joueur est dans un couloir
        case '8':
            ///initialiation de la localistion actuelle
            locaX=m_posX;
            locaY=m_posY;

            ///Haut
            if(key[KEY_UP])
            {
                ///Recherche de la case suivante
                if(locaY-1>=0)
                    locaY--;
                pos = matrice[locaY][locaX];

                ///La case suivante est un couloir
                if(m_posY-1 > 0 && pos=='8')
                {
                    m_posY--;
                    nb_depl--;
                    m_loca=pos;
                }
                ///La case suivante est une porte de salle
                else if(m_posY-1 > 0 && pos=='7')
                {
                    m_posY-=1;
                    m_loca=pos;
                    nb_depl--;
                }
                ///La case suivante est un mur (1 ou 0 pour mur de salle)
                else
                    textprintf_ex(buffer, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
            }
            ///Bas
            else if(key[KEY_DOWN])
            {
                ///Recherche de la case suivante
                if(locaY+1<=25)
                    locaY++;
                pos = matrice[locaY][locaX];

                ///On reste dans le couloir
                if(m_posY+1 <26 && pos=='8')
                {
                    m_posY++;
                    nb_depl--;
                    m_loca=pos;
                }
                ///La case suivante est une porte de salle
                else if(m_posY+1 <26 && pos=='7')
                {
                    m_posY+=1;
                    m_loca=pos;
                    nb_depl--;
                }
                ///La case suivante est un mur (1 ou 0 pour mur de salle)
                else
                    textprintf_ex(buffer, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
            }
            ///Gauche
            else if(key[KEY_LEFT])
            {
                ///Recherche de la case suivante
                if(locaX-1>=0)
                    locaX--;
                pos = matrice[locaY][locaX];

                ///La case suivainte est la suite du couloir
                if(m_posX-1 > 0 && pos=='8')
                {
                    m_posX--;
                    nb_depl--;
                    m_loca=pos;
                }
                ///La case suivante est une porte de salle
                else if(m_posX-1 > 0 && pos=='7')
                {
                    m_posX-=1;
                    m_loca=pos;
                    nb_depl--;
                }
                ///La case suivante est un mur (1 ou 0 pour mur de salle)
                else
                    textprintf_ex(buffer, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
            }
            ///Droite
            else if(key[KEY_RIGHT])
            {
                ///Recherche de la case suivante
                if(locaX+1<=25)
                    locaX++;
                pos = matrice[locaY][locaX];

                ///La case suivante est la suite du couloir
                if(m_posX+1 < 26 && pos=='8')
                {
                    m_posX++;
                    nb_depl--;
                    m_loca=pos;
                }
                ///La case suivante est la porte d'une salle
                else if(m_posX+1 <26 && pos=='7')
                {
                    m_posX+=1;
                    m_loca=pos;
                    nb_depl--;
                }
                ///La case suivante est un mur (1 ou 0 pour mur de salle)
                else
                    textprintf_ex(buffer, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
            }
            break;

        ///Le joueur est dans un couloir
        case '7':
            ///initialiation de la localistion actuelle
            locaX=m_posX;
            locaY=m_posY;

            ///Haut
            if(key[KEY_UP])
            {
                ///Recherche de la case suivante
                if(locaY-1>=0)
                    locaY--;
                pos = matrice[locaY][locaX];

                ///La case suivante est un couloir
                if(m_posY-1 > 0 && pos=='8')
                {
                    m_posY--;
                    nb_depl--;
                    m_loca=pos;
                }
                ///La case suivante est la salle
                else if(m_posY-1 > 0 && pos=='0')
                {
                    m_posY--;
                    m_loca=pos;
                }
                ///La case suivante est la porte d'une salle
                else if(m_posY-1 > 0 && pos=='7')
                {
                    m_posY--;
                    m_loca=pos;
                }
                ///La case suivante est un mur (1 ou 0 pour mur de salle)
                else
                    textprintf_ex(buffer, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
            }
            ///Bas
            else if(key[KEY_DOWN])
            {
                ///Recherche de la case suivante
                if(locaY+1<=25)
                    locaY++;
                pos = matrice[locaY][locaX];

                ///On reste dans le couloir
                if(m_posY+1 <26 && pos=='8')
                {
                    m_posY++;
                    nb_depl--;
                    m_loca=pos;
                }
                ///La case suivante est la salle
                else if(m_posY+1 <26 && pos=='0')
                {
                    m_posY++;
                    m_loca=pos;
                }
                ///La case suivante est la porte d'une salle
                else if(m_posY+1 <26 && pos=='7')
                {
                    m_posY++;
                    m_loca=pos;
                }
                ///La case suivante est un mur (1 ou 0 pour mur de salle)
                else
                    textprintf_ex(buffer, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
            }
            ///Gauche
            else if(key[KEY_LEFT])
            {
                ///Recherche de la case suivante
                if(locaX-1>=0)
                    locaX--;
                pos = matrice[locaY][locaX];

                ///La case suivainte est la suite du couloir
                if(m_posX-1 > 0 && pos=='8')
                {
                    m_posX--;
                    nb_depl--;
                    m_loca=pos;
                }
                ///La case suivante est la salle
                else if(m_posX-1 > 0 && pos=='0')
                {
                    m_posX--;
                    m_loca=pos;
                }
                ///La case suivante est la porte d'une salle
                else if(m_posX-1 > 0 && pos=='7')
                {
                    m_posX--;
                    m_loca=pos;
                }
                ///La case suivante est un mur (1 ou 0 pour mur de salle)
                else
                    textprintf_ex(buffer, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
            }
            ///Droite
            else if(key[KEY_RIGHT])
            {
                ///Recherche de la case suivante
                if(locaX+1<=25)
                    locaX++;
                pos = matrice[locaY][locaX];

                ///La case suivante est la suite du couloir
                if(m_posX+1 < 26 && pos=='8')
                {
                    m_posX++;
                    nb_depl--;
                    m_loca=pos;
                }
                ///La case suivante est la salle
                else if(m_posX+1 <26 && pos=='0')
                {
                    m_posX++;
                    m_loca=pos;
                }
                ///La case suivante est la porte d'une salle
                else if(m_posX+1 <26 && pos=='7')
                {
                    m_posX++;
                    m_loca=pos;
                }
                ///La case suivante est un mur (1 ou 0 pour mur de salle)
                else
                    textprintf_ex(buffer, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
            }
            break;

        ///Le joueur est sur sa case de départ
        case 'D':
            ///initialiation de la localistion actuelle
            locaX=m_posX;
            locaY=m_posY;

            ///Haut
            if(key[KEY_UP])
            {

                ///Recherche de la case suivante
                if(locaY-1>=0)
                    locaY--;
                pos = matrice[locaY][locaX];

                ///La case suivante est une couloir
                if(m_posY-1 > 0 && pos=='8')
                {
                    m_posY--;
                    nb_depl--;
                    m_loca=pos;
                }
                ///La case suivante est une porte de salle
                else if(m_posY-1 > 0 && pos=='7')
                {
                    m_posY-=2;
                    m_loca='0';
                    nb_depl--;
                }
                ///La case suivante est un mur (1 ou 0 pour mur de salle)
                else
                    textprintf_ex(buffer, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
            }
            ///Bas
            else if(key[KEY_DOWN])
            {
                ///Recherche de la case suivante
                if(locaY+1<=25)
                    locaY++;
                pos = matrice[locaY][locaX];

                ///La case suivante est un couloir
                if(m_posY+1 <26 && pos=='8')
                {
                    m_posY++;
                    nb_depl--;
                    m_loca=pos;
                }
                ///La case suivante est une porte de salle
                else if(m_posY+2 <26 && pos=='7')
                {
                    m_posY+=2;
                    m_loca='8';
                    nb_depl--;
                }
                ///La case suivante est un mur (1 ou 0 pour mur de salle)
                else
                    textprintf_ex(buffer, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
            }
            ///Gauche
            else if(key[KEY_LEFT])
            {
                ///Recherche de la case suivante
                if(locaY-1>=0)
                    locaX--;
                pos = matrice[locaY][locaX];

                ///La case suivante est un couloir
                if(m_posX-1 > 0 && pos=='8')
                {
                    m_posX--;
                    nb_depl--;
                    m_loca=pos;
                }
                ///La case suivante est une porte de salle
                else if(m_posX-2 > 0 && pos=='7')
                {
                    m_posX-=2;
                    m_loca='0';
                    nb_depl--;
                }
                ///La case suivante est un mur (1 ou 0 pour mur de salle)
                else
                    textprintf_ex(buffer, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
            }
            ///Droite
            else if(key[KEY_RIGHT])
            {
                ///Recherche de la case suivante
                if(locaX+1<=25)
                    locaX++;
                pos = matrice[locaY][locaX];

                ///La case suivante est un couloir
                if(m_posX+1 < 26 && pos=='8')
                {
                    m_posX++;
                    nb_depl--;
                    m_loca=pos;
                }
                ///La case suivante est une porte de salle
                else if(m_posX+2 <26 && pos=='7')
                {
                    m_posX+=2;
                    m_loca='0';
                    nb_depl--;
                }
                ///La case suivante est un mur (1 ou 0 pour mur de salle)
                else
                    textprintf_ex(buffer, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
            }
            break;
        }
        ///Affichage du plateau
        //blit(plateau, buffer, 0,0,0,0, SCREEN_W, SCREEN_H);
        ///Affichage du pion
        //masked_blit(m_imagePion, buffer, 0,0, (m_posX*23), ((m_posY*23)), SCREEN_W, SCREEN_H);
        ///Affichage du nombre de déplacements restants
        textprintf_ex(buffer, font, 700, 150, makecol(255, 255, 255), -1, "Il vous reste %d deplacements", nb_depl);
        ///Actualisation de l'écran
        //blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
        rest(100);


        setDeplacement(nb_depl);
    }
}

