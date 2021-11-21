#include "Hypothese.h"

Hypothese::Hypothese()
{}

Hypothese::~Hypothese()
{}


/// /////// ///
/// GETTERS ///
/// /////// ///

std::string Hypothese::getLieu()
{
    return m_lieu;
}
std::string Hypothese::getArme()
{
    return m_arme;
}
std::string Hypothese::getPersonnage()
{
    return m_personnage;
}
std::string Hypothese::getJou()
{
    return m_jou;
}



/// /////// ///
/// SETTERS ///
/// /////// ///

void Hypothese:: setLieu(std::string lieu)
{
    m_lieu=lieu;
}
void Hypothese:: setPersonnage(std::string personnage)
{
    m_personnage=personnage;
}
void Hypothese:: setArme(std::string arme)
{
    m_arme=arme;
}void Hypothese:: setJou(std::string jou)
{
    m_jou=jou;
}



/// ////// ///
/// AUTRES ///
/// ////// ///

void Hypothese::displayHypo()
{
    textprintf_ex(screen,font, 500, 475,makecol(239, 228, 176), -1, getPersonnage().c_str());
    textprintf_ex(screen,font, 500, 510,makecol(239, 228, 176), -1, getLieu().c_str());
    textprintf_ex(screen,font, 500, 535,makecol(239, 228, 176), -1, getArme().c_str());
    textprintf_ex(screen,font, 500, 560,makecol(239, 228, 176), -1, getJou().c_str());
}



/// ///////////////////////////////// ///
/// AFFICHAGE DE L'ÉCRAN D'YHOPTHÈSES ///
/// ///////////////////////////////// ///

void Hypothese::affichehypo(BITMAP* buffer, std::vector<Joueur>& joueurs, int& tour, int& nb_joueurs)
{
    clear_bitmap(buffer);

    ///BITMAP
    //personnages
    BITMAP* barbenoire      = load_bitmap("images/barbenoire.bmp",      NULL);
    BITMAP* billturner      = load_bitmap("images/billturner.bmp",      NULL);
    BITMAP* calypso         = load_bitmap("images/calypso.bmp",         NULL);
    BITMAP* davyjones       = load_bitmap("images/davyjones.bmp",       NULL);
    BITMAP* jacksparrow     = load_bitmap("images/jacksparrow.bmp",     NULL);
    BITMAP* jamesnorrington = load_bitmap("images/jamesnorrington.bmp", NULL);
    BITMAP* swann           = load_bitmap("images/swann.bmp",           NULL);
    BITMAP* barbossa        = load_bitmap("images/barbossa.bmp",        NULL);
    BITMAP* willturner      = load_bitmap("images/willturner.bmp",      NULL);

    //armes
    BITMAP* canon           = load_bitmap("images/canon.bmp",           NULL);
    BITMAP* cle             = load_bitmap("images/cle.bmp",             NULL);
    BITMAP* pistolet        = load_bitmap("images/pistolet.bmp",        NULL);
    BITMAP* poudre          = load_bitmap("images/poudre.bmp",          NULL);
    BITMAP* sabre           = load_bitmap("images/sabre.bmp",           NULL);
    BITMAP* tirebouchon     = load_bitmap("images/tirebouchon.bmp",     NULL);


    ///Grille d'hypothèse
    rectfill(buffer,0,0,400,600,makecol(239,228,176));
    for(int i=0; i<25; i++)
    {
        hline(buffer, 0, (25+ i*25), 400, makecol(0, 0, 0));
    }
    vline(buffer, 350, 0, 600, makecol(0, 0, 0));
    joueurs[tour].hypoDisplay(buffer);


    ///Affichage des personnages
    textprintf_ex(buffer,font, 500, 75,makecol(239, 228, 176), -1, "personnages: ");
    blit(barbenoire, buffer,0,0, 402, 85, SCREEN_W, SCREEN_H);
    blit(billturner, buffer,0,0, 490, 85, SCREEN_W, SCREEN_H);
    blit(calypso, buffer, 0,0,578, 85, SCREEN_W, SCREEN_H);
    blit(davyjones, buffer,0,0, 666, 85, SCREEN_W, SCREEN_H);
    blit(jacksparrow, buffer,0,0, 754, 85,SCREEN_W, SCREEN_H);
    blit(jamesnorrington, buffer,0,0, 842, 85, SCREEN_W, SCREEN_H);
    blit(swann, buffer,0,0, 930, 85, SCREEN_W, SCREEN_H);
    blit(barbossa, buffer, 0,0,1018, 85, SCREEN_W, SCREEN_H);
    blit(willturner, buffer,0,0, 1106, 85, SCREEN_W, SCREEN_H);


    ///Affichage des armes
    textprintf_ex(buffer,font, 500, 275,makecol(239, 228, 176), -1, "armes: ");
    blit(canon, buffer,0,0, 402, 285, SCREEN_W, SCREEN_H);
    blit(poudre, buffer,0,0, 535, 285, SCREEN_W, SCREEN_H);
    blit(tirebouchon, buffer, 0,0,668, 285, SCREEN_W, SCREEN_H);
    blit(cle, buffer,0,0, 801, 285, SCREEN_W, SCREEN_H);
    blit(sabre, buffer,0,0, 934, 285,SCREEN_W, SCREEN_H);
    blit(pistolet, buffer,0,0, 1067, 285, SCREEN_W, SCREEN_H);



    textprintf_ex(buffer,font, 500, 435,makecol(239, 228, 176), -1, "joueurs: ");

    int i=0;
    for(const auto& elem: joueurs)
    {
        draw_sprite(buffer, elem.getImagePion(), 450+i, 450) ;
        i=i+100;
    }

    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);


    destroy_bitmap(barbenoire);
    destroy_bitmap(billturner);
    destroy_bitmap(calypso);
    destroy_bitmap(davyjones);
    destroy_bitmap(jacksparrow);
    destroy_bitmap(jamesnorrington);
    destroy_bitmap(swann);
    destroy_bitmap(barbossa);
    destroy_bitmap(willturner);
    destroy_bitmap(canon);
    destroy_bitmap(cle);
    destroy_bitmap(pistolet);
    destroy_bitmap(poudre);
    destroy_bitmap(sabre);
    destroy_bitmap(tirebouchon);
}





