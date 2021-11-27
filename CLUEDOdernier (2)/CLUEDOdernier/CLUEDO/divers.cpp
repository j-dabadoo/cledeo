#include "header.h"

/// ////////////////////////////////// ///
/// PERMET DE PASSER AU JOUEUR SUIVANT ///
/// ////////////////////////////////// ///

void tourParTour(int& tour, int& nb_joueurs, std::vector<Joueur>& joueurs)
{

    while(key[KEY_SPACE]) //Permet de ne rien faire tant que la touche est appuy�e (ne va donc pas sauter plusieurs tour
    {}

    joueurs[tour].setDeplacement(0); //Si le joueur n'a pas effectu� tous ses d�placements on lui met � 0

    tour++ ; ///Incrementation du compteur tour pour passer au joueur suivant

    ///Revient au premier joueur
    if (tour==nb_joueurs)
        tour=0 ;
}



/// /////////////////// ///
/// LANCEMENT DES 2 D�S ///
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

    ///On efface le buffer de d�, on remet le fond vert de la case, puis on remet � l'�cran
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

    ///G�n�ration al�atoire pour les 2 d�s
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

void actualisation(BITMAP* buffer, BITMAP* plateau, std::vector<Joueur>& joueurs, int& tour, int& nb_joueurs, BITMAP *des, BITMAP* fond)
{
    blit(fond, buffer, 0, 0, 0, 0, 1200, 600);

    ///Affichage du plateau
    blit(plateau, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    ///Quitter le jeu
    rectfill(buffer,1110,15,1190,50,makecol(127,127,127));
    if(mouse_x>=1110 and mouse_x<=1190 and mouse_y>=15 and mouse_y<=50)
        rect(buffer, 1107, 12, 1193, 53,makecol(127,127,127));
    else
        rect(buffer, 1107, 12, 1193, 53, makecol(0,0,0));

    ///Bouton hypothese
    rectfill(buffer,620,75,820,125,makecol(208,82,41));
    if(mouse_x>=620 and mouse_x<=820 and mouse_y>=75 and mouse_y<=125)
        rect(buffer, 617, 72, 823, 128, makecol(208,82,41));
    else
        rect(buffer, 617, 72, 823, 128, makecol(0,0,0));

    ///Zone de d�
    rectfill(buffer,900,75,1150,325,makecol(59,162,71));
    if(mouse_x>=900 and mouse_x<=1150 and mouse_y>=75 and mouse_y<=325)
        rect(buffer, 897, 72, 1153, 328, makecol(59,162,71));
    else
        rect(buffer, 897, 72, 1153, 328, makecol(0,0,0));

    ///zone de grille d'hypo
    rectfill(buffer, 620, 175,820, 225, makecol(239,228,176));
    if(mouse_x>=620 and mouse_x<=820 and mouse_y>=175 and mouse_y<=225)
        rect(buffer, 617, 172, 823, 228, makecol(239,228,176));
    else
        rect(buffer, 617, 172, 823, 228, makecol(0,0,0));

    ///zone d'accusation finale
    rectfill(buffer, 620, 275,820, 325, makecol(255,255,255));
    if(mouse_x>=620 and mouse_x<=820 and mouse_y>=275 and mouse_y<=325)
        rect(buffer, 617, 272, 823, 328, makecol(255,255,255));
    else
        rect(buffer, 617, 272, 823, 328, makecol(0,0,0));



    blit(des, buffer, 0, 0, 900, 75, des->w, des->h) ;

    //blit(plateau, buffer, 0,0,0,0, SCREEN_W, SCREEN_H);
    //al_draw_text(font,makecol(255,255,255), 700,50, 0, "%s", joueurs[tour].getNom());


    ///Affichage des pions
    for(const auto& joueur:joueurs)
        draw_sprite(buffer, joueur.getImagePion(), joueur.getPosX()*23.25, joueur.getPosY()*23.5) ;

    ///Affichage du nom et du nombre de coups restant � jouer
    rect(buffer, 615, 340, 1150, 365, makecol(255,255,255));
    textprintf_ex(buffer, font, 630, 348, makecol(255,255,255), -1, "%s", joueurs[tour].getNom().c_str());
    textprintf_ex(buffer, font, 900, 348, makecol(255, 255, 255), -1, "Il vous reste %d deplacements", joueurs[tour].getDeplacement());

    ///Affichage des cartes du joueurs
    joueurs[tour].cardDisplay(buffer);

    ///Affichage du buffer � l'�cran
    blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
}


/// ////////////////////////////////////// ///
/// CASE BONUS/MALUS SUR LE PLATEAU DE JEU ///
/// ////////////////////////////////////// ///

bool casechance(BITMAP* plateau, std::vector<Joueur>& joueurs, int& tour, int nb_joueurs, BITMAP* buffer, std::vector<std::vector<char>> matrice, BITMAP* fond)
{
    int chance = rand()%4;
    int revelation = rand()%(joueurs[tour].getCartes().size());
    int posX = joueurs[tour].getPosX();
    int posY = joueurs[tour].getPosY();
    bool fin = false;
    BITMAP* des = create_bitmap(250, 250);

    switch(chance)
    {
    ///Deplacements illimit�s
    case 0:
        textprintf_ex(buffer, font, 730, 150, makecol(255,255,255), -1, "En route, moussaillons !");
        textprintf_ex(buffer, font, 600, 160, makecol(255,255,255), -1, "Vous pouvez aller a la prochaine salle souhaitee, vous ne pourrez pas passer par une autre case chance");

        ///Tant que le joueur n'est pas dans une salle
        while(joueurs[tour].getLoca() != '7')
        {
            actualisation(buffer, plateau, joueurs, tour, nb_joueurs, des, fond);
            joueurs[tour].deplacementChance(buffer, matrice);
        }

        ///Changement de tour
        tourParTour(tour, nb_joueurs, joueurs);

        fin = true;
        break;

    ///Rejouer
    case 1:
        textprintf_ex(buffer, font, 700, 150, makecol(255,255,255), -1, "Et c'est reparti !");
        textprintf_ex(buffer, font, 700, 160, makecol(255,255,255), -1, "Les d�s sont relanc�s pour encore plus de filouterie");

        ///Relancement des d�s
        joueurs[tour].setDeplacement(joueurs[tour].getDeplacement()+lancerDe(buffer, des));

        fin = true;
        break;

    ///Passe ton tour
    case 2:
        textprintf_ex(buffer, font, 700, 150, makecol(255,255,255), -1, "Bon voyage !");
        textprintf_ex(buffer, font, 700, 160, makecol(255,255,255), -1, "Passez votre tour");

        ///Changement de tour
        tourParTour(tour, nb_joueurs, joueurs);

        fin = true;
        break;

    ///Montrer une carte � tout le monde
    case 3:
        textprintf_ex(buffer, font, 700, 150, makecol(255,255,255), -1, "Aie aie aie, la tete...");
        textprintf_ex(buffer, font, 700, 160, makecol(255,255,255), -1, "Dans l'euphorie de la soiree d'hier, vous avez montrez cette carte a tout le monde :(");
        ///On change les coordonn�es de la carte pour l'afficher
        joueurs[tour].getCartes()[revelation].setPosX(1000);
        joueurs[tour].getCartes()[revelation].setPosY(400);
        ///On affiche la carte
        joueurs[tour].getCartes()[revelation].display(buffer);
        ///On redonne les coordonn�es initiales � la carte
        joueurs[tour].getCartes()[revelation].setPosX(posX);
        joueurs[tour].getCartes()[revelation].setPosY(posY);

        ///On coche la case de la carte revelee
        for(int i = 0; i < (int)(joueurs.size()); i++)
        {
            if(i != tour)
                joueurs[i].setHypo(joueurs[i].getCartes()[revelation].getNom());
        }

        fin = true;
        break;
    }
    actualisation(buffer, plateau, joueurs, tour, nb_joueurs, des, fond);
    rest(1000);

    destroy_bitmap(des);

    return fin;
}



/// /////////////////// ///
/// ACTIONS DES BOUTONS ///
/// /////////////////// ///

void actionsBoutons(std::vector <Joueur>& joueurs, std::vector <Carte>& secret, int& tour, int& nb_joueurs, BITMAP* buffer, BITMAP *des, std::vector<Carte>& cartes, std::vector <Arme> &armes,std::vector <Lieu> &lieux,std::vector <Personnage> &personnages)
{
    Hypothese hypothese ;

    ///Appuie sur un bouton hypo
    if(mouse_b &1)
    {
        ///Bouton hypoth�se
        if(mouse_x >= 620 and mouse_x <= 820 and mouse_y >= 75 and mouse_y <= 125)
        {
            if((joueurs[tour].getLoca()=='0' or joueurs[tour].getLoca()=='7') and (hypothese.trouvelieu(joueurs[tour])!="Couloir"))
                hypothese.actionhypo(joueurs,tour,nb_joueurs,buffer,cartes,armes,lieux,personnages, des);
        }

        ///Lancer de d�
        if(mouse_x >= 900 and mouse_x <= 1150 and mouse_y >= 75 and mouse_y <= 325)
            joueurs[tour].setDeplacement(lancerDe(buffer, des));

        ///affichage de la grille d'hypoth�se solo
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
                accusationfinale(buffer, joueurs, secret, armes,personnages,lieux);
        }
    }
}



