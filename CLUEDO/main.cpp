#include "header.h"



int main()
{
    std::vector <Carte> cartes ; ///non mélangées
    std::vector <Carte> cartes2 ;///Mélangées
    std::vector <Carte> secret ;///Pochette secrète de 3 cartes
    std::vector <Joueur> joueurs;///Ensemble des joueurs

    int nb_joueurs ;


    /// INITIALISATIONS

    allegroInit();
    cardInit(joueurs, cartes, cartes2);
    distribCarte(cartes2, secret, joueurs);



    ///BOUCLE D'ÉVÈNEMENTS

    while(!key[KEY_ESC])
    {
        menu(); ///Premier menu : appuie sur jouer
        nb_joueurs = choix_nbj();   ///2e : choisi le nombre de joueurs
        launch(); ///3e : lancement de partie sauvegardée, nouvelle partie...
    }


    ///Destruction des bitmap
    destruction(cartes);

    allegro_exit();
    return 0 ;

}END_OF_MAIN();
