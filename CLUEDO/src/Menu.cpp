#include "Menu.h"

Menu::Menu()
{}

Menu::~Menu()
{}


bool Menu::menu(std::vector <Joueur> &joueurs, std::vector <Carte> &cartes, std::vector <Carte> &cartes2, int &nb_joueurs,std::vector <Carte> &secret, int& tour, std::vector <Arme> &armes,std::vector <Lieu> &lieux,std::vector <Personnage> &personnages)
{
    BITMAP* menu = load_bitmap("images/menu1.bmp", NULL);

    ///On affiche play en gris en normal, rouge si on passe dessus
    while(!(mouse_b&1))
    {
        blit(menu, screen, 0, 0, 0, 0, 1200, 600);

        if(key[KEY_ESC])
            return true ;
    }

    ///2e menu : lancement de partie sauvegardée, nouvelle partie...
    launch(joueurs, cartes, cartes2, nb_joueurs, secret, tour, armes, lieux, personnages);

    ///Destruction bitmap
    destroy_bitmap(menu);
    return false ;
}


void Menu::launch(std::vector <Joueur> &joueurs, std::vector <Carte> &cartes, std::vector <Carte> &cartes2, int &nb_joueurs,std::vector <Carte> &secret, int& tour, std::vector <Arme> &armes,std::vector <Lieu> &lieux,std::vector <Personnage> &personnages)
{
    int choix =0 ;
    Sauvegarde save ;
    BITMAP* menu2 = load_bitmap("images/menu2.bmp", NULL);
    BITMAP* drapeauR = load_bitmap("images/drapeau rouge.bmp", NULL);

    BITMAP* buffer = create_bitmap(1200, 600);
    FONT* broadway = load_font("broadway.pcx",NULL, NULL);

    std::vector< bool> pionschoisis;
    for(int i=0 ; i<6 ; i++)
        pionschoisis.push_back(false);


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


    while(mouse_b&1) {}

    ///On agit en fonction du choix qui a été fait
    switch(choix)
    {

    ///Nouvelle partie
    case 1 :
        ///choix du nombre de joueurs
        nb_joueurs = choix_nbj(broadway);

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
                mode=inscriptionConnexion(broadway);

                ///Si inscription -> verif qu'il existe pas déjà
                if(mode=='i')
                {
                    nom = saisie1joueur(broadway) ;

                    if(save.alreadyExist(nom)==true)
                        allegro_message("Tu as deja un compte, connecte toi");

                    else
                    {
                        validation = 1 ;
                        allegro_message("Bienvenue ! saisie maintenant ton mot de passe !") ;
                        mdp = saisie1joueur(broadway);
                        save.saveNewCompte(nom, mdp);

                        joueurs[i].setNom(nom);
                        choix_couleur(joueurs[i], broadway, pionschoisis);
                    }
                }

                ///Si connexion -> saisie nom et mdp -> verif login, mdp
                else if(mode=='c')
                {
                    nom = saisie1joueur(broadway) ;
                    allegro_message("Saisie maintenant ton mot de passe !") ;
                    mdp = saisie1joueur(broadway) ;

                    if(save.connexionValide(nom, mdp)==false)
                        allegro_message("Mauvais identifiant ou mot de passe");

                    else
                    {
                        validation = 1 ;

                        joueurs[i].setNom(nom);
                        choix_couleur(joueurs[i], broadway, pionschoisis);
                    }
                }
            }
        }

        ///Animation des cartes
        animMelangeCarte(cartes, nb_joueurs, joueurs);

        break ;


    ///Partie sauvegardée
    case 2 :

        save.readNBJ(nb_joueurs);

        ///Initialisation des cartes
        cardInit(joueurs, cartes, cartes2, nb_joueurs, armes, lieux, personnages);

        ///On récupère toutes les infos (sauf bitmap)
        save.readAll(joueurs, nb_joueurs, tour, secret);

        ///Récup bitmap
        for(auto& joueur:joueurs)
            joueur.cardRecovery(cartes);

        for(auto& joueur:joueurs)
            joueur.pawnRecovery();

        //save.recupBitmap(secret, cartes);

        break ;

    ///Scores
    case 3 :
        ///Récupération des scores de la partie
        save.scoreDisplay(broadway);

        launch(joueurs, cartes, cartes2, nb_joueurs, secret, tour, armes, lieux, personnages);

        break ;

    ///Aide
    case 4 :
        system("reglescluedo.pdf");
        launch(joueurs, cartes, cartes2, nb_joueurs, secret, tour, armes, lieux, personnages);
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

