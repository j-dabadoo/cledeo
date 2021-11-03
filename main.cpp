#include "header.h"

int main()
{
    ///Genrateur de nombres aléatoires
    srand(time(NULL));
    ///Initialisation d'allegro
    allegroInit();

    ///Joueur qui va se deplacer
    Joueur lejoueur=Joueur();
    lejoueur.setlogo(load_bitmap("pion.bmp", NULL));
    lejoueur.setposX(1);
    lejoueur.setposY(17);
    lejoueur.setloca('D');

    ///Buffer
    BITMAP* page;
    page=create_bitmap(SCREEN_W, SCREEN_H);

    ///Chargement du plateau de jeu
    BITMAP* plateau;
    plateau=load_bitmap("plateau.bmp", NULL);

    std:: vector <std::vector <char>> matrice;
    matrice = initplateau();

    blit(plateau, page, 0,0,0,0, SCREEN_W, SCREEN_H);
    masked_blit(lejoueur.getlogo(), page, 0,0, (lejoueur.getposX()*23), (lejoueur.getposY()*23), SCREEN_W, SCREEN_H);
    blit(page, screen, 0,0,0,0, SCREEN_W, SCREEN_H);

    lejoueur.deplacement(plateau,page, matrice);

    return 0 ;
}
END_OF_MAIN();
