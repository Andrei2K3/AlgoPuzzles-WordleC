#include <stdio.h>
#include <stdlib.h>

void biti_numar(unsigned int x, unsigned int biti_x[])///pune in biti_x bitii lui x
{
    int i;
    for (i = 0; i < 4; i++)
        biti_x[i] = ((x & (1 << i)) != 0 ? 1 : 0);
}

unsigned int Adunare(unsigned int a, unsigned int b)
{
    unsigned int biti_a[4], biti_b[4], i, biti_rez[4], rez = 0, tr = 0; // tr=transportul
    //
    biti_numar(a, biti_a);
    biti_numar(b, biti_b);
    //
    for (i = 0; i < 4; i++)
    {
        //Am explicat in README ce face urmatoare secventa de cod
        biti_rez[i] = (biti_b[i] ^ biti_a[i] ^ tr);
        if ((biti_a[i] & biti_b[i]) == 1)///if (biti_a[i] && biti_b[i])
        {
            tr = 1;
        }
        else
            tr = ((biti_b[i] | biti_a[i] | tr) ^ (biti_b[i] ^ biti_a[i] ^ tr));
    }
    //Construiesc rezultatul operatiei de adunare
    for (i = 0; i < 4; i++)
        rez = (rez | (biti_rez[i] << i));
    return rez;
}

unsigned int Interschimbare(unsigned int a, unsigned int b)
{
    unsigned int aux, poz1, poz2, biti_a[4], rez = 0, i;
    biti_numar(a, biti_a);
    poz1 = ((b & 12) >> 2);//fac o masca pentru primii 2 biti(de la stanga la dreapta) din b, adica 1100 = 12
    poz2 = (b & 3);//ultimii 2 biti din b => 0011 = 3
    // facem indexarea conform cerintei, adica de la stanga la dreapta
    poz1 = 3 - poz1;
    poz2 = 3 - poz2;
    //Interschimb pozitiile
    aux = biti_a[poz1];
    biti_a[poz1] = biti_a[poz2];
    biti_a[poz2] = aux;
    //Construiesc rezultatul operatiei de interschimbare
    for (i = 0; i < 4; i++)
        rez = (rez | (biti_a[i] << i));
    return rez;
}

void rotire_stanga(unsigned int biti[])///rotesc la stanga cu o pozitie vectorul biti
{
    unsigned int i, aux = biti[3];
    for (i = 3; i >= 1; i--)
        biti[i] = biti[i - 1];
    biti[0] = aux;
}

unsigned int Rotatie_la_stanga(unsigned int a, unsigned int b)
{
    unsigned int biti_a[4], i, rez = 0;
    biti_numar(a, biti_a);
    b = b % 4;///Pentru explicatie -> README
    for (i = 1; i <= b; i++)///Facem maxim 3 rotiri
        rotire_stanga(biti_a);
    //Construiesc rezultatul operatiei de Rotatie la stanga
    for (i = 0; i < 4; i++)
        rez = (rez | (biti_a[i] << i));
    return rez;
}

unsigned int Xor(unsigned int a, unsigned int b)
{
    unsigned int biti_a[4], biti_b[4], i, biti_rez[4], rez = 0;
    biti_numar(a, biti_a);
    biti_numar(b, biti_b);
    for (i = 0; i < 4; i++)
    {
        if ((biti_a[i] & biti_b[i]) == 1)
            biti_rez[i] = 0;
        else
            biti_rez[i] = (biti_a[i] | biti_b[i]);
    }
    //Construiesc rezultatul operatiei Xor
    for (i = 0; i < 4; i++)
        rez = (rez | (biti_rez[i] << i));
    return rez;
}

unsigned int (*ar[4])(unsigned int a, unsigned int b);///vector de pointeri la functii

int main()
{
    ar[0] = Adunare;
    ar[1] = Interschimbare;
    ar[2] = Rotatie_la_stanga;
    ar[3] = Xor;
    //
    unsigned int N, M, biti_M[32], primu, al_doilea, op;
    int i;
    scanf("%u%u", &N, &M);
    //
    N = N * 6 + 4;
    for (i = 0; i < N; i++)
        biti_M[i] = (M & (1 << i)) != 0 ? 1 : 0;
    primu = biti_M[N - 1] * 8 + biti_M[N - 2] * 4 + biti_M[N - 3] * 2 + biti_M[N - 4] * 1;
    for (i = N - 5; i >= 0; i -= 6)
    {
        op = biti_M[i] * 2 + biti_M[i - 1] * 1;
        al_doilea = biti_M[i - 2] * 8 + biti_M[i - 3] * 4 + biti_M[i - 4] * 2 + biti_M[i - 5] * 1;
        primu = (*ar[op])(primu, al_doilea);
    }
    printf("%u", primu);
    return 0;
}