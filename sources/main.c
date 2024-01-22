#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "../includes/defines.h"
#include "../includes/types.h"
#include "../includes/procedures.h"
#include "../includes/techniques.h"
#include "../includes/tests.h"


int main()
{
    grille_t grille;
    int nbCasesVide;
    bool progression = true;
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

    nbCasesVide = getNbCaseVides(grille);
    printf("%d cases vides\n", nbCasesVide);

    initialiserCandidats(grille);

    clockDebut = clock();
    while ((nbCasesVide > 0) && progression)
    {
        progression = false;

        singletonNu(grille, &nbCasesVide, &progression);
        singletonCache(grille, &nbCasesVide, &progression);
    }
    backtracking(grille, 0);
    clockFin = clock();
    duree = (double) (clockFin - clockDebut) / CLOCKS_PER_SEC;

    secondes = duree;
    nbMinutes = 0;
    nbHeures = 0;
    while (secondes > 60)
    {
        secondes -= 60;
        nbMinutes++;
    }
    while (nbMinutes > 60)
    {
        nbMinutes -= 60;
        nbHeures++;
    }
    
    afficherGrille(grille);
    printf("Temps :");
    if (nbHeures > 0)
    {
        printf(" %d h", nbHeures);
    }
    if (nbMinutes > 0)
    {
        printf(" %d min", nbMinutes);
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