int Menu::choix_nbj(FONT* broadway)
{
    int nb_joueurs=0 ;
    BITMAP* menu = load_bitmap("images/nombre_de_joueur.bmp", NULL) ;
    BITMAP* buffer = create_bitmap(1200, 600);
    BITMAP* bateau = load_bitmap("images/bateau rouge.bmp", NULL);

    while(nb_joueurs==0)
    {
        blit(menu, buffer, 0, 0, 0, 0, menu->w, menu->h);

        if(mouse_y>202 and mouse_y<400)
        {
            ///1 joueur
            if(mouse_x>25 and mouse_x<180)
            {
                draw_sprite(buffer, bateau, 27, 209);
                textprintf_centre_ex(buffer,broadway,600, 420, makecol(220,3, 21), -1, "pas d'amis ? revenez avec quelqu'un") ;
            }

            ///2 joueurs
            if(mouse_x>225 and mouse_x<380)
            {
                for(int i=1 ; i<=2 ; i++)
                    draw_sprite(buffer, bateau, 25+(i-1)*200, 209);

                textprintf_centre_ex(buffer,broadway,600, 420, makecol(220,3, 21), -1, "c'est parti, mefiez vous") ;

                if(mouse_b&1)
                    nb_joueurs=2 ;
            }

            ///3 joueurs
            if(mouse_x>425 and mouse_x<580)
            {
                for(int i=1 ; i<=3 ; i++)
                    draw_sprite(buffer, bateau, 24+(i-1)*200, 209);

                textprintf_centre_ex(buffer,broadway,600, 420, makecol(220,3, 21), -1, "attention on ne peut plus faire confiance a personne") ;
                if(mouse_b&1)
                    nb_joueurs=3 ;
            }

            ///4 joueurs
            if(mouse_x>625 and mouse_x<780)
            {
                for(int i=1 ; i<=4 ; i++)
                    draw_sprite(buffer, bateau, 23+(i-1)*200, 208);
                textprintf_centre_ex(buffer,broadway,600, 420, makecol(220,3, 21), -1, "surveillez-vos arrieres !") ;

                if(mouse_b&1)
                    nb_joueurs=4 ;
            }

            ///5 joueurs
            if(mouse_x>825 and mouse_x<980)
            {
                for(int i=1 ; i<=5 ; i++)
                    draw_sprite(buffer, bateau, 23+(i-1)*200, 208);
                textprintf_centre_ex(buffer,broadway,600, 420, makecol(220,3, 21), -1, "OULA, ca fait beaucoup de potentiels traitres") ;

                if(mouse_b&1)
                    nb_joueurs=5 ;
            }

            ///6 joueurs
            if(mouse_x>1025 and mouse_x<1180)
            {
                for(int i=1 ; i<=6 ; i++)
                    draw_sprite(buffer, bateau, 23+(i-1)*200, 208);
                textprintf_centre_ex(buffer,broadway,600, 420, makecol(220,3, 21), -1, "des ennemis partout, trouvez qui a fait ca") ;

                if(mouse_b&1)
                    nb_joueurs=6 ;
            }
        }
        blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
    }

    destroy_bitmap(menu);
    destroy_bitmap(bateau);

    return nb_joueurs ;
}



/// /////////////////// ///
/// CHOIX DE LA COULEUR ///
/// /////////////////// ///

