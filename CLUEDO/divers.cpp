#include "header.h"

/// ////////////////////////////////// ///
/// PERMET DE PASSER AU JOUEUR SUIVANT ///
/// ////////////////////////////////// ///

void tourParTour(int& tour, int& nb_joueurs, std::vector<Joueur>& joueurs)
{

    while(key[KEY_SPACE]) //Permet de ne rien faire tant que la touche est appuyée (ne va donc pas sauter plusieurs tour
    {}

    joueurs[tour].setDeplacement(0); //Si le joueur n'a pas effectué tous ses déplacements on lui met à 0

    tour++ ; ///Incrementation du compteur tour pour passer au joueur suivant

    ///Revient au premier joueur
    if (tour==nb_joueurs)
        tour=0 ;
}



/// /////////////////// ///
/// LANCEMENT DES 2 DÉS ///
/// /////////////////// ///

int lancerDe(BITMAP *buffer, BITMAP *des)
{
    std::vector <BITMAP*> imgDe ;
    BITMAP* buffer2 = create_bitmap(1200, 600);
    int resultat1, resultat2;

    imgDe.push_back(load_bitmap("images/de.bmp", NULL));
    imgDe.push_back(load_bitmap("images/UN.bmp", NULL));
    imgDe.push_back(load_bitmap("images/DEUX.bmp", NULL));
    imgDe.push_back(load_bitmap("images/TROIS.bmp", NULL));
    imgDe.push_back(load_bitmap("images/QUATRE.bmp", NULL));
    imgDe.push_back(load_bitmap("images/CINQ.bmp", NULL));
    imgDe.push_back(load_bitmap("images/SIX.bmp", NULL));

    ///On efface le buffer de dé, on remet le fond vert de la case, puis on remet à l'écran
    clear_bitmap(des);
    rectfill(des,0,0,des->w,des->h,makecol(59,162,71));
    blit(des, buffer, 0, 0, 900, 75, SCREEN_W, SCREEN_H );

    for(int i=0; i<10; i++)
    {
        clear_bitmap(buffer2);
        blit(buffer, buffer2, 0, 0, 0, 0, SCREEN_W, SCREEN_H) ;
        rotate_sprite(buffer2, imgDe[0], 910, 140, ftofix(20*i));
        rotate_sprite(buffer2, imgDe[0],1030, 140, ftofix(20*i));

        blit(buffer2, screen, 0, 0,0, 0, SCREEN_W, SCREEN_H );

        rest(70);
    }

    ///Génération aléatoire pour les 2 dés
    resultat1 = rand()%(6)+1 ;
    resultat2 = rand()%(6)+1 ;


    draw_sprite(des, imgDe[resultat1], 20, 75);
    draw_sprite(des, imgDe[resultat2], 130, 75);


    for(int i=0 ; i<7 ; i++)
        destroy_bitmap(imgDe[i]) ;


    return resultat1 + resultat2 ;
}



/// //////////////////////////// ///
/// ACTUALISATION DE L'AFFICHAGE ///
/// //////////////////////////// ///

void actualisation(BITMAP* buffer, BITMAP* plateau, std::vector<Joueur>& joueurs, int& tour, int& nb_joueurs, BITMAP *des)
{
    ///Affichage du plateau et des boutons
    blit(plateau, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    ///Quitter le jeu
    rectfill(buffer,620,125,820,175,makecol(127,127,127));

    ///Bouton hypothese
    rectfill(buffer,620,225,820,275,makecol(208,82,41));
    if(mouse_x>=620 and mouse_x<=820 and mouse_y>=225 and mouse_y<=275)
        rect(buffer, 617, 222, 823, 278, makecol(208,82,41));
    else
        rect(buffer, 617, 222, 823, 278, makecol(0,0,0));

    ///Zone de dé
    rectfill(buffer,900,75,1150,325,makecol(59,162,71));
    if(mouse_x>=900 and mouse_x<=1150 and mouse_y>=75 and mouse_y<=325)
        rect(buffer, 897, 72, 1153, 328, makecol(59,162,71));
    else
        rect(buffer, 897, 72, 1153, 328, makecol(0,0,0));



    blit(des, buffer, 0, 0, 900, 75, des->w, des->h) ;

    //blit(plateau, buffer, 0,0,0,0, SCREEN_W, SCREEN_H);
    //al_draw_text(font,makecol(255,255,255), 700,50, 0, "%s", joueurs[tour].getNom());


    ///Affichage des pions
    for(const auto& joueur:joueurs)
        draw_sprite(buffer, joueur.getImagePion(), joueur.getPosX()*23.25, joueur.getPosY()*23.5) ;

    ///Affichage du nom et du nombre de coups restant à jouer
    textprintf_ex(buffer, font, 700, 50, makecol(255,255,255), -1, "%s", joueurs[tour].getNom().c_str());
    textprintf_ex(buffer, font, 600, 100, makecol(255, 255, 255), -1, "Il vous reste %d deplacements", joueurs[tour].getDeplacement());

    ///Affichage des cartes du joueurs
    joueurs[tour].cardDisplay(buffer);


    ///Affichage du buffer à l'écran
    blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
}



/// /////////////////// ///
/// ACTIONS DES BOUTONS ///
/// /////////////////// ///

void actionsBoutons(std::vector <Joueur>& joueurs, int& tour, int& nb_joueurs, BITMAP* buffer, BITMAP *des)
{
    Hypothese hypothese ;

    ///Appuie sur un bouton
    if(mouse_b &1)
    {
        ///Bouton hypothèse
        if(mouse_x >= 620 and mouse_x <= 820 and mouse_y >= 225 and mouse_y <= 275)
            hypothese.actionhypo(joueurs, tour, nb_joueurs, buffer);

        ///Lancer de dé
        if(mouse_x >= 900 and mouse_x <= 1150 and mouse_y >= 75 and mouse_y <= 325)
            joueurs[tour].setDeplacement(lancerDe(buffer, des));
    }
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
            ofs << joueur.getNom() << std::endl;

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
                std::string mot ;
                line="0";

                /// //////////////////
                while(line!=":")
                {
                    ifs >> line ;
                    mot += " " ;
                    mot += line ;
                }


                size_t tailleMot = mot.size() ;
                mot.resize(tailleMot-2) ;

                ifs >> car ;

                if(car=='T')
                    joueur.setHypo(mot, true);

                else
                    joueur.setHypo(mot, false);
            }

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

                line="0";
                while(line!=";")
                {
                    ifs >> line ;
                    nom += " " ;
                    nom += line ;
                }

                size_t tailleNom = nom.size() ;
                nom.resize(tailleNom-2) ;

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
