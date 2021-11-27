#include "header.h"


/// ////////////////////// ///
/// INITIALISATION ALLEGRO ///
/// ////////////////////// ///

void allegroInit()
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


/// /////////////////////////////////////////////////////// ///
/// INITIALISATION DES CARTES (CHARGEMENT BITMAP + MÉLANGE) ///
/// /////////////////////////////////////////////////////// ///

void cardInit(std::vector <Joueur> &joueurs, std::vector <Carte> &cartes, std::vector <Carte> &cartes2, int &nb_joueurs, std::vector <Arme> &armes,std::vector <Lieu> &lieux,std::vector <Personnage> &personnages)
{
    int ok=0, id ;

    ///Initialisation
    for(int i=0 ; i<nb_joueurs ; i++)
        joueurs.push_back(Joueur()) ;


    ///Initialisation des cartes - armes
    armes.push_back(Arme("Sabre",              load_bitmap("images/sabre.bmp",NULL), "arme"));
    armes.push_back(Arme("Pistolet",           load_bitmap("images/pistolet.bmp",NULL), "arme"));
    armes.push_back(Arme("Poudre a canon",     load_bitmap("images/poudre.bmp",NULL), "arme"));
    armes.push_back(Arme("Cle",                load_bitmap("images/cle.bmp",NULL), "arme"));
    armes.push_back(Arme("Tire bouchon",       load_bitmap("images/tirebouchon.bmp",NULL), "arme"));
    armes.push_back(Arme("Canon",              load_bitmap("images/canon.bmp",NULL), "arme"));

    personnages.push_back(Personnage("Will Turner",           load_bitmap("images/willturner.bmp",NULL), "perso"));
    personnages.push_back(Personnage("Bill Turner",           load_bitmap("images/billturner.bmp",NULL), "perso"));
    personnages.push_back(Personnage("Jack Sparrow",          load_bitmap("images/jacksparrow.bmp",NULL), "perso"));
    personnages.push_back(Personnage("Barbossa",              load_bitmap("images/barbossa.bmp",NULL), "perso"));
    personnages.push_back(Personnage("Elizabeth Swann",       load_bitmap("images/swann.bmp",NULL), "perso"));
    personnages.push_back(Personnage("Davy Jones",            load_bitmap("images/davyjones.bmp",NULL), "perso"));
    personnages.push_back(Personnage("Calypso",               load_bitmap("images/calypso.bmp",NULL), "perso"));
    personnages.push_back(Personnage("James Norrington",      load_bitmap("images/jamesnorrington.bmp",NULL), "perso"));
    personnages.push_back(Personnage("Barbe Noire",           load_bitmap("images/barbenoire.bmp",NULL), "perso"));

    lieux.push_back(Lieu("Baie des Naufrages",    load_bitmap("images/tortuga.bmp",NULL), "lieu"));
    lieux.push_back(Lieu("Port Royal",            load_bitmap("images/portroyale.bmp",NULL), "lieu"));
    lieux.push_back(Lieu("Ile de la Muerta",      load_bitmap("images/muerta.bmp",NULL), "lieu"));
    lieux.push_back(Lieu("Ile au rhum",           load_bitmap("images/rhum.bmp",NULL), "lieu"));
    lieux.push_back(Lieu("Hollandais Volant",     load_bitmap("images/hollandais.bmp",NULL), "lieu"));
    lieux.push_back(Lieu("Ile des 4 vents",       load_bitmap("images/quatresvents.bmp",NULL), "lieu"));
    lieux.push_back(Lieu("HMS Intrepide",         load_bitmap("images/intrepide.bmp",NULL), "lieu"));
    lieux.push_back(Lieu("Triangle des Bermudes", load_bitmap("images/bermudes.bmp",NULL), "lieu"));
    lieux.push_back(Lieu("Black Pearl",           load_bitmap("images/blackpearl.bmp",NULL), "lieu"));


    int j=0;

    for(int i=0; i<6; i++)
        cartes.push_back(Carte(i,armes[i].getNom(), armes[i].getImage(),armes[i].getType(), 0, 0));

    for(int i=6; i<15; i++)
    {
        cartes.push_back(Carte(i,personnages[j].getNom(), personnages[j].getImage(),personnages[j].getType(), 0, 0));
        j++;
    }

    j=0;
    for(int i=15; i<24; i++)
    {
        cartes.push_back(Carte(i,lieux[j].getNom(), lieux[j].getImage(),lieux[j].getType(), 0, 0));
        j++;
    }

    ///Mélanges des cartes
    for(int i=0 ; i<NB_CARTE  ; i++)
    {
        ok =0;
        ///On refait tant que le nombre aléatoire a déjà été piochée (pas francais mais tqt)
        do
        {
            id = rand()%(24);
            ok=0 ;

            ///Vérification si carte déjà piochée
            for(auto& item:cartes)
            {

                ///Si on trouve la carte par son id
                if(item.getId()==id)
                {
                    cartes2.push_back(item); //On ajoute la carte
                    item.setId(100) ; //Valeur non valide pour ne pas le reprendre
                    ok=1 ;
                }
            }
        }
        while(ok==0);
    }
}


/// //////////////////////////////////////////////////////////// ///
/// DISTRIBUTION DES CARTES À LA POCHETTE SECRÈTE ET AUX JOUEURS ///
/// //////////////////////////////////////////////////////////// ///