void Menu::choix_couleur(Joueur& lejoueur, FONT* broadway, std::vector<bool>& pionschoisis)
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
                if(pionschoisis[0]==false)
                {
                    pionschoisis[0]=true;
                    choisi=1 ;
                    lejoueur.setCouleur("Rouge");
                    stretch_blit(red, logo, 0,0, red->w, red->h, 0,0,logo->w, logo->h);
                    lejoueur.setImagePion(logo);
                    lejoueur.setPosX(10);
                    lejoueur.setPosY(0);
                    textprintf_ex(buffer, broadway, 500, 200, makecol(77, 3, 18), -1, "Tres bon choix...." );
                    lejoueur.setLogoHypo(red);
                }
                else
                    choisi=0 ;
            }
        }
        if(mouse_y>215 and mouse_y<385 and mouse_x>525 and mouse_x < 675)
        {
            masked_blit(yellow, buffer, 0, 0, 525, 213, SCREEN_W, SCREEN_H);
            if(mouse_b&1)
            {
                if(pionschoisis[1]==false)
                {
                    pionschoisis[1]=true;
                    choisi=1 ;
                    lejoueur.setCouleur("Jaune");
                    stretch_blit(yellow, logo, 0,0, yellow->w, yellow->h, 0,0,logo->w, logo->h);
                    lejoueur.setImagePion(logo);
                    lejoueur.setPosX(15);
                    lejoueur.setPosY(0);
                    textprintf_ex(buffer, broadway, 500, 200, makecol(77, 3, 18), -1, "Tres bon choix...." );
                    lejoueur.setLogoHypo(yellow);
                }
                else
                    choisi=0 ;
            }
        }
        if(mouse_y>215 and mouse_y<385 and mouse_x>825 and mouse_x < 975)
        {
            masked_blit(blue, buffer, 0, 0, 825, 213, SCREEN_W, SCREEN_H);
            if(mouse_b&1)
            {
                if(pionschoisis[2]==false)
                {
                    pionschoisis[2]=true;
                    choisi=1 ;
                    lejoueur.setCouleur("Bleu");
                    lejoueur.setLogoHypo(blue);
                    stretch_blit(blue, logo, 0,0, blue->w, blue->h, 0,0,logo->w, logo->h);
                    lejoueur.setImagePion(logo);
                    lejoueur.setPosX(24);
                    lejoueur.setPosY(6);
                    textprintf_ex(buffer, broadway, 500, 200, makecol(77, 3, 18), -1, "Tres bon choix...." );
                }
                else
                    choisi=0 ;
            }
        }
        if(mouse_y>415 and mouse_y<585 and mouse_x>325 and mouse_x < 475)
        {
            masked_blit(violet, buffer, 0, 0, 325, 412, SCREEN_W, SCREEN_H);
            if(mouse_b&1)
            {
                if(pionschoisis[3]==false)
                {
                    pionschoisis[3]=true;
                    choisi=1 ;
                    lejoueur.setCouleur("Violet");
                    lejoueur.setLogoHypo(violet);
                    stretch_blit(violet, logo, 0,0, violet->w, violet->h, 0,0,logo->w, logo->h);
                    lejoueur.setImagePion(logo);
                    lejoueur.setPosX(24);
                    lejoueur.setPosY(19);
                    textprintf_ex(buffer, broadway, 500, 200, makecol(77, 3, 18), -1, "Tres bon choix...." );
                }
                else
                    choisi=0 ;
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
                if(pionschoisis[2]==false)
                {
                    pionschoisis[2]=true;
                    choisi=1 ;
                    lejoueur.setCouleur("Blanc");
                    lejoueur.setLogoHypo(white);
                    stretch_blit(white, logo, 0,0, white->w, white->h, 0,0,logo->w, logo->h);
                    lejoueur.setImagePion(logo);
                    lejoueur.setPosX(8);
                    lejoueur.setPosY(24);
                    textprintf_ex(buffer, broadway, 500, 200, makecol(77, 3, 18), -1, "Tres bon choix...." );
                }
                else
                    choisi=0 ;
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

std::string Menu::saisie1joueur(FONT *broadway)
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

char Menu::inscriptionConnexion(FONT* broadway)
{
    BITMAP* fond = load_bitmap("images/tempete.bmp", NULL);
    BITMAP* buffer = create_bitmap(SCREEN_W,SCREEN_H);

    ///Choix connexion inscription avec appui sur les boutons
    while(1)
    {
        clear_bitmap(buffer);

        blit(fond, buffer,0,0,0,0, SCREEN_W, SCREEN_H);
        rectfill(buffer, 250, 200, 550, 300, makecol(0, 0, 0)) ;
        textprintf_ex(buffer, broadway, 300, 230, makecol(255,255,255), -1, "INSCRIPTION");
        rectfill(buffer, 650, 200, 950, 300, makecol(0, 0, 0)) ;
        textprintf_ex(buffer, broadway, 700, 230, makecol(255,255,255), -1, "CONNEXION");

        if(mouse_x>350 and mouse_x<550 and mouse_y>200 and mouse_y<300)
        {
            rectfill(buffer, 250, 200, 550, 300, makecol(255, 0, 0)) ;
            textprintf_ex(buffer, broadway, 300, 230, makecol(255,255,255), -1, "INSCRIPTION");
            if(mouse_b&1)
            {
                destroy_bitmap(buffer);
                destroy_bitmap(fond);
                return 'i' ;
            }
        }

        if(mouse_x>650 and mouse_x<850 and mouse_y>200 and mouse_y<300)
        {
            rectfill(buffer, 650, 200, 950, 300, makecol(255, 0, 0)) ;
            textprintf_ex(buffer, broadway, 700, 230, makecol(255,255,255), -1, "CONNEXION");
            if(mouse_b&1)
            {
                destroy_bitmap(buffer);
                destroy_bitmap(fond);
                return 'c' ;
            }
        }
        blit(buffer, screen,0,0,0,0, SCREEN_W, SCREEN_H);
    }
}




/// ///////////////////////////////////////////////////// ///
/// ANIMATION DU MELANGE ET DE LA DISTRIBUTION DES CARTES ///
/// ///////////////////////////////////////////////////// ///

void Menu::animMelangeCarte(std::vector<Carte>& cartes, int& nb_joueurs, std::vector<Joueur>& joueurs)
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
    for(int i=0 ; i<193 ; i++)
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
            cartes[i].setPosY((cartes[i].getPosX()-(50+compteursCarteJoueurs[tour]*30))*(250-(50+tour*120))/
                              (570-(50+compteursCarteJoueurs[tour]*30))+50+tour*120);

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





/// /////////////////////////////////////////////////////// ///
/// INITIALISATION DES CARTES (CHARGEMENT BITMAP + MÉLANGE) ///
/// /////////////////////////////////////////////////////// ///

void Menu::cardInit(std::vector <Joueur> &joueurs, std::vector <Carte> &cartes, std::vector <Carte> &cartes2, int &nb_joueurs, std::vector <Arme> &armes,std::vector <Lieu> &lieux,std::vector <Personnage> &personnages)
{
    int ok=0, id ;

    ///Initialisation
    for(int i=0 ; i<nb_joueurs ; i++)
        joueurs.push_back(Joueur()) ;


    ///Initialisation des cartes - armes
    armes.push_back(Arme("Sabre",              load_bitmap("images/sabre.bmp",NULL), "arme"));
    armes.push_back(Arme("Pistolet",           load_bitmap("images/pistolet.bmp",NULL), "arme"));
    armes.push_back(Arme("Poudre a canon",     load_bitmap("images/poudre.bmp",NULL), "arme"));
    armes.push_back(Arme("Cle",                load_bitmap("images/cle.bmp",NULL), "arme"));
    armes.push_back(Arme("Tire bouchon",       load_bitmap("images/tirebouchon.bmp",NULL), "arme"));
    armes.push_back(Arme("Canon",              load_bitmap("images/canon.bmp",NULL), "arme"));

    personnages.push_back(Personnage("Will Turner",           load_bitmap("images/willturner.bmp",NULL), "perso"));
    personnages.push_back(Personnage("Bill Turner",           load_bitmap("images/billturner.bmp",NULL), "perso"));
    personnages.push_back(Personnage("Jack Sparrow",          load_bitmap("images/jacksparrow.bmp",NULL), "perso"));
    personnages.push_back(Personnage("Barbossa",              load_bitmap("images/barbossa.bmp",NULL), "perso"));
    personnages.push_back(Personnage("Elizabeth Swann",       load_bitmap("images/swann.bmp",NULL), "perso"));
    personnages.push_back(Personnage("Davy Jones",            load_bitmap("images/davyjones.bmp",NULL), "perso"));
    personnages.push_back(Personnage("Calypso",               load_bitmap("images/calypso.bmp",NULL), "perso"));
    personnages.push_back(Personnage("James Norrington",      load_bitmap("images/jamesnorrington.bmp",NULL), "perso"));
    personnages.push_back(Personnage("Barbe Noire",           load_bitmap("images/barbenoire.bmp",NULL), "perso"));

    lieux.push_back(Lieu("Baie des Naufrages",    load_bitmap("images/tortuga.bmp",NULL), "lieu"));
    lieux.push_back(Lieu("Port Royal",            load_bitmap("images/portroyale.bmp",NULL), "lieu"));
    lieux.push_back(Lieu("Ile de la Muerta",      load_bitmap("images/muerta.bmp",NULL), "lieu"));
    lieux.push_back(Lieu("Ile au rhum",           load_bitmap("images/rhum.bmp",NULL), "lieu"));
    lieux.push_back(Lieu("Hollandais Volant",     load_bitmap("images/hollandais.bmp",NULL), "lieu"));
    lieux.push_back(Lieu("Ile des 4 vents",       load_bitmap("images/quatresvents.bmp",NULL), "lieu"));
    lieux.push_back(Lieu("HMS Intrepide",         load_bitmap("images/intrepide.bmp",NULL), "lieu"));
    lieux.push_back(Lieu("Triangle des Bermudes", load_bitmap("images/bermudes.bmp",NULL), "lieu"));
    lieux.push_back(Lieu("Black Pearl",           load_bitmap("images/blackpearl.bmp",NULL), "lieu"));


    int j=0;

    for(int i=0; i<6; i++)
        cartes.push_back(Carte(i,armes[i].getNom(), armes[i].getImage(),armes[i].getType(), 0, 0));

    for(int i=6; i<15; i++)
    {
        cartes.push_back(Carte(i,personnages[j].getNom(), personnages[j].getImage(),personnages[j].getType(), 0, 0));
        j++;
    }

    j=0;
    for(int i=15; i<24; i++)
    {
        cartes.push_back(Carte(i,lieux[j].getNom(), lieux[j].getImage(),lieux[j].getType(), 0, 0));
        j++;
    }

    ///Mélanges des cartes
    for(int i=0 ; i<NB_CARTE  ; i++)
    {
        ok =0;
        ///On refait tant que le nombre aléatoire a déjà été piochée (pas francais mais tqt)
        do
        {
            id = rand()%(24);
            ok=0 ;

            ///Vérification si carte déjà piochée
            for(auto& item:cartes)
            {

                ///Si on trouve la carte par son id
                if(item.getId()==id)
                {
                    cartes2.push_back(item); //On ajoute la carte
                    item.setId(100) ; //Valeur non valide pour ne pas le reprendre
                    ok=1 ;
                }
            }
        }
        while(ok==0);
    }
}


/// //////////////////////////////////////////////////////////// ///
/// DISTRIBUTION DES CARTES À LA POCHETTE SECRÈTE ET AUX JOUEURS ///
/// //////////////////////////////////////////////////////////// ///

void Menu::distribCarte(std::vector <Carte> &cartes2,std::vector <Carte> &secret,std::vector <Joueur> &joueurs, int &nb_joueurs)
{
    int tour=0 ;
    bool persoSecret=false, armeSecrete=false, lieuSecret=false ; ///Une fois pochette secrète remplie on met true

    for(auto& joueur : joueurs)
        joueur.hypotheseInit();

    ///Attribution des cartes (secret + joueurs)
    for(int i=0 ; i<NB_CARTE ; i++)
    {
        for(auto& item:cartes2)
        {
            ///On remplie la pochette secrète avec la première carte de type perso
            if(persoSecret==false and item.getType()=="perso")
            {
                persoSecret=true ;
                secret.push_back(item);
                item.setType("off");
            }
            ///On remplie la pochette secrète avec la première carte de type arme
            else if(armeSecrete==false and item.getType()=="arme")
            {
                armeSecrete=true ;
                secret.push_back(item);
                item.setType("off");
            }
            ///On remplie la pochette secrète avec la première carte de type lieu
            else if(lieuSecret==false and item.getType()=="lieu")
            {
                lieuSecret=true ;
                secret.push_back(item);
                item.setType("off");
            }

            ///Remplissage du reste des cartes pour les joueurs
            else if(item.getType()!="off")
            {
                joueurs[tour].add(item);
                joueurs[tour].setHypo(item.getNom());
                joueurs[tour].setFin(false);
                item.setType("off");

                tour++;
                if(tour==nb_joueurs)
                    tour=0 ;
            }
        }
    }
}






/// /////////////////////////////////////// ///
/// INITIALISATION DE LA MATRICE DU PLATEAU ///
/// /////////////////////////////////////// ///

std::vector<std::vector<char>> Menu::initPlateau()
{
    std::vector<std::vector <char>> matrice
    {
        {'1','1','1','1','1','1','1','1','1','1','D','1','1','1','1','D','1','1','1','1','1','1','1','1','1','1'},
        {'1','0','0','0','0','0','0','1','8','8','8','0','0','0','0','8','8','8','1','0','0','0','0','0','0','1'},
        {'1','0','0','0','0','0','0','8','8','0','0','0','0','0','0','0','0','8','8','0','0','0','0','0','0','1'},
        {'1','0','0','0','0','0','0','8','8','0','0','0','0','0','0','0','0','8','C','0','0','0','0','0','0','1'},
        {'1','0','0','0','0','0','0','8','8','0','0','0','0','0','0','0','0','8','8','0','0','0','0','0','0','1'},
        {'1','1','0','0','0','7','0','8','8','0','0','0','0','0','0','0','7','8','8','7','0','0','0','0','1','1'},
        {'1','8','C','8','8','8','8','8','8','0','7','0','0','0','0','0','0','8','8','8','8','8','8','8','D','1'},
        {'1','1','8','8','8','8','8','8','8','8','8','8','8','8','8','8','8','8','8','8','C','8','8','8','1','1'},
        {'1','0','0','0','0','0','8','8','8','8','8','8','8','8','8','8','8','8','8','0','0','0','0','0','0','1'},
        {'1','0','0','0','0','0','0','0','0','8','8','7','7','7','7','7','8','8','8','7','0','0','0','0','0','1'},
        {'1','0','0','0','0','0','0','0','0','C','8','7','0','0','0','7','8','8','8','0','0','0','0','0','0','1'},
        {'1','0','0','0','0','0','0','0','0','8','8','7','0','0','0','7','8','8','8','0','0','0','0','0','0','1'},
        {'1','0','0','0','0','0','0','0','0','8','8','7','0','0','0','7','8','8','8','0','0','0','0','7','0','1'},
        {'1','0','0','0','0','0','0','0','0','8','8','7','0','0','0','7','C','8','8','8','8','8','8','8','1','1'},
        {'1','0','0','0','0','0','0','0','0','8','8','7','0','0','0','7','8','8','8','0','0','7','0','0','1','1'},
        {'1','0','0','0','0','0','0','7','0','8','8','7','0','0','0','7','8','8','0','0','0','0','0','0','0','1'},
        {'1','1','8','C','8','8','8','8','8','8','8','7','7','7','7','7','8','8','7','0','0','0','0','0','0','1'},
        {'1','D','8','8','8','8','8','8','8','8','8','8','8','8','8','8','8','8','0','0','0','0','0','0','0','1'},
        {'1','1','8','8','8','8','8','8','8','C','0','0','0','7','0','0','8','8','8','0','0','0','0','0','1','1'},
        {'1','0','0','0','0','0','0','7','8','8','0','0','0','0','0','0','8','8','8','8','8','8','8','8','D','1'},
        {'1','0','0','0','0','0','0','0','8','8','0','0','0','0','0','0','8','8','8','8','C','8','8','8','1','1'},
        {'1','0','0','0','0','0','0','0','8','8','0','0','0','0','0','0','8','8','7','0','0','0','0','0','0','1'},
        {'1','0','0','0','0','0','0','0','8','8','0','0','0','0','0','0','8','8','0','0','0','0','0','0','0','1'},
        {'1','0','0','0','0','0','0','0','8','8','0','0','0','0','0','0','8','8','0','0','0','0','0','0','0','1'},
        {'1','0','0','0','0','0','0','1','D','1','0','0','0','0','0','0','8','8','0','0','0','0','0','0','0','1'},
        {'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'}
    };

    return matrice;
}
