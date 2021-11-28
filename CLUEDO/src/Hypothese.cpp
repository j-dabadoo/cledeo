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

void Hypothese::affichehypo(BITMAP* buffer, std::vector<Joueur>& joueurs, int& tour, int& nb_joueurs, std::vector<Carte>& cartes, std::vector <Arme> &armes,std::vector <Lieu> &lieux,std::vector <Personnage> &personnages)
{
    clear_bitmap(buffer);

    ///Grille d'hypothèse
    rectfill(buffer,0,0,400,600,makecol(239,228,176));
    for(int i=0; i<25; i++)
    {
        hline(buffer, 0, (25+ i*25), 400, makecol(0, 0, 0));
    }
    vline(buffer, 350, 0, 600, makecol(0, 0, 0));
    joueurs[tour].hypoDisplay(buffer);

    int i=0;

    ///affichage des cartes armes
    for(const auto& elem: armes)
    {
        draw_sprite(buffer, elem.getImage(), 450+i, 285) ;
        i=i+80;
    }
    i=0;

    ///affichage des cartes personnages
    for(const auto& elem: personnages)
    {
        draw_sprite(buffer, elem.getImage(), 402+i, 85) ;
        i=i+88;
    }

    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}





/// ///////////////////////////////////////////////////////// ///
/// PERMET DE RENTRER DANS LE MENU HYPOTHÈSE ET D'EN FORMULER ///
/// ///////////////////////////////////////////////////////// ///

void Hypothese::actionhypo(std::vector<Joueur>& joueurs, int& tour, int& nb_joueurs, BITMAP* buffer, std::vector<Carte>& cartes, std::vector <Arme> &armes,std::vector <Lieu> &lieux,std::vector <Personnage> &personnages, BITMAP *des)
{
    int valiarme=0, valiperso=0, valilieu=0, joueurchoisi=0 ;

    Hypothese hypformulee;
    std::string hypoarme, hypopersonnage, hypojou, hypolieu ;

    ///appel du sous programme
    hypformulee.affichehypo(buffer, joueurs,tour,nb_joueurs,cartes,armes,lieux,personnages);

    while(not(key[KEY_SPACE]))
    {

        /// saisie du personnage
        if((mouse_b & 1)and(mouse_x>=402 and mouse_x<=462 and mouse_y>=85 and mouse_y<=185))
        {
            hypopersonnage="Will Turner";
            valiperso=1;

        }
        if((mouse_b & 1)and(mouse_x>=490 and mouse_x<=550 and mouse_y>=85 and mouse_y<=185))
        {
            hypopersonnage="Bill Turner";
            valiperso=1;
        }
        if((mouse_b & 1)and(mouse_x>=578 and mouse_x<=638 and mouse_y>=85 and mouse_y<=185))
        {
            hypopersonnage="Jack Sparrow";
            valiperso=1;
        }
        if((mouse_b & 1)and(mouse_x>=666 and mouse_x<=726 and mouse_y>=85 and mouse_y<=185))
        {
            hypopersonnage="Barbossa";
            valiperso=1;
        }
        if((mouse_b & 1)and(mouse_x>=754 and mouse_x<=814 and mouse_y>=85 and mouse_y<=185))
        {
            hypopersonnage="Elizabeth Swann";
            valiperso=1;

        }
        if((mouse_b & 1)and(mouse_x>=842 and mouse_x<=902 and mouse_y>=85 and mouse_y<=185))
        {
            hypopersonnage="Davy Jones";
            valiperso=1;
        }
        if((mouse_b & 1)and (mouse_x>=930 and mouse_x<=990 and mouse_y>=85 and mouse_y<=185))
        {
            hypopersonnage="Calypso";
            valiperso=1;
        }
        if((mouse_b & 1)and( mouse_x>=1018 and mouse_x<=1078 and mouse_y>=85 and mouse_y<=185))
        {
            hypopersonnage="James Norrington";
            valiperso=1;
        }
        if((mouse_b & 1)and(mouse_x>=1106 and mouse_x<=1166 and mouse_y>=85 and mouse_y<=185))
        {
            hypopersonnage="Barbe Noire";
            valiperso=1;
        }

        ///saisie de l'arme
        if(mouse_b&1 and(mouse_x>=450 and mouse_x<=510 and mouse_y>=285 and mouse_y<=385))
        {
            hypoarme="Sabre";
            valiarme=1;
        }
        if((mouse_b & 1)and(mouse_x>=530 and mouse_x<=590 and mouse_y>=285 and mouse_y<=385))
        {
            hypoarme="Pistolet";

            valiarme=1;
        }
        if((mouse_b & 1)and(mouse_x>=610 and mouse_x<=670 and mouse_y>=285 and mouse_y<=385))
        {
            hypoarme="Poudre a canon";
            valiarme=1;
        }
        if((mouse_b & 1)and(mouse_x>=690 and mouse_x<=750 and mouse_y>=285 and mouse_y<=385))
        {
            hypoarme="Cle";
            valiarme=1;
        }
        if((mouse_b & 1)and(mouse_x>=770 and mouse_x<=830 and mouse_y>=285 and mouse_y<=385))
        {
            hypoarme="Tire bouchon";
            valiarme=1;
        }
        if((mouse_b & 1)and(mouse_x>=850 and mouse_x<=910 and mouse_y>=285 and mouse_y<=385))
        {
            hypoarme="Canon";
            valiarme=1;
        }


        hypolieu=hypformulee.trouvelieu(joueurs[tour]);
        valilieu=1;

        ///changement avec les setters
        hypformulee.setArme(hypoarme);
        hypformulee.setLieu(hypolieu);
        hypformulee.setPersonnage(hypopersonnage);


        if(tour==nb_joueurs-1)
            joueurchoisi=0;

        else
            joueurchoisi=tour+1;

        if(valiarme==1 and valiperso==1 and valilieu==1)
            hypformulee.verifhypochezlejoueuraccuse(joueurs, joueurchoisi,hypoarme,hypopersonnage, hypolieu, tour, buffer);
    }

    while(key[KEY_SPACE]){}
}