void distribCarte(std::vector <Carte> &cartes2,std::vector <Carte> &secret,std::vector <Joueur> &joueurs, int &nb_joueurs)
{
    int tour=0 ;
    bool persoSecret=false, armeSecrete=false, lieuSecret=false ; ///Une fois pochette secrète remplie on met true

    for(auto& joueur : joueurs)
        joueur.hypotheseInit();

    ///Attribution des cartes (secret + joueurs)
    for(int i=0 ; i<NB_CARTE ; i++)
    {
        for(auto& item:cartes2)
        {
            ///On remplie la pochette secrète avec la première carte de type perso
            if(persoSecret==false and item.getType()=="perso")
            {
                persoSecret=true ;
                secret.push_back(item);
                item.setType("off");
            }
            ///On remplie la pochette secrète avec la première carte de type arme
            else if(armeSecrete==false and item.getType()=="arme")
            {
                armeSecrete=true ;
                secret.push_back(item);
                item.setType("off");
            }
            ///On remplie la pochette secrète avec la première carte de type lieu
            else if(lieuSecret==false and item.getType()=="lieu")
            {
                lieuSecret=true ;
                secret.push_back(item);
                item.setType("off");
            }

            ///Remplissage du reste des cartes pour les joueurs
            else if(item.getType()!="off")
            {
                joueurs[tour].add(item);
                joueurs[tour].setHypo(item.getNom());
                joueurs[tour].setFin(false);
                item.setType("off");

                tour++;
                if(tour==nb_joueurs)
                    tour=0 ;
            }
        }
    }
}



/// /////////////////////// ///
///  DESTRUCTION DES BITMAP ///
/// /////////////////////// ///

void destruction(std::vector<Carte> &cartes, BITMAP *plateau, std::vector<Joueur>& joueurs)
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


/// /////////////////////////////////////// ///
/// INITIALISATION DE LA MATRICE DU PLATEAU ///
/// /////////////////////////////////////// ///

std::vector<std::vector<char>> initPlateau()
{
    std::vector<std::vector <char>> matrice
    {
        {'1','1','1','1','1','1','1','1','1','1','D','1','1','1','1','D','1','1','1','1','1','1','1','1','1','1'},
        {'1','0','0','0','0','0','0','1','8','8','8','0','0','0','0','8','8','8','1','0','0','0','0','0','0','1'},
        {'1','0','0','0','0','0','0','8','8','0','0','0','0','0','0','0','0','8','8','0','0','0','0','0','0','1'},
        {'1','0','0','0','0','0','0','8','8','0','0','0','0','0','0','0','0','8','C','0','0','0','0','0','0','1'},
        {'1','0','0','0','0','0','0','8','8','0','0','0','0','0','0','0','0','8','8','0','0','0','0','0','0','1'},
        {'1','1','0','0','0','7','0','8','8','0','0','0','0','0','0','0','7','8','8','7','0','0','0','0','1','1'},
        {'1','8','C','8','8','8','8','8','8','0','7','0','0','0','0','0','0','8','8','8','8','8','8','8','D','1'},
        {'1','1','8','8','8','8','8','8','8','8','8','8','8','8','8','8','8','8','8','8','C','8','8','8','1','1'},
        {'1','0','0','0','0','0','8','8','8','8','8','8','8','8','8','8','8','8','8','0','0','0','0','0','0','1'},
        {'1','0','0','0','0','0','0','0','0','8','8','7','7','7','7','7','8','8','8','7','0','0','0','0','0','1'},
        {'1','0','0','0','0','0','0','0','0','C','8','7','0','0','0','7','8','8','8','0','0','0','0','0','0','1'},
        {'1','0','0','0','0','0','0','0','0','8','8','7','0','0','0','7','8','8','8','0','0','0','0','0','0','1'},
        {'1','0','0','0','0','0','0','0','0','8','8','7','0','0','0','7','8','8','8','0','0','0','0','7','0','1'},
        {'1','0','0','0','0','0','0','0','0','8','8','7','0','0','0','7','C','8','8','8','8','8','8','8','1','1'},
        {'1','0','0','0','0','0','0','0','0','8','8','7','0','0','0','7','8','8','8','0','0','7','0','0','1','1'},
        {'1','0','0','0','0','0','0','7','0','8','8','7','0','0','0','7','8','8','0','0','0','0','0','0','0','1'},
        {'1','1','8','C','8','8','8','8','8','8','8','7','7','7','7','7','8','8','7','0','0','0','0','0','0','1'},
        {'1','D','8','8','8','8','8','8','8','8','8','8','8','8','8','8','8','8','0','0','0','0','0','0','0','1'},
        {'1','1','8','8','8','8','8','8','8','C','0','0','0','7','0','0','8','8','8','0','0','0','0','0','1','1'},
        {'1','0','0','0','0','0','0','7','8','8','0','0','0','0','0','0','8','8','8','8','8','8','8','8','D','1'},
        {'1','0','0','0','0','0','0','0','8','8','0','0','0','0','0','0','8','8','8','8','C','8','8','8','1','1'},
        {'1','0','0','0','0','0','0','0','8','8','0','0','0','0','0','0','8','8','7','0','0','0','0','0','0','1'},
        {'1','0','0','0','0','0','0','0','8','8','0','0','0','0','0','0','8','8','0','0','0','0','0','0','0','1'},
        {'1','0','0','0','0','0','0','0','8','8','0','0','0','0','0','0','8','8','0','0','0','0','0','0','0','1'},
        {'1','0','0','0','0','0','0','1','D','1','0','0','0','0','0','0','8','8','0','0','0','0','0','0','0','1'},
        {'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'}
    };

    return matrice;
}
