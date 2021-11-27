#include "header.h"


void menu(std::vector <Joueur> &joueurs, std::vector <Carte> &cartes, std::vector <Carte> &cartes2, int &nb_joueurs,std::vector <Carte> &secret, int& tour, std::vector <Arme> &armes,std::vector <Lieu> &lieux,std::vector <Personnage> &personnages)
{
    BITMAP* menu = load_bitmap("images/menu1.bmp", NULL);

    ///On affiche play en gris en normal, rouge si on passe dessus
    while(!(mouse_b&1))
    {
        blit(menu, screen, 0, 0, 0, 0, 1200, 600);

        if(key[KEY_ESC])
            allegro_exit();
    }

    ///2e menu : lancement de partie sauvegardée, nouvelle partie...
    launch(joueurs, cartes, cartes2, nb_joueurs, secret, tour, armes, lieux, personnages);

    ///Destruction bitmap
    destroy_bitmap(menu);
}


void launch(std::vector <Joueur> &joueurs, std::vector <Carte> &cartes, std::vector <Carte> &cartes2, int &nb_joueurs,std::vector <Carte> &secret, int& tour, std::vector <Arme> &armes,std::vector <Lieu> &lieux,std::vector <Personnage> &personnages)
{
    int choix =0 ;
    BITMAP* menu2 = load_bitmap("images/menu2.bmp", NULL);
    BITMAP* drapeauR = load_bitmap("images/drapeau rouge.bmp", NULL);

    BITMAP* buffer = create_bitmap(1200, 600);
    FONT* broadway = load_font("broadway.pcx",NULL, NULL);


    ///Saisie du choix en cliquant sur l'écran
    while(choix==0)
    {
        blit(menu2, buffer, 0, 0, 0, 0, menu2->w, menu2->h);

        ///Clique sur un des drapeaux
        if(mouse_x>60 and mouse_x<165)
        {
            ///Nouvelle partie
            if(mouse_y>160 and mouse_y<220)
            {
                stretch_sprite(buffer, drapeauR, 70, 162, drapeauR->w/3, drapeauR->h/3);
                if(mouse_b&1)
                    choix=1 ;
            }

            ///Partie sauvegardée
            if(mouse_y>230 and mouse_y<290)
            {
                stretch_sprite(buffer, drapeauR, 70, 234, drapeauR->w/3, drapeauR->h/3);
                if(mouse_b&1)
                    choix=2 ;
            }

            ///Scores
            if(mouse_y>300 and mouse_y<360)
            {
                stretch_sprite(buffer, drapeauR, 70, 303, drapeauR->w/3, drapeauR->h/3);
                if(mouse_b&1)
                    choix=3 ;
            }

            ///Aide
            if(mouse_y>370 and mouse_y<430)
            {
                stretch_sprite(buffer, drapeauR, 70, 372, drapeauR->w/3, drapeauR->h/3);
                if(mouse_b&1)
                    choix=4 ;
            }

            ///Quitter
            if(mouse_y>440 and mouse_y<500)
            {
                stretch_sprite(buffer, drapeauR, 70, 441, drapeauR->w/3, drapeauR->h/3);
                if(mouse_b&1)
                    choix=5 ;
            }
        }
        blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
    }



    ///On agit en fonction du choix qui a été fait
    switch(choix)
    {

    ///Nouvelle partie
    case 1 :
        ///choix du nombre de joueurs
        nb_joueurs = choix_nbj();

        ///Initialisation des cartes et mélange
        cardInit(joueurs, cartes, cartes2, nb_joueurs, armes, lieux, personnages);

        ///Distribution des cartes
        distribCarte(cartes2, secret, joueurs, nb_joueurs);

        for(int i=0; i<nb_joueurs; i++)
        {
            char mode ;
            std::string nom, mdp ;
            int validation = 0 ;


            ///ON RENTRE LES INFORMATIONS DU JOUEUR
            while(validation == 0)
            {
                ///Inscirption ou Connexion ?
                mode=inscriptionConnexion();

                ///Si inscription -> verif qu'il existe pas déjà
                if(mode=='i')
                {
                    nom = saisie1joueur(broadway) ;

                    if(alreadyExist(nom)==true)
                        allegro_message("Tu as deja un compte, connecte toi");

                    else
                    {
                        validation = 1 ;
                        allegro_message("Bienvenue ! saisie maintenant ton mot de passe !") ;
                        mdp = saisie1joueur(broadway);
                        saveNewCompte(nom, mdp);

                        joueurs[i].setNom(nom);
                        choix_couleur(joueurs[i], broadway);
                    }
                }

                ///Si connexion -> saisie nom et mdp -> verif login, mdp
                else if(mode=='c')
                {
                    nom = saisie1joueur(broadway) ;
                    allegro_message("Saisie maintenant ton mot de passe !") ;
                    mdp = saisie1joueur(broadway) ;

                    if(connexionValide(nom, mdp)==false)
                        allegro_message("Mauvais identifiant ou mot de passe");

                    else
                    {
                        validation = 1 ;

                        joueurs[i].setNom(nom);
                        choix_couleur(joueurs[i], broadway);
                    }
                }
            }
        }

        ///Animation des cartes
        animMelangeCarte(cartes, nb_joueurs, joueurs);

        break ;


    ///Partie sauvegardée
    case 2 :
        readNBJ(nb_joueurs);

        ///Initialisation des cartes
        cardInit(joueurs, cartes, cartes2, nb_joueurs, armes, lieux, personnages);

        readAll(joueurs, nb_joueurs, tour, secret);

        for(auto& joueur:joueurs)
            joueur.cardRecovery(cartes);

        for(auto& joueur:joueurs)
            joueur.pawnRecovery();

        break ;

    ///Scores
    case 3 :
        ///Récupération des scores de la partie
        scoreDisplay();

        launch(joueurs, cartes, cartes2, nb_joueurs, secret, tour, armes, lieux, personnages);

        break ;

    ///Aide
    case 4 :
        break ;

    ///Quitter
    case 5 :
        menu(joueurs, cartes, cartes2, nb_joueurs, secret, tour, armes, lieux, personnages);
        break ;
    }

    destroy_bitmap(buffer);
    destroy_bitmap(menu2);
    destroy_bitmap(drapeauR);
}



