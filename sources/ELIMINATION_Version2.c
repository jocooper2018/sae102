#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "../includes/defines.h"
#include "../includes/types2.h"
#include "../includes/procedures_version2.h"
#include "../includes/techniques_version2.h"


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
    printf("Temps : %f s\n", duree);

    return EXIT_SUCCESS;
}


/*
int main2()
{
    t_grille1 grille;
    int nbCasesVide;
    bool progression = true;

    bool grilleCharge = false;
    while (!grilleCharge)
    {
        grilleCharge = chargerGrille(grille);
    }

    afficherGrille(grille);

    nbCasesVide = getNbCaseVides(grille);
    printf("%d cases vides\n", nbCasesVide);

    initialiserCandidats(grille);

    printf("nbCandidats : %d\ncandidats : ", grille[0][1].nbCandidats);
    for (int i = 0; i < TAILLE_GRILLE; i++)
    {
        printf("%d ", grille[0][1].candidats[i]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}
*/

