#include "sprgm.h"
using namespace std;

////////////////////////////////////////
//        ECRIRE UNE STD::STRING      //
//       nom de la string.c_str()     //
////////////////////////////////////////

int main()
{
    BITMAP* plateau;
    BITMAP* page;
    std::string lieuactuel;

    ///initialisation d'allegro
    initialisation_allegro();
    ///creation du ouble buffer
    page=create_bitmap(SCREEN_W, SCREEN_H);

    /*initialisation aleatoire du lieu du joueur
    lieuactuel=lieuxhasard();
    textprintf_ex(page,font, 600, 40,makecol(255, 0, 0), -1, "attention vous etes en ");
    textprintf_ex(page,font, 800, 40,makecol(255, 0, 0), -1, "%s", lieuactuel.c_str());*/

    ///boucle pour lancer
    while(1)
    {
        ///affichage du second plateau
        show_mouse(page);
        //plateaudebase(page);
        plateau_hyp(page);

        blit(page, screen, 0,0,0,0,SCREEN_W,SCREEN_H);


    }
    return 0;
}
END_OF_MAIN();

