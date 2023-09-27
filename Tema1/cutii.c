#include <stdio.h>
#include <stdlib.h>

void read(int *Prisoners, int *Prisoners_div_2, int *Content_box)///Citire date
{
    int i;
    scanf("%d", Prisoners);
    *Prisoners_div_2 = *Prisoners / 2;
    for (i = 1; i <= *Prisoners; i++)
            scanf("%d",&Content_box[i]);
}

void task1(int Prisoners, int Prisoners_div_2, int *Content_Box)
{
    int i, j, ans = 1, steps;///ans=1, daca toti prizonierii pot evada
                             ///ans=0, daca exista unul care nu poate evada
    for (i = 1; i <= Prisoners && ans; i++)
    {
        j = i;
        steps = 0;
        while (Content_Box[j] != i)///Comparam continutul cutiei j cu i
        {
            steps++;
            if (steps == Prisoners_div_2)///deschidem cel mult Prisoners/2 cutii
                break;
            j = Content_Box[j];
        }
        if (Content_Box[j] != i)
            ans = 0;
    }
    if (ans)
        printf("Da\n");
    else
        printf("Nu\n");
}

void task2(int Prisoners, int *Content_Box, int *Counts)
{
    int i, j;
    for (i = 1; i <= Prisoners; i++)
        if (Counts[i] == 0)///Daca un prizonier face parte dintr un ciclu, 
                           ///automat nu va mai face parte din altul
        {
            j = i;
            Counts[j] = 1;
            printf("%d", j);
            while (Content_Box[j] != i)
            {
                j = Content_Box[j];
                printf(" %d", j);
                Counts[j] = 1;
            }
            printf("\n");
        }
}

int main()
{
    int Prisoners, Prisoners_div_2, Content_Box[501], Counts[501] = {0};
    //
    read(&Prisoners, &Prisoners_div_2, Content_Box);
    task1(Prisoners, Prisoners_div_2, Content_Box);
    task2(Prisoners, Content_Box, Counts);
    return 0;
}