/// ////////////////////////// ///
/// CHOIX DU NOMBRE DE JOUEURS ///
/// ////////////////////////// ///

int choix_nbj()
{
    int nb_joueurs=0 ;
    BITMAP* menu = load_bitmap("images/choix_nbj.bmp", NULL) ;
    BITMAP* buffer = create_bitmap(1200, 600);

    while(nb_joueurs==0)
    {
        if(mouse_b&1 and mouse_y>320 and mouse_y<470)
        {
            ///2 joueurs
            if(mouse_x>120 and mouse_x<260)
                nb_joueurs=2 ;

            else if(mouse_x>380 and mouse_x<520)
                nb_joueurs=3 ;

            else if(mouse_x>640 and mouse_x<780)
                nb_joueurs=4 ;

            else if(mouse_x>900 and mouse_x<1040)
                nb_joueurs=5 ;
        }
        blit(menu, buffer, 0, 0, 0, 0, menu->w, menu->h);
        blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
    }
    destroy_bitmap(menu);

    return nb_joueurs ;
}



/// /////////////////// ///
/// CHOIX DE LA COULEUR ///
/// /////////////////// ///

void choix_couleur(Joueur& lejoueur, FONT* broadway)
{
    int choisi=0 ;
    BITMAP* menu =   load_bitmap("images/choix_couleur.bmp", NULL) ;
    BITMAP* red =    load_bitmap("images/pionRouge.bmp", NULL);
    BITMAP* yellow = load_bitmap("images/pionJaune.bmp", NULL);
    BITMAP* blue =   load_bitmap("images/pionBleu.bmp", NULL);
    BITMAP* green =  load_bitmap("images/pionVert.bmp", NULL);
    BITMAP* violet = load_bitmap("images/pionViolet.bmp", NULL);
    BITMAP* white =  load_bitmap("images/pionBlanc.bmp", NULL);

    BITMAP* logo = create_bitmap(23, 25);
    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);

    while(choisi==0)
    {
        clear_bitmap(buffer);
        blit(menu, buffer, 0, 0, 0, 0, menu->w, menu->h);
        textprintf_centre_ex(buffer, broadway, 600, 110, makecol(77, 3, 18), -1, "%s", lejoueur.getNom().c_str());

        if(mouse_y>215 and mouse_y<385 and mouse_x>225 and mouse_x < 375)
        {
            masked_blit(red, buffer, 0, 0, 225, 213, SCREEN_W, SCREEN_H);
            if(mouse_b&1)
            {
                choisi=1 ;
                lejoueur.setCouleur("Rouge");
                stretch_blit(red, logo, 0,0, red->w, red->h, 0,0,logo->w, logo->h);
                lejoueur.setImagePion(logo);
                lejoueur.setPosX(10);
                lejoueur.setPosY(0);
                textprintf_ex(buffer, broadway, 500, 200, makecol(77, 3, 18), -1, "Tres bon choix...." );
                lejoueur.setLogoHypo(red);
            }
        }
        if(mouse_y>215 and mouse_y<385 and mouse_x>525 and mouse_x < 675)
        {
            masked_blit(yellow, buffer, 0, 0, 525, 213, SCREEN_W, SCREEN_H);
            if(mouse_b&1)
            {
                choisi=1 ;
                lejoueur.setCouleur("Jaune");
                stretch_blit(yellow, logo, 0,0, yellow->w, yellow->h, 0,0,logo->w, logo->h);
                lejoueur.setImagePion(logo);
                lejoueur.setPosX(15);
                lejoueur.setPosY(0);
                textprintf_ex(buffer, broadway, 500, 200, makecol(77, 3, 18), -1, "Tres bon choix...." );
                lejoueur.setLogoHypo(yellow);
            }
        }
        if(mouse_y>215 and mouse_y<385 and mouse_x>825 and mouse_x < 975)
        {
            masked_blit(blue, buffer, 0, 0, 825, 213, SCREEN_W, SCREEN_H);
            if(mouse_b&1)
            {
                choisi=1 ;
                lejoueur.setCouleur("Bleu");
                lejoueur.setLogoHypo(blue);
                stretch_blit(blue, logo, 0,0, blue->w, blue->h, 0,0,logo->w, logo->h);
                lejoueur.setImagePion(logo);
                lejoueur.setPosX(24);
                lejoueur.setPosY(6);
                textprintf_ex(buffer, broadway, 500, 200, makecol(77, 3, 18), -1, "Tres bon choix...." );
            }
        }
        if(mouse_y>415 and mouse_y<585 and mouse_x>325 and mouse_x < 475)
        {
            masked_blit(violet, buffer, 0, 0, 325, 412, SCREEN_W, SCREEN_H);
            if(mouse_b&1)
            {
                choisi=1 ;
                lejoueur.setCouleur("Violet");
                lejoueur.setLogoHypo(violet);
                stretch_blit(violet, logo, 0,0, violet->w, violet->h, 0,0,logo->w, logo->h);
                lejoueur.setImagePion(logo);
                lejoueur.setPosX(24);
                lejoueur.setPosY(19);
                textprintf_ex(buffer, broadway, 500, 200, makecol(77, 3, 18), -1, "Tres bon choix...." );
            }
        }
        if(mouse_y>415 and mouse_y<585 and mouse_x>525 and mouse_x < 675)
        {
            masked_blit(green, buffer, 0, 0, 525, 412, SCREEN_W, SCREEN_H);
            if(mouse_b&1)
            {
                choisi=1 ;
                lejoueur.setCouleur("Vert");
                lejoueur.setLogoHypo(green);
                stretch_blit(green, logo, 0,0, green->w, green->h, 0,0,logo->w, logo->h);
                lejoueur.setImagePion(logo);
                lejoueur.setPosX(1);
                lejoueur.setPosY(17);
                textprintf_ex(buffer, broadway, 500, 200, makecol(77, 3, 18), -1, "Tres bon choix...." );
            }
        }
        if(mouse_y>415 and mouse_y<585 and mouse_x>725 and mouse_x < 875)
        {
            masked_blit(white, buffer, 0, 0, 725, 412, SCREEN_W, SCREEN_H);
            if(mouse_b&1)
            {
                choisi=1 ;
                lejoueur.setCouleur("Blanc");
                lejoueur.setLogoHypo(white);
                stretch_blit(white, logo, 0,0, white->w, white->h, 0,0,logo->w, logo->h);
                lejoueur.setImagePion(logo);
                lejoueur.setPosX(8);
                lejoueur.setPosY(24);
                textprintf_ex(buffer, broadway, 500, 200, makecol(77, 3, 18), -1, "Tres bon choix...." );
            }
        }

        blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
    }
    rest(500);
    destroy_bitmap(menu);
    destroy_bitmap(red);
    destroy_bitmap(yellow);
    destroy_bitmap(blue);
    destroy_bitmap(green);
    destroy_bitmap(violet);
    destroy_bitmap(white);
    destroy_bitmap(buffer);
}



