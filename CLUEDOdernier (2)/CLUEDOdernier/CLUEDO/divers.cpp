#include "header.h"

/// ////////////////////////////////// ///
/// PERMET DE PASSER AU JOUEUR SUIVANT ///
/// ////////////////////////////////// ///

void tourParTour(int& tour, int& nb_joueurs, std::vector<Joueur>& joueurs)
{

    while(key[KEY_SPACE]) //Permet de ne rien faire tant que la touche est appuyée (ne va donc pas sauter plusieurs tour
    {}

    joueurs[tour].setDeplacement(0); //Si le joueur n'a pas effectué tous ses déplacements on lui met à 0

    tour++ ; ///Incrementation du compteur tour pour passer au joueur suivant

    ///Revient au premier joueur
    if (tour==nb_joueurs)
        tour=0 ;
}



/// /////////////////// ///
/// LANCEMENT DES 2 DÉS ///
/// /////////////////// ///

int lancerDe(BITMAP *buffer, BITMAP *des, FONT* broadway)
{
    std::vector <BITMAP*> imgDe ;
    BITMAP* buffer2 = create_bitmap(1200, 600);
    int resultat1, resultat2;

    imgDe.push_back(load_bitmap("images/de.bmp", NULL));
    imgDe.push_back(load_bitmap("images/UN.bmp", NULL));
    imgDe.push_back(load_bitmap("images/DEUX.bmp", NULL));
    imgDe.push_back(load_bitmap("images/TROIS.bmp", NULL));
    imgDe.push_back(load_bitmap("images/QUATRE.bmp", NULL));
    imgDe.push_back(load_bitmap("images/CINQ.bmp", NULL));
    imgDe.push_back(load_bitmap("images/SIX.bmp", NULL));

    ///On efface le buffer de dé, on remet le fond vert de la case, puis on remet à l'écran
    clear_bitmap(des);
    rectfill(des,0,0,des->w,des->h,makecol(59,162,71));
    blit(des, buffer, 0, 0, 900, 75, SCREEN_W, SCREEN_H );

    for(int i=0; i<10; i++)
    {
        clear_bitmap(buffer2);
        blit(buffer, buffer2, 0, 0, 0, 0, SCREEN_W, SCREEN_H) ;
        rotate_sprite(buffer2, imgDe[0], 910, 140, ftofix(20*i));
        rotate_sprite(buffer2, imgDe[0],1030, 140, ftofix(20*i));
        textprintf_ex(buffer, broadway, 955, 282, 1, -1, "LANCER");

        blit(buffer2, screen, 0, 0,0, 0, SCREEN_W, SCREEN_H );

        rest(70);
    }

    ///Génération aléatoire pour les 2 dés
    resultat1 = rand()%(6)+1 ;
    resultat2 = rand()%(6)+1 ;


    draw_sprite(des, imgDe[resultat1], 20, 75);
    draw_sprite(des, imgDe[resultat2], 130, 75);


    for(int i=0 ; i<7 ; i++)
        destroy_bitmap(imgDe[i]) ;

    return resultat1 + resultat2 ;
}



/// //////////////////////////// ///
/// ACTUALISATION DE L'AFFICHAGE ///
/// //////////////////////////// ///

