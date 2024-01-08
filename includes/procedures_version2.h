#ifndef PROCEDURES1_H
    #define PROCEDURES1_H

    #include <stdbool.h>

    #include "types2.h"


    bool chargerGrille(t_grille2 grille);
    void initialiserCandidats(t_grille2 grille);
    int getNbCaseVides(t_grille2 grille);
    void ajouterCandidat(t_case2 *laCase, int valeur);
    void retirerCandidat(t_case2 *laCase, int valeur);
    void retirerTousLesCandidat(t_case2 *laCase);
    bool estCandidat(t_case2 laCase, int valeur);
    int nbCandidats(t_case2 laCase);
    void afficherGrille(t_grille2 grille);
    bool possible(t_grille2 grille, int numLigne, int numColone, int valeur);

#endif

