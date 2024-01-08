#ifndef TYPES1_H
    #define TYPES1_H

    #include "defines.h"


    typedef struct
    {
        int valeur;
        bool candidats[TAILLE_GRILLE + 1];
    } t_case2;

    typedef t_case2 t_grille2[TAILLE_GRILLE][TAILLE_GRILLE];


#endif

