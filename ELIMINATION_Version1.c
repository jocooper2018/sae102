#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAILLE_SOUS_GRILLE 3
#define TAILLE_GRILLE (TAILLE_SOUS_GRILLE*TAILLE_SOUS_GRILLE)
#define NBR_SOUS_GRILLE TAILLE_SOUS_GRILLE

typedef struct
{
    int valeur;
    int candidats[TAILLE_GRILLE];
    int nbCandidats;
} t_case1;

typedef t_case1 t_grille[TAILLE_GRILLE][TAILLE_GRILLE];

bool chargerGrille(t_grille grille);
void initialiserCandidats(t_grille grille);
int getNbCaseVides(t_grille grille);
void ajouterCandidat(t_case1 *laCase, int valeur);
void retirerCandidat(t_case1 laCase, int valeur);
bool estCandidat(t_case1 laCase, int valeur);
int nbCandidats(t_case1 laCase);
void afficherGrille(t_grille grille);
bool possible(t_grille grille, int numLigne, int numColone, int valeur);


int main()
{
    t_grille grille;
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
    t_grille grille;
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


bool chargerGrille(t_grille grille)
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


void initialiserCandidats(t_grille grille)
{
    for (int numLigne = 0; numLigne < TAILLE_GRILLE; numLigne++)
    {
        for (int numCol = 0; numCol < TAILLE_GRILLE; numCol++)
        {
            grille[numLigne][numCol].nbCandidats = 0;
            if (grille[numLigne][numCol].valeur == 0)
            {
                for (int i = 0; i < TAILLE_GRILLE; i++)
                {
                    grille[numLigne][numCol].candidats[i] = 0;
                }
                for (int candidat = 1; candidat <= TAILLE_GRILLE; candidat++)
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


int getNbCaseVides(t_grille grille)
{
    int nbCaseVides = 0;

    for (int numLigne = 0; numLigne < TAILLE_GRILLE; numLigne++)
    {
        for (int numCol = 0; numCol < TAILLE_GRILLE; numCol++)
        {
            if (grille[numLigne][numCol].valeur == 0)
            {
                nbCaseVides++;
            }
        }
    }

    return nbCaseVides;
}


void ajouterCandidat(t_case1 *laCase, int valeur)
{
    laCase->candidats[laCase->nbCandidats] = valeur;
    laCase->nbCandidats++;
}


void retirerCandidat(t_case1 laCase, int valeur)
{
    int i = 0;
    while ((laCase.candidats[i] != valeur) && (i < TAILLE_GRILLE))
    {
        i++;
    }
    if (i < TAILLE_GRILLE)
    {
        while (i < TAILLE_GRILLE - 1)
        {
            laCase.candidats[i] = laCase.candidats[i + 1];
            i++;
        }
        laCase.nbCandidats--;
    }
}


bool estCandidat(t_case1 laCase, int valeur)
{
    bool _estCadidat = false;
    int i = 0;
    while (!_estCadidat && (i < TAILLE_GRILLE))
    {
        if (laCase.candidats[i] == valeur)
        {
            _estCadidat = true;
        }
    }

    return _estCadidat;
}


int nbCandidats(t_case1 laCase)
{
    return laCase.nbCandidats;
}


/**
 * @fn void afficherGrille(t_grille grille)
 * @param grille `t_grille` Grille a afficher.
 * @brief Affiche la grille passe en parametre.
*/
void afficherGrille(t_grille grille)
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


/**
 * @fn bool possible(t_grille grille, int numLigne, int numColone, int valeur)
 * @param grille `t_grille` Grille dans laquelle on veut savoir si il est 
 * possible d'inserer une valeur.
 * @param numLigne `int` Numero de la ligne ou inserer une valeur.
 * @param numColone `int` Numero de la colone ou inserer une valeur.
 * @param valeur `int` Valeur a inserer.
 * @return `bool` `true` si il est possible d'inserer la valeur a l'emplacement 
 * donnee, `false` sinon.
 * @brief Permet de verifier si il est possible d'inserer une valeur a un 
 * certain emplacement d'une grille donnee sans enfreindre les regles du sudoku.
*/
bool possible(t_grille grille, int numLigne, int numColone, int valeur)
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

