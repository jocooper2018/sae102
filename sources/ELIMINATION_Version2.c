#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "../includes/defines.h"
#include "../includes/types2.h"
#include "../includes/procedures_version2.h"
#include "../includes/techniques_version2.h"
#include "../includes/tests_version2.h"


int main()
{
    t_grille2 grille;
    int nbCasesVide;
    bool progression = true;
    clock_t clockDebut, clockFin;
    double duree;

    bool grilleCharge = false;
    while (!grilleCharge)
    {
        grilleCharge = chargerGrille(grille);
    }

    afficherGrille(grille);

    nbCasesVide = getNbCaseVides(grille);
    printf("%d cases vides\n", nbCasesVide);

    initialiserCandidats(grille);

    clockDebut = clock();
    while ((nbCasesVide > 0) && progression)
    {
        progression = false;

        singletonNu(grille, &nbCasesVide, &progression);
        singletonCache(grille, &nbCasesVide, &progression);

        if (progression)
        {
            printf("true\n");
        }
        else
        {
            printf("false\n");
        }
    }
    clockFin = clock();
    duree = (double) (clockFin - clockDebut) / CLOCKS_PER_SEC;

    afficherGrille(grille);
    printf("%d cases vides\n", nbCasesVide);
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


