#ifndef TESTS_BACKTRACKING_H
    #define TESTS_BACKTRACKING_H

    #include <stdbool.h>

    #include "types_backtracking.h"

    
    bool testLigne(t_grille_backtracking grille, int numLigne);
    bool testColonne(t_grille_backtracking grille, int numCol);
    bool testBlock(t_grille_backtracking grille, int numLigne, int numCol);
    bool testGrille(t_grille_backtracking grille);

#endif