/// //////////////////////////// ///
/// �CRITURE DE TOUS LES JOUEURS ///
/// //////////////////////////// ///

void writeAll(std::vector <Joueur>& joueurs, int& tour, std::vector <Carte> &secret)
{
    std::ofstream ofs("saveGame.txt", std::ios::out);

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

            ///Sauvegarde nb d�placements restants
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



            ///Sauvegarder de la map d'hypoth�ses

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

        ///Sauvegarde de la pochette secr�te
        for(auto& scret:secret)
        {
            ///Sauvegarde d'une carte

            //Sauvegarde id de la carte
            ofs << scret.getId() << std::endl ;

            //Sauvegarde position X
            ofs << scret.getPosX() << std::endl ;

            //Sauvegarde position Y
            ofs << scret.getPosY() << std::endl ;

            //Sauvegarde nom
            ofs << scret.getNom() << " ;" << std::endl ;

            //Sauvegarde type
            ofs << scret.getType() << std::endl ;
        }

        ofs.close(); // fermeture du flux
    }
}



void readNBJ(int& nb_joueurs)
{
    std::ifstream ifs("saveGame.txt");

    if (ifs) // test si le fichier est bien ouvert
    {
        ifs >> nb_joueurs ;
        ifs.close();
    }
}


/// /////////////////////////////////////////////////// ///
/// LECTURE D'UN FICHIER TEXTE EN FONCTION DU NOM SAISI ///
/// /////////////////////////////////////////////////// ///

