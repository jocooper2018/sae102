#include <stdio.h>
#include <stdlib.h>

#include "../includes/defines.h"
#include "../includes/types1.h"
#include "../includes/tests_version1.h"


bool testLigne(t_grille1 grille, int numLigne)
{
    bool ok;
    int valeur;
    int nbOcurencesValeur;
    int numCol;

    ok = true;
    valeur = 1;
    
    while (ok && (valeur <= TAILLE_GRILLE))
    {
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
            }
            numCol++;
        }
        valeur++;
    }
    
    return ok;
}


bool testColonne(t_grille1 grille, int numCol)
{
    bool ok;
    int valeur;
    int nbOcurencesValeur;
    int numLigne;

    ok = true;
    valeur = 1;
    
    while (ok && (valeur <= TAILLE_GRILLE))
    {
        numLigne = 0;
        while (ok && (numLigne < TAILLE_GRILLE))
        {
            if (grille[numLigne][numCol].valeur == valeur)
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


bool testBlock(t_grille1 grille, int numLigne, int numCol)
{
    bool ok = true;

    int i, iMax;
    int j, jMax;

    //

    return ok;
}


bool testCase(t_grille1 grille, int numLigne, int numCol)
{
    return testLigne(grille, numLigne) && testColonne(grille, numCol) && testBlock(grille, numLigne, numCol);
}


bool testGrille(t_grille1 grille)
{
    bool ok = true;
    int numLigne;
    int numCol;

    numLigne = 0;

    while (ok && (numLigne < TAILLE_GRILLE))
    {
        numCol = 0;

        while (ok && (numCol < TAILLE_GRILLE))
        {
            ok = testCase(grille, numLigne, numCol);
            numCol++;
        }
        numLigne++;
    }

    return ok;
}

