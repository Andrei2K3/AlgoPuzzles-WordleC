#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap_int(int *a, int *b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}

void swap_char(char *a, char *b)
{
    char aux = *a;
    *a = *b;
    *b = aux;
}

void Initializare(char *litere) /// litere=abcd...xyzwABCD...XYZW
{
    int i;
    for (i = 0; i < 26; i++)///stim ca sunt 26 de litere mici in alfabet
        litere[i] = 'a' + i;
    for (i = 26; i < 52; i++)///stim ca sunt 26 de litere mari in alfabet
        litere[i] = 'A' + i - 26;
}

void CodificareA(char *s)
{
    //Initializare
    int lg_sir, lg_cheie, poz,///le folosesc pentru "s" si "cheie"
        mat[500][50], l, c, i, j,///l+1=nr linii,c=nr coloane ale lui mat
        index[50];///memorez pozitile caracterelor din cheie dupa sortare
        ///Exemplu: cheie=dcba,index[]={0,1,2,3} => cheie=abcd,index[]={3,2,1,0}
    char cheie[52]; /// maxim 50 de caractere + 1 caracter null + 1 caracter '\n'
    //Citire
    getchar(); /// sar peste spatiu
    fgets(cheie, 52, stdin);
    cheie[strlen(cheie) - 1] = '\0';
    //
    lg_sir = strlen(s);
    lg_cheie = strlen(cheie);
    l = 0;
    c = 0;
    //Construiesc matricea
    for (poz = 0; poz < lg_sir; poz++)
    {
        mat[l][c++] = s[poz];
        if (c == lg_cheie)
        {
            l++;
            c = 0;
        }
    }
    if (c == 0) /// daca ultimul element din s corespunde coltului dreapta jos in matrice
        l--;
    else
    {
        while (c < lg_cheie)///umplu celulele "nevizitate" de spatii
            mat[l][c++] = ' ';
        /// c--; <=> c=lg_cheie-1;
    }
    //Sortez lexicografic cheia
    for (i = 0; i < lg_cheie; i++)
        index[i] = i;
    for (i = 0; i < lg_cheie; i++)
        for (j = i + 1; j < lg_cheie; j++)
            if (cheie[i] > cheie[j])
            {
                swap_char(&cheie[i], &cheie[j]);
                swap_int(&index[i], &index[j]);
            }
    //Construiesc solutia
    lg_sir = 0;
    for (j = 0; j < lg_cheie; j++)
        for (i = 0; i <= l; i++)
            s[lg_sir++] = mat[i][index[j]];
    s[lg_sir] = '\0';
    //Afisare
    puts(s);
}

void DecodificareA(char *s)
{
    //Initializare
    int lg_sir, lg_cheie, poz,
        mat[500][50], l, c, i, j,
        index[50], index_dec[50];//index are aceeasi semnificatie ca la functia
    ///CodificareA; index_dec[i]=pe ce pozitie se afla i in index[i]
    ///Exemplu index[]={1,3,5,4,0,2} => index_dec[]={4,0,5,1,3,2}
    char cheie[52]; /// maxim 50 de caractere + 1 caracter null + 1 caracter '\n'
    //Citire
    getchar(); /// sar peste spatiu
    fgets(cheie, 52, stdin);
    cheie[strlen(cheie) - 1] = '\0';
    //
    lg_cheie = strlen(cheie);
    lg_sir = strlen(s);
    //Determin dimensiunile matricei pe care o indexez de la 0
    c = lg_cheie - 1;
    l = lg_sir / lg_cheie;
    if (lg_sir % lg_cheie != 0)
        l++;
    l--; /// indexare de la 0
    //Umplu mat de spatii
    for (i = 0; i <= l; i++)
        for (j = 0; j <= c; j++)
            mat[i][j] = ' ';
    //Construiesc matricea
    i = 0;
    j = 0;
    for (poz = 0; poz < lg_sir; poz++)
    {
        mat[i++][j] = s[poz];
        if (i == l + 1)
        {
            i = 0;
            j++;
        }
    }
    //Sortez lexicografic cheia
    for (i = 0; i < lg_cheie; i++)
        index[i] = i;
    for (i = 0; i < lg_cheie; i++)
        for (j = i + 1; j < lg_cheie; j++)
            if (cheie[i] > cheie[j])
            {
                swap_char(&cheie[i], &cheie[j]);
                swap_int(&index[i], &index[j]);
            }
    //Construiesc index_dec[]
    poz = 0;
    for (j = 0; j < lg_cheie; j++)
        for (i = 0; i < lg_cheie; i++)
            if (index[i] == j)
            {
                index_dec[poz++] = i;
                break;
            }
    //Construiesc solutia
    poz = 0;
    for (i = 0; i <= l; i++)
        for (j = 0; j <= c; j++)
            s[poz++] = mat[i][index_dec[j]];
    s[poz] = '\0';
    //Afisare
    puts(s);
}

