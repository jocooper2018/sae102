#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "../includes/types_backtracking.h"
#include "../includes/procedures_backtracking.h"
#include "../includes/tests_backtracking.h"


int main()
{
    t_grille_backtracking grille;
    clock_t clockDebut, clockFin;
    double duree;

    bool grilleCharge = false;
    while (!grilleCharge)
    {
        grilleCharge = chargerGrille(grille);
    }

    afficherGrille(grille);

    clockDebut = clock();
    backtracking(grille, 0);
    clockFin = clock();
    duree = (double) (clockFin - clockDebut) / CLOCKS_PER_SEC;

    afficherGrille(grille);
    printf("Temps : %.3f s\n", duree);

    if (testGrille(grille))
    {
        printf("Grille rempie sans erreurs.\n");
    }
    else
    {
        printf("Une erreur s'est produite lors du remplissage de la grille.\n");
    }

    return EXIT_SUCCESS;
}

