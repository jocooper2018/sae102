#ifndef TESTS_V2_H
    #define TESTS_V2_H

    #include <stdbool.h>

    #include "types2.h"

    
    bool testLigne(t_grille2 grille, int numLigne);
    bool testColonne(t_grille2 grille, int numCol);
    bool testBlock(t_grille2 grille, int numLigne, int numCol);
    bool testGrille(t_grille2 grille);

#endif