void CodificareB(char *s)
{
    //Initializare
    int deplasare, B, i;
    char aux[501], litere_CodifB[53];
    Initializare(litere_CodifB); /// litere_CodifB memoreaza "crescator"(NU lexicografic,
    /// deoarece consider ca literele mici sunt in fata celor mari) toate literele.
    //Citire
    scanf("%d", &B);
    //Fac prima parte a codificarii
    strcpy(aux, s + strlen(s) - B);
    strncat(aux, s, strlen(s) - B);
    strcpy(s, aux);
    //Fac a doua parte a codificarii
    for (i = 0; i < B; i++)
        if (s[i] != ' ') /// Daca e litera
        {
            ///deplasare=pozitia in litere_CodifB corespunzatoare lui s[i]
            if (s[i] >= 'a' && s[i] <= 'z')
                deplasare = s[i] - 'a';
            else
                deplasare = s[i] - 'A' + 26;
            s[i] = litere_CodifB[(deplasare + B) % 52];
            ///(deplasare+B)%52=ma deplasez cu B pozitii la dreapta
        }
    //Afisare
    puts(s);
}

void DecodificareB(char *s)
{
    //Initializare
    int deplasare, B, i;
    char aux[501], litere_CodifB[53];
    Initializare(litere_CodifB); /// litere_CodifB memoreaza "crescator"(NU lexicografic,
    ///deoarece consider ca literele mici sunt in fata celor mari) toate literele.
    //Citire
    scanf("%d", &B);
    //Fac a doua parte a codificarii <=> Fac prima parte a DEcodificarii
    for (i = 0; i < B; i++)
        if (s[i] != ' ') /// daca e litera
        {
            ///deplasare=pozitia in litere_CodifB corespunzatoare lui s[i]
            if (s[i] >= 'a' && s[i] <= 'z')
                deplasare = s[i] - 'a';
            else
                deplasare = s[i] - 'A' + 26;
            deplasare -= B;
            while (deplasare < 0)
                deplasare += 52;
            ///m-am deplasat cu B pozitii la stanga
            s[i] = litere_CodifB[deplasare];
        }
    //Fac prima parte a codificarii <=> Fac a doua parte a DEcodificarii
    strcpy(aux, s + B);
    strncat(aux, s, B);
    strcpy(s, aux);
    //Afisare
    puts(s);
}

int main()
{
    char s[502], codificare[15];
    /// fgets pune si '\n' in s, de aceea dimensiunea lui poate fi maxim 502
    fgets(s, 502, stdin);
    s[strlen(s) - 1] = '\0'; /// elimin '\n'
    scanf("%s", codificare);
    while (strcmp(codificare, "STOP"))
    {
        if (strcmp(codificare, "CodificareA") == 0)
            CodificareA(s);
        else if (strcmp(codificare, "DecodificareA") == 0)
            DecodificareA(s);
        else if (strcmp(codificare, "CodificareB") == 0)
            CodificareB(s);
        else /// if(strcmp(codificare,"DecodificareB") == 0)
            DecodificareB(s);
        //
        scanf("%s", codificare);
    }
    return 0;
}