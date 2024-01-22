#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../includes/defines.h"
#include "../includes/types.h"
#include "../includes/procedures.h"
#include "../includes/techniques.h"


int nbOccurenceCandidatLigne(grille_t grille, int numLigne, int candidat)
{
    int nbOccurence = 0;

    for (int numCol = 0; numCol < TAILLE_GRILLE; numCol++)
    {
        if (grille[numLigne][numCol].c_candidats[candidat])
        {
            nbOccurence++;
        }
    }

    return nbOccurence;
}


int nbOccurenceCandidatColonne(grille_t grille, int numCol, int candidat)
{
    int nbOccurence = 0;

    for (int numLigne = 0; numLigne < TAILLE_GRILLE; numLigne++)
    {
        if (grille[numLigne][numCol].c_candidats[candidat])
        {
            nbOccurence++;
        }
    }

    return nbOccurence;
}


int nbOccurenceCandidatBlock(grille_t grille, int numLigne, int numCol, int candidat)
{
    int nbOccurence = 0;

    int coordonneeXBlock = (numLigne / NBR_SOUS_GRILLE) * NBR_SOUS_GRILLE;
    int coordonneeYBlock = (numCol / NBR_SOUS_GRILLE) * NBR_SOUS_GRILLE;

    for (int numLigneBlock = coordonneeXBlock; 
         numLigneBlock < coordonneeXBlock + TAILLE_SOUS_GRILLE; 
         numLigneBlock++)
    {
        for (int numColBlock = coordonneeYBlock;
             numColBlock < coordonneeYBlock + TAILLE_SOUS_GRILLE;
             numColBlock++)
        {
            if (grille[numLigneBlock][numColBlock].c_candidats[candidat])
            {
                nbOccurence++;
            }
        }
    }

    return nbOccurence;
}


void accepterCandidat(grille_t grille, int numLigne, int numCol, int candidat)
{
    //printf("accepterCandidat(grille, %d, %d, %d)\n", numLigne, numCol, candidat);

    grille[numLigne][numCol].c_valeur = candidat;

    retirerTousLesCandidat(&grille[numLigne][numCol]);

    for (int i = 0; i < TAILLE_GRILLE; i++)
    {
        retirerCandidat(&grille[numLigne][i], grille[numLigne][numCol].c_valeur);
        retirerCandidat(&grille[i][numCol], grille[numLigne][numCol].c_valeur);
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
            retirerCandidat(&grille[i][j], grille[numLigne][numCol].c_valeur);
            j++;
        }
        i++;
    }
}


void singletonNu(grille_t grille, int *nbCasesVide, bool *progression)
{
    //printf("technique du singleton nu\n");
    for (int numLigne = 0; numLigne < TAILLE_GRILLE; numLigne++)
    {
        for (int numCol = 0; numCol < TAILLE_GRILLE; numCol++)
        {
            if ((grille[numLigne][numCol].c_valeur == 0) &&
                (getNbCandidats(grille[numLigne][numCol]) == 1))
            {
                int candidat = 1;
                bool trouve = false;
                while (!trouve && candidat <= TAILLE_GRILLE + 1)
                {
                    if (grille[numLigne][numCol].c_candidats[candidat])
                    {
                        trouve = true;
                    }
                    else 
                    {
                        candidat++;
                    }
                }
                if (candidat >= TAILLE_GRILLE + 1)
                {
                    printf("Erreur\n");
                    continue; // passage au tour de boucle suivant : on ne veut pas accepter une valeur errone
                }
                accepterCandidat(grille, numLigne, numCol, candidat);
                (*nbCasesVide)--;
                *progression = true;
            }
        }
    }
}


void singletonCache(grille_t grille, int *nbCasesVide, bool *progression)
{
    //printf("technique du singleton cache\n");
    for (int numLigne = 0; numLigne < TAILLE_GRILLE; numLigne++)
    {
        for (int numCol = 0; numCol < TAILLE_GRILLE; numCol++)
        {
            for (int numCandidat = 1; numCandidat <= TAILLE_GRILLE; numCandidat++)
            {
                if (grille[numLigne][numCol].c_candidats[numCandidat])
                {
                    if ((nbOccurenceCandidatLigne(grille, numLigne, numCandidat) == 1) ||
                        (nbOccurenceCandidatColonne(grille, numCol, numCandidat) == 1) ||
                        (nbOccurenceCandidatBlock(grille, numLigne, numCol, numCandidat == 1))/**/)
                    {
                        accepterCandidat(grille, numLigne, numCol, numCandidat);
                        (*nbCasesVide)--;
                        *progression = true;
                    }
                }
            }
        }
    }
}


bool backtracking(grille_t grille, int numeroCase)
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
        if (grille[ligne][colonne].c_valeur != 0)
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
                    grille[ligne][colonne].c_valeur = valeur;
                    // ... et on passe à la suivante : appel récursif
                    // pour voir si ce choix est bon par la suite
                    if (backtracking(grille, numeroCase + 1))
                    {
                        result = true;
                    }
                    else
                    {
                        grille[ligne][colonne].c_valeur = 0;
                    }
                }
            }
        }
    }

    return result;
}
