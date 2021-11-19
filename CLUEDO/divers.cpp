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

void actualisation(BITMAP* buffer, BITMAP* plateau, std::vector<Joueur>& joueurs, int& tour, int& nb_joueurs)
{
    int choixint = 0 ;
    Hypothese hypothese ;

    choixint=plateaudebase(buffer);

    //blit(plateau, buffer, 0,0,0,0, SCREEN_W, SCREEN_H);
    //al_draw_text(font,makecol(255,255,255), 700,50, 0, "%s", joueurs[tour].getNom());

    ///Si le joueur choisit d'afficher les hypothèses
    if(choixint == 1)
        hypothese.actionhypo(choixint, joueurs, tour, nb_joueurs, buffer);

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



    ///Bouton hypothèse
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







/// //////////////////////////// ///
/// ÉCRITURE DE TOUS LES JOUEURS ///
/// //////////////////////////// ///

void writeAll(std::vector <Joueur>& joueurs, int& tour)
{
    std::ofstream ofs("saveGame", std::ios::out);

    if (ofs)
    {
        ///Sauvegarde du nombre de joueurs
        ofs << joueurs.size() << std::endl ;

        ///Sauvegarde du tour
        ofs << tour << std::endl ;

        ///Sauvegarde de tous les joueurs
        for(auto& joueur:joueurs)
        {
            ///Sauvegarde nom
            ofs << joueur.getNom() << std::endl; //<< " fin" << std::endl;


            ///Sauvegarde PosX
            ofs << joueur.getPosX() << std::endl;

            ///Sauvegarde PosY
            ofs << joueur.getPosY() << std::endl;

            ///Sauvegarde nb déplacements restants
            ofs << joueur.getDeplacement() << std::endl;

            ///Sauvegarde la localisation
            ofs << joueur.getLoca() << std::endl;

            ///Sauvegarde le score
            ofs << joueur.getScore() << std::endl;

            ///Sauvegarde de la couleur
            ofs << joueur.getCouleurPion() << std::endl;


            ///Sauvegarde de la map

            ///Sauvegarde de la taille de la map
            size_t tailleMatrice = joueur.getHypo().size();
            ofs << tailleMatrice << std::endl ;



            ///Sauvegarder de la map d'hypothèses

            std::map<std::string, bool>::iterator it ;
            std::map<std::string, bool> hypo = joueur.getHypo();
            for (it = hypo.begin() ; it != hypo.end(); it++)
            {
                if(it->second == true)
                    ofs << it->first.c_str() <<" : " << 'T' << std::endl ;

                else
                    ofs << it->first.c_str() <<" : " << 'F' << std::endl ;
            }

            ///Sauvegarde du vecteur de carte

            ///Sauvegarde de la taille du vecteur
            ofs << joueur.getCartes().size() << std::endl ;

            for(auto& carte:joueur.getCartes())
            {
                ///Sauvegarde d'une carte

                //Sauvegarde id de la carte
                ofs << carte.getId() << std::endl ;

                //Sauvegarde position X
                ofs << carte.getPosX() << std::endl ;

                //Sauvegarde position Y
                ofs << carte.getPosY() << std::endl ;

                //Sauvegarde nom
                ofs << carte.getNom() << " ;" << std::endl ;

                //Sauvegarde type
                ofs << carte.getType() << std::endl ;
            }
        }

        ofs.close(); // fermeture du flux
    }
}



/// /////////////////////////////////////////////////// ///
/// LECTURE D'UN FICHIER TEXTE EN FONCTION DU NOM SAISI ///
/// /////////////////////////////////////////////////// ///

void readAll(std::vector <Joueur>& joueurs, int& nb_joueurs, int& tour)
{
    std::ifstream ifs("saveGame");

    if (ifs) // test si le fichier est bien ouvert
    {
        std::string line;
        int entier;
        char car;

        ///Lecture du nombre de joueurs
        ifs >> entier ;
        nb_joueurs = entier ;

        ///Adaptation du vecteur de joueurs
        joueurs.resize(nb_joueurs);

        ///Lecture du tour
        ifs >> entier ;
        tour = entier ;

        for(auto& joueur:joueurs)
        {
            ///Lecture nom
            ifs >> line ;
            joueur.setNom(line);

            /*std::string nomm ;

            while(line!="fin")
            {
                ifs >> line ;
                nomm += " " ;
                nomm += line ;
                std::cout << line<<std::endl ;
            }

            size_t tailleNom = nomm.size() ;
            nomm.resize(tailleNom-4) ;
            joueur.setNom(nomm);*/




            ///Lecture PosX
            ifs >> entier ;
            joueur.setPosX(entier);

            ///Lecture PosY
            ifs >> entier ;
            joueur.setPosY(entier);

            ///Lecture nb déplacements
            ifs >> entier ;
            joueur.setDeplacement(entier);

            ///Lecture de la localisation
            ifs >> car ;
            joueur.setLoca(car);

            ///Lecture du score
            ifs >> entier ;
            joueur.setScore(entier);

            ///Lecture couleur
            ifs >> line;
            joueur.setCouleur(line);

            ///Lecture de la taille de la map
            ifs >> entier ;

            ///Lecture de la map
            for(int i=0 ; i<entier ; i++)
            {
                std::cout<<"debut"<<std::endl ;
                std::string mot ;
                line="0";
                //ifs >> line ;
                //ifs >> car >> car;

                /// //////////////////
                while(line!=":")
                {
                    ifs >> line ;
                    mot += " " ;
                    mot += line ;
                    std::cout<<"line : "<<line<<std::endl ;
                }


                size_t tailleMot = mot.size() ;
                mot.resize(tailleMot-2) ;
                std::cout << "mot : " << mot << std::endl ;

                ifs >> car ;
                std::cout << "carac : " << car << std::endl ;
                /// //////////////////////

                if(car=='T')
                    joueur.setHypo(line, true);

                else
                    joueur.setHypo(line, false);

                std::cout<<"fin"<<std::endl ;
            }

            std::cout <<"sortie boucle"<<std::endl ;
            ///Lecture du vecteur de cartes
            int tailleVec ;
            ifs >> tailleVec ;

            int id, posX, posY ;
            std::string type ;


            for(int i=0 ; i<tailleVec ; i++)
            {
                std::string nom = "";
                //Lecture id
                ifs >> id ;

                //Lecture posX
                ifs >> posX ;

                //Lecture posY
                ifs >> posY ;

                //Lecture nom
                //ifs >> nom ;
                /// //////////////////
                std::cout << "debut vec"<<std::endl;
                line="0";
                while(line!=";")
                {
                    ifs >> line ;
                    nom += " " ;
                    nom += line ;
                }

                size_t tailleNom = nom.size() ;
                nom.resize(tailleNom-2) ;
                std::cout << "fin vec // nom : "<< nom << "//"<< std::endl;
                /// //////////////////////

                //Lecture type
                ifs >> type ;

                ///Ajout d'une carte dans le vecteur
                Carte newCarte(id, nom, NULL, type, posX, posY);
                joueur.add(newCarte);
            }
        }

        ///Fermeture du fichier
        ifs.close();
    }

    else
        std::cout << "Le joueur n'existe pas " << std::endl ;

}