/// //////////////////////////// ///
/// SAISIE DU PSEUDO D'UN JOUEUR ///
/// //////////////////////////// ///

std::string saisie1joueur(FONT *broadway)
{
    int  i=0 ;
    char tempo[50]=" ";
    std::string nom;

    BITMAP* buffer = create_bitmap(SCREEN_W,SCREEN_H);
    BITMAP* fond =   load_bitmap("images/choix_nom.bmp", NULL);
    //FONT *onyx = load_font("onyx.pcx",NULL, NULL);


    blit(fond, buffer, 0,0,0,0, SCREEN_W, SCREEN_H);
    textprintf_centre_ex(buffer, broadway, 600, 90, makecol(77, 3, 18), -1, "Appuie sur ENTREE pour valider") ;
    blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);

    fflush(stdin);

    ///Tant qu'on appuie pas sur Entrée on est dans la saisie du nom du joueur
    while(!key[KEY_ENTER])
    {
        clear_bitmap(buffer);
        blit(fond, buffer, 0,0,0,0, SCREEN_W, SCREEN_H);
        textprintf_centre_ex(buffer, broadway, 600, 90, makecol(77, 3, 18), -1, "Appuie sur ENTREE pour valider") ;
        ///On range chaque lettre
        tempo[i] = readkey() ;

        ///Si on fait Entrée, c'est la fin du mot, on remplace donc par \0
        if(key[KEY_ENTER])
            tempo[i]='\0' ;

        ///Si on appuie sur supprimer, on supprime la dernière lettre
        if(key[KEY_BACKSPACE])
        {
            tempo[i]=' ';
            if(i>0)
                i-- ;
            tempo[i]=' ';
            textprintf_centre_ex(buffer, broadway, 600, 120, makecol(77, 3, 18), -1, "%s", tempo) ;
        }

        ///Si on appuie pas sur supprimer on affiche le texte normalement
        else
        {
            textprintf_centre_ex(buffer, broadway, 600, 120, makecol(77, 3, 18), -1, "%s", tempo) ;
            i++ ;
        }

        blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
    }

    ///Voici le nom final du joueur
    nom=tempo;

    destroy_bitmap(fond);
    destroy_bitmap(buffer);

    return nom ;
}



