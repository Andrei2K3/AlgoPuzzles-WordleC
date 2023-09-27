#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dictionary_entry
{
    char *word;
    int priority;
};

int substring(char *ss, char *s) /// returneaza 1 daca s incepe cu ss, altfel 0
{
    int i;
    for (i = 0; ss[i]; i++)
        if (ss[i] != s[i])
            return 0;
    return 1;
}

void creare_dictionar(int *N, int *Lg_dictionar, struct dictionary_entry **P)
{
    int i, lg_cuv;
    char cuv[21];
    // Citire N si cele N cuvinte
    scanf("%d", N);
    *Lg_dictionar = *N;
    *P = (struct dictionary_entry *)malloc(*Lg_dictionar * sizeof(**P));
    for (i = 0; i < *Lg_dictionar; i++)
    {
        scanf("%s", cuv);
        lg_cuv = strlen(cuv);
        (*(*P + i)).word = (char *)malloc((lg_cuv + 1) * sizeof(char));
        strcpy((*(*P + i)).word, cuv);
        (*(*P + i)).priority = 0;
    }
}

int cautare_cuv_asterix(int Lg_dictionar, char *cuv, struct dictionary_entry *P)
/// daca gasim cuv in dictionar ii incrementam prioritatea cu 1 si returnam 1, altfel 0
{
    int i;
    for (i = 0; i < Lg_dictionar; i++)
        if (strcmp(cuv, P[i].word) == 0) /// il gasim pe cuv in dictionar
        {
            P[i].priority++;
            return 1;
        }
    return 0;
}

void adaugare_cuvant_in_dictionar(int *Lg_dictionar, struct dictionary_entry **P, char *cuv, int lg_cuv)
{
    //Alocare memorie //Readme (*)
    *P = (struct dictionary_entry *)realloc(*P, (*Lg_dictionar + 1) * sizeof(**P));
    (*(*P+*Lg_dictionar)).word = (char *)malloc((lg_cuv + 1) * sizeof(char));
    //Adaugare cuvant
    strcpy((*(*P+*Lg_dictionar)).word, cuv);
    (*(*P+*Lg_dictionar)).priority = 1;
    *Lg_dictionar = *Lg_dictionar + 1;
}

int cautare_cuv(int Lg_dictionar, char *cuv, struct dictionary_entry *P, char *ans)
{
    int prioritate_maxima = -1, poz = -1, i;
    for (i = 0; i < Lg_dictionar; i++)
    {
        if (substring(cuv, P[i].word)) /// Am gasit cuvant in dictionar care incepe cu "cuv"
        {
            if (P[i].priority > prioritate_maxima)
            {
                poz = i;
                prioritate_maxima = P[i].priority;
                strcpy(ans, P[i].word);
            }
            else if (P[i].priority == prioritate_maxima)
            {
                if (strcmp(ans, P[i].word) > 0)
                {
                    strcpy(ans, P[i].word);
                    poz = i;
                }
            }
        }
    }
    if (poz != -1)
        P[poz].priority++;
    return poz;
}

void dealocare(struct dictionary_entry *P, int Lg_dictionar)
{
    int i;
    for (i = 0; i < Lg_dictionar; i++)
    {
        free(P[i].word);
    }
    free(P);
}

int main()
{
    // Initializare
    int N, Lg_Dictionar, M, i, lg_cuv;
    struct dictionary_entry *P;
    char cuv[21], ans[21];
    //
    creare_dictionar(&N, &Lg_Dictionar, &P);
    //
    // Citire M si cele M cuvinte si rezolvarea problemei
    scanf("%d", &M);
    for (i = 0; i < M; i++)
    {
        scanf("%s", cuv);
        /// cuv ori contine numai litere, ori numai caracterele ,.:!?
        /// => e suficient sa verific pentru cuv[0]
        if (!(cuv[0] >= 'a' && cuv[0] <= 'z'))
            printf("%s", cuv);
        else
        {
            lg_cuv = strlen(cuv);
            if (cuv[lg_cuv - 1] == '*') /// situatia a doua din enunt
            {
                cuv[lg_cuv - 1] = '\0';
                lg_cuv--;
                if (cautare_cuv_asterix(Lg_Dictionar, cuv, P) == 0) /// cuv nu apare in dictionar, trebuie sa-l adaugam
                {
                    adaugare_cuvant_in_dictionar(&Lg_Dictionar, &P,cuv,lg_cuv);
                }
                printf("%s", cuv);
            }
            else /// prima si a treia situatie
            {
                if (cautare_cuv(Lg_Dictionar, cuv, P, ans) != -1) /// Am gasit cuvant
                {
                    printf("%s", ans);
                }
                else /// N am gasit cuvinte care incep cu cuv in dictionar=>il adaugam
                {
                    adaugare_cuvant_in_dictionar(&Lg_Dictionar, &P,cuv,lg_cuv);
                    printf("%s", cuv);
                }
            }
        }
        printf(" ");
    }
    ///Readme (**)
    dealocare(P,Lg_Dictionar);
    return 0;
}