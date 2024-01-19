#ifndef TYPES_H
    #define TYPES_H

    #include <stdbool.h>

    #include "defines.h"

    typedef struct {
        int c_valeur;
        bool c_candidats[TAILLE_GRILLE + 1];
    } case_t;

    typedef case_t grille_t[TAILLE_GRILLE][TAILLE_GRILLE];

#endif
