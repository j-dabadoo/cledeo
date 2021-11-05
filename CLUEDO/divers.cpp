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
    blit(plateau, buffer, 0,0,0,0, SCREEN_W, SCREEN_H);

    ///Affichage des pions
    for(const auto& joueur:joueurs)
        draw_sprite(buffer, joueur.getImagePion(), joueur.getPosX()*23, joueur.getPosY()*23) ;

    ///Affichage des cartes du joueurs
    joueurs[tour].cardDisplay(buffer);

    ///Affichage du buffer à l'écran
    blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
}




