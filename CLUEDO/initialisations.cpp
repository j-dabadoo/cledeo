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

void cardInit(std::vector <Joueur> &joueurs, std::vector <Carte> &cartes, std::vector <Carte> &cartes2, int &nb_joueurs)
{
    int ok=0, id ;

    ///Initialisation
    for(int i=0 ; i<nb_joueurs ; i++)
        joueurs.push_back(Joueur()) ;


    ///Initialisation des cartes
    cartes.push_back(Carte(0,"Sabre",                  load_bitmap("images/sabre.bmp",NULL), "arme"));
    cartes.push_back(Carte(1,"Pistolet",               load_bitmap("images/pistolet.bmp",NULL), "arme"));
    cartes.push_back(Carte(2,"Poudre a canon",         load_bitmap("images/poudre.bmp",NULL), "arme"));
    cartes.push_back(Carte(3,"Cle",                    load_bitmap("images/cle.bmp",NULL), "arme"));
    cartes.push_back(Carte(4,"Tire bouchon",           load_bitmap("images/tirebouchon.bmp",NULL), "arme"));
    cartes.push_back(Carte(5,"Canon",                  load_bitmap("images/canon.bmp",NULL), "arme"));
    cartes.push_back(Carte(6,"Will Turner",            load_bitmap("images/willturner.bmp",NULL), "perso"));
    cartes.push_back(Carte(7,"Bill Turner",            load_bitmap("images/billturner.bmp",NULL), "perso"));
    cartes.push_back(Carte(8,"Jack Sparrow",           load_bitmap("images/jacksparrow.bmp",NULL), "perso"));
    cartes.push_back(Carte(9,"Barbossa",               load_bitmap("images/barbossa.bmp",NULL), "perso"));
    cartes.push_back(Carte(10,"Elizabeth Swann",       load_bitmap("images/swann.bmp",NULL), "arme"));
    cartes.push_back(Carte(11,"Davy Jones",            load_bitmap("images/davyjones.bmp",NULL), "perso"));
    cartes.push_back(Carte(12,"Calypso",               load_bitmap("images/calypso.bmp",NULL), "perso"));
    cartes.push_back(Carte(13,"James Norrington",      load_bitmap("images/jamesnorrington.bmp",NULL), "perso"));
    cartes.push_back(Carte(14,"Barbe Noire",           load_bitmap("images/barbenoire.bmp",NULL), "perso"));
    cartes.push_back(Carte(15,"Tortuga",               load_bitmap("images/tortuga.bmp",NULL), "lieu"));
    cartes.push_back(Carte(16,"Port Royal",            load_bitmap("images/portroyale.bmp",NULL), "lieu"));
    cartes.push_back(Carte(17,"Ile de la Muerta",      load_bitmap("images/muerta.bmp",NULL), "lieu"));
    cartes.push_back(Carte(18,"Ile au rhum",           load_bitmap("images/rhum.bmp",NULL), "lieu"));
    cartes.push_back(Carte(19,"Hollandais Volant",     load_bitmap("images/naufrager.bmp",NULL), "lieu"));
    cartes.push_back(Carte(20,"Ile des 4 vents",       load_bitmap("images/quatresvents.bmp",NULL), "lieu"));
    cartes.push_back(Carte(21,"HMS Intrepide",         load_bitmap("images/intrepide.bmp",NULL), "lieu"));
    cartes.push_back(Carte(22,"Triangle des Bermudes", load_bitmap("images/bermudes.bmp",NULL), "lieu"));
    cartes.push_back(Carte(23,"Black Pearl",           load_bitmap("images/blackpearl.bmp",NULL), "lieu"));

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


    ///Attribution des cartes (secret + joueurs)
    for(int i=0 ; i<NB_CARTE ; i++)
    {
        for(auto& item:cartes2)
        {
            ///On remplie la pochette secrète avec la première carte de type perso
            if(persoSecret==false && item.getType()=="perso")
            {
                persoSecret=true ;
                secret.push_back(item);
                item.setType("off");
            }
            ///On remplie la pochette secrète avec la première carte de type arme
            else if(armeSecrete==false && item.getType()=="arme")
            {
                armeSecrete=true ;
                secret.push_back(item);
                item.setType("off");
            }
            ///On remplie la pochette secrète avec la première carte de type lieu
            else if(lieuSecret==false && item.getType()=="lieu")
            {
                lieuSecret=true ;
                secret.push_back(item);
                item.setType("off");
            }

            ///Remplissage du reste des cartes pour les joueurs
            else if(item.getType()!="off")
            {
                joueurs[tour].add(item);
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

void destruction(std::vector<Carte> &cartes, BITMAP *plateau)
{
    for(auto& carte:cartes)
        destroy_bitmap(carte.getImage());

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
        {'1','0','0','0','0','0','0','8','8','0','0','0','0','0','0','0','0','8','8','0','0','0','0','0','0','1'},
        {'1','0','0','0','0','0','0','8','8','0','0','0','0','0','0','0','0','8','8','0','0','0','0','0','0','1'},
        {'1','1','0','0','0','7','0','8','8','0','0','0','0','0','0','0','7','8','8','7','0','0','0','0','1','1'},
        {'1','8','8','8','8','8','8','8','8','0','7','0','0','0','0','0','0','8','8','8','8','8','8','8','D','1'},
        {'1','1','8','8','8','8','8','8','8','8','8','8','8','8','8','8','8','8','8','8','8','8','8','8','1','1'},
        {'1','0','0','0','0','0','8','8','8','8','8','8','8','8','8','8','8','8','8','0','0','0','0','0','0','1'},
        {'1','0','0','0','0','0','0','0','0','8','8','7','7','7','7','7','8','8','8','7','0','0','0','0','0','1'},
        {'1','0','0','0','0','0','0','0','0','8','8','7','0','0','0','7','8','8','8','0','0','0','0','0','0','1'},
        {'1','0','0','0','0','0','0','0','0','8','8','7','0','0','0','7','8','8','8','0','0','0','0','0','0','1'},
        {'1','0','0','0','0','0','0','0','0','8','8','7','0','0','0','7','8','8','8','0','0','0','0','7','0','1'},
        {'1','0','0','0','0','0','0','0','0','8','8','7','0','0','0','7','8','8','8','8','8','8','8','8','1','1'},
        {'1','0','0','0','0','0','0','0','0','8','8','7','0','0','0','7','8','8','8','0','0','7','0','0','1','1'},
        {'1','0','0','0','0','0','0','7','0','8','8','7','0','0','0','7','8','8','0','0','0','0','0','0','0','1'},
        {'1','1','8','8','8','8','8','8','8','8','8','7','7','7','7','7','8','8','7','0','0','0','0','0','0','1'},
        {'1','D','8','8','8','8','8','8','8','8','8','8','8','8','8','8','8','8','0','0','0','0','0','0','0','1'},
        {'1','1','8','8','8','8','8','8','8','8','0','0','0','7','0','0','8','8','8','0','0','0','0','0','1','1'},
        {'1','0','0','0','0','0','0','7','8','8','0','0','0','0','0','0','8','8','8','8','8','8','8','8','D','1'},
        {'1','0','0','0','0','0','0','0','8','8','0','0','0','0','0','0','8','8','8','8','8','8','8','8','1','1'},
        {'1','0','0','0','0','0','0','0','8','8','0','0','0','0','0','0','8','8','7','0','0','0','0','0','0','1'},
        {'1','0','0','0','0','0','0','0','8','8','0','0','0','0','0','0','8','8','0','0','0','0','0','0','0','1'},
        {'1','0','0','0','0','0','0','0','8','8','0','0','0','0','0','0','8','8','0','0','0','0','0','0','0','1'},
        {'1','0','0','0','0','0','0','1','D','1','0','0','0','0','0','0','8','8','0','0','0','0','0','0','0','1'},
        {'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'}
    };

    return matrice;
}
