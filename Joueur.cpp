#include "Joueur.h"

Joueur::Joueur()
    : m_loca('D')
{
    //ctor
}

Joueur::~Joueur()
{
    //dtor
}


void Joueur::setnom(std::string nom)
{
    m_nom=nom;
}

void Joueur::setlogo(BITMAP* logo)
{
    m_imagePion=logo;
}

void Joueur::sethypot(std::string nouvinfo)
{
    m_hypothese[nouvinfo]=true;
}

void Joueur::setcouleur(std::string couleur)
{
    m_couleurPion=couleur;
}

void Joueur::setposX(int posX)
{
    m_posX=posX;
}

void Joueur::setposY(int posY)
{
    m_posY=posY;
}

void Joueur::setloca(char loca)
{
    m_loca=loca;
}

std::string Joueur::getnom()
{
    return m_nom;
}

BITMAP* Joueur::getlogo()
{
    return m_imagePion;
}

std::map <std::string, bool> Joueur::gethypo()
{
    return m_hypothese;
}

std::string Joueur::getcouleur()
{
    return m_couleurPion;
}

int Joueur::getposX()
{
    return m_posX;
}

int Joueur::getposY()
{
    return m_posY;
}

char Joueur::getloca()
{
    return m_loca;
}

void Joueur::add(Carte carte)
{
    m_cartes.push_back(carte);
}

void Joueur::cardDisplay(BITMAP* page)const
{
    for(const auto& item : m_cartes)
    {
        item.display(page);
    }
}

void Joueur::hypotheseinit()
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

void Joueur::infodisplay(BITMAP* page)
{
    textprintf_ex(page, font, 660, 450, makecol(255, 255, 255), -1, "Joueur : ");
    textprintf_ex(page, font, 730, 450, makecol(255, 255, 255), -1,"%s", m_nom);
    masked_blit(m_imagePion, page, 0,0, 610, 430, SCREEN_W, SCREEN_H);
    cardDisplay(page);
    blit(page, screen, 0, 0,0,0, SCREEN_W, SCREEN_H);
}

void Joueur::hypodisplay(BITMAP* page) const
{
    int i=0;
    for(const auto& it : m_hypothese)
    {
        textprintf_ex(page, font, 20, (10+25*i), makecol(0,0,0), -1, "%s", &it.first);
        if(it.second==true)
            rectfill(page, 370, (5+25*i), 385, (20+25*i), makecol(0,0,0));
        else rect(page, 370, (5+25*i), 385, (20+25*i), makecol(0,0,0));
        i++;
    }
}

void Joueur::deplacement(BITMAP* plateau, BITMAP* page, std::vector<std::vector <char>> matrice)
{
    int nb_depl, locaX, locaY;
    char touche='a';
    char pos;

    ///Lancement de dé
    nb_depl=(rand()%(6))+1;

    while(nb_depl>0)
    {
        ///Effacer la page precedante
        clear_bitmap(page);

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
                else if(m_posY-2 > 0 && pos=='7')
                {
                    m_posY-=2;
                    m_loca='8';
                    nb_depl--;
                }
                ///La case suivante est un mur (1 ou 8 pour mur de salle)
                else
                    textprintf_ex(page, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
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
                else if(m_posY+2 <26 && pos=='7')
                {
                    m_posY+=2;
                    m_loca='8';
                    nb_depl--;
                }
                ///La case suivante est un mur (1 ou 8 pour mur de salle)
                else
                    textprintf_ex(page, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
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
                else if(m_posX-2 > 0 && pos=='7')
                {
                    m_posX-=2;
                    m_loca='8';
                    nb_depl--;
                }
                ///La case suivante est un mur (1 ou 8 pour mur de salle)
                else
                    textprintf_ex(page, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
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
                else if(m_posX+2 <26 && pos=='7')
                {
                    m_posX+=2;
                    m_loca='8';
                    nb_depl--;
                }
                ///La case suivante est un mur (1 ou 8 pour mur de salle)
                else
                    textprintf_ex(page, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
                break;
            }


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

                ///La case suivante est une couloir
                if(m_posY-1 > 0 && pos=='8')
                {
                    m_posY--;
                    nb_depl--;
                    m_loca=pos;
                }
                ///La case suivante est une porte de salle
                else if(m_posY-2 > 0 && pos=='7')
                {
                    m_posY-=2;
                    m_loca='0';
                    nb_depl--;
                }
                ///La case suivante est un mur (1 ou 0 pour mur de salle)
                else
                    textprintf_ex(page, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
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
                else if(m_posY+2 <26 && pos=='7')
                {
                    m_posY+=2;
                    m_loca='0';
                    nb_depl--;
                }
                ///La case suivante est un mur (1 ou 0 pour mur de salle)
                else
                    textprintf_ex(page, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
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
                else if(m_posX-2 > 0 && pos=='7')
                {
                    m_posX-=2;
                    m_loca='0';
                    nb_depl--;
                }
                ///La case suivante est un mur (1 ou 0 pour mur de salle)
                else
                    textprintf_ex(page, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
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
                else if(m_posX+2 <26 && pos=='7')
                {
                    m_posX+=2;
                    m_loca='0';
                    nb_depl--;
                }
                ///La case suivante est un mur (1 ou 0 pour mur de salle)
                else
                    textprintf_ex(page, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
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
                else if(m_posY-2 > 0 && pos=='7')
                {
                    m_posY-=2;
                    m_loca='0';
                    nb_depl--;
                }
                ///La case suivante est un mur (1 ou 0 pour mur de salle)
                else
                    textprintf_ex(page, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
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
                    textprintf_ex(page, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
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
                    textprintf_ex(page, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
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
                    textprintf_ex(page, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
            }

        }
        ///Affichage du plateau
        blit(plateau, page, 0,0,0,0, SCREEN_W, SCREEN_H);
        ///Affichage du pion
        masked_blit(m_imagePion, page, 0,0, (m_posX*23), ((m_posY*23)), SCREEN_W, SCREEN_H);
        ///Affichage du nombre de déplacements restants
        textprintf_ex(page, font, 700, 150, makecol(255, 255, 255), -1, "Il vous reste %d deplacements", nb_depl);
        ///Actualisation de l'écran
        blit(page, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
    }
}

