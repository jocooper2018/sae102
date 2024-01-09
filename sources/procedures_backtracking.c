#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../includes/types_backtracking.h"
#include "../includes/procedures_backtracking.h"


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


bool chargerGrille(t_grille_backtracking grille)
{
    bool fileLoadSuccess;
    int grilleTmp[TAILLE_GRILLE][TAILLE_GRILLE];

    char nomFichier[30];
    printf("Nom du fichier ? ");
    scanf("%s", nomFichier);

    FILE *f;
    f = fopen(nomFichier, "rb");

    if (f == NULL)
    {
        printf("\n ERREUR sur le fichier %s\n", nomFichier);
        fileLoadSuccess = false;
    } 
    else 
    {
        fread(grilleTmp, sizeof(int), TAILLE_GRILLE*TAILLE_GRILLE, f);
        fileLoadSuccess = true;

        for (int numLigne = 0; numLigne < TAILLE_GRILLE; numLigne++)
        {
            for (int numCol = 0; numCol < TAILLE_GRILLE; numCol++)
            {
                grille[numLigne][numCol].valeur = grilleTmp[numLigne][numCol];
            }
        }
    }
    /*
    if (!feof(f))
    {
        fileLoadSuccess = false;
    }
    */
    fclose(f);

    return fileLoadSuccess;
}


/**
 * @fn void afficherGrille(t_grille1 grille)
 * @param grille `t_grille_backtracking` Grille a afficher.
 * @brief Affiche la grille passe en parametre.
*/
void afficherGrille(t_grille_backtracking grille)
{
    // printf("     1  2  3   4  5  6   7  8  9\n");
    printf("   ");
    for (int i = 0; i < TAILLE_GRILLE; i++)
    {
        if (i % TAILLE_SOUS_GRILLE == 0)
        {
            printf(" ");
        }
        printf(" %d ", i+1);
    }
    printf("\n");

    for (int i = 0; i < TAILLE_GRILLE; i++)
    {
        if (i % TAILLE_SOUS_GRILLE == 0)
        {
            // printf("   +---------+---------+---------+\n");
            printf("   ");
            for (int j = 0; j < TAILLE_GRILLE; j++)
            {
                if (j % TAILLE_SOUS_GRILLE == 0)
                {
                    printf("+");
                }
                printf("---");
            }
            printf("+\n");
        }
        printf("%d  ", i+1);
        for (int j = 0 ; j < TAILLE_GRILLE ; j++)
        {
            if (j % TAILLE_SOUS_GRILLE == 0)
            {
                printf("|");
            }
            if (grille[i][j].valeur == 0)
            {
                printf(" . ");
            }
            else
            {
                printf(" %d ", grille[i][j].valeur);
            }
        }
        printf("|\n");
    }
    printf("   ");
    for (int j = 0; j < TAILLE_GRILLE; j++)
    {
        if (j % TAILLE_SOUS_GRILLE == 0)
        {
            printf("+");
        }
        printf("---");
    }
    printf("+\n");
}
