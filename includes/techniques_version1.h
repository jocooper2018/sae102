#ifndef TECNIQUE_V1_H
    #define TECNIQUE_V1_H

    void singletonNu(t_grille1 grille, int *nbCasesVide, bool *progression);
    void singletonCache(t_grille1 grille, int *nbCasesVide, bool *progression);
    void accepterCandidat(t_grille1 grille, int numLigne, int numCol, int candidat);

    int nbOccurenceCandidatLigne(t_grille1 grille, int numLigne, int candidat);
    int nbOccurenceCandidatColonne(t_grille1 grille, int numCol, int candidat);
    int nbOccurenceCandidatBlock(t_grille1 grille, int numLigne, int numCol, int candidat);

#endif

