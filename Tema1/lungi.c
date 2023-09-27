#include <stdio.h>
#include <stdlib.h>

void Adunare(int A[], int B[])
{
    /// Calculam A <-- A+B, rezultatul este trunchiat
    /// la cele mai putin semnificative cifre
    int i, T = 0;
    for (i = 1; i <= A[0]; i++)
    {
        T += A[i] + B[i];
        A[i] = T % 10;
        T /= 10;
    }
}

void Scadere(int A[], int B[])
{
    /// Calculam A <-- A-B, A >= B, rezultatul este trunchiat
    /// la cele mai putin semnificative cifre
    int i, T = 0;
    for (i = 1; i <= A[0]; i++)
    {
        A[i] -= B[i] + T;
        if (A[i] < 0)
        {
            A[i] += 10;
            T = 1;
        }
        else
            T = 0;
    }
}

int Comparare(int A[], int B[])
{
    /** Functia returneaza 1, daca A>B
                           0, daca A=B
                          -1, daca A<B
    */
    int i;
    for (i = A[0]; i > 0; i--)
        if (A[i] > B[i])
            return 1;
        else if (A[i] < B[i])
            return -1;
    return 0;
}

void Copiere(int A[], int B[]) /// A <-- B
{
    int i;
    A[0] = B[0];
    for (i = 1; i <= A[0]; i++)
        A[i] = B[i];
}

void Afisare(int A[])
{
    int i;
    for (i = A[0]; i > 0; i--)
        printf("%d", A[i]);
}

void Citire_numar_complex(int N, int *bit_real, int *bit_im, int *R, int *Im)
{
    int i, poz;
    char s[2020];
    scanf("%s", s);///Citim numarul complex ca sir
    *bit_real = s[0] - '0';
    *bit_im = s[N / 2] - '0';
    //
    poz = 0;
    for (i = N / 2 - 1; i >= 1; i--)///memoram in R partea reala cu 
        R[++poz] = s[i] - '0';///toate zerourile necesare ca "numar mare"
    R[0] = N / 2 - 1;
    poz = 0;
    for (i = N - 2; i > N / 2; i--)///memoram in Im partea imaginara cu 
        Im[++poz] = s[i] - '0';///toate zerourile necesare ca "numar mare"
    Im[0] = N / 2 - 1;
}

void operatii(int *bit_last, int *bit_current, int *last, int *current)
///functia primeste ca parametrii fie partile reale a doua numere complexe,
///fie partile imaginare ale acestor doua numere complexe
{
    int comp;
    if (*bit_last == 1 && *bit_current == 1)///daca cele doua numere sunt negative
            Adunare(last, current); /// *bit_last=1
        else if (*bit_last == 1 && *bit_current == 0)
        ///daca primul e negativ, al doilea pozitiv
        {
            comp = Comparare(last, current);
            if (comp > 0)
                Scadere(last, current);
            else
            {
                *bit_last = 0;
                Scadere(current, last);
                Copiere(last, current);
            }
        }
        else if (*bit_last == 0 && *bit_current == 1)
        ///daca primul e pozitiv, al doilea negativ
        {
            comp = Comparare(last, current);
            if (comp >= 0)
                Scadere(last, current);
            else
            {
                *bit_last = 1;
                Scadere(current, last);
                Copiere(last, current);
            }
        }
        else /// if (bit_last == 0 && bit_current == 0)
        ///daca ambele numere sunt pozitive
        {
            Adunare(last, current); /// R_bit_last=0
        }
}

int main()
{
    int N,
        R_bit_last, Im_bit_last, R_bit_current, Im_bit_current,
        R_last[1010], Im_last[1010], R_current[1010], Im_current[1010];
    char semn;
    scanf("%d", &N);
    ///Citesc primul numar complex
    Citire_numar_complex(N, &R_bit_last, &Im_bit_last, R_last, Im_last);
    //
    while ((getchar()) != '\n')///golesc buffer ul
        ;
    scanf("%c", &semn);
    while (semn != '0')
    {
        ///Citesc un nou numar complex
        Citire_numar_complex(N, &R_bit_current, &Im_bit_current, R_current, Im_current);
        //Actualizez valoarea primului numar citit in urma operatiilor 
        //cu al doilea, al treilea ...
        if (semn == '-')///fac un artificiu, daca semnul e '-',
                        ///atunci numarul complex curent z devine -z
        {
            R_bit_current = 1 - R_bit_current;
            Im_bit_current = 1 - Im_bit_current;
        }
        operatii(&R_bit_last,&R_bit_current,R_last,R_current);
        operatii(&Im_bit_last,&Im_bit_current,Im_last,Im_current);
        //Afisare
        printf("%d", R_bit_last);
        Afisare(R_last);
        printf("%d", Im_bit_last);
        Afisare(Im_last);
        printf("\n");
        //
        while ((getchar()) != '\n')
            ;
        scanf("%c", &semn);
    }
    return 0;
}