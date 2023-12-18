#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../includes/defines.h"
#include "../includes/types1.h"
#include "../includes/procedures_version1.h"
#include "../includes/techniques_version1.h"


int main()
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

    while ((nbCasesVide > 0) && progression)
    {
        progression = false;

        // technique du singleton nu
        singletonNu(grille, &nbCasesVide, &progression);

        if (progression)
        {
            printf("true\n");
        }
        else
        {
            printf("false\n");
        }
    }

    afficherGrille(grille);
    printf("%d cases vides\n", nbCasesVide);

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
