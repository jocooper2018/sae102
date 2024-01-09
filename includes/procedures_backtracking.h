#ifndef PRCEDURES_BACKTRACKING_H
    #define PRCEDURES_BACKTRACKING_H

    #include <stdbool.h>

    #include "types_backtracking.h"


    bool backtracking(t_grille_backtracking grille, int numeroCase);
    bool chargerGrille(t_grille_backtracking grille);
    bool possible(t_grille_backtracking grille, int numLigne, int numColone, int valeur);
    void afficherGrille(t_grille_backtracking grille);

#endif

