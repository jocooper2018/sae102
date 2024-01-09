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
    double secondes;
    int nbMinutes;
    int nbHeures;

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

    secondes = duree;
    nbMinutes = duree / 60;
    nbHeures = nbMinutes / 60;
    while (secondes > 60)
    {
        secondes -= 60;
    }
    nbMinutes %= 60;

    afficherGrille(grille);
    printf("Temps :");
    if (nbHeures > 0)
    {
        printf(" %d h", nbHeures);
    }
    if (nbMinutes > 0)
    {
        printf(" %d m", nbMinutes);
    }
    printf(" %.3f s\n", secondes);

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

