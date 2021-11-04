#ifndef SPRGM_H_INCLUDED
#define SPRGM_H_INCLUDED
#include "iostream"
#include "vector"
#include "map"
#include "allegro.h"
///ssprgm qui initialise allegro
void initialisation_allegro();

///ssprgm qui met en place le seond plateau d'hypothèses
void plateau_hyp(BITMAP* page);

///ssprgm qui donne aleatoirement le lieu dans lequel il se trouve
std::string lieuxhasard();

void plateaudebase(BITMAP* page);

#endif // SPRGM_H_INCLUDED
