#include "header.h"


int menu(std::vector <Joueur> &joueurs, std::vector <Carte> &cartes, std::vector <Carte> &cartes2, int &nb_joueurs,std::vector <Carte> &secret)
{
    BITMAP *menuG = load_bitmap("images/menu1 gris.bmp", NULL) ;
    BITMAP *menuR = load_bitmap("images/menu1 rouge.bmp", NULL) ;
    BITMAP *buffer = create_bitmap(1200,600);

    int choix =0 ;

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
        choix = launch(joueurs, cartes, cartes2, nb_joueurs, secret);



    ///Destruction bitmap
    destroy_bitmap(menuG);
    destroy_bitmap(menuR);
    destroy_bitmap(buffer);

    return choix ;
}

int launch(std::vector <Joueur> &joueurs, std::vector <Carte> &cartes, std::vector <Carte> &cartes2, int &nb_joueurs,std::vector <Carte> &secret)
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

    return choix ;
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

    return nb_joueurs ;
}


