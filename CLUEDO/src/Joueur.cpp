#include "Joueur.h"

/// ////////////////////////// ///
/// CONSTRUCTEUR / DESTRUCTEUR ///
/// ////////////////////////// ///
Joueur::Joueur()
{
    m_loca='D' ;
}

Joueur::~Joueur()
{}


/// /////// ///
/// GETTERS ///
/// /////// ///

std::string Joueur::getNom()const {return m_nom;}
int Joueur::getPosX()const {return m_posX;}
int Joueur::getPosY()const {return m_posY;}
char Joueur::getLoca()const {return m_loca;}
std::string Joueur::getCouleurPion()const {return m_couleurPion;}
BITMAP* Joueur::getImagePion()const {return m_imagePion ;}
std::map <std::string, bool> Joueur::getHypo()const {return m_hypothese;}
std::vector<Carte> Joueur::getCartes()const {return m_cartes ;}


/// /////// ///
/// SETTERS ///
/// /////// ///

void Joueur::setNom(std::string nom){m_nom=nom;}
void Joueur::setPosX(int posX){m_posX=posX;}
void Joueur::setPosY(int posY){m_posY=posY;}
void Joueur::setLoca(char loca) {m_loca=loca;}
void Joueur::setCouleur(std::string couleur){m_couleurPion=couleur;}
void Joueur::setLogo(BITMAP* logo){m_imagePion=logo;}
void Joueur::setHypo(std::string nouvinfo){m_hypothese[nouvinfo]=true;}



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

void Joueur::cardDisplay(BITMAP* page)const
{
    for(const auto& item : m_cartes)
        item.display(page);
}



/// ////////// ///
/// HYPOTHÈSES ///
/// ////////// ///

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

void Joueur::deplacement(BITMAP* page)
{
    int nb_depl;
    char touche;
    char pos;

    nb_depl=(rand()%(6))+1;
    while(nb_depl>0 || touche!=' ')
    {

        switch(m_loca)
        {
        case '0':
            if(kbhit())
            {
                touche=getch();
                switch(touche)
                {
                case HAUT:
                    if(m_posY-1 > 0 && pos=='0')
                        m_posY--;
                    else if(m_posY-2 > 0 && pos=='7')
                    {
                        m_posY-=2;
                        m_loca='8';
                        nb_depl--;
                    }
                    else
                        textprintf_ex(page, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
                    break;

                case BAS:
                    if(m_posY+1 <26 && pos=='0')
                        m_posY++;
                    else if(m_posY+2 <26 && pos=='7')
                    {
                        m_posY+=2;
                        m_loca='8';
                        nb_depl--;
                    }
                    else
                        textprintf_ex(page, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
                    break;

                case GAUCHE:
                    if(m_posX-1 > 0 && pos=='0')
                        m_posX--;
                    else if(m_posX-2 > 0 && pos=='7')
                    {
                        m_posX-=2;
                        m_loca='8';
                        nb_depl--;
                    }
                    else
                        textprintf_ex(page, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
                    break;

                case DROITE:
                    if(m_posX+1 < 26 && pos=='0')
                        m_posX++;
                    else if(m_posY+2 <26 && pos=='7')
                    {
                        m_posY+=2;
                        m_loca='8';
                        nb_depl--;
                    }
                    else
                        textprintf_ex(page, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
                    break;
                }
            }
            break;

        case '8':

            if(kbhit())
            {
                touche=getch();
                switch(touche)
                {
                case HAUT:
                    if(m_posY-1 > 0 && pos=='8')
                    {
                        m_posY--;
                        nb_depl--;
                    }
                    else if(m_posY-2 > 0 && pos=='7')
                    {
                        m_posY-=2;
                        m_loca='0';
                        nb_depl--;
                    }
                    else
                        textprintf_ex(page, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
                    break;

                case BAS:
                    if(m_posY+1 <26 && pos=='8')
                    {
                        m_posY++;
                        nb_depl--;
                    }
                    else if(m_posY+2 <26 && pos=='7')
                    {
                        m_posY+=2;
                        m_loca='8';
                        nb_depl--;
                    }
                    else
                        textprintf_ex(page, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
                    break;

                case GAUCHE:
                    if(m_posX-1 > 0 && pos=='8')
                    {
                        m_posX--;
                        nb_depl--;
                    }
                    else if(m_posX-2 > 0 && pos=='7')
                    {
                        m_posX-=2;
                        m_loca='0';
                        nb_depl--;
                    }
                    else
                        textprintf_ex(page, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
                    break;

                case DROITE:
                    if(m_posX+1 < 26 && pos=='8')
                    {
                        m_posX++;
                        nb_depl--;
                    }
                    else if(m_posY+2 <26 && pos=='7')
                    {
                        m_posY+=2;
                        m_loca='0';
                        nb_depl--;
                    }
                    else
                        textprintf_ex(page, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
                    break;
                }
            }
            break;

        case 'D':

            if(kbhit())
            {
                touche=getch();
                switch(touche)
                {
                case HAUT:
                    if(m_posY-1 > 0 && pos=='8')
                    {
                        m_posY--;
                        nb_depl--;
                    }
                    else if(m_posY-2 > 0 && pos=='7')
                    {
                        m_posY-=2;
                        m_loca='0';
                        nb_depl--;
                    }
                    else
                        textprintf_ex(page, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
                    break;

                case BAS:
                    if(m_posY+1 <26 && pos=='8')
                    {
                        m_posY++;
                        nb_depl--;
                    }
                    else if(m_posY+2 <26 && pos=='7')
                    {
                        m_posY+=2;
                        m_loca='8';
                        nb_depl--;
                    }
                    else
                        textprintf_ex(page, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
                    break;

                case GAUCHE:
                    if(m_posX-1 > 0 && pos=='8')
                    {
                        m_posX--;
                        nb_depl--;
                    }
                    else if(m_posX-2 > 0 && pos=='7')
                    {
                        m_posX-=2;
                        m_loca='0';
                        nb_depl--;
                    }
                    else
                        textprintf_ex(page, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
                    break;

                case DROITE:
                    if(m_posX+1 < 26 && pos=='8')
                    {
                        m_posX++;
                        nb_depl--;
                    }
                    else if(m_posY+2 <26 && pos=='7')
                    {
                        m_posY+=2;
                        m_loca='0';
                        nb_depl--;
                    }
                    else
                        textprintf_ex(page, font, 700, 100, makecol(255,255, 255), -1, "Deplacement impossible");
                    break;
                }
            }
            break;
        }
    }
}
