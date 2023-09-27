#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void task1(char **comb, int N, int *ans)
{
    int i;
    for (i = 0; i < N; i++)
        ans[comb[i][0] - 'a']++;
}

void task2(int N, char **brand, char **combustibil, double *consum, int *km, int *Ap, double *Consum_total, double *Pret)
{
    int i, j, val = 0;
    double consum_curent;
    for (i = 0; i < N; i++)
        if (Ap[i] == 0)
        {
            val++;
            Ap[i] = val;
            for (j = i; j < N; j++)
                if (strcmp(brand[i], brand[j]) == 0)
                {
                    Ap[j] = val;
                    consum_curent = (double)((consum[j] * km[j]) / 100);
                    Consum_total[i] += consum_curent;
                    if (strcmp(combustibil[j], "motorina") == 0)
                        Pret[i] += (double)(consum_curent * 9.29);
                    else if (strcmp(combustibil[j], "benzina") == 0 || strcmp(combustibil[j], "hibrid") == 0)
                        Pret[i] += (double)(consum_curent * 8.02);
                }
        }
}

int litera(char c)
{
    if (c >= 'A' && c <= 'Z')
        return 1;
    return 0;
}

int cifra(char c)
{
    if (c >= '0' && c <= '9')
        return 1;
    return 0;
}

void task3(int N, char **nr, int *ans)
{
    int i, ok, lg_nr;
    ans[0] = 0;
    for (i = 0; i < N; i++)
    {
        ok = 1;
        lg_nr = strlen(nr[i]);
        if (lg_nr < 6) /// daca lungimea numarului < 6 => e invalid
            ok = 0;
        else
        {
            if (!litera(nr[i][0]))
                ok = 0;
            else /// primul caracter e litera
            {
                if (litera(nr[i][1])) /// primele 2 caractere sunt litere
                {
                    if (cifra(nr[i][2]) && cifra(nr[i][3])) /// 2litere+2cifre
                    {
                        if (cifra(nr[i][4])) /// 2litere+3cifre
                        {
                            if (lg_nr == 8 && litera(nr[i][5]) && litera(nr[i][6]) && litera(nr[i][7]))
                            {
                            } /// e valid
                            else
                                ok = 0;
                        }
                        else if (litera(nr[i][4])) /// 2litere+2cifre
                        {
                            if (lg_nr == 7 && litera(nr[i][5]) && litera(nr[i][6]))
                            {
                            } /// e valid
                            else
                                ok = 0;
                        }
                        else
                            ok = 0;
                    }
                    else
                        ok = 0;
                }
                else // primul caracter e litera
                {
                    if (cifra(nr[i][1]) && cifra(nr[i][2])) /// 1litera+2cifre
                    {
                        if (cifra(nr[i][3])) /// 1litera+3cifre
                        {
                            if (lg_nr == 7 && litera(nr[i][4]) && litera(nr[i][5]) && litera(nr[i][6]))
                            {
                            } /// e valid
                            else
                                ok = 0;
                        }
                        else if (litera(nr[i][3]))/// 1litera+2cifre
                        {
                            if (lg_nr == 6 && litera(nr[i][4]) && litera(nr[i][5]))
                            {
                            } /// e valid
                            else
                                ok = 0;
                        }
                        else
                            ok = 0;
                    }
                    else
                        ok = 0;
                }
            }
        }
        if(!ok)
            ans[++ans[0]]=i;
    }
}

int main()
{
    int N, i, val_curenta,
        ans_task_a[26] = {0}; /// pentru Cerinta a): fac un artificiu, ans_task_a
    /// memoreaza frecventa literelor de la 'a' la 'z' --> in practica ma intereseaza
    /// doar frecventa literelor 'b'(benzina),'m'(motorina),'h'(hibrid),'e'(electric)
    double *Consum_total, *Pret;  /// cerinta b)
    int *Aparitii;                /**pentru Cerinta b):Pe exemplul 2 Aparitii[0]=Aparitii[1]=Aparitii[3]=1,
                                  Aparitii[2]=Aparitii[4]=2, adica marchez cu o valoare toate aparitiile lu' "Toyota",
                                  apoi marchez cu valoare+1 aparitiile lu' "Renault", apoi(nu in exemplul acesta) ...
                                  valoare+2 etc */
    int *Ans;/// cerinta c):in Ans retinem pozitile numerelor invalide si Ans[0]=numarul pozitiilor
    char **brand, **numar, **combustibil, sir[21], cerinta;
    double *consum;
    int *km;
    // Citire
    scanf("%d", &N);
    Ans=(int *)malloc((N+1)*sizeof(int));
    // Alocam dinamic memoria
    brand = (char **)malloc(N * sizeof(char *));
    numar = (char **)malloc(N * sizeof(char *));
    combustibil = (char **)malloc(N * sizeof(char *));
    consum = (double *)malloc(N * sizeof(double));
    km = (int *)malloc(N * sizeof(int));
    Aparitii = (int *)calloc(N, sizeof(int));
    Consum_total = (double *)calloc(N, sizeof(double));
    Pret = (double *)calloc(N, sizeof(double));
    //Citire
    for (i = 0; i < N; i++)
    {
        scanf("%s", sir);
        *(brand + i) = (char *)malloc((strlen(sir) + 1) * sizeof(char));
        strcpy(brand[i], sir);
        //
        scanf("%s", sir);
        numar[i] = (char *)malloc((strlen(sir) + 1) * sizeof(char));
        strcpy(numar[i], sir);
        //
        scanf("%s", sir);
        combustibil[i] = (char *)malloc((strlen(sir) + 1) * sizeof(char));
        strcpy(combustibil[i], sir);
        //
        scanf("%lf%d", consum + i, km + i);
        //
    }
    while ((getchar()) != '\n')/// golesc buffer-ul
        ; 
    scanf("%c", &cerinta);
    //Rezolvare
    if (cerinta == 'a')
    {
        task1(combustibil, N, ans_task_a);
        printf("benzina - %d\n", ans_task_a['b' - 'a']);
        printf("motorina - %d\n", ans_task_a['m' - 'a']);
        printf("hibrid - %d\n", ans_task_a['h' - 'a']);
        printf("electric - %d\n", ans_task_a['e' - 'a']);
    }
    else if (cerinta == 'b')
    {
        task2(N, brand, combustibil, consum, km, Aparitii, Consum_total, Pret);
        val_curenta = 1;
        for (i = 0; i < N; i++)
        {
            if (Aparitii[i] == val_curenta)
            {
                val_curenta++;
                printf("%s a consumat", brand[i]);
                ///Consum_2_zec = Consum_total[i] * 100;
                ///Pret_2_zec = Pret[i] * 100;
                printf(" %.2lf - %.2lf lei\n", Consum_total[i],Pret[i]);
            }
        }
    }
    else //if (cerinta == 'c')
    {
        task3(N, numar, Ans);
        if(Ans[0]==0)
            printf("Numere corecte!\n");
        else
        {
            for(i=1;i<=Ans[0];i++)
                printf("%s cu numarul %s: numar invalid\n",brand[Ans[i]],numar[Ans[i]]);
        }
    }
    return 0;
}