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
                if (possible(grille, ligne, colonne, valeur))
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
    printf("    ");
    for (int i = 0; i < TAILLE_GRILLE; i++)
    {
        if (i % TAILLE_SOUS_GRILLE == 0)
        {
            printf(" ");
        }
        printf(" %2d ", i+1);
    }
    printf("\n");

    for (int i = 0; i < TAILLE_GRILLE; i++)
    {
        if (i % TAILLE_SOUS_GRILLE == 0)
        {
            // printf("   +---------+---------+---------+\n");
            printf("    ");
            for (int j = 0; j < TAILLE_GRILLE; j++)
            {
                if (j % TAILLE_SOUS_GRILLE == 0)
                {
                    printf("+");
                }
                printf("----");
            }
            printf("+\n");
        }
        printf("%2d  ", i+1);
        for (int j = 0 ; j < TAILLE_GRILLE ; j++)
        {
            if (j % TAILLE_SOUS_GRILLE == 0)
            {
                printf("|");
            }
            if (grille[i][j].valeur == 0)
            {
                printf("  . ");
            }
            else
            {
                printf(" %2d ", grille[i][j].valeur);
            }
        }
        printf("|\n");
    }
    printf("    ");
    for (int j = 0; j < TAILLE_GRILLE; j++)
    {
        if (j % TAILLE_SOUS_GRILLE == 0)
        {
            printf("+");
        }
        printf("----");
    }
    printf("+\n");
}


/**
 * @fn bool possible(t_grille1 grille, int numLigne, int numColone, int valeur)
 * @param grille `t_grille1` Grille dans laquelle on veut savoir si il est 
 * possible d'inserer une valeur.
 * @param numLigne `int` Numero de la ligne ou inserer une valeur.
 * @param numColone `int` Numero de la colone ou inserer une valeur.
 * @param valeur `int` Valeur a inserer.
 * @return `bool` `true` si il est possible d'inserer la valeur a l'emplacement 
 * donnee, `false` sinon.
 * @brief Permet de verifier si il est possible d'inserer une valeur a un 
 * certain emplacement d'une grille donnee sans enfreindre les regles du sudoku.
*/
bool possible(t_grille_backtracking grille, int numLigne, int numColone, int valeur)
{
    bool peutInserer = true;
    int i, j;
    int iMax, jMax;

    // Verification sur la ligne et sur la colonne
    i = 0;
    while ((i < TAILLE_GRILLE) && peutInserer)
    {
        if ((grille[numLigne][i].valeur == valeur) ||
            (grille[i][numColone].valeur == valeur))
        {
            peutInserer = false;
        }
        i++;
    }
    // Verification sur le groupe de 9 case
    i = (numLigne / NBR_SOUS_GRILLE) * NBR_SOUS_GRILLE;
    iMax = i + TAILLE_SOUS_GRILLE;
    while ((i < iMax) && peutInserer)
    {
        j = (numColone / NBR_SOUS_GRILLE) * NBR_SOUS_GRILLE;
        jMax = j + TAILLE_SOUS_GRILLE;
        while ((j < jMax) && peutInserer)
        {
            if (grille[i][j].valeur == valeur)
            {
                peutInserer = false;
            }
            j++;
        }
        i++;
    }

    return peutInserer;
}

