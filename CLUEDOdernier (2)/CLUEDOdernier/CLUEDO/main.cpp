#include "header.h"

int main()
{
    std::vector <Carte> cartes ; ///non mélangées
    std::vector <Arme> armes;
    std::vector <Lieu> lieux;
    std::vector <Personnage> personnages;

    std::vector <Carte> cartes2 ;///Mélangées
    std::vector <Carte> secret ;///Pochette secrète de 3 cartes
    std::vector <Joueur> joueurs;///Ensemble des joueurs
    std:: vector <std::vector <char>> matrice = initPlateau(); ///Matrice du plateau

    int nb_joueurs, tour = 0 ;


    /// INITIALISATION
    allegroInit();

    BITMAP* buffer = create_bitmap(1200, 600); ///Buffer
    BITMAP* plateau = load_bitmap("images/plateau.bmp", NULL); ///Chargement du plateau de jeu
    BITMAP* fond = load_bitmap("images/fond.bmp", NULL);
    BITMAP* des = create_bitmap(250, 250);
    rectfill(des,0,0,des->w,des->h,makecol(59,162,71));


    ///MENU DE DÉPART
    menu(joueurs, cartes, cartes2, nb_joueurs, secret, tour, armes, lieux, personnages); ///1er menu : appuie sur jouer


    ///BOUCLE DE JEU
    while(!key[KEY_ESC])
    {
        clear_bitmap(buffer);

        ///Si le joueur n'est pas sur une case chance
        if(joueurs[tour].getLoca() != 'C')
            joueurs[tour].setFin(false);

        ///Si le joueur vient d'arriver sur une carte chance
        if(joueurs[tour].getLoca() == 'C' and joueurs[tour].getFin() == false)
            joueurs[tour].setFin(casechance(plateau, joueurs, tour, nb_joueurs, buffer, matrice, fond));
        else joueurs[tour].deplacement(buffer, matrice);

        ///Appel tour par tour
        if(key[KEY_SPACE])
            tourParTour(tour, nb_joueurs, joueurs);

        ///Actualisation de l'affichage
        actualisation(buffer, plateau, joueurs, tour, nb_joueurs, des, fond);

        ///Zoom
        zoom(buffer);

        ///Action selon le bouton appuyé
        actionsBoutons(joueurs,secret, tour, nb_joueurs, buffer, des, cartes, armes, lieux, personnages) ;
    }


    ///Sauvegarde de la partie (tous les joueurs dans le même fichier)
    writeAll(joueurs, tour, secret);

    ///Sauvegarde du score
    saveScore(joueurs);

    ///Destruction des bitmap
    destruction(cartes, plateau, joueurs);
    destroy_bitmap(fond);

    allegro_exit();
    return 0 ;

}END_OF_MAIN();