/// ///////////////////////////////////////////////////////// ///
/// PERMET DE RENTRER DANS LE MENU HYPOTHÈSE ET D'EN FORMULER ///
/// ///////////////////////////////////////////////////////// ///

void Hypothese::actionhypo(std::vector<Joueur>& joueurs, int& tour, int& nb_joueurs, BITMAP* buffer)
{
    int valiarme=0, valiperso=0, valilieu=0, valijou=0, joueurchoisi=0 ;

    Hypothese hypformulee;
    std::string hypoarme, hypopersonnage, hypojou, hypolieu ;




    hypformulee.affichehypo(buffer, joueurs, tour, nb_joueurs);


    while(not(key[KEY_SPACE]) or not(valiarme==1 and valiperso==1 and valilieu==1 and valijou==1))
    {
        hypformulee.affichehypo(buffer, joueurs, tour, nb_joueurs);


        /// saisie du personnage
        if((mouse_b & 1)and(mouse_x>=402 and mouse_x<=462 and mouse_y>=85 and mouse_y<=185))
        {
            hypopersonnage="Barbe Noire";
            valiperso=1;
        }
        if((mouse_b & 1)and(mouse_x>=490 and mouse_x<=550 and mouse_y>=85 and mouse_y<=185))
        {
            hypopersonnage="Bill Turner";
            valiperso=1;
        }
        if((mouse_b & 1)and(mouse_x>=578 and mouse_x<=638 and mouse_y>=85 and mouse_y<=185))
        {
            hypopersonnage="Calypso";
            valiperso=1;
        }
        if((mouse_b & 1)and(mouse_x>=666 and mouse_x<=726 and mouse_y>=85 and mouse_y<=185))
        {
            hypopersonnage="Davy Jones";
            valiperso=1;
        }
        if((mouse_b & 1)and(mouse_x>=754 and mouse_x<=814 and mouse_y>=85 and mouse_y<=185))
        {
            hypopersonnage="Jack Sparrow";
            valiperso=1;

        }
        if((mouse_b & 1)and(mouse_x>=842 and mouse_x<=902 and mouse_y>=85 and mouse_y<=185))
        {
            hypopersonnage="James Norrington";
            valiperso=1;
        }
        if((mouse_b & 1)and (mouse_x>=930 and mouse_x<=990 and mouse_y>=85 and mouse_y<=185))
        {
            hypopersonnage="Elizabeth Swann";
            valiperso=1;
        }
        if((mouse_b & 1)and( mouse_x>=1018 and mouse_x<=1078 and mouse_y>=85 and mouse_y<=185))
        {
            hypopersonnage="Barbossa";
            valiperso=1;
        }
        if((mouse_b & 1)and(mouse_x>=1106 and mouse_x<=1166 and mouse_y>=85 and mouse_y<=185))
        {
            hypopersonnage="Will Turner";
            valiperso=1;
        }


        ///saisie de l'arme
        if(mouse_b&1 and(mouse_x>=402 and mouse_x<=462 and mouse_y>=285 and mouse_y<=385))
        {
            hypoarme="Canon";
            valiarme=1;
        }
        if((mouse_b & 1)and(mouse_x>=535 and mouse_x<=595 and mouse_y>=285 and mouse_y<=385))
        {
            hypoarme="Poudre a canon";
            valiarme=1;
        }
        if((mouse_b & 1)and(mouse_x>=668 and mouse_x<=728 and mouse_y>=285 and mouse_y<=385))
        {
            hypoarme="Tire Bouchon";
            valiarme=1;
        }
        if((mouse_b & 1)and(mouse_x>=801 and mouse_x<=861 and mouse_y>=285 and mouse_y<=385))
        {
            hypoarme="Cle";
            valiarme=1;
        }
        if((mouse_b & 1)and(mouse_x>=934 and mouse_x<=994 and mouse_y>=285 and mouse_y<=385))
        {
            hypoarme="Sabre";
            valiarme=1;
        }
        if((mouse_b & 1)and(mouse_x>=1067 and mouse_x<=1127 and mouse_y>=285 and mouse_y<=385))
        {
            hypoarme="Pistolet";
            valiarme=1;
        }

        ///saisie du joueur accuse
        if(mouse_b &1 and(mouse_x>=450 and mouse_x<=473 and mouse_y>=450 and mouse_y<=475))
        {
            joueurchoisi=0;
            if(joueurchoisi!=tour)
            {
                hypojou=joueurs[joueurchoisi].getNom();
                valijou=1;
            }

        }
        if(mouse_b &1 and(mouse_x>=550 and mouse_x<=573 and mouse_y>=450 and mouse_y<=475))
        {
            joueurchoisi=1;
            if(joueurchoisi!=tour)
            {
                hypojou=joueurs[joueurchoisi].getNom();
                valijou=1;
            }
        }

        if(mouse_b &1 and(mouse_x>=650 and mouse_x<=673 and mouse_y>=450 and mouse_y<=475))
        {
            joueurchoisi=2;
            if(joueurchoisi!=tour)
            {
                hypojou=joueurs[joueurchoisi].getNom();
                valijou=1;
            }

        }
        if(mouse_b &1 and(mouse_x>=750 and mouse_x<=773 and mouse_y>=450 and mouse_y<=475))
        {
            joueurchoisi=3;
            if(joueurchoisi!=tour)
            {
                hypojou=joueurs[joueurchoisi].getNom();
                valijou=1;
            }

        }
        if(mouse_b &1 and(mouse_x>=850 and mouse_x<=873 and mouse_y>=450 and mouse_y<=475))
        {
            joueurchoisi=4;
            if(joueurchoisi!=tour)
            {
                hypojou=joueurs[joueurchoisi].getNom();
                valijou=1;
            }

        }

        hypolieu=trouvlieu(joueurs[tour]);
        //std::cout<<"lieu : " << hypolieu << std::endl ;
        valilieu=1;


        ///changement avec les setters
        hypformulee.setArme(hypoarme);
        hypformulee.setLieu(hypolieu);
        hypformulee.setPersonnage(hypopersonnage);

        if(valiarme==1 and valiperso==1 and valilieu==1 and valijou==1)
            hypformulee.verifhypochezlejoueuraccuse(joueurs, joueurchoisi,hypoarme,hypopersonnage, hypolieu, tour);
    }
}



