#ifndef TECHNIQUES_H
    #define TECHNIQUES_H

    #include "types.h"


    void singletonNu(grille_t grille, int *nbCasesVide, bool *progression);
    void singletonCache(grille_t grille, int *nbCasesVide, bool *progression);
    void accepterCandidat(grille_t grille, int numLigne, int numCol, int candidat);

    int nbOccurenceCandidatLigne(grille_t grille, int numLigne, int candidat);
    int nbOccurenceCandidatColonne(grille_t grille, int numCol, int candidat);
    int nbOccurenceCandidatBlock(grille_t grille, int numLigne, int numCol, int candidat);
    bool backtracking(grille_t grille, int numeroCase);

#endif

