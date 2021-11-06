#include "header.h"


void menu(std::vector <Joueur> &joueurs, std::vector <Carte> &cartes, std::vector <Carte> &cartes2, int &nb_joueurs,std::vector <Carte> &secret)
{
    BITMAP *menuG = load_bitmap("images/menu1 gris.bmp", NULL) ;
    BITMAP *menuR = load_bitmap("images/menu1 rouge.bmp", NULL) ;
    BITMAP *buffer = create_bitmap(1200,600);


    ///On affiche play en gris en normal, rouge si on passe dessus
    while(!(mouse_b&1 && mouse_x>548 && mouse_x<649 && mouse_y>460 && mouse_y<555))
    {
        if(mouse_x>548 && mouse_x<649 && mouse_y>460 && mouse_y<555)
            blit(menuR, buffer, 0, 0, 0, 0, 1200, 600);

        else
            blit(menuG, buffer, 0, 0, 0, 0, 1200, 600);

        blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);

        if(key[KEY_ESC])
            allegro_exit();
    }


    ///2e menu : lancement de partie sauvegardée, nouvelle partie...
    if(mouse_b&1 && mouse_x>548 && mouse_x<649 && mouse_y>460 && mouse_y<555)
        launch(joueurs, cartes, cartes2, nb_joueurs, secret);



    ///Destruction bitmap
    destroy_bitmap(menuG);
    destroy_bitmap(menuR);
    destroy_bitmap(buffer);
}