/// ///////////////////////////////////////// ///
/// CHERCHE LE LIEU DANS LEQUEL LE JOUEUR EST ///
/// ///////////////////////////////////////// ///

std::string Hypothese::trouvlieu(Joueur lejoueur)
{
    ///Si le joueur est dans :
    ///Le Hollandais Volant
    if(lejoueur.getPosX() < 7 and lejoueur.getPosY() < 7)
        return "Hollandais Volant";

    ///L'Ile des 4 vents
    else if(lejoueur.getPosX() > 10 and lejoueur.getPosX() < 17 and lejoueur.getPosY() < 8)
        return "Ile des 4 vents";

    ///Le Port Royal
    else if(lejoueur.getPosX() > 20 and lejoueur.getPosY() < 6)
        return "Port Royal";

    ///L'Ile de la Muerta
    else if(lejoueur.getPosX() < 9 and lejoueur.getPosY() > 9 and lejoueur.getPosY() < 16)
        return "Ile de la Muerta";

    ///Le Triangle des Bermudes
    else if(lejoueur.getPosX() > 11 and lejoueur.getPosY() > 8 and lejoueur.getPosY() < 13)
        return "Triangle des Bermudes";

    ///L'Ile au rhum
    else if(lejoueur.getPosX() > 18 and lejoueur.getPosY() > 14 and lejoueur.getPosY() < 19)
        return "Ile au rhum";

    ///Le Black Pearl
    else if(lejoueur.getPosX() < 8 and lejoueur.getPosY() > 19)
        return "Black Pearl";

    ///La Baie des Naufragés
    else if(lejoueur.getPosX() > 10 and lejoueur.getPosX() < 16 and lejoueur.getPosY() > 18)
        return "Baie des Naufrages";

    ///Le HMS Intrepide
    else if(lejoueur.getPosX() > 18 and lejoueur.getPosY() > 21)
        return "HMS Intrepide";

    ///L'Ile de Tortuga
    else if(lejoueur.getPosX() > 11 and lejoueur.getPosX() < 16 and lejoueur.getPosY() > 9 and lejoueur.getPosY() < 17)
        return "Tortuga";

    else return "Couloir";
}



/// ////////////////// ///
/// VERIF D'HYPOTHÈSES ///
/// ////////////////// ///

void Hypothese::verifhypochezlejoueuraccuse(std::vector<Joueur>& joueurs, int accuse, std::string armeverif, std::string persoverif, std::string lieuverif, int tour)
{
    Hypothese hypoverifee;

    for( auto& elem: joueurs[accuse].getCartes())
    {
        if(elem.getNom()==armeverif)
            hypoverifee.setArme(armeverif);

        if(elem.getNom()==lieuverif)
            hypoverifee.setLieu(lieuverif);

        if(elem.getNom()==persoverif)
            hypoverifee.setLieu(persoverif);
    }
    hypoverifee.incluhypo(joueurs, tour, hypoverifee);
}




/// ////////////////// ///
/// AJOUT D'HYPOTHÈSES ///
/// ////////////////// ///

void Hypothese::incluhypo(std::vector<Joueur>& joueurs, int& tour, Hypothese hypoaajt)
{
    if(hypoaajt.getLieu() != "Couloir")
    {
        joueurs[tour].setHypo(hypoaajt.getArme());
        joueurs[tour].setHypo(hypoaajt.getLieu());
        joueurs[tour].setHypo(hypoaajt.getPersonnage());
    }
}


