#ifndef TYPES1_H
    #define TYPES1_H

    #include "defines.h"


    typedef struct
    {
        int valeur;
        int candidats[TAILLE_GRILLE];
        int nbCandidats;
    } t_case1;

    typedef t_case1 t_grille1[TAILLE_GRILLE][TAILLE_GRILLE];


#endif

