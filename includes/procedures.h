#ifndef PROCEDURES_H
    #define PROCEDURES_H

    #include <stdbool.h>

    #include "types.h"


    bool chargerGrille(grille_t grille);
    void initialiserCandidats(grille_t grille);
    int getNbCaseVides(grille_t grille);
    void ajouterCandidat(case_t *laCase, int valeur);
    void retirerCandidat(case_t *laCase, int valeur);
    void retirerTousLesCandidat(case_t *laCase);
    bool estCandidat(case_t *laCase, int valeur);
    int getNbCandidats(case_t *laCase);
    void afficherGrille(grille_t grille);
    bool possible(grille_t grille, int numLigne, int numColone, int valeur);

#endif

