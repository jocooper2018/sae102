#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../includes/defines.h"
#include "../includes/types.h"
#include "../includes/procedures.h"


bool chargerGrille(grille_t grille)
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
                grille[numLigne][numCol].c_valeur = grilleTmp[numLigne][numCol];
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


void initialiserCandidats(grille_t grille)
{
    for (int numLigne = 0; numLigne < TAILLE_GRILLE; numLigne++)
    {                                                               // case
        for (int numCol = 0; numCol < TAILLE_GRILLE; numCol++)      
        {
            for (int i = 1; i <= TAILLE_GRILLE; i++)             // init
            {
                grille[numLigne][numCol].c_candidats[i] = false;
            }
            if (grille[numLigne][numCol].c_valeur == 0)               // case vide ?
            {
                for (int candidat = 1; candidat <= TAILLE_GRILLE; candidat++)   //
                {
                    if (possible(grille, numLigne, numCol, candidat))
                    {
                        ajouterCandidat(&(grille[numLigne][numCol]), candidat);
                        // printf("%d %d %d\n", numLigne+1, numCol+1, candidat);
                    }
                }
            }
        }
    }
}


int getNbCaseVides(grille_t grille)
{
    int nbCaseVides = 0;

    for (int numLigne = 0; numLigne < TAILLE_GRILLE; numLigne++)
    {
        for (int numCol = 0; numCol < TAILLE_GRILLE; numCol++)
        {
            if (grille[numLigne][numCol].c_valeur == 0)
            {
                nbCaseVides++;
            }
        }
    }

    return nbCaseVides;
}


void ajouterCandidat(case_t *laCase, int valeur)
{
    laCase->c_candidats[valeur] = true;
}


void retirerCandidat(case_t *laCase, int valeur)
{
    laCase->c_candidats[valeur] = false;
}


void retirerTousLesCandidat(case_t *laCase)
{
    for (int i = 1; i <= TAILLE_GRILLE; i++)
    {
        laCase->c_candidats[i] = false;
    }
}


bool estCandidat(case_t laCase, int valeur)
{
    bool _estCadidat = false;
    int i = 0;
    while (!_estCadidat && (i < TAILLE_GRILLE))
    {
        if (laCase.c_candidats[i])
        {
            _estCadidat = true;
        }
    }

    return _estCadidat;
}


int getNbCandidats(case_t laCase)
{
    int nbCandidats = 0;
    for (int i = 1; i <= TAILLE_GRILLE; i++)
    {
        if (laCase.c_candidats[i])
        {
            nbCandidats++;
        }
    }
    return nbCandidats;
}


/**
 * @fn void afficherGrille(grille_t grille)
 * @param grille `grille_t` Grille a afficher.
 * @brief Affiche la grille passe en parametre.
*/
void afficherGrille(grille_t grille)
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
            if (grille[i][j].c_valeur == 0)
            {
                printf("  . ");
            }
            else
            {
                printf(" %2d ", grille[i][j].c_valeur);
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
 * @fn bool possible(grille_t grille, int numLigne, int numColone, int valeur)
 * @param grille `grille_t` Grille dans laquelle on veut savoir si il est 
 * possible d'inserer une valeur.
 * @param numLigne `int` Numero de la ligne ou inserer une valeur.
 * @param numColone `int` Numero de la colone ou inserer une valeur.
 * @param valeur `int` Valeur a inserer.
 * @return `bool` `true` si il est possible d'inserer la valeur a l'emplacement 
 * donnee, `false` sinon.
 * @brief Permet de verifier si il est possible d'inserer une valeur a un 
 * certain emplacement d'une grille donnee sans enfreindre les regles du sudoku.
*/
bool possible(grille_t grille, int numLigne, int numColone, int valeur)
{
    bool peutInserer = true;
    int i, j;
    int iMax, jMax;

    // Verification sur la ligne et sur la colonne
    i = 0;
    while ((i < TAILLE_GRILLE) && peutInserer)
    {
        if ((grille[numLigne][i].c_valeur == valeur) ||
            (grille[i][numColone].c_valeur == valeur))
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
            if (grille[i][j].c_valeur == valeur)
            {
                peutInserer = false;
            }
            j++;
        }
        i++;
    }

    return peutInserer;
}

