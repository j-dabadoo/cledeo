#include "header.h"

int main()
{
    std::vector <Carte> cartes ; ///non m�lang�es
    std::vector <Carte> cartes2 ;///M�lang�es
    std::vector <Carte> secret ;///Pochette secr�te de 3 cartes
    std::vector <Joueur> joueurs;///Ensemble des joueurs
    std:: vector <std::vector <char>> matrice = initPlateau(); ///Matrice du plateau

    int nb_joueurs, tour =0 ;

    /// INITIALISATIONS
    allegroInit();

    BITMAP* buffer = create_bitmap(1200, 600); ///Buffer
    BITMAP* plateau = load_bitmap("images/plateau.bmp", NULL); ///Chargement du plateau de jeu
    BITMAP* des = create_bitmap(250, 250);

    rectfill(des,0,0,des->w,des->h,makecol(59,162,71));

    ///MENU DE D�PART
    menu(joueurs, cartes, cartes2, nb_joueurs, secret, tour); ///1er menu : appuie sur jouer


    ///BOUCLE DE JEU
    while(!key[KEY_ESC])
    {
        clear_bitmap(buffer);


        ///Appel du d�placement d'un joueur
        joueurs[tour].deplacement(plateau,buffer, matrice);

        ///Appel tour par tour
        if(key[KEY_SPACE])
        {
            tourParTour(tour, nb_joueurs);

            ///Quand on passe � l'autre joueur on lui relance ses d�s
            //joueurs[tour].setDeplacement(lancerDe());
        }


        ///Actualisation de l'affichage
        actualisation(buffer, plateau, joueurs, tour, nb_joueurs, des);

        actionsBoutons(joueurs, tour, nb_joueurs, buffer, des) ;
    }


    ///Sauvegarde des joueurs
    //for(auto& joueur:joueurs)
        //joueur.writeFile();

    ///Sauvegarde de la partie (tous les joueurs dans le m�me fichier)
    writeAll(joueurs, tour);

    ///Destruction des bitmap
    destruction(cartes, plateau, joueurs);

    allegro_exit();
    return 0 ;

}END_OF_MAIN();
