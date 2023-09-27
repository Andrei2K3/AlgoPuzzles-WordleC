#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>//pentru generare numar aleator
#include <ncurses.h>//jocul in consola
#include <unistd.h>//pentru sleep()

int citire_litera(WINDOW *w, int x, int y)
{
    noecho();//nu afisez caracterele pe care le citesc
    int caracter = mvwgetch(w, x, y);//citesc din pozitia de coordonate x,y
    refresh();
    wrefresh(w);
    return caracter;
}

void afisare_litera(WINDOW *w, int x, int y, int ch)
{
    mvwprintw(w, x, y, "%c", ch);//afisez caracterul ch in pozitia (x,y)
    refresh();
    wrefresh(w);
}

void citire_cuvant(WINDOW *w, int linie, char *cuv, int *ans)//ans=0 <=> citesc ':'
{
    int i = 1, ch;
    while (1)
    {
        ch = citire_litera(w, linie, i);
        if (ch == ':')
        {
            *ans = 0;
            return;
        }
        else if (ch == KEY_ENTER || ch == 10) /// ENTER
        {
            if (i < 6)
            {
                mvprintw(1, 30, "Cuvant incomplet");
                refresh();
                sleep(1);
                mvprintw(1, 30, "                ");
                refresh();
            }
            else//am terminat de citit cuvantul
            {
                cuv[5] = '\0';
                return;
            }
        }
        else if (ch == KEY_BACKSPACE || ch == 127 || ch == '\b') /// BACKSPACE
        {
            if (i > 1)
            {
                i--;
                mvwprintw(w, linie, i, "%c", ' ');
            }
        }
        else /// caracter "valid"
        {
            if (i < 6)
            {
                cuv[i - 1] = ch;
                afisare_litera(w, linie, i, ch);
                i++;
            }
        }
    }
    /// cuv[5] = '\0';
}

void colorare_litera(WINDOW *w, int x, int y, int optiune)
{
    use_default_colors();//dupa ce colorez un caracter, sa revina by default ce voi face in continuare
    start_color();
    //Definesc perechile
    init_pair(1, COLOR_GREEN, COLOR_WHITE);
    init_pair(2, COLOR_YELLOW, COLOR_WHITE);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    //
    wmove(w, x, y);//ma mut in pozitia (x,y)
    wchgat(w, 1, A_STANDOUT, optiune, NULL);//colorez acea pozitie cu "optiune"
    //Actualizez terminalul si fereastra
    refresh();
    wrefresh(w);
}

void colorare_cuvant(WINDOW *w, int linie, char *cuv_joc, char *cuv_citit)
{
    int i, j;
    for (i = 0; i < 5; i++)
        if (cuv_citit[i] == cuv_joc[i])
            colorare_litera(w, linie, i + 1, 1);//colorez verde
        else
        {
            for (j = 0; j < 5; j++)
                if (cuv_citit[i] == cuv_joc[j])
                {
                    break;
                }
            if (j < 5)
                colorare_litera(w, linie, i + 1, 2);//colorez galben
            else
                colorare_litera(w, linie, i + 1, 3);//colorez negru
        }
}

int citire_DNXJ(int x, int y) /// citire D sau N sau X sau J sau :
{
    echo();
    int caracter = mvgetch(x, y);
    refresh();
    return caracter;
}

void meniu_de_control(int *ans)
{
    mvprintw(1, 30, "Alegeti una dintre optiunile:");
    mvprintw(2, 30, "Pentru a incheia jocul apasati tasta X");
    mvprintw(3, 30, "Pentru a incepe un joc nou apasati tasta J");
    *ans = citire_DNXJ(4, 30); // ans='X' sau 'J' aici
    if (*ans == 'J')
        *ans = 1;
    else
        *ans = 0;
}

int main()
{
    char lista_cuvinte[][6] = {"arici", "atent", "baiat", "ceata", "debut", "peste", "fixat",
                               "hamac", "harta", "jalon", "jucam", "lacat", "magie", "nufar", "oaste", "perus", "rigle",
                               "roman", "sanie", "scris", "sonda", "texte", "tipar", "titan", "zebra", "vapor", "vatra"};
    char cuvant_joc[6], cuvant_citit[6];//cuvant_joc reprezinta cuvantul
    //ce trebuie ghicit, cuvant_citit reprezinta cuvantul introdus de la tastatura
    int i, ans = 1;
    while (ans)///ans=1 mai jucam un joc,ans=0 jocul s-a incheiat
    {
        srand(time(0));
        strcpy(cuvant_joc, lista_cuvinte[rand()%27]);//aleg un cuvant aleator
        //
        initscr();//creez consola/terminalul si initializez toate structurile de implementare
        /// cbreak();
        mvaddstr(0, 30, "WORDLE");//afisez incepand cu (0,30) string ul "WORDLE"
        WINDOW *win = newwin(9, 9, 1, 2);//creez o fereastra
        box(win, 0, 0);//o bordez cu '|' si '-'
        //Actualizez terminalul si fereastra
        refresh();
        wrefresh(win);
        //
        i = 0;
        while (ans && i < 6)//cat timp n-am citit ':' si mai pot citi cuvinte executa
        {
            citire_cuvant(win, 2 + i, cuvant_citit, &ans);
            if (ans)
            {
                colorare_cuvant(win, 2 + i, cuvant_joc, cuvant_citit);
                if (strcmp(cuvant_joc, cuvant_citit) == 0)
                    break;
                i++;
            }
        }
        if (ans)//daca n-am citit ':'(ori am citit 6 cuvinte si am pierdut jocul,
        //ori am citit un cuvant "castigator")
        {
            if (strcmp(cuvant_joc, cuvant_citit) == 0)//am castigat
            {
                mvprintw(1, 30, "Felicitari! Ati castigat!!!");
                mvprintw(2, 30, "Doriti sa jucati din nou? D/N?");
                ans = citire_DNXJ(3, 30);//D sau N sau :
                if (ans == ':')
                    meniu_de_control(&ans);
                else
                {
                    if (ans == 'N')
                        ans = 0;
                    else
                        ans = 1;
                }
            }
            else//am pierdut
            {
                mvprintw(1, 30, "Ati pierdut jocul... Cuvantul corect este: %s", cuvant_joc);
                ans = 0;
            }
        }
        else//am citit ':'
        {
            meniu_de_control(&ans);
        }
        refresh();
        sleep(3);//sta 3 secunde in sleep dupa care ori incepe joc nou, ori se inchide
        delwin(win);//stergem fereastra jocului curent
        endwin();
        for (i = 1; i <= 4; i++)//stergem mesajele afisate
            mvprintw(i, 30, "                                                                    ");
    }
    return 0;
}
