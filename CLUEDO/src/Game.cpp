#include "Game.h"

Game::Game(){}
Game::~Game(){}


/// //// ///
/// MAIN ///
/// //// ///

void Game::jeu()
{
    /// INITIALISATION
    allegroInit();

    BITMAP* buffer = create_bitmap(1200, 600); ///Buffer
    BITMAP* plateau = load_bitmap("images/plateau.bmp", NULL); ///Chargement du plateau de jeu
    BITMAP* fond = load_bitmap("images/fond.bmp", NULL);
    BITMAP* des = create_bitmap(250, 250);
    FONT* broadway = load_font("broadway.pcx",NULL, NULL);
    rectfill(des,0,0,des->w,des->h,makecol(59,162,71));


    ///MENU DE DÉPART
    menu.menu(joueurs, cartes, cartes2, nb_joueurs, secret, tour, armes, lieux, personnages); ///1er menu : appuie sur jouer


    ///BOUCLE DE JEU
    while(!key[KEY_ESC] and quitter==false)
    {
        clear_bitmap(buffer);

        ///Appel tour par tour
        if(key[KEY_SPACE])
            tourParTour(tour, nb_joueurs, joueurs);

        ///Actualisation de l'affichage
        actualisation(buffer, plateau, joueurs, tour, nb_joueurs, des, fond, broadway);

        ///Si le joueur n'est pas sur une case chance
        if(joueurs[tour].getLoca() != 'C')
            joueurs[tour].setFin(false);

        ///Si le joueur vient d'arriver sur une carte chance
        if(joueurs[tour].getLoca() == 'C' and joueurs[tour].getFin() == false)
            joueurs[tour].setFin(casechance(plateau, joueurs, tour, nb_joueurs, buffer, matrice, fond, des, broadway));
        else joueurs[tour].deplacement(buffer, matrice);

        ///Zoom
        zoom(buffer);

        ///Action selon le bouton appuyé
        actionsBoutons(joueurs,secret, tour, nb_joueurs, buffer, des, cartes, armes, lieux, personnages, quitter, broadway) ;
    }


    ///Sauvegarde de la partie (tous les joueurs dans le même fichier)
    save.writeAll(joueurs, tour, secret);

    ///Sauvegarde du score
    save.saveScore(joueurs);

    ///Destruction des bitmap
    destruction(cartes, plateau, joueurs);
    destroy_bitmap(fond);

    allegro_exit();
}









/// ////////////////////// ///
/// INITIALISATION ALLEGRO ///
/// ////////////////////// ///