void launch(std::vector <Joueur> &joueurs, std::vector <Carte> &cartes, std::vector <Carte> &cartes2, int &nb_joueurs,std::vector <Carte> &secret)
{
    int choix =0 ;
    BITMAP* menu2 = load_bitmap("images/menu2.bmp", NULL);
    BITMAP* menu2_1 = load_bitmap("images/menu2.1.bmp", NULL);
    BITMAP* menu2_2 = load_bitmap("images/menu2.2.bmp", NULL);
    BITMAP* menu2_3 = load_bitmap("images/menu2.3.bmp", NULL);
    BITMAP* menu2_4 = load_bitmap("images/menu2.4.bmp", NULL);
    BITMAP* menu2_5 = load_bitmap("images/menu2.5.bmp", NULL);

    BITMAP* buffer = create_bitmap(1200, 600);



    ///Saisie du choix en cliquant sur l'écran
    while(choix==0)
    {
        blit(menu2, buffer, 0, 0, 0, 0, menu2->w, menu2->h);

        ///Clique sur un des drapeaux
        if(mouse_x>60 && mouse_x<165)
        {
            ///Nouvelle partie
            if(mouse_y>160 && mouse_y<220)
            {
                blit(menu2_1, buffer, 0, 0, 0, 0, menu2->w, menu2->h);
                if(mouse_b&1)
                    choix=1 ;
            }

            ///Partie sauvegardée
            if(mouse_y>230 && mouse_y<290)
            {
                blit(menu2_2, buffer, 0, 0, 0, 0, menu2->w, menu2->h);
                if(mouse_b&1)
                    choix=2 ;
            }

            ///Scores
            if(mouse_y>300 && mouse_y<360)
            {
                blit(menu2_3, buffer, 0, 0, 0, 0, menu2->w, menu2->h);
                if(mouse_b&1)
                    choix=3 ;
            }

            ///Aide
            if(mouse_y>370 && mouse_y<430)
            {
                blit(menu2_4, buffer, 0, 0, 0, 0, menu2->w, menu2->h);
                if(mouse_b&1)
                    choix=4 ;
            }

            ///Quitter
            if(mouse_y>440 && mouse_y<500)
            {
                blit(menu2_5, buffer, 0, 0, 0, 0, menu2->w, menu2->h);
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
            cardInit(joueurs, cartes, cartes2, nb_joueurs);

            ///Distribution des cartes
            distribCarte(cartes2, secret, joueurs, nb_joueurs);

            for(int i=0; i<nb_joueurs; i++)
            {
                joueurs[i].setNom(saisie1joueur()) ;
                choix_couleur(joueurs[i]);
            }

        break ;

        ///Partie sauvegardée
        case 2 :
        break ;

        ///Scores
        case 3 :
        break ;

        ///Aide
        case 4 :
        break ;

        ///Quitter
        case 5 :
            menu(joueurs, cartes, cartes2, nb_joueurs, secret);
        break ;
    }

    destroy_bitmap(buffer);
    destroy_bitmap(menu2);
    destroy_bitmap(menu2_1);
    destroy_bitmap(menu2_2);
    destroy_bitmap(menu2_3);
    destroy_bitmap(menu2_4);
    destroy_bitmap(menu2_5);
}

int choix_nbj()
{
    int nb_joueurs=0 ;
    BITMAP* menu = load_bitmap("images/choix_nbj.bmp", NULL) ;
    BITMAP* buffer = create_bitmap(1200, 600);

    while(nb_joueurs==0)
    {
        if(mouse_b&1 && mouse_y>320 && mouse_y<470)
        {
            ///2 joueurs
            if(mouse_x>120 && mouse_x<260)
                nb_joueurs=2 ;

            else if(mouse_x>380 && mouse_x<520)
                nb_joueurs=3 ;

            else if(mouse_x>640 && mouse_x<780)
                nb_joueurs=4 ;

            else if(mouse_x>900 && mouse_x<1040)
                nb_joueurs=5 ;
        }
        blit(menu, buffer, 0, 0, 0, 0, menu->w, menu->h);
        blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
    }
    destroy_bitmap(menu);

    return nb_joueurs ;
}

void choix_couleur(Joueur& lejoueur)
{
    int choisi=0 ;
    BITMAP* menu =   load_bitmap("images/choix_couleur.bmp", NULL) ;
    BITMAP* red =    load_bitmap("images/pionR.bmp", NULL);
    BITMAP* yellow = load_bitmap("images/pionY.bmp", NULL);
    BITMAP* blue =   load_bitmap("images/pionB.bmp", NULL);
    BITMAP* green =  load_bitmap("images/pionG.bmp", NULL);
    BITMAP* violet = load_bitmap("images/pionV.bmp", NULL);
    BITMAP* white =  load_bitmap("images/pionW.bmp", NULL);

    BITMAP* logo = create_bitmap(23, 25);
    clear_bitmap(logo);
    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);

    while(choisi==0)
    {
        clear_bitmap(buffer);
        blit(menu, buffer, 0, 0, 0, 0, menu->w, menu->h);
        textprintf_ex(buffer, font, 580, 110, makecol(77, 3, 18), -1, "%s", lejoueur.getNom().c_str());
            if(mouse_y>215 && mouse_y<385 && mouse_x>225 && mouse_x < 375)
            {
                masked_blit(red, buffer, 0, 0, 225, 213, SCREEN_W, SCREEN_H);
                if(mouse_b&1)
                {
                    choisi=1 ;
                    lejoueur.setCouleur("rouge");
                    stretch_blit(red, logo, 0,0, red->w, red->h, 0,0,logo->w, logo->h);
                    lejoueur.setImagePion(logo);
                    lejoueur.setPosX(10);
                    lejoueur.setPosY(0);
                    textprintf_ex(buffer, font, 500, 200, makecol(77, 3, 18), -1, "Tres bon choix...." );
                }
            }
            if(mouse_y>215 && mouse_y<385 && mouse_x>525 && mouse_x < 675)
            {
                masked_blit(yellow, buffer, 0, 0, 525, 213, SCREEN_W, SCREEN_H);
                if(mouse_b&1)
                {
                    choisi=1 ;
                    lejoueur.setCouleur("jaune");
                    stretch_blit(yellow, logo, 0,0, yellow->w, yellow->h, 0,0,logo->w, logo->h);
                    lejoueur.setImagePion(logo);
                    lejoueur.setPosX(15);
                    lejoueur.setPosY(0);
                    textprintf_ex(buffer, font, 500, 200, makecol(77, 3, 18), -1, "Tres bon choix...." );
               }
            }
            if(mouse_y>215 && mouse_y<385 && mouse_x>825 && mouse_x < 975)
            {
                masked_blit(blue, buffer, 0, 0, 825, 213, SCREEN_W, SCREEN_H);
                if(mouse_b&1)
                {
                    choisi=1 ;
                    lejoueur.setCouleur("bleu");
                    stretch_blit(blue, logo, 0,0, blue->w, blue->h, 0,0,logo->w, logo->h);
                    lejoueur.setImagePion(logo);
                    lejoueur.setPosX(24);
                    lejoueur.setPosY(6);
                    textprintf_ex(buffer, font, 500, 200, makecol(77, 3, 18), -1, "Tres bon choix...." );
                }
            }
            if(mouse_y>415 && mouse_y<585 && mouse_x>325 && mouse_x < 475)
            {
                masked_blit(violet, buffer, 0, 0, 325, 412, SCREEN_W, SCREEN_H);
                if(mouse_b&1)
                {
                    choisi=1 ;
                    lejoueur.setCouleur("violet");
                    stretch_blit(violet, logo, 0,0, violet->w, violet->h, 0,0,logo->w, logo->h);
                    lejoueur.setImagePion(logo);
                    lejoueur.setPosX(24);
                    lejoueur.setPosY(19);
                    textprintf_ex(buffer, font, 500, 200, makecol(77, 3, 18), -1, "Tres bon choix...." );
                }
            }
            if(mouse_y>415 && mouse_y<585 && mouse_x>525 && mouse_x < 675)
            {
                masked_blit(green, buffer, 0, 0, 525, 412, SCREEN_W, SCREEN_H);
                if(mouse_b&1)
                {
                    choisi=1 ;
                    lejoueur.setCouleur("vert");
                    stretch_blit(green, logo, 0,0, green->w, green->h, 0,0,logo->w, logo->h);
                    lejoueur.setImagePion(logo);
                    lejoueur.setPosX(1);
                    lejoueur.setPosY(17);
                    textprintf_ex(buffer, font, 500, 200, makecol(77, 3, 18), -1, "Tres bon choix...." );
                }
            }
            if(mouse_y>415 && mouse_y<585 && mouse_x>725 && mouse_x < 875)
            {
                masked_blit(white, buffer, 0, 0, 725, 412, SCREEN_W, SCREEN_H);
                if(mouse_b&1)
                {
                    choisi=1 ;
                    lejoueur.setCouleur("blanc");
                    stretch_blit(white, logo, 0,0, white->w, white->h, 0,0,logo->w, logo->h);
                    lejoueur.setImagePion(logo);
                    lejoueur.setPosX(8);
                    lejoueur.setPosY(24);
                    textprintf_ex(buffer, font, 500, 200, makecol(77, 3, 18), -1, "Tres bon choix...." );
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

std::string saisie1joueur()
{
    int  i=0, x=580, y=110 ;
    char tempo[50]=" ";
    std::string nom;

    BITMAP* buffer = create_bitmap(SCREEN_W,SCREEN_H);
    BITMAP* fond =   load_bitmap("images/choix_nom.bmp", NULL);

    blit(fond, buffer, 0,0,0,0, SCREEN_W, SCREEN_H);
    textprintf_ex(buffer, font, 480, 90, makecol(77, 3, 18), -1, "Appuie sur ESPACE pour valider") ;
    blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);

    ///Tant qu'on appuie pas sur Entrée on est dans la saisie du nom du joueur
    while(!key[KEY_ENTER])
    {
        clear_bitmap(buffer);
        blit(fond, buffer, 0,0,0,0, SCREEN_W, SCREEN_H);
        textprintf_ex(buffer, font, 480, 90, makecol(77, 3, 18), -1, "Appuie sur ESPACE pour valider") ;

        ///On range chaque lettre
        tempo[i] = readkey() ;

        ///Si on fait Entrée, c'est la fin du mot, on remplace donc par \0
        if(key[KEY_ENTER])
            tempo[i]='\0' ;

        ///Si on appuie sur supprimer, on supprime la dernière lettre
        if(key[KEY_BACKSPACE])
        {
            tempo[i]=' ';
            i-- ;
            tempo[i]=' ';
            textprintf_ex(buffer, font, x, y, makecol(77, 3, 18), -1, "%s", tempo) ;
        }

        ///Si on appuie pas sur supprimer on affiche le texte normalement
        else
        {
            textprintf_ex(buffer, font, x, y, makecol(77, 3, 18), -1, "%s", tempo) ;
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
