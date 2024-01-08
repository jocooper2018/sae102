#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../includes/defines.h"
#include "../includes/types2.h"
#include "../includes/procedures_version2.h"
#include "../includes/techniques_version2.h"


int nbOccurenceCandidatLigne(t_grille2 grille, int numLigne, int candidat)
{
    int nbOccurence = 0;

    for (int numCol = 0; numCol < TAILLE_GRILLE; numCol++)
    {
        int nbCandidats = getNbCandidats(grille[numLigne][numCol]);
        for (int i = 0; i < nbCandidats; i++)
        {
            if (grille[numLigne][numCol].candidats[i] == candidat)
            {
                nbOccurence++;
            }
        }
    }

    return nbOccurence;
}


int nbOccurenceCandidatColonne(t_grille2 grille, int numCol, int candidat)
{
    int nbOccurence = 0;

    for (int numLigne = 0; numLigne < TAILLE_GRILLE; numLigne++)
    {
        int nbCandidats = getNbCandidats(grille[numLigne][numCol]);
        for (int i = 0; i < nbCandidats; i++)
        {
            if (grille[numLigne][numCol].candidats[i] == candidat)
            {
                nbOccurence++;
            }
        }
    }

    return nbOccurence;
}


int nbOccurenceCandidatBlock(t_grille2 grille, int numLigne, int numCol, int candidat)
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
            int nbCandidats = getNbCandidats(grille[numLigne][numCol]);
            for (int i = 0; i < nbCandidats; i++)
            {
                if (grille[numLigneBlock][numColBlock].candidats[i] == candidat)
                {
                    nbOccurence++;
                }
            }
        }
    }

    return nbOccurence;
}


void accepterCandidat(t_grille2 grille, int numLigne, int numCol, int candidat)
{
    grille[numLigne][numCol].valeur = candidat;

    retirerTousLesCandidat(&grille[numLigne][numCol]);

    for (int i = 0; i < TAILLE_GRILLE; i++)
    {
        retirerCandidat(&grille[numLigne][i], grille[numLigne][numCol].valeur);
        retirerCandidat(&grille[i][numCol], grille[numLigne][numCol].valeur);
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
            retirerCandidat(&grille[i][j], grille[numLigne][numCol].valeur);
            j++;
        }
        i++;
    }
}


void singletonNu(t_grille2 grille, int *nbCasesVide, bool *progression)
{
    // technique du singleton nu
    for (int numLigne = 0; numLigne < TAILLE_GRILLE; numLigne++)
    {
        for (int numCol = 0; numCol < TAILLE_GRILLE; numCol++)
        {
            if ((grille[numLigne][numCol].valeur == 0) &&
                (getNbCandidats(grille[numLigne][numCol]) == 1))
            {
                accepterCandidat(grille, numLigne, numCol, grille[numLigne][numCol].candidats[0]);
                (*nbCasesVide)--;
                *progression = true;
            }
        }
    }
}


void singletonCache(t_grille2 grille, int *nbCasesVide, bool *progression)
{
    int candidat;

    for (int numLigne = 0; numLigne < TAILLE_GRILLE; numLigne++)
    {
        for (int numCol = 0; numCol < TAILLE_GRILLE; numCol++)
        {
            int nbCandidats = getNbCandidats(grille[numLigne][numCol]);
            for (int numCandidat = 0; numCandidat < nbCandidats; numCandidat++)
            {
                candidat = grille[numLigne][numCol].candidats[numCandidat];
                if ((nbOccurenceCandidatLigne(grille, numLigne, candidat) == 1) ||
                    (nbOccurenceCandidatColonne(grille, numCol, candidat) == 1) ||
                    (nbOccurenceCandidatBlock(grille, numLigne, numCol, candidat == 1)))
                {
                    accepterCandidat(grille, numLigne, numCol, candidat);
                    (*nbCasesVide)--;
                    *progression = true;
                }
            }
        }
    }
}