void Game::allegroInit()
{
    allegro_init();
    set_color_depth(desktop_color_depth());
    if((set_gfx_mode(GFX_AUTODETECT_WINDOWED,1200,600,0,0))!=0)
    {
        allegro_message("Pb de mode graphique") ;
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    install_keyboard();
    install_mouse();
    show_mouse(screen) ;

    ///Aléatoire
    srand(time(NULL)) ;
}



/// /////////////////////// ///
///  DESTRUCTION DES BITMAP ///
/// /////////////////////// ///

void Game::destruction(std::vector<Carte> &cartes, BITMAP *plateau, std::vector<Joueur>& joueurs)
{
    for(auto& carte:cartes)
        destroy_bitmap(carte.getImage());

    for(auto& joueur:joueurs)
    {
        destroy_bitmap(joueur.getImagePion());
        //destroy_bitmap(joueur.getLogoHypo());
    }

    destroy_bitmap(plateau);
}



/// ////////////////////////////////// ///
/// PERMET DE PASSER AU JOUEUR SUIVANT ///
/// ////////////////////////////////// ///

void Game::tourParTour(int& tour, int& nb_joueurs, std::vector<Joueur>& joueurs)
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

int Game::lancerDe(BITMAP *buffer, BITMAP *des, FONT* broadway)
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
        textprintf_ex(buffer, broadway, 955, 282, 1, -1, "LANCER");

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

void Game::actualisation(BITMAP* buffer, BITMAP* plateau, std::vector<Joueur>& joueurs, int& tour, int& nb_joueurs, BITMAP *des, BITMAP* fond, FONT* broadway)
{
    blit(fond, buffer, 0, 0, 600, 0, fond->w, fond->h);

    ///Affichage du plateau
    blit(plateau, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    ///Quitter le jeu
    rectfill(buffer,1040,15,1190,50,makecol(127,127,127));
    if(mouse_x>=1040 and mouse_x<=1190 and mouse_y>=15 and mouse_y<=50)
        rect(buffer, 1037, 12, 1193, 53,makecol(127,127,127));
    textprintf_ex(buffer, broadway, 1043, 14, 1, -1, "QUITTER");

    ///Bouton hypothese
    rectfill(buffer,620,75,820,125,makecol(208,82,41));
    if(mouse_x>=620 and mouse_x<=820 and mouse_y>=75 and mouse_y<=125)
        rect(buffer, 617, 72, 823, 128, makecol(208,82,41));
    textprintf_ex(buffer, broadway, 620, 82, 1, -1, "HYPOTHESE");

    ///Zone de dé
    rectfill(buffer,900,75,1150,325,makecol(59,162,71));
    blit(des, buffer, 0, 0, 900, 75, des->w, des->h) ;
    if(mouse_x>=900 and mouse_x<=1150 and mouse_y>=75 and mouse_y<=325)
        rect(buffer, 897, 72, 1153, 328, makecol(59,162,71));
    textprintf_ex(buffer, broadway, 955, 282, 1, -1, "LANCER");

    ///zone de grille d'hypo
    rectfill(buffer, 620, 175,820, 225, makecol(239,228,176));
    if(mouse_x>=620 and mouse_x<=820 and mouse_y>=175 and mouse_y<=225)
        rect(buffer, 617, 172, 823, 228, makecol(239,228,176));
    textprintf_ex(buffer, broadway, 665, 184, 1, -1, "NOTES");

    ///zone d'accusation finale
    rectfill(buffer, 620, 275,820, 325, makecol(255,255,255));
    if(mouse_x>=620 and mouse_x<=820 and mouse_y>=275 and mouse_y<=325)
        rect(buffer, 617, 272, 823, 328, makecol(255,255,255));
    textprintf_ex(buffer, broadway, 652, 284, 1, -1, "ACCUSE");



    ///Affichage des pions
    for(const auto& joueur:joueurs)
        draw_sprite(buffer, joueur.getImagePion(), joueur.getPosX()*23.25, joueur.getPosY()*23.5) ;

    ///Affichage du nom et du nombre de coups restant à jouer
    rect(buffer, 615, 340, 1150, 365, makecol(255,255,255));
    textprintf_ex(buffer, font, 630, 348, makecol(255,255,255), -1, "%s", joueurs[tour].getNom().c_str());
    textprintf_ex(buffer, font, 900, 348, makecol(255, 255, 255), -1, "Il vous reste %d deplacements", joueurs[tour].getDeplacement());

    ///Affichage des cartes du joueurs
    joueurs[tour].cardDisplay(buffer);

    ///Affichage du buffer à l'écran
    blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
}



/// ////////////////////////////////////// ///
/// CASE BONUS/MALUS SUR LE PLATEAU DE JEU ///
/// ////////////////////////////////////// ///

bool Game::casechance(BITMAP* plateau, std::vector<Joueur>& joueurs, int& tour, int nb_joueurs, BITMAP* buffer,
                      std::vector<std::vector<char>> matrice, BITMAP* fond, BITMAP* des, FONT* broadway)
{
    int chance = 3;//rand()%4;
    int revelation = rand()%(joueurs[tour].getCartes().size());
    bool fin = false;
    FONT* calisto = load_font("calisto.pcx", NULL, NULL);


    switch(chance)
    {

    ///Deplacements illimités
    case 0:

        ///Tant que le joueur n'est pas dans une salle
        while(joueurs[tour].getLoca() != '7')
        {
            actualisation(buffer, plateau, joueurs, tour, nb_joueurs, des, fond, broadway);

            textprintf_ex(screen, calisto, 610, 30, makecol(255,255,255), -1, "Moussaillon ! Fonce dans la prochaine salle !");

            joueurs[tour].deplacementChance(buffer, matrice);
        }

        fin = true;
        break;



    ///Rejouer
    case 1:
        textprintf_ex(screen, calisto, 610, 30, makecol(255,255,255), -1, "Et c'est reparti !");
        textprintf_ex(screen, calisto, 610, 50, makecol(255,255,255), -1, "Les des sont relances !");

        rest(2500);

        ///Relancement des dés
        joueurs[tour].setDeplacement(joueurs[tour].getDeplacement()+lancerDe(buffer, des, broadway));

        fin = true;
        break;



    ///Passe ton tour
    case 2:
        textprintf_ex(screen, calisto, 610, 30, makecol(255,255,255), -1, "Bon voyage !");
        textprintf_ex(screen, calisto, 610, 50, makecol(255,255,255), -1, "Passez votre tour");

        rest(2500);

        ///Changement de tour
        tourParTour(tour, nb_joueurs, joueurs);

        fin = true;
        break;


    ///Montrer une carte à tout le monde
    case 3:
        textprintf_ex(screen, calisto, 610, 30, makecol(255,255,255), -1, "Aie aie aie, la tete...");
        textprintf_ex(screen, calisto, 610, 50, makecol(255,255,255), -1, "Vous avez fait tomber votre carte !");


        ///Affichage de la carte
        rectfill(screen, 520, 180, 680, 420, makecol(255, 0, 0));
        stretch_blit(joueurs[tour].getCartes()[revelation].getImage(), screen, 0, 0, 60, 100, 540, 200, 2*60, 2*100);

        rest(2000);

        ///On coche la case de la carte revelee
        for(int i = 0; i < static_cast<int>(joueurs.size()); i++)
        {
            if(i != tour)
                joueurs[i].setHypo(joueurs[tour].getCartes()[revelation].getNom());
        }

        fin = true;
        break;
    }

    actualisation(buffer, plateau, joueurs, tour, nb_joueurs, des, fond, broadway);

    return fin;
}



/// /////////////////// ///
/// ACTIONS DES BOUTONS ///
/// /////////////////// ///

void Game::actionsBoutons(std::vector <Joueur>& joueurs, std::vector <Carte>& secret, int& tour, int& nb_joueurs, BITMAP* buffer, BITMAP *des, std::vector<Carte>& cartes, std::vector <Arme> &armes,std::vector <Lieu> &lieux,std::vector <Personnage> &personnages, bool& quitter, FONT* broadway)
{
    Hypothese hypothese ;
    int resultat ;

    ///Appuie sur un bouton hypo
    if(mouse_b &1)
    {
        ///Bouton quitter
        if(mouse_x>1040 and mouse_x<1190 and mouse_y>15 and mouse_y<50)
            quitter=true ;

        ///Bouton hypothèse
        if(mouse_x >= 620 and mouse_x <= 820 and mouse_y >= 75 and mouse_y <= 125)
        {
            if((joueurs[tour].getLoca()=='0' or joueurs[tour].getLoca()=='7') and (hypothese.trouvelieu(joueurs[tour])!="Couloir"))
                hypothese.actionhypo(joueurs,tour,nb_joueurs,buffer,cartes,armes,lieux,personnages, des);
        }

        ///Lancer de dé
        if(mouse_x >= 900 and mouse_x <= 1150 and mouse_y >= 75 and mouse_y <= 325 and joueurs[tour].getLancerDe() == false)
        {
            joueurs[tour].setDeplacement(lancerDe(buffer, des, broadway));
            joueurs[tour].setLancerDe(true); //Le joueur a lancé les dés
        }

        ///affichage de la grille d'hypothèse solo
        if(mouse_x >= 620 and mouse_x <= 820 and mouse_y >= 175 and mouse_y <= 225)
        {
            while(not(key[KEY_RIGHT]))
            {
                clear_bitmap(buffer);
                rectfill(buffer,0,0,400,600,makecol(239,228,176));

                for(int i=0; i<25; i++)
                    hline(buffer, 0, (25+ i*25), 400, makecol(0, 0, 0));

                vline(buffer, 350, 0, 600, makecol(0, 0, 0));
                joueurs[tour].hypoDisplay(buffer);
                textprintf_ex(buffer,font,800, 450, makecol(255, 255,255),-1,"appuyez sur la fleche de droite ->");
                textprintf_ex(buffer,font,850, 475, makecol(255, 255,255),-1,"pour revenir au plateau");

                blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
            }
        }

        ///L'accusation finale
        if(mouse_x >= 620 and mouse_x <= 820 and mouse_y >= 275 and mouse_y <= 325)
        {
            if((joueurs[tour].getLoca()=='0' or joueurs[tour].getLoca()=='7') and (hypothese.trouvelieu(joueurs[tour])=="Tortuga"))
            {
                resultat = hypothese.accusationfinale(buffer,joueurs,secret,armes,personnages,lieux);

                if(resultat==1)
                {
                    allegro_message("bravoooo");

                    ///Incrémentation de son nombre de points
                    joueurs[tour].setScore(joueurs[tour].getScore()+1);

                    //ecran de victoire
                }

                if(resultat==0)
                {
                    allegro_message("perduuuu");
                    joueurs.erase(joueurs.begin()+tour);

                    for(const auto& restant: joueurs)
                        allegro_message(restant.getNom().c_str());

                    nb_joueurs--;

                    if(nb_joueurs==1)
                    {
                        //ecrande victoire pour l'autre joueur
                        allegro_message("gagne pour votre adversaire");
                    }
                }
            }
        }
    }
}


/// /////////////////////////////////////////////////////////////// ///
/// PERMET DE ZOOMER SUR UNE ZONE DE L'ÉCRAN CHOISIE AVEC LA SOURIS ///
/// /////////////////////////////////////////////////////////////// ///

void Game::zoom(BITMAP * buffer)
{
    ///On ne fait quelque chose que si la touche est appuyée
    if(key[KEY_Z])
    {
        ///Création d'un buffer temporaire pour le zoom
        BITMAP* buff = create_bitmap(1200,600); ;

        while(key[KEY_Z])
        {
            ///On est met le buffer sur le buffer (du sspg)
            blit(buffer, buff, 0, 0, 0, 0, buffer->w, buffer->h);

            ///On ne fait rien si la souris n'est pas dans ces valeurs (tout l'écran peut être zoomer dans ces valeurs)
            if(mouse_y>200 && mouse_x>200 && mouse_x<1000 )
                masked_stretch_blit(buff,screen,mouse_x-200,mouse_y-200,400,200,75,100,1000,500);
        }

        destroy_bitmap(buff);
    }
}
