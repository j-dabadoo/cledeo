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
/// LANCEMENT DES 2 D�S ///
/// /////////////////// ///

int lancerDe()
{
    return rand()%(11)+1; ///G�n�ration d'un nombre al�atoire entre 2 et 12
}
