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



    ///MENU DE D�PART
    menu(joueurs, cartes, cartes2, nb_joueurs, secret, tour); ///1er menu : appuie sur jouer



    std::cout << "//////////////////////////////////////////////////"<<std::endl ;
       for(auto& joueur:joueurs)
       {
           //std::map<std::string, bool>hypo = joueur.getHypo();
           //std::map<std::string, bool>:iterator it ;
           for(auto& hypo:joueur.getHypo())
           {
               std::cout<<hypo.first<< " : " << hypo.second << std::endl ;
           }

           std::cout<<"FIN JOUEUR"<<std::endl ;
       }
    std::cout << "//////////////////////////////////////////////////"<<std::endl ;


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
            joueurs[tour].setDeplacement(lancerDe());
        }
       ///Actualisation de l'affichage
       actualisation(buffer, plateau, joueurs, tour, nb_joueurs);

       std::cout << "//////////////////////////////////////////////////"<<std::endl ;
       for(auto& joueur:joueurs)
       {
           //std::map<std::string, bool>hypo = joueur.getHypo();
           //std::map<std::string, bool>:iterator it ;
           for(auto& hypo:joueur.getHypo())
           {
               std::cout<<hypo.first<< " : " << hypo.second << std::endl ;
           }
       }
        std::cout << "//////////////////////////////////////////////////"<<std::endl ;

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
