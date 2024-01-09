#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "../includes/types_backtracking.h"


int main()
{
    t_grille_backtracking grille;
    int nbCasesVide;
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
    backtracking(grille, 0);
    clockFin = clock();
    duree = (double) (clockFin - clockDebut) / CLOCKS_PER_SEC;

    afficherGrille(grille);
    printf("%d cases vides\n", nbCasesVide);
    printf("Temps : %f s\n", duree);

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


bool backtracking(t_grille_backtracking grille, int numeroCase)
{
    bool result;
    int ligne, colonne;

    result = false;

    if (numeroCase == TAILLE_GRILLE * TAILLE_GRILLE)
    {
        // On a traité toutes les cases, la grille est résolue
        result = true;
    }
    else
    {
        // On récupère les "coordonnées" de la case
        ligne = numeroCase / TAILLE_GRILLE;
        colonne = numeroCase % TAILLE_GRILLE;
        if (grille[ligne][colonne].valeur != 0)
        {
            // Si la case n’est pas vide, on passe à la suivante
            // (appel récursif)
            result = backtracking(grille, numeroCase + 1);
        }
        else
        {
            for (int valeur = 1; valeur <= TAILLE_GRILLE; valeur++)
            {
                if (possible())
                {
                    // Si la valeur est autorisée on l'inscrit
                    //dans la case...
                    grille[ligne][colonne].valeur = valeur;
                    // ... et on passe à la suivante : appel récursif
                    // pour voir si ce choix est bon par la suite
                    if (backtracking(grille, numeroCase + 1))
                    {
                        result = true;
                    }
                    else
                    {
                        grille[ligne][colonne].valeur = 0;
                    }
                }
            }
        }
    }

    return result;
}

