#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear_buffer()
{
    while ((getchar()) != '\n')
        ;
}

void citire(int *N, char ***vector)
{
    int i, lg_s;
    /// s memoreaza caracterele de pe o linie(maxim 100) + caracterul '\n' + caracterul '\0'
    char s[102];
    // Citire N
    scanf("%d", N);
    clear_buffer();
    // Citire linii
    *vector = (char **)malloc(*N * sizeof(char *));
    for (i = 0; i < *N; i++)
    {
        fgets(s, 102, stdin);
        lg_s = strlen(s);
        /// elimin caracterul '\n'
        s[lg_s - 1] = '\0';
        lg_s--;
        //
        *(*vector+i) = (char *)malloc((lg_s + 1) * sizeof(char));
        strcpy(*(*vector+i), s);
    }
}

void gasit(char *s, char *cheie, int poz, char *sub)
///daca "s" incepe cu un cuvant cheie, marchez in "sub" pozitiile
///corespunzatoare lui(din intreaga linie -> sub[poz+i]) cu '_'
{
    int i, j;
    //
    char Ap[101];
    ///initializez Ap cu un caracter != '_'; am ales ' '. Puteam pune ORICE.
    for (i = 0; i < 101; i++)
        Ap[i] = ' ';
    //
    i = 0, j = 0;
    while (cheie[i])
    {
        if (cheie[i] != ' ')
        {
            if (cheie[i] != s[j])
                return;
            Ap[j] = '_';
            i++;
            j++;
        }
        else /// cheie[i] e spatiu
        {
            if (cheie[i] != s[j])
                return;
            while (s[j] == ' ')///sar spatiile
            {
                Ap[j] = '_';
                j++;
            }
            i++;
        }
    }
    if (s[j] == ' ' || s[j] == '\0') /// s-a terminat cuvantul cheie
    {
        for (i = 0; i < j; i++)
            if (Ap[i] == '_')
                sub[poz + i] = '_';
        ///return;
    }
    return;
}

void afisare_linie(char *linie, char Chei[][9])
{
    int i, j;
    ///Initializez subliniat cu spatii si cu caracterul null
    char subliniat[101];
    for (i = 0; linie[i]; i++)
        subliniat[i] = ' '; /// marchez cu spatii
    subliniat[i] = '\0';
    //
    for (i = 0; linie[i]; i++)
        /// inceput de cuvant in "linie"
        if (i == 0 || (linie[i - 1] == ' ' && linie[i] != ' '))
        /// i-1 >=0, adica daca i=0 se executa prima conditie, altfel a doua cand i>=1
        {
            for (j = 0; j < 15; j++)
                gasit(linie + i, Chei[j], i, subliniat);
        }
    printf("%s\n%s\n", linie, subliniat);
}

void solve(int N, char **vec, char keywords[][9])
{
    int i;
    for (i = 0; i < N; i++)///analizez linie cu linie
    {
        afisare_linie(vec[i], keywords);
    }
}

void eliberare_memorie(char **vec, int N)
{
    int i;
    for (i = 0; i < N; i++)
        free(vec[i]);
    free(vec);
}

int main()
{
    //initializare
    int N;
    char **Vector, Cuvinte_cheie[][9] = {"first of", "for", "for each", "from", "in", 
    "is", "is a", "list of", "unit", "or", "while", "int", "float", "double", "string"};
    //Rezolvare
    citire(&N, &Vector);
    solve(N,Vector,Cuvinte_cheie);
    //Golire heap
    eliberare_memorie(Vector,N);
    return 0;
}