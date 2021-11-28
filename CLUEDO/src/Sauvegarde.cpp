#include "Sauvegarde.h"

Sauvegarde::Sauvegarde()
{
    //ctor
}

Sauvegarde::~Sauvegarde()
{
    //dtor
}

/// //////////////////////////// ///
/// ÉCRITURE DE TOUS LES JOUEURS ///
/// //////////////////////////// ///

void Sauvegarde::writeAll(std::vector <Joueur>& joueurs, int& tour, std::vector <Carte> &secret)
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

        ///Sauvegarde de la pochette secrète
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



void Sauvegarde::readNBJ(int& nb_joueurs)
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

void Sauvegarde::readAll(std::vector <Joueur>& joueurs, int& nb_joueurs, int& tour, std::vector <Carte> &secret)
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

        ///Lecture de la pochette secrète
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
}




/// ///////////////////////////////////////// ///
/// AJOUT D'UNE CARTE DANS LE JEU D'UN JOUEUR ///
/// ///////////////////////////////////////// ///

template <typename T>
void Sauvegarde::ajoutVec(std::vector <T>& cartes, T newCarte)
{
    cartes.push_back(newCarte);
}


/// ///////////////////////////////////////////// ///
/// RÉCUPÉRATION DES BITMAP D'UNE ANCIENNE PARTIE ///
/// ///////////////////////////////////////////// ///
template <typename A>
void Sauvegarde::recupBitmap(std::vector <A>& cartes, std::vector <Carte>& paquet)
{
    std::string nom ;

    for(int i=0 ; i < static_cast <int> (cartes.size()) ; i++)
    {
        for(auto& cartePaquet:paquet)
        {
            ///Si on trouve la carte dans le paquet, on la récupère (pour surtout récupérer sa bitmap)
            if(cartes[i].getNom()==nom)
                cartes[i].setImage(cartePaquet.getImage());
        }
    }
}





/// //////////////////////////////// ///
/// AFFICHAGE DES SCORES DES JOUEURS ///
/// //////////////////////////////// ///

void Sauvegarde::scoreDisplay(FONT* broadway)
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


    ///Réécriture de la map dans le fichier A SUPPRIMER
    std::ofstream outFile("saveScore.txt", std::ios::out);

    for(const auto& item:scores)
        outFile << item.first << " " << item.second << std::endl ;

    outFile.close();



    int y = 0 ;

    ///Affichage des scores enregistrés
    for(const auto& item:scores)
    {
        textprintf_ex(screen, broadway, 200, 50+y, makecol(255,255,255), -1, "%s : %d", item.first.c_str(), item.second);
        y+=40 ;
    }

    ///On reste dessus tant qu'on n'a pas cliqué
    while(!mouse_b&1)
    {}
}


/// ///////////////////////////// ///
/// ECRITURE DU SCORE DES JOUEURS ///
/// ///////////////////////////// ///

void Sauvegarde::saveScore(std::vector <Joueur>& joueurs)
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


    for(auto& joueur:joueurs)
        scores[joueur.getNom()] = joueur.getScore() ;


    ///Réécriture de la map dans le fichier A SUPPRIMER
    std::ofstream outFile("saveScore.txt", std::ios::out);

    for(const auto& item:scores)
        outFile << item.first << " " << item.second << std::endl ;

    outFile.close();
}


/// ////////////////////////////////// ///
/// ENREGISTREMENT D'UN NOUVEAU COMPTE ///
/// ////////////////////////////////// ///

void Sauvegarde::saveNewCompte(std::string& nom, std::string& mdp)
{
    ///Le joueur existe déjà : non valide
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
/// VÉRIFICATION SI LE JOUEUR PEUT SE CONNECTER OU NON ///
/// ////////////////////////////////////////////////// ///

bool Sauvegarde::connexionValide(std::string& nom, std::string& mdp)
{
    std::ifstream ifs("saveCompte.txt", std::ios::in);
    bool exist = false ;

    if(ifs)
    {
        std::string word ;

        while(ifs)
        {
            ///On lit des mots jusqu'à trouver le nom du joueur
            ifs >> word ;

            if(word==nom)
            {
                ///Si on a lu le nom du joueur, on lit le mot d'après pour savoir si c'est le bon mdp
                ifs >> word ;

                ///Si oui alors on valide l'existence du joueur
                if(word==mdp)
                {
                    exist = true ;
                    break ; ///Permet de quitter la boucle while une fois nom et mdp validés
                }
            }
        }
    }

    return exist ;
}


/// ///////////////////////////////////////////// ///
/// VÉRIFICATION SI LE JOUEUR EST DÉJÀ ENREGISTRÉ ///
/// ///////////////////////////////////////////// ///

bool Sauvegarde::alreadyExist(std::string& nom)
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
            else
                ifs >> login ; //permet de ne pas lire le mdp
        }
    }

    return exist ;
}
