#include "header.h"

/// ////////////////////////////////// ///
/// PERMET DE PASSER AU JOUEUR SUIVANT ///
/// ////////////////////////////////// ///

void tourParTour(int& tour, int& nb_joueurs)
{
    while(key[KEY_SPACE])
    {}

    tour++ ; ///Incrementation du compteur tour pour passer au joueur suivant

    ///Revient au premier joueur
    if (tour==nb_joueurs)
        tour=0 ;
}

/// /////////////////// ///
/// LANCEMENT DES 2 DÉS ///
/// /////////////////// ///

int lancerDe()
{
    return rand()%(11)+2; ///Génération d'un nombre aléatoire entre 2 et 12
}




/// //////////////////////////// ///
/// ACTUALISATION DE L'AFFICHAGE ///
/// //////////////////////////// ///

void actualisation(BITMAP* buffer, BITMAP* plateau, std::vector<Joueur>& joueurs, int& tour)
{
    int choixint;
    Hypothese hypothese ;

    choixint=plateaudebase(buffer);

    //blit(plateau, buffer, 0,0,0,0, SCREEN_W, SCREEN_H);
    //al_draw_text(font,makecol(255,255,255), 700,50, 0, "%s", joueurs[tour].getNom());

    ///Si le joueur choisit d'afficher les hypothèses
    if(choixint == 1)
    {
        while(!key[KEY_SPACE])
        {
            hypothese.affichehypo(buffer, joueurs, tour);
            hypothese.actionhypo(choixint, joueurs, tour);
        }
    }

    ///Affichage du plateau de jeu
    else
    {
        ///Affichage des pions
        for(const auto& joueur:joueurs)
            draw_sprite(buffer, joueur.getImagePion(), joueur.getPosX()*23.25, joueur.getPosY()*23.5) ;

        ///Affichage du nom et du nombre de coups restant à jouer
        textprintf_ex(buffer, font, 700, 50, makecol(255,255,255), -1, "%s", joueurs[tour].getNom().c_str());
        textprintf_ex(buffer, font, 600, 100, makecol(255, 255, 255), -1, "Il vous reste %d deplacements", joueurs[tour].getDeplacement());

        ///Affichage des cartes du joueurs
        joueurs[tour].cardDisplay(buffer);
    }


    ///Affichage du buffer à l'écran
    blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
}



/// //////////////////////////// ///
/// AFFICHAGE DU PLATEAU INITIAL ///
/// //////////////////////////// ///

int plateaudebase(BITMAP* page)
{
    BITMAP* plateau;

    plateau=load_bitmap("images/plateau.bmp", NULL);
    blit(plateau, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    ///quitter le jeu
    rectfill(page,620,125,820,175,makecol(127,127,127));
    ///bouton hypothese
    rectfill(page,620,225,820,275,makecol(208,82,41));
    ///zone de dé
    rectfill(page,900,75,1150,325,makecol(59,162,71));
    ///zone des joueurs
    rectfill(page,620,375,1100,685,makecol(136,0,21));

    if(mouse_x>=620 && mouse_x<=820 && mouse_y>=225 && mouse_y<=275)
        rect(page, 617, 222, 823, 278, makecol(208,82,41));

    else
        rect(page, 617, 222, 823, 278, makecol(0,0,0));

    if(mouse_b &1)
    {
        if(mouse_x>=620 && mouse_x<=820 && mouse_y>=225 && mouse_y<=275)
            return 1;
    }

    return 0 ;
}

