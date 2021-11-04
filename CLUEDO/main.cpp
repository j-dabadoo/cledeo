#include "header.h"

int main()
{
    std::vector <Carte> cartes ; ///non mélangées
    std::vector <Carte> cartes2 ;///Mélangées
    std::vector <Carte> secret ;///Pochette secrète de 3 cartes
    std::vector <Joueur> joueurs;///Ensemble des joueurs
    std:: vector <std::vector <char>> matrice = initPlateau(); ///Matrice du plateau

    int nb_joueurs, choix =0 ;

    /// INITIALISATIONS
    allegroInit();

    BITMAP* buffer = create_bitmap(1200, 600); ///Buffer
    BITMAP* plateau = load_bitmap("images/plateau.bmp", NULL); ///Chargement du plateau de jeu



    ///MENU DE DÉPART
    ///Pas forcément besoin de récupérer le choix ici. les initialisations en fonction des modes de jeu sont faites dans les menus
    /// donc dans le main on n'a que la boucle de jeu pour les choix 1 et 2 qui est la même donc pas besoin
    choix = menu(joueurs, cartes, cartes2, nb_joueurs, secret); ///1er menu : appuie sur jouer

    clear_bitmap(screen);


    ///BOUCLE DE JEU

    while(!key[KEY_ESC])
    {
        blit(plateau, buffer, 0,0,0,0, SCREEN_W, SCREEN_H);
        masked_blit(joueurs[0].getImagePion(), buffer, 0,0, (joueurs[0].getPosX()*23), (joueurs[0].getPosY()*23), SCREEN_W, SCREEN_H);
        blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);

        joueurs[0].deplacement(plateau,buffer, matrice);
        //rest(1000);

        ///Appel tour par tour
    }


    ///Destruction des bitmap
    destruction(cartes);

    allegro_exit();
    return 0 ;

}END_OF_MAIN();
