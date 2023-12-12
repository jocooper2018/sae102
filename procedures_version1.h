#ifndef PROCEDURES1_H
    #define PROCEDURES1_H

    #include <stdbool.h>

    #include "types1.h"


    bool chargerGrille(t_grille grille);
    void initialiserCandidats(t_grille grille);
    int getNbCaseVides(t_grille grille);
    void ajouterCandidat(t_case1 *laCase, int valeur);
    void retirerCandidat(t_case1 laCase, int valeur);
    bool estCandidat(t_case1 laCase, int valeur);
    int nbCandidats(t_case1 laCase);
    void afficherGrille(t_grille grille);
    bool possible(t_grille grille, int numLigne, int numColone, int valeur);

#endif

