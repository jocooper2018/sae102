#ifndef TESTS_V1_H
    #define TESTS_V1_H

    #include <stdbool.h>

    #include "types1.h"

    
    bool testLigne(t_grille1 grille, int numLigne);
    bool testColonne(t_grille1 grille, int numCol);
    bool testBlock(t_grille1 grille, int numLigne, int numCol);
    bool testCase(t_grille1 grille, int numLigne, int numCol);
    bool testGrille(t_grille1 grille);

#endif