void actualisation(BITMAP* buffer, BITMAP* plateau, std::vector<Joueur>& joueurs, int& tour, int& nb_joueurs, BITMAP *des, BITMAP* fond, FONT* broadway)
{
    blit(fond, buffer, 0, 0, 600, 0, fond->w, fond->h);

    ///Affichage du plateau
    blit(plateau, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    ///Quitter le jeu
    rectfill(buffer,1040,15,1190,50,makecol(127,127,127));
    if(mouse_x>=1040 and mouse_x<=1190 and mouse_y>=15 and mouse_y<=50)
        rect(buffer, 1037, 12, 1193, 53,makecol(127,127,127));
    textprintf_ex(buffer, broadway, 1043, 14, 1, -1, "QUITTER");

    ///Bouton hypothese
    rectfill(buffer,620,75,820,125,makecol(208,82,41));
    if(mouse_x>=620 and mouse_x<=820 and mouse_y>=75 and mouse_y<=125)
        rect(buffer, 617, 72, 823, 128, makecol(208,82,41));
    textprintf_ex(buffer, broadway, 620, 82, 1, -1, "HYPOTHESE");

    ///Zone de dé
    rectfill(buffer,900,75,1150,325,makecol(59,162,71));
    blit(des, buffer, 0, 0, 900, 75, des->w, des->h) ;
    if(mouse_x>=900 and mouse_x<=1150 and mouse_y>=75 and mouse_y<=325)
        rect(buffer, 897, 72, 1153, 328, makecol(59,162,71));
    textprintf_ex(buffer, broadway, 955, 282, 1, -1, "LANCER");

    ///zone de grille d'hypo
    rectfill(buffer, 620, 175,820, 225, makecol(239,228,176));
    if(mouse_x>=620 and mouse_x<=820 and mouse_y>=175 and mouse_y<=225)
        rect(buffer, 617, 172, 823, 228, makecol(239,228,176));
    textprintf_ex(buffer, broadway, 665, 184, 1, -1, "NOTES");

    ///zone d'accusation finale
    rectfill(buffer, 620, 275,820, 325, makecol(255,255,255));
    if(mouse_x>=620 and mouse_x<=820 and mouse_y>=275 and mouse_y<=325)
        rect(buffer, 617, 272, 823, 328, makecol(255,255,255));
    textprintf_ex(buffer, broadway, 652, 284, 1, -1, "ACCUSE");



    ///Affichage des pions
    for(const auto& joueur:joueurs)
        draw_sprite(buffer, joueur.getImagePion(), joueur.getPosX()*23.25, joueur.getPosY()*23.5) ;

    ///Affichage du nom et du nombre de coups restant à jouer
    rect(buffer, 615, 340, 1150, 365, makecol(255,255,255));
    textprintf_ex(buffer, font, 630, 348, makecol(255,255,255), -1, "%s", joueurs[tour].getNom().c_str());
    textprintf_ex(buffer, font, 900, 348, makecol(255, 255, 255), -1, "Il vous reste %d deplacements", joueurs[tour].getDeplacement());

    ///Affichage des cartes du joueurs
    joueurs[tour].cardDisplay(buffer);

    ///Affichage du buffer à l'écran
    blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
}


/// ////////////////////////////////////// ///
/// CASE BONUS/MALUS SUR LE PLATEAU DE JEU ///
/// ////////////////////////////////////// ///

bool casechance(BITMAP* plateau, std::vector<Joueur>& joueurs, int& tour, int nb_joueurs, BITMAP* buffer, std::vector<std::vector<char>> matrice, BITMAP* fond, FONT* broadway)
{
    int chance = rand()%4;
    int revelation = rand()%(joueurs[tour].getCartes().size());
    int posX = joueurs[tour].getPosX();
    int posY = joueurs[tour].getPosY();
    bool fin = false;
    BITMAP* des = create_bitmap(250, 250);

    switch(chance)
    {
    ///Deplacements illimités
    case 0:
        textprintf_ex(buffer, font, 730, 150, makecol(255,255,255), -1, "En route, moussaillons !");
        textprintf_ex(buffer, font, 600, 160, makecol(255,255,255), -1, "Vous pouvez aller a la prochaine salle souhaitee, vous ne pourrez pas passer par une autre case chance");

        ///Tant que le joueur n'est pas dans une salle
        while(joueurs[tour].getLoca() != '7')
        {
            actualisation(buffer, plateau, joueurs, tour, nb_joueurs, des, fond, broadway);
            joueurs[tour].deplacementChance(buffer, matrice);
        }

        ///Changement de tour
        tourParTour(tour, nb_joueurs, joueurs);

        fin = true;
        break;

    ///Rejouer
    case 1:
        textprintf_ex(buffer, font, 700, 150, makecol(255,255,255), -1, "Et c'est reparti !");
        textprintf_ex(buffer, font, 700, 160, makecol(255,255,255), -1, "Les dés sont relancés pour encore plus de filouterie");

        ///Relancement des dés
        joueurs[tour].setDeplacement(joueurs[tour].getDeplacement()+lancerDe(buffer, des, broadway));

        fin = true;
        break;

    ///Passe ton tour
    case 2:
        textprintf_ex(buffer, font, 700, 150, makecol(255,255,255), -1, "Bon voyage !");
        textprintf_ex(buffer, font, 700, 160, makecol(255,255,255), -1, "Passez votre tour");

        ///Changement de tour
        tourParTour(tour, nb_joueurs, joueurs);

        fin = true;
        break;

    ///Montrer une carte à tout le monde
    case 3:
        textprintf_ex(buffer, font, 700, 150, makecol(255,255,255), -1, "Aie aie aie, la tete...");
        textprintf_ex(buffer, font, 700, 160, makecol(255,255,255), -1, "Dans l'euphorie de la soiree d'hier, vous avez montrez cette carte a tout le monde :(");
        ///On change les coordonnées de la carte pour l'afficher
        joueurs[tour].getCartes()[revelation].setPosX(1000);
        joueurs[tour].getCartes()[revelation].setPosY(400);
        ///On affiche la carte
        joueurs[tour].getCartes()[revelation].display(buffer);
        ///On redonne les coordonnées initiales à la carte
        joueurs[tour].getCartes()[revelation].setPosX(posX);
        joueurs[tour].getCartes()[revelation].setPosY(posY);

        ///On coche la case de la carte revelee
        for(int i = 0; i < (int)(joueurs.size()); i++)
        {
            if(i != tour)
                joueurs[i].setHypo(joueurs[i].getCartes()[revelation].getNom());
        }

        fin = true;
        break;
    }
    actualisation(buffer, plateau, joueurs, tour, nb_joueurs, des, fond, broadway);
    rest(1000);

    destroy_bitmap(des);

    return fin;
}



/// /////////////////// ///
/// ACTIONS DES BOUTONS ///
/// /////////////////// ///

void actionsBoutons(std::vector <Joueur>& joueurs, std::vector <Carte>& secret, int& tour, int& nb_joueurs, BITMAP* buffer, BITMAP *des, std::vector<Carte>& cartes, std::vector <Arme> &armes,std::vector <Lieu> &lieux,std::vector <Personnage> &personnages, bool& quitter, FONT* broadway)
{
    Hypothese hypothese ;
    int resultat ;

    ///Appuie sur un bouton hypo
    if(mouse_b &1)
    {
        ///Bouton quitter
        if(mouse_x>1040 and mouse_x<1190 and mouse_y>15 and mouse_y<50)
            quitter=true ;

        ///Bouton hypothèse
        if(mouse_x >= 620 and mouse_x <= 820 and mouse_y >= 75 and mouse_y <= 125)
        {
            if((joueurs[tour].getLoca()=='0' or joueurs[tour].getLoca()=='7') and (hypothese.trouvelieu(joueurs[tour])!="Couloir"))
                hypothese.actionhypo(joueurs,tour,nb_joueurs,buffer,cartes,armes,lieux,personnages, des);
        }

        ///Lancer de dé
        if(mouse_x >= 900 and mouse_x <= 1150 and mouse_y >= 75 and mouse_y <= 325)
            joueurs[tour].setDeplacement(lancerDe(buffer, des, broadway));

        ///affichage de la grille d'hypothèse solo
        if(mouse_x >= 620 and mouse_x <= 820 and mouse_y >= 175 and mouse_y <= 225)
        {
            while(not(key[KEY_RIGHT]))
            {
                clear_bitmap(buffer);
                rectfill(buffer,0,0,400,600,makecol(239,228,176));

                for(int i=0; i<25; i++)
                    hline(buffer, 0, (25+ i*25), 400, makecol(0, 0, 0));

                vline(buffer, 350, 0, 600, makecol(0, 0, 0));
                joueurs[tour].hypoDisplay(buffer);
                textprintf_ex(buffer,font,800, 450, makecol(255, 255,255),-1,"appuyez sur la fleche de droite ->");
                textprintf_ex(buffer,font,850, 475, makecol(255, 255,255),-1,"pour revenir au plateau");

                blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
            }
        }

        ///L'accusation finale
        if(mouse_x >= 620 and mouse_x <= 820 and mouse_y >= 275 and mouse_y <= 325)
        {
            if((joueurs[tour].getLoca()=='0' or joueurs[tour].getLoca()=='7') and (hypothese.trouvelieu(joueurs[tour])=="Tortuga"))
            {
                resultat=accusationfinale(buffer,joueurs,secret,armes,personnages,lieux);

                if(resultat==1)
                {
                    allegro_message("bravoooo");
                    //ecran de victoire
                }

                if(resultat==0)
                {
                    allegro_message("perduuuu");
                    joueurs.erase(joueurs.begin()+tour);
                    for(const auto& restant: joueurs)
                    {
                        allegro_message(restant.getNom().c_str());
                    }
                    nb_joueurs--;
                    if(nb_joueurs==1)
                    {
                        //ecrande victoire pour l'autre joueur
                        allegro_message("gagne pour votre adversaire");
                    }
                }
            }
        }
    }
}







/// ///////////////// ///
/// ACCUSATION FINALE ///
/// ///////////////// ///

int accusationfinale(BITMAP* buffer, std::vector<Joueur> joueurs, std::vector <Carte> &secret, std::vector<Arme> armes, std::vector<Personnage> persos, std::vector<Lieu> lieux)
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
        /*allegro_message("vous avez perdu");
        allegro_message(joueurs[tour].getNom().c_str());
        allegro_message("tu es elimine");
        //on supprime le joueur actuel car il a perdu
        joueurs.erase(joueurs.begin()+tour);
        for(const auto& restant: joueurs)
        {
            allegro_message(restant.getNom().c_str());
        }
        nb_joueurs--;
        */
        return 0;
    }
}



