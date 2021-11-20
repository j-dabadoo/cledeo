#include "header.h"

int main()
{
    std::vector <Carte> cartes ; ///non mélangées
    std::vector <Carte> cartes2 ;///Mélangées
    std::vector <Carte> secret ;///Pochette secrète de 3 cartes
    std::vector <Joueur> joueurs;///Ensemble des joueurs
    std:: vector <std::vector <char>> matrice = initPlateau(); ///Matrice du plateau

    int nb_joueurs, tour =0 ;

    /// INITIALISATIONS
    allegroInit();

    BITMAP* buffer = create_bitmap(1200, 600); ///Buffer
    BITMAP* plateau = load_bitmap("images/plateau.bmp", NULL); ///Chargement du plateau de jeu



    ///MENU DE DÉPART
    menu(joueurs, cartes, cartes2, nb_joueurs, secret, tour); ///1er menu : appuie sur jouer


    ///BOUCLE DE JEU
    while(!key[KEY_ESC])
    {
        clear_bitmap(buffer);


        ///Appel du déplacement d'un joueur
        joueurs[tour].deplacement(plateau,buffer, matrice);

        ///Appel tour par tour
        if(key[KEY_SPACE])
        {
            tourParTour(tour, nb_joueurs);

            ///Quand on passe à l'autre joueur on lui relance ses dés
            joueurs[tour].setDeplacement(lancerDe());
        }
       ///Actualisation de l'affichage
       actualisation(buffer, plateau, joueurs, tour, nb_joueurs);
    }


    ///Sauvegarde des joueurs
    //for(auto& joueur:joueurs)
        //joueur.writeFile();

    ///Sauvegarde de la partie (tous les joueurs dans le même fichier)
    writeAll(joueurs, tour);

    ///Destruction des bitmap
    destruction(cartes, plateau, joueurs);

    allegro_exit();
    return 0 ;

}END_OF_MAIN();