void readAll(std::vector <Joueur>& joueurs, int& nb_joueurs, int& tour, std::vector <Carte> &secret)
{
    std::ifstream ifs("saveGame.txt");

    if (ifs) // test si le fichier est bien ouvert
    {
        int id, posX, posY ;
        std::string type ;
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

            ///Lecture nb d�placements
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

        ///Lecture de la pochette secr�te
        for(int i=0 ; i<3 ; i++)
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
            nom.erase(0,1);

            //Lecture type
            ifs >> type ;

            ///Ajout d'une carte dans le vecteur
            Carte newSecret(id, nom, NULL, type, posX, posY);
            ajoutVec(secret, newSecret);
        }

        ///Fermeture du fichier
        ifs.close();
    }

    else
        std::cout << "Le joueur n'existe pas " << std::endl ;
}




/// ///////////////////////////////////////// ///
/// AJOUT D'UNE CARTE DANS LE JEU D'UN JOUEUR ///
/// ///////////////////////////////////////// ///

template <typename T>
void ajoutVec(std::vector <T>& cartes, T newCarte)
{
    cartes.push_back(newCarte);
}


/// ///////////////////////////////////////////// ///
/// R�CUP�RATION DES BITMAP D'UNE ANCIENNE PARTIE ///
/// ///////////////////////////////////////////// ///
/*template <typename A>
void recupBitmap(std::vector <A>& cartes)
{
    std::string nom ;

    for(int i=0 ; i < static_cast <int> (cartes.size()) ; i++)
    {
        for(auto& cartePaquet:cartes)
        {
            nom=" ";
            nom+=cartePaquet.getNom();

            ///Si on trouve la carte dans le paquet, on la r�cup�re (pour surtout r�cup�rer sa bitmap)
            if(m_cartes[i].getNom()==nom)
                m_cartes[i].setImage(cartePaquet.getImage());
        }
    }
}*/





/// //////////////////////////////// ///
/// AFFICHAGE DES SCORES DES JOUEURS ///
/// //////////////////////////////// ///

