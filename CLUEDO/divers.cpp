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
    BITMAP* detournant  = load_bitmap("images/de.bmp", NULL);
    BITMAP* un          = load_bitmap("images/UN.bmp", NULL);
    BITMAP* deux        = load_bitmap("images/DEUX.bmp", NULL);
    BITMAP* trois       = load_bitmap("images/TROIS.bmp", NULL);
    BITMAP* quatre      = load_bitmap("images/QUATRE.bmp", NULL);
    BITMAP* cinq        = load_bitmap("images/CINQ.bmp", NULL);
    BITMAP* six         = load_bitmap("images/SIX.bmp", NULL);
    BITMAP* buffer      = create_bitmap(1200, 600);
    BITMAP* buffer1     = create_bitmap(1200, 600);

    int resultat1, resultat2;


    blit(detournant, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H );

    for(int i=0; i<10; i++)
    {
        clear_bitmap(buffer1);
        rotate_sprite(buffer1, detournant,0, 0, ftofix(20*i));
        blit(buffer1, screen, 0, 0,0, 0, SCREEN_W, SCREEN_H );
        blit(buffer1, screen, 0, 0,0, 300, SCREEN_W, SCREEN_H );

        rest(70);
    }

    resultat1 = rand()%(7)+1 ;
    resultat2 = rand()%(7)+1 ;

    while(not(key[KEY_SPACE]))
    {
        //premier de
        if(resultat1==1)
            masked_blit(un,     buffer,  0, 0, 400, 0, SCREEN_W, SCREEN_H );
        if(resultat1==2)
            masked_blit(deux,   buffer,  0, 0, 400, 0, SCREEN_W, SCREEN_H );
        if(resultat1==3)
            masked_blit(trois,  buffer,  0, 0, 400, 0, SCREEN_W, SCREEN_H );
        if(resultat1==4)
            masked_blit(quatre, buffer,  0, 0, 400, 0, SCREEN_W, SCREEN_H );
        if(resultat1==5)
            masked_blit(cinq,   buffer,  0, 0, 400, 0, SCREEN_W, SCREEN_H );
        if(resultat1==6)
            masked_blit(six,    buffer,  0, 0, 400, 0, SCREEN_W, SCREEN_H );

        //deuxieme dé
        if(resultat2==1)
            masked_blit(un,     buffer,  0, 0, 400, 400, SCREEN_W, SCREEN_H );
        if(resultat2==2)
            masked_blit(deux,   buffer,  0, 0, 400, 400, SCREEN_W, SCREEN_H );
        if(resultat2==3)
            masked_blit(trois,  buffer,  0, 0, 400, 400, SCREEN_W, SCREEN_H );
        if(resultat2==4)
            masked_blit(quatre, buffer,  0, 0, 400, 400, SCREEN_W, SCREEN_H );
        if(resultat2==5)
            masked_blit(cinq,   buffer,  0, 0, 400, 400, SCREEN_W, SCREEN_H );
        if(resultat2==6)
            masked_blit(six,    buffer,  0, 0, 400, 400, SCREEN_W, SCREEN_H );

        blit(buffer, screen, 0, 0,0, 0, SCREEN_W, SCREEN_H );
        rest(100);
    }


    destroy_bitmap(detournant) ;
    destroy_bitmap(un) ;
    destroy_bitmap(deux) ;
    destroy_bitmap(trois) ;
    destroy_bitmap(quatre) ;
    destroy_bitmap(cinq) ;
    destroy_bitmap(six) ;


    return resultat1 + resultat2 ;
}




/// //////////////////////////// ///
/// ACTUALISATION DE L'AFFICHAGE ///
/// //////////////////////////// ///

void actualisation(BITMAP* buffer, BITMAP* plateau, std::vector<Joueur>& joueurs, int& tour, int& nb_joueurs)
{
    ///Affichage du plateau et des boutons
    blit(plateau, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    ///quitter le jeu
    rectfill(buffer,620,125,820,175,makecol(127,127,127));

    ///bouton hypothese
    rectfill(buffer,620,225,820,275,makecol(208,82,41));
    if(mouse_x>=620 && mouse_x<=820 && mouse_y>=225 && mouse_y<=275)
        rect(buffer, 617, 222, 823, 278, makecol(208,82,41));
    else
        rect(buffer, 617, 222, 823, 278, makecol(0,0,0));

    ///zone de dé
    rectfill(buffer,900,75,1150,325,makecol(59,162,71));



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

void actionsBoutons(std::vector <Joueur>& joueurs, int& tour, int& nb_joueurs, BITMAP* buffer)
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
            joueurs[tour].setDeplacement(lancerDe());
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
