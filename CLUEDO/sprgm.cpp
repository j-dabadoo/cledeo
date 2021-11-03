#include "sprgm.h"

///ssprgm qui initialise allegro
void initialisation_allegro()
{
    allegro_init() ; ///Permet d'initialiser Allegro et utiliser ses fonctions
    srand(time(NULL)) ;
    set_color_depth(desktop_color_depth()); ///Initialiser la couleur de la fenêtre (arrière plan)

    if((set_gfx_mode(GFX_AUTODETECT_WINDOWED,1200,600,0,0))!=0)  ///Création de la fenêtre Allegro et vérification si elle est bien ouevrte
    {
        allegro_message("Pb de mode graphique") ;
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    install_keyboard();
    install_mouse();

}
void maphypo_create(std::map<std::string, bool> hypo)
{
    ///ajout des string dans la map
    //personnages
    hypo.insert({"barbenoire",false});
    hypo.insert({"billturner",false});
    hypo.insert({"calypso",false});
    hypo.insert({"davyjones",false});
    hypo.insert({"jacksparrow",false});
    hypo.insert({"jamesnorrington",false});
    hypo.insert({"swann",false});
    hypo.insert({"barbossa",false});
    hypo.insert({"willturner",false});

    //armes
    hypo.insert({"canon",false});
    hypo.insert({"poudre",false});
    hypo.insert({"tirebouchon",false});
    hypo.insert({"cle",false});
    hypo.insert({"sabre",false});
    hypo.insert({"pistolet",false});


}

///ssprgm qui met en place le seond plateau d'hypothèses
void plateau_hyp(BITMAP* page)
{
    show_mouse(page);
    ///map d'hypothese
    std::map<std::string, bool>hypothese;

    ///BITMAP
    //personnages
    BITMAP* barbenoire;
    BITMAP* billturner;
    BITMAP* calypso;
    BITMAP* davyjones;
    BITMAP* jacksparrow;
    BITMAP* jamesnorrington;
    BITMAP* swann;
    BITMAP* barbossa;
    BITMAP* willturner;

    //armes
    BITMAP* canon;
    BITMAP* cle;
    BITMAP* pistolet;
    BITMAP* poudre;
    BITMAP* sabre;
    BITMAP* tirebouchon;


    ///telechargement des bitmap
    //personnages
    barbenoire=load_bitmap("barbenoire.bmp", NULL);
    billturner=load_bitmap("billturner.bmp", NULL);
    calypso=load_bitmap("calypso.bmp", NULL);
    davyjones=load_bitmap("davyjones.bmp", NULL);
    jacksparrow=load_bitmap("jacksparrow.bmp", NULL);
    jamesnorrington=load_bitmap("jamesnorrington.bmp", NULL);
    swann=load_bitmap("swann.bmp", NULL);
    barbossa=load_bitmap("barbossa.bmp", NULL);
    willturner=load_bitmap("willturner.bmp", NULL);

    //armes
    canon=load_bitmap("canon.bmp", NULL);
    pistolet=load_bitmap("pistolet.bmp", NULL);
    poudre=load_bitmap("poudre.bmp", NULL);
    sabre=load_bitmap("sabre.bmp", NULL);
    cle=load_bitmap("cle.bmp", NULL);
    tirebouchon=load_bitmap("tirebouchon.bmp", NULL);

    ///creation de la map
    maphypo_create(hypothese);

    ///cadre de jade
    rectfill(page,0,0,400,600,makecol(239,228,176));
    for(int i=0; i<25; i++)
    {
        hline(page, 0, (25+ i*25), 400, makecol(0, 0, 0));
    }
    vline(page, 350, 0, 600, makecol(0, 0, 0));

    ///affichage des personnages
    textprintf_ex(page,font, 500, 75,makecol(239, 228, 176), -1, "personnages: ");

    if(mouse_x>=402 && mouse_x<=462 && mouse_y>=85 && mouse_y<=185)
    {
        hypothese["barbenoire"]=true;
    }
    if(mouse_x>=490 && mouse_x<=550 && mouse_y>=85 && mouse_y<=185)
    {
        hypothese["billturner"]=true;
    }
    if(mouse_x>=578 && mouse_x<=638 && mouse_y>=85 && mouse_y<=185)
    {
        hypothese["calypso"]=true;
    }
    if(mouse_x>=666 && mouse_x<=726 && mouse_y>=85 && mouse_y<=185)
    {
        hypothese["davyjones"]=true;
    }
    if(mouse_x>=754 && mouse_x<=814 && mouse_y>=85 && mouse_y<=185)
    {
        hypothese["jacksparrow"]=true;
    }
    if(mouse_x>=842 && mouse_x<=902 && mouse_y>=85 && mouse_y<=185)
    {
        hypothese["jamesnorrington"]=true;
    }
    if(mouse_x>=930 && mouse_x<=990 && mouse_y>=85 && mouse_y<=185)
    {
        hypothese["swann"]=true;
    }
    if(mouse_x>=1018 && mouse_x<=1078 && mouse_y>=85 && mouse_y<=185)
    {
        hypothese["barbossa"]=true;
    }
    if(mouse_x>=1106 && mouse_x<=1166 && mouse_y>=85 && mouse_y<=185)
    {
        hypothese["willturner"]=true;
    }

    blit(barbenoire, page,0,0, 402, 85, SCREEN_W, SCREEN_H);
    blit(billturner, page,0,0, 490, 85, SCREEN_W, SCREEN_H);
    blit(calypso, page, 0,0,578, 85, SCREEN_W, SCREEN_H);
    blit(davyjones, page,0,0, 666, 85, SCREEN_W, SCREEN_H);
    blit(jacksparrow, page,0,0, 754, 85,SCREEN_W, SCREEN_H);
    blit(jamesnorrington, page,0,0, 842, 85, SCREEN_W, SCREEN_H);
    blit(swann, page,0,0, 930, 85, SCREEN_W, SCREEN_H);
    blit(barbossa, page, 0,0,1018, 85, SCREEN_W, SCREEN_H);
    blit(willturner, page,0,0, 1106, 85, SCREEN_W, SCREEN_H);

    show_mouse(page);

    ///affichage des armes
    textprintf_ex(page,font, 500, 275,makecol(239, 228, 176), -1, "armes: ");

    if(mouse_x>=402 && mouse_x<=462 && mouse_y>=285 && mouse_y<=385)
    {
        hypothese["canon"]=true;
    }
    if(mouse_x>=535 && mouse_x<=595 && mouse_y>=285 && mouse_y<=385)
    {
        hypothese["poudre"]=true;
    }
    if(mouse_x>=668 && mouse_x<=728 && mouse_y>=285 && mouse_y<=385)
    {
        hypothese["tirebouchon"]=true;
    }
    if(mouse_x>=801 && mouse_x<=861 && mouse_y>=285 && mouse_y<=385)
    {
        hypothese["cle"]=true;
    }
    if(mouse_x>=934 && mouse_x<=994 && mouse_y>=285 && mouse_y<=385)
    {
        hypothese["sabre"]=true;
    }
    if(mouse_x>=1067 && mouse_x<=1127 && mouse_y>=285 && mouse_y<=385)
    {
        hypothese["pitolet"]=true;
    }


    blit(canon, page,0,0, 402, 285, SCREEN_W, SCREEN_H);
    blit(poudre, page,0,0, 535, 285, SCREEN_W, SCREEN_H);
    blit(tirebouchon, page, 0,0,668, 285, SCREEN_W, SCREEN_H);
    blit(cle, page,0,0, 801, 285, SCREEN_W, SCREEN_H);
    blit(sabre, page,0,0, 934, 285,SCREEN_W, SCREEN_H);
    blit(pistolet, page,0,0, 1067, 285, SCREEN_W, SCREEN_H);

    show_mouse(page);

    textprintf_ex(page,font, 500, 480,makecol(239, 228, 176), -1, "joueurs: ");

    blit(page, screen, 0,0,0,0,SCREEN_W,SCREEN_H);

}

///ssprgm qui donne aleatoirement le lieu dans lequel il se trouve
std::string lieuxhasard()
{
    int has;
    std::vector<std::string>lieux;

    lieux.push_back("Tortuga");
    lieux.push_back("Port Royal");
    lieux.push_back("Ile de la Muerta");
    lieux.push_back("Ile au rhum");
    lieux.push_back("Hollandais Volant");
    lieux.push_back("Ile des 4 vents");
    lieux.push_back("HMS Intrepide");
    lieux.push_back("Triangle des Bermudes");
    lieux.push_back("Black Pearl");

    has=rand()%(10);
    return lieux[has];
}

void plateaudebase(BITMAP* page)
{
    BITMAP* plateau;

    plateau=load_bitmap("plateau.bmp", NULL);
    blit(plateau, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    ///quitter le jeu
    rectfill(page,620,125,820,175,makecol(127,127,127));
    ///bouton hypothese
    rectfill(page,620,225,820,275,makecol(208,82,41));
    ///zone de dé
    rectfill(page,900,75,1150,325,makecol(59,162,71));
    ///zone des joueurs
    rectfill(page,620,375,1150,550,makecol(136,0,21));

    show_mouse(page);
    if(mouse_x>=620 && mouse_x<=820 && mouse_y>=225 && mouse_y<=275)
    {
        rect(page, 617, 222, 823, 278, makecol(208,82,41));

    }
    else
        rect(page, 617, 222, 823, 278, makecol(0,0,0));

    while(mouse_b &1)
    {
        if(mouse_x>=620 && mouse_x<=820 && mouse_y>=225 && mouse_y<=275)
        {
            plateau_hyp(page);
        }

    }

    blit(page, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
}