void scoreDisplay()
{
    std::map <std::string, int> scores ;
    std::string nom ;
    int score ;

    clear_bitmap(screen);

    while(mouse_b&1)
    {}

    ///Lecture du fichier de score dans la map (permet de tout trier en fonction du score)
    std::ifstream inFile("saveScore.txt");

    while(inFile)
    {
        inFile >> nom ;
        inFile >> score ;

        scores[nom] = score ;
    }
    inFile.close();


    ///R��criture de la map dans le fichier A SUPPRIMER
    std::ofstream outFile("saveScore.txt", std::ios::out);

    for(const auto& item:scores)
        outFile << item.first << " " << item.second << std::endl ;

    outFile.close();



    int y = 0 ;

    ///Affichage des scores enregistr�s
    for(const auto& item:scores)
    {
        textprintf_ex(screen, font, 200, 50+y, makecol(255,255,255), -1, "%s : %d", item.first.c_str(), item.second);
        y+=20 ;
    }

    ///On reste dessus tant qu'on n'a pas cliqu�
    while(!mouse_b&1)
    {}
}


/// ///////////////////////////// ///
/// ECRITURE DU SCORE DES JOUEURS ///
/// ///////////////////////////// ///

void saveScore(std::vector <Joueur>& joueurs)
{
    ;
    std::map <std::string, int> scores ;
    std::string nom ;
    int score ;

    clear_bitmap(screen);

    while(mouse_b&1)
    {}

    ///Lecture du fichier de score dans la map (permet de tout trier en fonction du score)
    std::ifstream inFile("saveScore.txt");

    while(inFile)
    {
        inFile >> nom ;
        inFile >> score ;

        scores[nom] = score ;
    }
    inFile.close();



    for(auto& item:scores)
    {
        for(auto& joueur:joueurs)
            scores[joueur.getNom()] = joueur.getScore() ;
    }


    ///R��criture de la map dans le fichier A SUPPRIMER
    std::ofstream outFile("saveScore.txt", std::ios::out);

    for(const auto& item:scores)
        outFile << item.first << " " << item.second << std::endl ;

    outFile.close();
}


/// ////////////////////////////////// ///
/// ENREGISTREMENT D'UN NOUVEAU COMPTE ///
/// ////////////////////////////////// ///

void saveNewCompte(std::string& nom, std::string& mdp)
{
    ///Le joueur existe d�j� : non valide
    if(alreadyExist(nom) == false)
    {
        std::ofstream ofs("saveCompte.txt", std::ios::app);
        if(ofs)
        {
            ofs << std::endl << nom << " " << mdp ;

            ofs.close();
        }
    }
}


/// ////////////////////////////////////////////////// ///
/// V�RIFICATION SI LE JOUEUR PEUT SE CONNECTER OU NON ///
/// ////////////////////////////////////////////////// ///

bool connexionValide(std::string& nom, std::string& mdp)
{
    std::ifstream ifs("saveCompte.txt", std::ios::in);
    bool exist = false ;

    if(ifs)
    {
        std::string word ;

        while(ifs)
        {
            ///On lit des mots jusqu'� trouver le nom du joueur
            ifs >> word ;

            if(word==nom)
            {
                ///Si on a lu le nom du joueur, on lit le mot d'apr�s pour savoir si c'est le bon mdp
                ifs >> word ;

                ///Si oui alors on valide l'existence du joueur
                if(word==mdp)
                {
                    exist = true ;
                    break ; ///Permet de quitter la boucle while une fois nom et mdp valid�s
                }
            }
        }
    }

    return exist ;
}


/// ///////////////////////////////////////////// ///
/// V�RIFICATION SI LE JOUEUR EST D�J� ENREGISTR� ///
/// ///////////////////////////////////////////// ///

bool alreadyExist(std::string& nom)
{
    std::ifstream ifs("saveCompte.txt", std::ios::in);
    bool exist = false ;

    if(ifs)
    {
        std::string login ;

        while(ifs)
        {
            ifs >> login ;

            if(login==nom)
                exist = true ;
        }
    }

    return exist ;
}



/// ///////////////// ///
/// ACCUSATION FINALE ///
/// ///////////////// ///