/// /////////////////////////////////////////// ///
/// CHOIX SI INSCRIPTION OU CONNEXION DU JOUEUR ///
/// /////////////////////////////////////////// ///

char inscriptionConnexion()
{
    clear_bitmap(screen);

    rectfill(screen, 350, 200, 550, 300, makecol(255, 200, 200)) ;
    textprintf_ex(screen, font, 400, 250, makecol(255,255,255), -1, "INSCRIPTION");
    rectfill(screen, 650, 200, 850, 300, makecol(255, 200, 200)) ;
    textprintf_ex(screen, font, 700, 250, makecol(255,255,255), -1, "CONNEXION");


    ///Choix connexion inscription avec appui sur les boutons
    while(1)
    {
        if(mouse_b&1 and mouse_x>350 and mouse_x<550 and mouse_y>200 and mouse_y<300)
            return 'i' ;

        if(mouse_b&1 and mouse_x>650 and mouse_x<850 and mouse_y>200 and mouse_y<300)
            return 'c' ;
    }
}



/// ///////////////////////////////////////////////////// ///
/// ANIMATION DU MELANGE ET DE LA DISTRIBUTION DES CARTES ///
/// ///////////////////////////////////////////////////// ///

void animMelangeCarte(std::vector<Carte>& cartes, int& nb_joueurs, std::vector<Joueur>& joueurs)
{
    float phase2 = 0 ;
    BITMAP * buffer = create_bitmap(1200, 600);


    ///PARTIE CERCLE
    for(int j=0 ; j<1000 ; j++)
    {
        clear_bitmap(buffer);
        for(int i=0 ; i<24 ; i++)
        {
            cartes[i].setPosX(SCREEN_W/2 - cartes[i].getImage()->w/2 + 250*cos(phase2+2*i));
            cartes[i].setPosY(SCREEN_H/2 - cartes[i].getImage()->h/2 + 250*sin(phase2+2*i));
            blit(cartes[i].getImage(), buffer, 0, 0, cartes[i].getPosX(), cartes[i].getPosY(), cartes[i].getImage()->w, cartes[i].getImage()->h);
        }

        phase2+=3.14/2000;
        blit(buffer, screen, 0, 0, 0, 0, 1200, 600);
    }


    ///REMISE AU MILIEU
    for(int j=0 ; j<1000 ; j++)
    {
        clear_bitmap(buffer);
        for(int i=0 ; i<24 ; i++)
        {
            if(cartes[i].getPosX()>(SCREEN_W-cartes[i].getImage()->w)/2)
                cartes[i].setPosX(cartes[i].getPosX()-1);
            if(cartes[i].getPosX()<(SCREEN_W-cartes[i].getImage()->w)/2)
                cartes[i].setPosX(cartes[i].getPosX()+1);
            if(cartes[i].getPosY()>(SCREEN_H-cartes[i].getImage()->h)/2)
                cartes[i].setPosY(cartes[i].getPosY()-1);
            if(cartes[i].getPosY()<(SCREEN_H-cartes[i].getImage()->h)/2)
                cartes[i].setPosY(cartes[i].getPosY()+1);

            blit(cartes[i].getImage(), buffer, 0, 0, cartes[i].getPosX(), cartes[i].getPosY(), cartes[i].getImage()->w, cartes[i].getImage()->h);
        }
        blit(buffer, screen, 0, 0, 0, 0, 1200, 600);
    }


    ///PHASE DE TRANSITION AVEC LES CROISÉS
    for(int i=0 ; i<110 ; i++)
    {
        clear_bitmap(buffer);

        for(int j=0 ; j<6 ; j++)
        {
            if(cartes[4*j].getPosX()>(SCREEN_W-cartes[4*j].getImage()->w)/2-150+20*j)
                cartes[4*j].setPosX(cartes[4*j].getPosX()-1);
            if(cartes[4*j].getPosY()>(SCREEN_H-cartes[4*j].getImage()->h)/2-150+20*j)
                cartes[4*j].setPosY(cartes[4*j].getPosY()-1);

            if(cartes[1+4*j].getPosX()<(SCREEN_W-cartes[1+4*j].getImage()->w)/2+150-20*j)
                cartes[1+4*j].setPosX(cartes[1+4*j].getPosX()+1);
            if(cartes[1+4*j].getPosY()>(SCREEN_H-cartes[1+4*j].getImage()->h)/2-150+20*j)
                cartes[1+4*j].setPosY(cartes[1+4*j].getPosY()-1);

            if(cartes[2+4*j].getPosX()>(SCREEN_W-cartes[2+4*j].getImage()->w)/2-150+20*j)
                cartes[2+4*j].setPosX(cartes[2+4*j].getPosX()-1);
            if(cartes[2+4*j].getPosY()<(SCREEN_H-cartes[2+4*j].getImage()->h)/2+150-20*j)
                cartes[2+4*j].setPosY(cartes[2+4*j].getPosY()+1);

            if(cartes[3+4*j].getPosX()<(SCREEN_W-cartes[3+4*j].getImage()->w)/2+150-20*j)
                cartes[3+4*j].setPosX(cartes[3+4*j].getPosX()+1);
            if(cartes[3+4*j].getPosY()<(SCREEN_H-cartes[3+4*j].getImage()->h)/2+150-20*j)
                cartes[3+4*j].setPosY(cartes[3+4*j].getPosY()+1);
        }

        for(int j=0 ; j<24 ; j++)
            blit(cartes[j].getImage(), buffer, 0, 0, cartes[j].getPosX(), cartes[j].getPosY(), cartes[j].getImage()->w, cartes[j].getImage()->h);

        blit(buffer, screen, 0, 0, 0, 0, 1200, 600);
    }


    ///CROISÉS
    for(int j=0 ; j<2000 ; j++)
    {
        clear_bitmap(buffer);
        for(int i=0 ; i<12 ; i++)
        {
            cartes[i].setPosX(SCREEN_W/2 - cartes[i].getImage()->w/2 + 150*cos(phase2+2*i));
            cartes[i].setPosY(SCREEN_H/2 - cartes[i].getImage()->h/2 + 150*cos(phase2+2*i));
            blit(cartes[i].getImage(), buffer, 0, 0, cartes[i].getPosX(), cartes[i].getPosY(), cartes[i].getImage()->w, cartes[i].getImage()->h);
        }
        for(int i=12 ; i<24 ; i++)
        {
            cartes[i].setPosX(SCREEN_W/2 - cartes[i].getImage()->w/2 + 150*sin(phase2-2*i));
            cartes[i].setPosY(SCREEN_H/2 - cartes[i].getImage()->h/2 - 150*sin(phase2-2*i));
            blit(cartes[i].getImage(), buffer, 0, 0, cartes[i].getPosX(), cartes[i].getPosY(), cartes[i].getImage()->w, cartes[i].getImage()->h);

        }
        phase2+=3.14/1000;
        blit(buffer, screen, 0, 0, 0, 0, 1200, 600);
    }


    ///REMISE AU MILIEU
    for(int j=0 ; j<1500 ; j++)
    {
        clear_bitmap(buffer);

        for(int i=0 ; i<24 ; i++)
        {
            if(cartes[i].getPosX()>(SCREEN_W-cartes[i].getImage()->w)/2)
                cartes[i].setPosX(cartes[i].getPosX()-1);
            if(cartes[i].getPosX()<(SCREEN_W-cartes[i].getImage()->w)/2)
                cartes[i].setPosX(cartes[i].getPosX()+1);
            if(cartes[i].getPosY()>(SCREEN_H-cartes[i].getImage()->h)/2)
                cartes[i].setPosY(cartes[i].getPosY()-1);
            if(cartes[i].getPosY()<(SCREEN_H-cartes[i].getImage()->h)/2)
                cartes[i].setPosY(cartes[i].getPosY()+1);

            blit(cartes[i].getImage(), buffer, 0, 0, cartes[i].getPosX(), cartes[i].getPosY(), cartes[i].getImage()->w, cartes[i].getImage()->h);
        }
        blit(buffer, screen, 0, 0, 0, 0, 1200, 600);
    }


    ///RETOURNEMENT DES CARTES
    BITMAP* dos = load_bitmap("images/dos carte.bmp", NULL);

    ///Fais tourner les cartes de face en accélérant
    for(int i=0 ; i<200 ; i++)
    {
        for(int j=0 ; j<24 ; j++)
        {
            clear_bitmap(buffer) ;
            rotate_sprite(buffer, cartes[j].getImage(),cartes[j].getPosX(), cartes[j].getPosY(), ftofix(2*i));
        }
        blit(buffer, screen, 0, 0, 0, 0, 1200, 600);
    }
    ///Fais tourner les cartes de dos en ralentissant
    for(int i=0 ; i<200 ; i++)
    {
        for(int j=0 ; j<24 ; j++)
        {
            clear_bitmap(buffer) ;
            rotate_sprite(buffer, cartes[j].getImage(),cartes[j].getPosX(), cartes[j].getPosY(), ftofix(10*i));
        }
        blit(buffer, screen, 0, 0, 0, 0, 1200, 600);
    }
    ///Fais tourner les cartes de face en accélérant
    for(int i=0 ; i<200 ; i++)
    {
        for(int j=0 ; j<24 ; j++)
        {
            clear_bitmap(buffer) ;
            rotate_sprite(buffer, dos,cartes[j].getPosX(), cartes[j].getPosY(), ftofix(10*i));
        }
        blit(buffer, screen, 0, 0, 0, 0, 1200, 600);
    }
    ///Fais tourner les cartes de dos en ralentissant
    for(int i=0 ; i<200 ; i++)
    {
        for(int j=0 ; j<24 ; j++)
        {
            clear_bitmap(buffer) ;
            rotate_sprite(buffer, dos,cartes[j].getPosX(), cartes[j].getPosY(), ftofix(2*i));
        }
        blit(buffer, screen, 0, 0, 0, 0, 1200, 600);
    }
    rest(1000);







    ///DISTRIBUTION DES CARTES

    ///Pochette secrète
    for(int i=0 ; i<3 ; i++)
    {
        while(cartes[i].getPosX()<800)
        {
            clear_bitmap(buffer);
            textprintf_ex(buffer, font, 770, 230, makecol(255, 255, 255), -1, "POCHETTE SECRETE");
            cartes[i].setPosX(cartes[i].getPosX()+1);

            for(int j=0 ; j<24 ; j++)
                blit(dos, buffer, 0, 0, cartes[j].getPosX(), cartes[j].getPosY(), dos->w, dos->h);

            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        }
    }

    rest(1000);


    /// DISTRIBUTION DES CARTES AUX JOUEURS

    int tour = 0 ; //Tour de chaque joueur
    std::vector<int> compteursCarteJoueurs ; //Vecteurs pour savoir cb de cartes on a donné à chaque joueurs

    //Initialisation du vecteur de compteurs
    for(int i=0 ; i<nb_joueurs ; i++)
        compteursCarteJoueurs.push_back(0);

    for(int i=3 ; i<24 ; i++)
    {
        while(cartes[i].getPosX()>50+compteursCarteJoueurs[tour]*30/* and cartes[i].getPosY()>50+tour*120*/)
        {
            clear_bitmap(buffer);

            textprintf_ex(buffer, font, 770, 230, makecol(255, 255, 255), -1, "POCHETTE SECRETE");
            for(int j=0 ; j<nb_joueurs ; j++)
                textprintf_ex(buffer, font, 50, 42+j*120, makecol(255, 255, 255), -1, "Joueur : %s", joueurs[j].getNom().c_str());

            cartes[i].setPosX(cartes[i].getPosX()-7);
            cartes[i].setPosY((cartes[i].getPosX()-(50+compteursCarteJoueurs[tour]*30))*(250-(50+tour*120))/(570-(50+compteursCarteJoueurs[tour]*30))+50+tour*120);

            for(int j=0 ; j<24 ; j++)
                blit(dos, buffer, 0, 0, cartes[j].getPosX(), cartes[j].getPosY(), dos->w, dos->h);

            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        }

        compteursCarteJoueurs[tour]++ ;
        tour++ ;

        if(tour==nb_joueurs)
            tour=0 ;
    }

    rest(2000);




    ///ENREGISTRER LE PLATEAU D'APRÈS DANS UN BUFFER
    ///FAIRE UNE FONDUE ENCHAINÉE ENTRE LES 2 IMAGES
}
