#ifndef TESTS_H
    #define TESTS_H

    #include <stdbool.h>

    #include "types.h"

    
    bool testLigne(grille_t grille, int numLigne);
    bool testColonne(grille_t grille, int numCol);
    bool testBlock(grille_t grille, int numLigne, int numCol);
    bool testGrille(grille_t grille);

#endif

