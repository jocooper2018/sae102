#include <stdio.h>
#include <stdlib.h>

#include "../includes/defines.h"
#include "../includes/types.h"
#include "../includes/tests.h"

/**
 * @fn testLigne(grille_t grille, int numLigne)
 * @brief Vérifie qu'il n'y a pas deux fois la même 
 * valeur dans une ligne de grille de sudoku.
 * @param grille `grille_t` Grille de sudoku dans laquelle vérifier.
 * @param numLigne `int` Numéro de la ligne de la grille à vérifier.
 * @return `true` si il n'y a pas deux fois la même valeur dans la ligne, 
 * `false` sinon.
*/
bool testLigne(grille_t grille, int numLigne)
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
            if (grille[numLigne][numCol].c_valeur == valeur)
            {
                nbOcurencesValeur++;
            }
            if (nbOcurencesValeur > 1)
            {
                ok = false;
            }
            numCol++;
        }
        valeur++;
    }
    
    return ok;
}


/**
 * @fn testColonne(grille_t grille, int numCol)
 * @brief Vérifie qu'il n'y a pas deux fois la même 
 * valeur dans une colonne de grille de sudoku.
 * @param grille `grille_t` Grille de sudoku dans laquelle vérifier.
 * @param numCol `int` Numéro de la colonne de la grille à vérifier.
 * @return `true` si il n'y a pas deux fois la même valeur dans la colonne, 
 * `false` sinon.
*/
bool testColonne(grille_t grille, int numCol)
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
            if (grille[numLigne][numCol].c_valeur == valeur)
            {
                nbOcurencesValeur++;
            }
            if (nbOcurencesValeur > 1)
            {
                ok = false;
            }
            numLigne++;
        }
        valeur++;
    }
    
    return ok;
}


/**
 * @fn testBlock(grille_t grille, int numLigne, int numCol)
 * @brief Vérifie qu'il n'y a pas deux fois la même 
 * valeur dans un block de grille de sudoku.
 * @param grille `grille_t` Grille de sudoku dans laquelle vérifier.
 * @param numLigne `int` Numéro de la ligne de la grille à vérifier.
 * @param numCol `int` Numéro de la colonne de la grille à vérifier.
 * @return `true` si il n'y a pas deux fois la même valeur dans le block, 
 * `false` sinon.
*/
bool testBlock(grille_t grille, int numLigne, int numCol)
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
                if (grille[i][j].c_valeur == valeur)
                {
                    nbOcurencesValeur++;
                }
                if (nbOcurencesValeur > 1)
                {
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


/**
 * @fn testGrille(grille_t grille)
 * @brief Vérifie qu'une grille de sudoku respecte les règles du sudoku.
 * @param grille `grille_t` Grille de sudoku à vérifier.
 * @return `true` si la grille respecte les règles du sudoku, 
 * `false` sinon.
*/
bool testGrille(grille_t grille)
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

