#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "defines.h"
#include "types1.h"
#include "procedures_version1.h"


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
        for (int numLigne = 0; numLigne < TAILLE_GRILLE; numLigne++)
        {
            for (int numCol = 0; numCol <TAILLE_GRILLE; numCol++)
            {
                if ((grille[numLigne][numCol].valeur == 0) &&
                    grille[numLigne][numCol].nbCandidats == 1)
                {

                    grille[numLigne][numCol].valeur = grille[numLigne][numCol].candidats[0];
                    printf("%d\n", grille[numLigne][numCol].nbCandidats);
                    for (int i = 0; i < TAILLE_GRILLE; i++)
                    {
                        retirerCandidat(grille[numLigne][i], grille[numLigne][numCol].valeur);
                        retirerCandidat(grille[i][numCol], grille[numLigne][numCol].valeur);
                    }
                    int i, j;
                    int iMax, jMax;
                    i = (numLigne / NBR_SOUS_GRILLE) * NBR_SOUS_GRILLE;
                    iMax = i + TAILLE_SOUS_GRILLE;
                    while (i < iMax)
                    {
                        j = (numCol / NBR_SOUS_GRILLE) * NBR_SOUS_GRILLE;
                        jMax = j + TAILLE_SOUS_GRILLE;
                        while (j < jMax)
                        {
                            retirerCandidat(grille[i][j], grille[numLigne][numCol].valeur);
                            j++;
                        }
                        i++;
                    }
                    nbCasesVide--;
                    progression = true;
                }
            }
        }
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