void disaccusationfinale(BITMAP* buffer, std::vector<Joueur> joueurs, std::vector <Carte> &secret, std::vector<Arme> armes, std::vector<Personnage> persos, std::vector<Lieu> lieux)
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


/// /////////////////////////////////////////////////////////////// ///
/// PERMET DE ZOOMER SUR UNE ZONE DE L'ÉCRAN CHOISIE AVEC LA SOURIS ///
/// /////////////////////////////////////////////////////////////// ///

void zoom(BITMAP * buffer)
{
    ///On ne fait quelque chose que si la touche est appuyée
    if(key[KEY_Z])
    {
        ///Création d'un buffer temporaire pour le zoom
        BITMAP* buff = create_bitmap(1200,600); ;

        while(key[KEY_Z])
        {
            ///On est met le buffer sur le buffer (du sspg)
            blit(buffer, buff, 0, 0, 0, 0, buffer->w, buffer->h);

            ///On ne fait rien si la souris n'est pas dans ces valeurs (tout l'écran peut être zoomer dans ces valeurs)
            if(mouse_y>200 && mouse_x>200 && mouse_x<1000 )
                masked_stretch_blit(buff,screen,mouse_x-200,mouse_y-200,400,200,75,100,1000,500);
        }

        destroy_bitmap(buff);
    }
}