void accusationfinale(BITMAP* buffer, std::vector<Joueur> joueurs, std::vector <Carte> &secret, std::vector<Arme> armes, std::vector<Personnage> persos, std::vector<Lieu> lieux)
{
    std::string what;
    std::string where;
    std::string who;

    bool goodarme=false;
    bool goodlieu=false;
    bool goodperso=false;

    int valiarme=0;
    int valiperso=0;
    int valilieu=0;
    std::cout << "test 1" << std::endl ;
    disaccusationfinale(buffer,joueurs,secret,armes,persos, lieux);
    std::cout << "test 2" << std::endl ;
    std::cout<<secret[0].getNom()<<std::endl;
    std::cout<<secret[1].getNom()<<std::endl;
    std::cout<<secret[2].getNom()<<std::endl;
    std::cout << "test 3" << std::endl ;
    while(not(key[KEY_LEFT]) and not(valiarme==1 and valilieu==1 and valiperso==1))
    {

        ///saisie du personnage
        if((mouse_b & 1)and(mouse_x>=50 and mouse_x<=110 and mouse_y>=85 and mouse_y<=185))
        {
            who="Will Turner";
            valiperso=1;
        }
        if((mouse_b & 1)and(mouse_x>=138 and mouse_x<=198 and mouse_y>=85 and mouse_y<=185))
        {
            who="Bill Turner";
            valiperso=1;
        }
        if((mouse_b & 1)and(mouse_x>=226 and mouse_x<=286 and mouse_y>=85 and mouse_y<=185))
        {
            who="Jack Sparrow";
            valiperso=1;
        }
        if((mouse_b & 1)and(mouse_x>=314 and mouse_x<=374 and mouse_y>=85 and mouse_y<=185))
        {
            who="Barbossa";
            valiperso=1;
        }
        if((mouse_b & 1)and(mouse_x>=402 and mouse_x<=462 and mouse_y>=85 and mouse_y<=185))
        {
            who="Elizabeth Swann";
            valiperso=1;
        }
        if((mouse_b & 1)and(mouse_x>=490 and mouse_x<=550 and mouse_y>=85 and mouse_y<=185))
        {
            who="Davy Jones";
            valiperso=1;
        }
        if((mouse_b & 1)and (mouse_x>=578 and mouse_x<=638 and mouse_y>=85 and mouse_y<=185))
        {
            who="Calypso";
            valiperso=1;
        }
        if((mouse_b & 1)and( mouse_x>=666 and mouse_x<=726 and mouse_y>=85 and mouse_y<=185))
        {
            who="James Norrington";
            valiperso=1;
        }
        if((mouse_b & 1)and(mouse_x>=754 and mouse_x<=814 and mouse_y>=85 and mouse_y<=185))
        {
            who="Barbe Noire";
            valiperso=1;
        }

        ///Saisie de l'arme
        if(mouse_b&1 and(mouse_x>=50 and mouse_x<=110 and mouse_y>=285 and mouse_y<=385))
        {
            what="Sabre";
            valiarme=1;
        }
        if((mouse_b & 1)and(mouse_x>=138 and mouse_x<=198 and mouse_y>=285 and mouse_y<=385))
        {
            what="Pistolet";
            valiarme=1;
        }
        if((mouse_b & 1)and(mouse_x>=226 and mouse_x<=286 and mouse_y>=285 and mouse_y<=385))
        {
            what="Poudre a canon";
            valiarme=1;
        }
        if((mouse_b & 1)and(mouse_x>=314 and mouse_x<=374 and mouse_y>=285 and mouse_y<=385))
        {
            what="Cle";
            valiarme=1;
        }
        if((mouse_b & 1)and(mouse_x>=402 and mouse_x<=462 and mouse_y>=285 and mouse_y<=385))
        {
            what="Tire bouchon";
            valiarme=1;
        }
        if((mouse_b & 1)and(mouse_x>=490 and mouse_x<=550 and mouse_y>=285 and mouse_y<=385))
        {
            what="Canon";
            valiarme=1;
        }

        ///Saisie du lieu
        if((mouse_b & 1)and(mouse_x>=50 and mouse_x<=110 and mouse_y>=485 and mouse_y<=585))
        {
            where="Baie des Naufrages";
            valilieu=1;
        }
        if((mouse_b & 1)and(mouse_x>=138 and mouse_x<=198 and mouse_y>=485 and mouse_y<=585))
        {
            where="Port Royal";
            valilieu=1;
        }
        if((mouse_b & 1)and(mouse_x>=226 and mouse_x<=286 and mouse_y>=485 and mouse_y<=585))
        {
            where="Ile de la Muerta";
            valilieu=1;
        }
        if((mouse_b & 1)and(mouse_x>=314 and mouse_x<=374 and mouse_y>=485 and mouse_y<=585))
        {
            where="Ile au rhum";
            valilieu=1;
        }
        if((mouse_b & 1)and(mouse_x>=402 and mouse_x<=462 and mouse_y>=485 and mouse_y<=585))
        {
            where="Hollandais Volant";
            valilieu=1;
        }
        if((mouse_b & 1)and(mouse_x>=490 and mouse_x<=550 and mouse_y>=485 and mouse_y<=585))
        {
            where="Ile des 4 vents";
            valilieu=1;
        }
        if((mouse_b & 1)and (mouse_x>=578 and mouse_x<=638 and mouse_y>=485 and mouse_y<=585))
        {
            where="HMS Intrepide";
            valilieu=1;
        }
        if((mouse_b & 1)and( mouse_x>=666 and mouse_x<=726 and mouse_y>=485 and mouse_y<=585))
        {
            where="Triangle des Bermudes";
            valilieu=1;
        }
        if((mouse_b & 1)and(mouse_x>=754 and mouse_x<=814 and mouse_y>=485 and mouse_y<=585))
        {
            where="Balck Pearl";
            valilieu=1;
        }

        std::cout << "test avant verif" << std::endl ;

        textprintf_ex(buffer, font,910, 319, makecol(0, 0, 0), -1, who.c_str());
        textprintf_ex(buffer, font,910, 344, makecol(0, 0, 0), -1, what.c_str());
        textprintf_ex(buffer, font,910, 369, makecol(0, 0, 0), -1, where.c_str());

        blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);

        if(valiarme==1 and valilieu==1 and valiperso==1)
        {
            ///verification avec la pochette secrete
            for(const auto& verif: secret)
            {
                if(verif.getNom()==who)
                    goodperso=true;

                if(verif.getNom()==where)
                    goodlieu=true;

                if(verif.getNom()==what)
                    goodarme=true;
            }
        }
    }

    std::cout << "test apres verif" << std::endl ;
    if(goodarme==true and goodlieu==true and goodperso==true)
        allegro_message("bravo vous avez gagnE");

    else
        allegro_message("vous avez perdu");
}