/// ///////////////////////////////////////// ///
/// CHERCHE LE LIEU DANS LEQUEL LE JOUEUR EST ///
/// ///////////////////////////////////////// ///

std::string Hypothese::trouvelieu(Joueur lejoueur)
{
    ///Si le joueur est dans :
    //Le Hollandais Volant
    if(lejoueur.getPosX() < 9 and lejoueur.getPosY() < 7)
        return "Hollandais Volant";

    //L'Ile des 4 vents
    else if(lejoueur.getPosX() > 8 and lejoueur.getPosX() < 17 and lejoueur.getPosY() < 8)
        return "Ile des 4 vents";

    //Le Port Royal
    else if(lejoueur.getPosX() > 18 and lejoueur.getPosY() < 7)
        return "Port Royal";

    //L'Ile de la Muerta
    else if(lejoueur.getPosX() < 10 and lejoueur.getPosY() > 8 and lejoueur.getPosY() < 16)
        return "Ile de la Muerta";

    //Le Triangle des Bermudes
    else if(lejoueur.getPosX() > 19 and lejoueur.getPosY() > 8 and lejoueur.getPosY() < 13)
        return "Triangle des Bermudes";

    //L'Ile au rhum
    else if(lejoueur.getPosX() > 18 and lejoueur.getPosY() > 14 and lejoueur.getPosY() < 19)
        return "Ile au rhum";

    //Le Black Pearl
    else if(lejoueur.getPosX() < 9 and lejoueur.getPosY() > 19)
        return "Black Pearl";

    //La Baie des Naufragés
    else if(lejoueur.getPosX() > 10 and lejoueur.getPosX() < 17 and lejoueur.getPosY() > 18)
        return "Baie des Naufrages";

    //Le HMS Intrepide
    else if(lejoueur.getPosX() > 18 and lejoueur.getPosY() > 21)
        return "HMS Intrepide";

    //L'Ile de Tortuga
    else if(lejoueur.getPosX() > 9 and lejoueur.getPosX() < 17 and lejoueur.getPosY() > 9 and lejoueur.getPosY() < 17)
        return "Tortuga";

    else return "Couloir";
}



/// ////////////////// ///
/// VERIF D'HYPOTHÈSES ///
/// ////////////////// ///

void Hypothese::verifhypochezlejoueuraccuse(std::vector<Joueur>& joueurs, int accuse, std::string armeverif, std::string persoverif, std::string lieuverif, int tour, BITMAP* buffer)
{
    Hypothese hypoverifee;

    for( const auto& elem : joueurs[accuse].getCartes())
    {
        if(elem.getNom()==armeverif)
            hypoverifee.setArme(armeverif);

        if(elem.getNom()==lieuverif)
            hypoverifee.setLieu(lieuverif);

        if(elem.getNom()==persoverif)
            hypoverifee.setLieu(persoverif);
    }
    hypoverifee.incluhypo(joueurs, tour, hypoverifee, buffer);
}




/// ////////////////// ///
/// AJOUT D'HYPOTHÈSES ///
/// ////////////////// ///

