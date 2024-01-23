#include <stdio.h>
#include <stdlib.h>

#include "../includes/defines.h"
#include "../includes/types_backtracking.h"
#include "../includes/tests_backtracking.h"


bool testLigne(t_grille_backtracking grille, int numLigne)
{
    bool ok;
    int valeur;
    int nbOcurencesValeur;
    int numCol;

    ok = true;
    valeur = 1;
    
    while (ok && (valeur <= TAILLE_GRILLE))
    {
        nbOcurencesValeur = 0;
        numCol = 0;
        while (ok && (numCol < TAILLE_GRILLE))
        {
            if (grille[numLigne][numCol].valeur == valeur)
            {
                nbOcurencesValeur++;
            }
            if (nbOcurencesValeur > 1)
            {
                ok = false;
                printf("Ligne %d : la valeur %d aparait %d fois\n", numLigne, valeur, nbOcurencesValeur);
            }
            numCol++;
        }
        valeur++;
    }
    
    return ok;
}


bool testColonne(t_grille_backtracking grille, int numCol)
{
    bool ok;
    int valeur;
    int nbOcurencesValeur;
    int numLigne;

    ok = true;
    valeur = 1;
    
    while (ok && (valeur <= TAILLE_GRILLE))
    {
        nbOcurencesValeur = 0;
        numLigne = 0;
        while (ok && (numLigne < TAILLE_GRILLE))
        {
            if (grille[numLigne][numCol].valeur == valeur)
            {
                nbOcurencesValeur++;
            }
            if (nbOcurencesValeur > 1)
            {
                printf("Colonne %d : la valeur %d aparait %d fois\n", numCol, valeur, nbOcurencesValeur);
                ok = false;
            }
            numLigne++;
        }
        valeur++;
    }
    
    return ok;
}


bool testBlock(t_grille_backtracking grille, int numLigne, int numCol)
{
    bool ok = true;
    int valeur;
    int nbOcurencesValeur;

    int i, j;
    int iMax, jMax;

    valeur = 1;

    while (ok && valeur <= TAILLE_GRILLE)
    {
        nbOcurencesValeur = 0;
        i = (numLigne / NBR_SOUS_GRILLE) * NBR_SOUS_GRILLE;
        iMax = i + TAILLE_SOUS_GRILLE;
        while (ok && i < iMax)
        {
            j = (numCol / NBR_SOUS_GRILLE) * NBR_SOUS_GRILLE;
            jMax = j + TAILLE_SOUS_GRILLE;
            while (ok && j < jMax)
            {
                if (grille[i][j].valeur == valeur)
                {
                    nbOcurencesValeur++;
                }
                if (nbOcurencesValeur > 1)
                {
                    printf("Block %d %d : la valeur %d aparait %d fois\n", numLigne / NBR_SOUS_GRILLE, numCol / NBR_SOUS_GRILLE, valeur, nbOcurencesValeur);
                    ok = false;
                }
                j++;
            }
            i++;
        }
        valeur++;
    }
    return ok;
}


bool testGrille(t_grille_backtracking grille)
{
    bool ok = true;
    int i, j;

    i = 0;
    while (ok && i < TAILLE_GRILLE)
    {
        ok = testLigne(grille, i) && testColonne(grille, i);
        i++;
    }
    i = 0;
    while (ok && i < NBR_SOUS_GRILLE)
    {
        j = 0;
        while (ok && j < NBR_SOUS_GRILLE)
        {
            ok = testBlock(grille, i * TAILLE_SOUS_GRILLE, j * TAILLE_SOUS_GRILLE);
            j++;
        }
        i++;
    }

    return ok;
}

