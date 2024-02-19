**Tema 2**
**Ciucan Andrei-Alexandru**
**Grupa 313CC**

## Table of Contents

- [1. Text Highlight](#1-text-highlight)
- [2. Autocomplete](#2-autocomplete)
- [3. Calculator pe biti](#3-calculator-pe-biti)
- [4. WORDLE](#4-wordle)

## 1. Text Highlight
```
    In rezolvarea problemei am memorat in "Vector" cele N linii.
    Am parcurs fiecare linie astfel:
    -ma deplasez de la stanga la dreapta(in functia afisare_linie())
si cand sunt la inceputul unui cuvant apelez functia gasit() care va marca in
vectorul "subliniat" cu '_' daca am gasit un keyword care incepe pe linie de
la acea pozitie.
    
    Exemplu:
1
first     of all this   is my string

Apelez gasit() pentru:

first     of all this   is my string -> (gaseste first     of)
of all this   is my string
all this   is my string
this   is my string
is my string -> (gaseste is)
my string
string  -> (gaseste string)
------------------------------------------------------------------------------
    Am avut dificultati in a implementa functia gasit().
------------------------------------------------------------------------------
    Timp de rezolvare al problemei:
    2 ore
```


## 2. Autocomplete
```
    In rezolvarea problemei am memorat Dictionarul in P.
    Am facut functie in care se memoreaza in dictionar primele N cuvinte, urmand
ca mai apoi, odata cu citirea celor M cuvinte sa facem si rezolvarea efectiva a problemei.
    Distingem cele 3 cazuri din enuntul problemei(respectiv cuvant, cuvant*, cuv):
    -pe cuvant* il tratam separat, iar pe cuvant si cuv impreuna(ori gasim in dictionar 
cuvinte de forma "\bcuv[a-zA-Z]*", ori adaugam in dictionar "cuvant")
------------------------------------------------------------------------------
    Am avut dificultati in a aloca si a dealoca memoria.
------------------------------------------------------------------------------
    Pentru a evita posibilele fragmentari ale memoriei, deoarece folosim realloc
de foarte multe ori(in acest caz, asa este specificat in restrictiile problemei
"Folosiți alocarea şi realocarea dinamică pentru dicționarul de cuvinte, astfel încât să
nu existe memorie nefolosită!"), puteam face astfel:
    //Corespunzator lui Readme (*)
    if (*Lg_Dictionar % *N == 0)
    {
        *P = (struct dictionary_entry *) realloc(*P, (*Lg_dictionar + *N) * sizeof(**P));
    }
    iar la final sa realocam cat ne este necesar si suficient
    //Corespunzator lui Readme (**)
    P = (struct dictionary_entry *) realloc(P, Lg_Dictionar * sizeof(*P));
------------------------------------------------------------------------------
    Timp de rezolvare al problemei:
    3 ore
```


## 3. Calculator pe biti
```
    IMPLEMENTARE FUNCTIA ADUNARE:
    Memoram in biti_a, biti_b cei 4 biti ai lui a, respectiv ai lui b.
    tr memoreaza transportul.
    Pentru un i arbitrar ales avem situatiile:
    tr biti_a[i] biti_b[i] ==>  tr_nou      biti_rez[i]
    0      0        0             0             0
    0      0        1             0             1
    0      1        0             0             1
    0      1        1             1             0

    1      0        0             0             1
    1      0        1             1             0
    1      1        0             1             0
    1      1        1             1             1
    Observam ca:
    -biti_rez[i]=(biti_b[i] ^ biti_a[i] ^ tr);
    -tr = ((biti_b[i] | biti_a[i] | tr) ^ (biti_b[i] ^ biti_a[i] ^ tr));
se observa ca aceasta formula este valabila pe toate cazurile, mai putin
atunci cand biti_a[i] = biti_b[i] = 1 => acest caz il tratam separat, iar tr=1
------------------------------------------------------------------------------
    IMPLEMENTARE FUNCTIA INTERSCHIMBARE:
    Memoram in biti_a cei 4 biti ai lui a.
    Extragem din b primii 2 biti, respectiv ultimii 2 biti astfel:
    b(10)=000...00abcd(scriere in binar a tipului unsigned int)
    Primii 2 biti ai lui b conform enuntului sunt ab. Pentru a-i extrage
este suficient sa facem (b & 12)>>2 (Explicatie:12 = 000...001100, b & 12 = 000...00ab00,
(b&12)>>2=000...0000ab).
    Ultimii 2 biti ai lui b conform enuntului sunt cd. Pentru a-i extrage
este suficient sa facem b & 3 (Explicatie: 3 = 000...000011, b & 3 = 000...0000cd).
------------------------------------------------------------------------------
    IMPLEMENTARE FUNCTIA ROTATIE LA STANGA
    Memoram in biti_a cei 4 biti ai lui a.
    In rezolvarea problemei am pornit de la urmatoare observatie:
Fie x un numar reprezentabil pe 4 biti => x(10)=abcd
Dupa o rotatie la stanga:       bcda
Dupa doua rotatii la stanga:    cdab
Dupa trei rotatii la stanga:    dabc
Dupa patru rotatii la stanga:   abcd !!!
    Deci observam ca rotatiile la stanga sunt de periodicitate 4
    => b = b % 4
    Urmeaza sa facem rotirile propriu-zise.
------------------------------------------------------------------------------
    IMPLEMENTARE FUNCTIA XOR:
    Pentru un i arbitrar ales avem situatiile:
    biti_a[i]   biti_b[i]   biti_rez[i]
        0           0           0
        0           1           1
        1           0           1
        1           1           0
    Daca biti_a[i] = biti_b[i] = 1 atunci
            biti_rez[i] = 0
    Altfel
            biti_rez[i] = (biti_a[i] | biti_b[i]);
------------------------------------------------------------------------------
    Am avut dificultati in a implementa functia Adunare.
------------------------------------------------------------------------------
    Am folosit vectori pentru a memora cifrele numerelor pentru a fi codul mai
usor de inteles. Tot ce-am pus in vectori se poate manipula si fara ajutorul lor.
De pilda, pot pune in loc de biti_a[i] direct expresia ((a & (1 << i)) != 0 ? 1 : 0).
La fel si rez, il pot construi si fara a-i memora bitii in biti_rez[] astfel:
rez=0;
for(i = 3; i >= 0; i--)
{
    rez = operatii;
    rez<<=1;
}
------------------------------------------------------------------------------
Am avut in vedere situatiile de tipul for(i = 3; i>=0 ; i--); cand i e de tip unsigned int
programul va returna "bus error", deoarece i va lua valoarea -1 care nu e pozitiva.
Rezolvare: declarare i de tip int.
------------------------------------------------------------------------------
    Timp de rezolvare al problemei:
    3 ore
```


## 4. WORDLE
```
    Am avut dificultati in a colora literele si in a afla codul ascii pentru tastele
BACKSPACE si ENTER(codul lor difera in functie de arhitectura sistemului de calcul).
------------------------------------------------------------------------------
    Algoritmul este urmatorul:
    -Citesc cuvintele, am grija ca atunci cand se citeste un cuvant la introducerea
caracterului ':'.
    -Vad daca jucatorul a castigat jocul sau a pierdut(am iar grija la introducerea
caracterului ':').
------------------------------------------------------------------------------
    Am ales ca mesajul de pierdere al jocului sa fie urmat de un sleep() si incheierea
executiei programului. Puteam face si cu un getch()(adica sa fie introdus orice 
caracter de la tastatura si dupa sa se incheie executia programului).
------------------------------------------------------------------------------
    Timp de rezolvare al problemei:
    10 ore
```
