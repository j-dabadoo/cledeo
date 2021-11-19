#include "Joueur.h"

/// ////////////////////////// ///
/// CONSTRUCTEUR / DESTRUCTEUR ///
/// ////////////////////////// ///
Joueur::Joueur()
{
    m_nom = "pas de nom" ;
    m_posX = 0 ;
    m_posY = 0 ;
    m_deplacement = 0;
    m_loca='D' ;
    m_score = 0 ;
    m_couleurPion = "pas de couleur" ;
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
int Joueur::getScore()const
{
    std::cout << "score : " << m_score ;
    return m_score ;
}
std::string Joueur::getCouleurPion()const
{
    return m_couleurPion;
}
BITMAP* Joueur::getImagePion()const
{
    return m_imagePion ;
}
BITMAP* Joueur::getLogoHypo()const
{
    return m_logohypo ;
}
std::map <std::string, bool> Joueur::getHypo()const
{
    return m_hypothese;
}
std::vector<Carte> Joueur::getCartes()
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
void Joueur::setLogoHypo(BITMAP* logohypo)
{
    m_logohypo=logohypo;
}
void Joueur::setHypo(std::string nouvinfo)
{
    m_hypothese[nouvinfo]=true;
    /*for(auto& hypo:m_hypothese)
    {
        std::cout<<hypo.first<< " : " << hypo.second << std::endl ;
    }
    std::cout << "FIN------------------------------------" << std::endl ;*/
}
void Joueur::setHypo(std::string nouvinfo, bool etat)
{
    m_hypothese[nouvinfo]=etat;
}
void Joueur::setScore(int score)
{
    m_score = score;
}
void Joueur::setCartes(std::vector <Carte> cartes)
{
    m_cartes = cartes ;
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

void Joueur::cardDisplay(BITMAP* buffer)
{
    int x=0, y=0 ;

    if( static_cast <int> ( getCartes().size() ) > 7)
        rectfill(buffer,615,375,1045,595,makecol(136,0,21));

    else
        rectfill(buffer,615,375,1115,490,makecol(136,0,21));

    for(auto& carte : getCartes())
    {
        ///On donne les positions des cartes
        carte.setPosX(625+70*x);
        carte.setPosY(380+y);
        carte.display(buffer);
        x++;

        ///On affiche les cartes sur une autre ligne à partir de la moitié s'il reste plus de 7 cartes au joueur
        if(((x >= (static_cast <int>(getCartes().size())/2)) and (x >= (static_cast <int>(getCartes().size()+1)/2)))   and    (static_cast <int>(getCartes().size())) > 7)
        {
            x = 0 ;
            y = 110 ;
        }
    }
}




/// ////////// ///
/// HYPOTHÈSES ///
/// ////////// ///

void Joueur::hypotheseInit()
{
    m_hypothese["Sabre"]=false;
    m_hypothese["Pistolet"]=false;
    m_hypothese["Poudre a canon"]=false;
    m_hypothese["Cle"]=false;
    m_hypothese["Tire bouchon"]=false;
    m_hypothese["Canon"]=false;
    m_hypothese["Will Turner"]=false;
    m_hypothese["Bill Turner"]=false;
    m_hypothese["Jack Sparrow"]=false;
    m_hypothese["Barbossa"]=false;
    m_hypothese["Elizabeth Swann"]=false;
    m_hypothese["Davy Jones"]=false;
    m_hypothese["Calypso"]=false;
    m_hypothese["James Norrington"]=false;
    m_hypothese["Barbe Noire"]=false;
    m_hypothese["Baie des Naufrages"]=false;
    m_hypothese["Port Royal"]=false;
    m_hypothese["Ile de la Muerta"]=false;
    m_hypothese["Ile au rhum"]=false;
    m_hypothese["Hollandais Volant"]=false;
    m_hypothese["Ile des 4 vents"]=false;
    m_hypothese["HMS Intrepide"]=false;
    m_hypothese["Triangle des Bermudes"]=false;
    m_hypothese["Black Pearl"]=false;

    /*std::string inter;

    inter = "Sabre";
    m_hypothese[inter]=false;

    inter = "Pistolet";
    m_hypothese[inter]=false;

    inter = "Poudre a canon";
    m_hypothese[inter]=false;

    inter = "Cle";
    m_hypothese[inter]=false;

    inter = "Tire bouchon";
    m_hypothese[inter]=false;

    inter = "Canon";
    m_hypothese[inter]=false;

    inter = "Will Turner";
    m_hypothese[inter]=false;

    inter = "Bill Turner";
    m_hypothese[inter]=false;

    inter = "Jack Sparrow";
    m_hypothese[inter]=false;

    inter = "Barbossa";
    m_hypothese[inter]=false;

    inter = "Elizabeth Swann";
    m_hypothese[inter]=false;

    inter = "Davy Jones";
    m_hypothese[inter]=false;

    inter = "Calypso";
    m_hypothese[inter]=false;

    inter = "James Norrington";
    m_hypothese[inter]=false;

    inter = "Barbe Noire";
    m_hypothese[inter]=false;

    inter = "Baie des Naufrages";
    m_hypothese[inter]=false;

    inter = "Port Royal";
    m_hypothese[inter]=false;

    inter = "Ile de la Muerta";
    m_hypothese[inter]=false;

    inter = "Ile au rhum";
    m_hypothese[inter]=false;

    inter = "Hollandais Volant";
    m_hypothese[inter]=false;

    inter = "Ile des 4 vents";
    m_hypothese[inter]=false;

    inter = "HMS Intrepide";
    m_hypothese[inter]=false;

    inter = "Triangle des Bermudes";
    m_hypothese[inter]=false;

    inter = "Black Pearl";
    m_hypothese[inter]=false;*/
}





/*void Joueur::infoDisplay(BITMAP* buffer)
{
    textprintf_ex(buffer, font, 660, 450, makecol(255, 255, 255), -1, "Joueur : ");
    textprintf_ex(buffer, font, 730, 450, makecol(255, 255, 255), -1,"%s", getNom().c_str());
    masked_blit(m_imagePion, buffer, 0,0, 610, 430, SCREEN_W, SCREEN_H);
    cardDisplay(buffer);
    blit(buffer, screen, 0, 0,0,0, SCREEN_W, SCREEN_H);
}*/




/// ///////////////////////////////////////////////// ///
/// AFFICHAGE DES HYPOTHÈSES DU JOUEUR DANS LA GRILLE ///
/// ///////////////////////////////////////////////// ///

void Joueur::hypoDisplay(BITMAP* buffer) const
{
    int i=0;

    for(const auto& hypo : getHypo())
    {
        textprintf_ex(buffer, font, 20, (10+25*i), makecol(0,0,0), -1, "%s", hypo.first.c_str());

        ///Carré plein si hypo validée
        if(hypo.second==true)
            rectfill(buffer, 370, (5+25*i), 385, (20+25*i), makecol(0,0,0));

        ///Carré vide si non
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
        rest(60);


        setDeplacement(nb_depl);
    }
}



/// /////////////////////////////////////////////////////// ///
/// ECRITURE DANS UN FICHIER TEXTE EN FONCTION DU NOM SAISI ///
/// /////////////////////////////////////////////////////// ///

void Joueur::writeFile()
{
    // pour le mode append, utiliser std::ios::app
    std::ofstream ofs(getNom().c_str(), std::ios::out);

    if (ofs)
    {
        ///Sauvegarde nom
        ofs << getNom() << std::endl;

        ///Sauvegarde PosX
        ofs << getPosX() << std::endl;

        ///Sauvegarde PosY
        ofs << getPosY() << std::endl;

        ///Sauvegarde nb déplacements restants
        ofs << getDeplacement() << std::endl;

        ///Sauvegarde la localisation
        ofs << getLoca() << std::endl;

        ///Sauvegarde le score
        ofs << getScore() << std::endl;

        ///Sauvegarde de la couleur
        ofs << getCouleurPion() << std::endl;


        ///Sauvegarde de la map

        ///Sauvegarde de la taille de la map
        size_t tailleMatrice = m_hypothese.size();
        ofs << tailleMatrice << std::endl ;

        ///Sauvegarder de la map
        std::map<std::string, bool>::iterator it ;
        for (it = m_hypothese.begin() ; it != m_hypothese.end(); it++)
        {
            if(it->second == true)
                ofs << it->first.c_str() <<" : " << 'T' << std::endl ;

            else
                ofs << it->first.c_str() <<" : " << 'F' << std::endl ;
        }

        ///Sauvegarde du vecteur de carte

        ///Sauvegarde de la taille du vecteur
        size_t tailleVec = m_cartes.size();
        ofs << tailleVec << std::endl ;

        for(const auto& carte:getCartes())
        {
            ///Sauvegarde d'une carte

            //Sauvegarde id de la carte
            ofs << carte.getId() << std::endl ;

            //Sauvegarde position X
            ofs << carte.getPosX() << std::endl ;

            //Sauvegarde position Y
            ofs << carte.getPosY() << std::endl ;

            //Sauvegarde nom
            ofs << carte.getNom() << std::endl ;

            //Sauvegarde type
            ofs << carte.getType() << std::endl ;
        }


        ofs.close(); // fermeture du flux
    }
}



/// /////////////////////////////////////////////////// ///
/// LECTURE D'UN FICHIER TEXTE EN FONCTION DU NOM SAISI ///
/// /////////////////////////////////////////////////// ///

void Joueur::readFile()
{
    std::ifstream ifs(getNom().c_str());

    if (ifs) // test si le fichier est bien ouvert
    {
        std::string line;
        int entier;
        char car;

        ///Lecture nom
        ifs >> line ;
        setNom(line);

        ///Lecture PosX
        ifs >> entier ;
        setPosX(entier);

        ///Lecture PosY
        ifs >> entier ;
        setPosY(entier);

        ///Lecture nb déplacements
        ifs >> entier ;
        setDeplacement(entier);

        ///Lecture de la localisation
        ifs >> car ;
        setLoca(car);

        ///Lecture du score
        ifs >> entier ;
        setScore(entier);

        ///Lecture couleur
        ifs >> line;
        setCouleur(line);

        ///Lecture de la taille de la map
        for(int i=0 ; i<5 ; i++)
        {
            ifs >> line ;
            ifs >> car >> car;

            if(car=='T')
                setHypo(line, true);

            else
                setHypo(line, false);
        }


        ///Lecture du vecteur de cartes
        ///Sauvegarde de la taille du vecteur
        int tailleVec ;

        ifs >> tailleVec ;
        m_cartes.resize(tailleVec);

        for(int i=0 ; i < tailleVec ; i++)
        {
            //Lecture id
            ifs >> entier ;
            m_cartes[i].setId(entier) ;

            //Lecture posX
            ifs >> entier ;
            m_cartes[i].setPosX(entier) ;

            //Lecture posY
            ifs >> entier ;
            m_cartes[i].setPosY(entier) ;

            //Lecture nom
            ifs >> line ;
            m_cartes[i].setNom(line) ;

            //Lecture type
            ifs >> line ;
            m_cartes[i].setType(line) ;
        }

        ifs.close(); // fermeture du flux
    }

    else
        std::cout << "Le joueur n'existe pas " << std::endl ;

}


/// ///////////////////////////////////////////// ///
/// RÉCUPÉRATION DES CARTES D'UNE ANCIENNE PARTIE ///
/// ///////////////////////////////////////////// ///

void Joueur::cardRecovery(std::vector <Carte>& cartes)
{
    std::string nom ;

    for(int i=0 ; i < static_cast <int> (getCartes().size()) ; i++)
    {
        std::cout<<"nom carte : " << m_cartes[i].getNom() << "//"<<std::endl;
        for(auto& cartePaquet:cartes)
        {
            nom=" ";
            nom+=cartePaquet.getNom();
            std::cout<<"nom carte paquet : " << cartePaquet.getNom() << "//"<<std::endl;
            ///Si on trouve la carte dans le paquet, on la récupère (pour surtout récupérer sa bitmap)
            if(m_cartes[i].getNom()==nom)
            {
                m_cartes[i].setImage(cartePaquet.getImage());
                std::cout<<"carte recup"<<std::endl;
            }


        }
    }
}



/// /////////////////////////////// ///
/// RÉCUPÉRATION DE L'IMAGE DU PION ///
/// /////////////////////////////// ///

void Joueur::pawnRecovery()
{
    BITMAP * logo = create_bitmap(23, 23);
    std::string path = "images/pion" ;

    path += m_couleurPion + ".bmp" ;

    ///Chargement image
    m_imagePion = load_bitmap(path.c_str(), NULL);

    ///Changement de la taille de l'image
    stretch_blit(m_imagePion, logo, 0,0, m_imagePion->w, m_imagePion->h, 0,0,logo->w, logo->h);
    m_imagePion = logo ;
}