void Hypothese::incluhypo(std::vector<Joueur>& joueurs, int& tour, Hypothese hypoaajt, BITMAP* buffer)
{
    if(hypoaajt.getLieu() != "Couloir")
    {
        joueurs[tour].setHypo(hypoaajt.getArme());
        joueurs[tour].setHypo(hypoaajt.getLieu());
        joueurs[tour].setHypo(hypoaajt.getPersonnage());
        rectfill(buffer,0,0,400,600,makecol(239,228,176));

        for(int i=0; i<25; i++)
        {
            hline(buffer, 0, (25+ i*25), 400, makecol(0, 0, 0));
        }
        vline(buffer, 350, 0, 600, makecol(0, 0, 0));
        joueurs[tour].hypoDisplay(buffer);
        blit(buffer,screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
}


/// ///////////////// ///
/// ACCUSATION FINALE ///
/// ///////////////// ///

int Hypothese::accusationfinale(BITMAP* buffer, std::vector<Joueur> joueurs, std::vector <Carte> &secret, std::vector<Arme> armes, std::vector<Personnage> persos, std::vector<Lieu> lieux)
{
    std::string what;
    std::string where;
    std::string who;

    bool goodarme=false;
    bool goodlieu=false;
    bool goodperso=false;

    int valiarme=0;
    int valiperso=0;
    int valilieu=0;

    disaccusationfinale(buffer,joueurs,secret,armes,persos, lieux);

    std::cout<<secret[0].getNom()<<std::endl;
    std::cout<<secret[1].getNom()<<std::endl;
    std::cout<<secret[2].getNom()<<std::endl;

    while(not(key[KEY_LEFT]) and not(valiarme==1 and valilieu==1 and valiperso==1))
    {

        ///saisie du personnage
        if((mouse_b & 1)and(mouse_x>=50 and mouse_x<=110 and mouse_y>=85 and mouse_y<=185))
        {
            who="Will Turner";
            valiperso=1;
        }
        if((mouse_b & 1)and(mouse_x>=138 and mouse_x<=198 and mouse_y>=85 and mouse_y<=185))
        {
            who="Bill Turner";
            valiperso=1;
        }
        if((mouse_b & 1)and(mouse_x>=226 and mouse_x<=286 and mouse_y>=85 and mouse_y<=185))
        {
            who="Jack Sparrow";
            valiperso=1;
        }
        if((mouse_b & 1)and(mouse_x>=314 and mouse_x<=374 and mouse_y>=85 and mouse_y<=185))
        {
            who="Barbossa";
            valiperso=1;
        }
        if((mouse_b & 1)and(mouse_x>=402 and mouse_x<=462 and mouse_y>=85 and mouse_y<=185))
        {
            who="Elizabeth Swann";
            valiperso=1;
        }
        if((mouse_b & 1)and(mouse_x>=490 and mouse_x<=550 and mouse_y>=85 and mouse_y<=185))
        {
            who="Davy Jones";
            valiperso=1;
        }
        if((mouse_b & 1)and (mouse_x>=578 and mouse_x<=638 and mouse_y>=85 and mouse_y<=185))
        {
            who="Calypso";
            valiperso=1;
        }
        if((mouse_b & 1)and( mouse_x>=666 and mouse_x<=726 and mouse_y>=85 and mouse_y<=185))
        {
            who="James Norrington";
            valiperso=1;
        }
        if((mouse_b & 1)and(mouse_x>=754 and mouse_x<=814 and mouse_y>=85 and mouse_y<=185))
        {
            who="Barbe Noire";
            valiperso=1;
        }

        ///Saisie de l'arme
        if(mouse_b&1 and(mouse_x>=50 and mouse_x<=110 and mouse_y>=285 and mouse_y<=385))
        {
            what="Sabre";
            valiarme=1;
        }
        if((mouse_b & 1)and(mouse_x>=138 and mouse_x<=198 and mouse_y>=285 and mouse_y<=385))
        {
            what="Pistolet";
            valiarme=1;
        }
        if((mouse_b & 1)and(mouse_x>=226 and mouse_x<=286 and mouse_y>=285 and mouse_y<=385))
        {
            what="Poudre a canon";
            valiarme=1;
        }
        if((mouse_b & 1)and(mouse_x>=314 and mouse_x<=374 and mouse_y>=285 and mouse_y<=385))
        {
            what="Cle";
            valiarme=1;
        }
        if((mouse_b & 1)and(mouse_x>=402 and mouse_x<=462 and mouse_y>=285 and mouse_y<=385))
        {
            what="Tire bouchon";
            valiarme=1;
        }
        if((mouse_b & 1)and(mouse_x>=490 and mouse_x<=550 and mouse_y>=285 and mouse_y<=385))
        {
            what="Canon";
            valiarme=1;
        }

        ///Saisie du lieu
        if((mouse_b & 1)and(mouse_x>=50 and mouse_x<=110 and mouse_y>=485 and mouse_y<=585))
        {
            where="Baie des Naufrages";
            valilieu=1;
        }
        if((mouse_b & 1)and(mouse_x>=138 and mouse_x<=198 and mouse_y>=485 and mouse_y<=585))
        {
            where="Port Royal";
            valilieu=1;
        }
        if((mouse_b & 1)and(mouse_x>=226 and mouse_x<=286 and mouse_y>=485 and mouse_y<=585))
        {
            where="Ile de la Muerta";
            valilieu=1;
        }
        if((mouse_b & 1)and(mouse_x>=314 and mouse_x<=374 and mouse_y>=485 and mouse_y<=585))
        {
            where="Ile au rhum";
            valilieu=1;
        }
        if((mouse_b & 1)and(mouse_x>=402 and mouse_x<=462 and mouse_y>=485 and mouse_y<=585))
        {
            where="Hollandais Volant";
            valilieu=1;
        }
        if((mouse_b & 1)and(mouse_x>=490 and mouse_x<=550 and mouse_y>=485 and mouse_y<=585))
        {
            where="Ile des 4 vents";
            valilieu=1;
        }
        if((mouse_b & 1)and (mouse_x>=578 and mouse_x<=638 and mouse_y>=485 and mouse_y<=585))
        {
            where="HMS Intrepide";
            valilieu=1;
        }
        if((mouse_b & 1)and( mouse_x>=666 and mouse_x<=726 and mouse_y>=485 and mouse_y<=585))
        {
            where="Triangle des Bermudes";
            valilieu=1;
        }
        if((mouse_b & 1)and(mouse_x>=754 and mouse_x<=814 and mouse_y>=485 and mouse_y<=585))
        {
            where="Black Pearl";
            valilieu=1;
        }

        rectfill(buffer, 901, 319, 1050, 333, makecol(239, 228, 176));
        rectfill(buffer, 901, 344, 1050, 358, makecol(239, 228, 176));
        rectfill(buffer, 901, 369, 1050, 383, makecol(239, 228, 176));
        textprintf_ex(buffer, font,910, 319, makecol(0, 0, 0), makecol(239, 228, 176), who.c_str());
        textprintf_ex(buffer, font,910, 344, makecol(0, 0, 0), makecol(239, 228, 176), what.c_str());
        textprintf_ex(buffer, font,910, 369, makecol(0, 0, 0), makecol(239, 228, 176), where.c_str());

        blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);

        if(valiarme==1 and valilieu==1 and valiperso==1)
        {
            ///verification avec la pochette secrete
            for(const auto& verif: secret)
            {
                if(verif.getNom()==who)
                    goodperso=true;

                if(verif.getNom()==where)
                    goodlieu=true;

                if(verif.getNom()==what)
                    goodarme=true;
            }
        }
    }

    if(goodarme==true and goodlieu==true and goodperso==true)
    {
        //allegro_message("bravo vous avez gagne");
        ///on rajoute l'écran de fin
        return 1;
    }
    else
    {
        return 0;
    }
}



void Hypothese::disaccusationfinale(BITMAP* buffer, std::vector<Joueur> joueurs, std::vector <Carte> &secret, std::vector<Arme> armes, std::vector<Personnage> persos, std::vector<Lieu> lieux)
{
    clear_bitmap(buffer);

    int i=0;

    rectfill(buffer,750,285,1050,385,makecol(239,228,176));

    for(int i=0; i<3; i++)
        hline(buffer, 750, 310+25*i, 1050, makecol(0, 0, 0));

    vline(buffer, 900, 310, 385, makecol(0, 0, 0));
    textprintf_ex(buffer, font, 800, 294, makecol(0, 0, 0), -1, "VOTRE ACCUSATION FINALE");
    textprintf_ex(buffer, font, 775, 319, makecol(0, 0, 0), -1, "PERSONNAGE");
    textprintf_ex(buffer, font,800, 344, makecol(0, 0, 0), -1, "ARME");
    textprintf_ex(buffer, font, 800, 369, makecol(0, 0, 0), -1, "LIEU");

    ///affichage des cartes personnages
    for(const auto& elem: persos)
    {
        draw_sprite(buffer, elem.getImage(), 50+i, 85) ;
        i=i+88;
    }
    i=0;
    ///affichage des cartes armes
    for(const auto& elem: armes)
    {
        draw_sprite(buffer, elem.getImage(), 50+i, 285) ;
        i=i+88;
    }
    i=0;
    ///affichage des cartes personnages
    for(const auto& elem: lieux)
    {
        draw_sprite(buffer, elem.getImage(), 50+i, 485) ;
        i=i+88;
    }
    blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
}