void disaccusationfinale(BITMAP* buffer, std::vector<Joueur> joueurs, std::vector <Carte> &secret, std::vector<Arme> armes, std::vector<Personnage> persos, std::vector<Lieu> lieux)
{
    clear_bitmap(buffer);

    int i=0;

    rectfill(buffer,750,285,1050,385,makecol(239,228,176));

    for(int i=0; i<3; i++)
        hline(buffer, 750, 310+25*i, 1050, makecol(0, 0, 0));

    vline(buffer, 900, 310, 385, makecol(0, 0, 0));
    textprintf_ex(buffer, font, 800, 294, makecol(0, 0, 0), -1, "VOTRE ACCUSATION FINALE");
    textprintf_ex(buffer, font, 775, 319, makecol(0, 0, 0), -1, "PERSONNAGE");
    textprintf_ex(buffer, font,800, 344, makecol(0, 0, 0), -1, "ARME");
    textprintf_ex(buffer, font, 800, 369, makecol(0, 0, 0), -1, "LIEU");

    ///affichage des cartes personnages
    for(const auto& elem: persos)
    {
        draw_sprite(buffer, elem.getImage(), 50+i, 85) ;
        i=i+88;
    }
    i=0;
    ///affichage des cartes armes
    for(const auto& elem: armes)
    {
        draw_sprite(buffer, elem.getImage(), 50+i, 285) ;
        i=i+88;
    }
    i=0;
    ///affichage des cartes personnages
    for(const auto& elem: lieux)
    {
        draw_sprite(buffer, elem.getImage(), 50+i, 485) ;
        i=i+88;
    }
    blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
}


/// /////////////////////////////////////////////////////////////// ///
/// PERMET DE ZOOMER SUR UNE ZONE DE L'�CRAN CHOISIE AVEC LA SOURIS ///
/// /////////////////////////////////////////////////////////////// ///

void zoom(BITMAP * buffer)
{
    ///On ne fait quelque chose que si la touche est appuy�e
    if(key[KEY_Z])
    {
        ///Cr�ation d'un buffer temporaire pour le zoom
        BITMAP* buff = create_bitmap(1200,600); ;

        while(key[KEY_Z])
        {
            ///On est met le buffer sur le buffer (du sspg)
            blit(buffer, buff, 0, 0, 0, 0, buffer->w, buffer->h);

            ///On ne fait rien si la souris n'est pas dans ces valeurs (tout l'�cran peut �tre zoomer dans ces valeurs)
            if(mouse_y>200 && mouse_x>200 && mouse_x<1000 )
                masked_stretch_blit(buff,screen,mouse_x-200,mouse_y-200,400,200,75,100,1000,500);
        }

        destroy_bitmap(buff);
    }
}
