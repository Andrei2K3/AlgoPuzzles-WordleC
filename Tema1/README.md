**Tema 1**
**Ciucan Andrei-Alexandru**
**Grupa 313CC**

## Table of Contents

- [1. PROBLEMA CUTIILOR](#1-problema-cutiilor)
- [2. NUMERE COMPLEXE LUNGI](#2-numere-complexe-lungi)
- [3. TRANSMISIE BRUIATA](#3-transmisie-bruiata)
- [4. CAR DEALER](#4-car-dealer)


## 1. PROBLEMA CUTIILOR
```
    Folosesc 3 functii:
- de citire a datelor de intrare;
- pentru rezolvarea taskului 1;
- pentru rezolvarea taaskului 2. 
-----------------------------------------------------------
    Cel mai dificil a fost de implementat deschiderea cutiilor:
- Content_Box[i] inseamna continutul cutiei i;
- Am pornit de la observatia ca Content_Box[Content_box[i]] inseamna continutul
continutului cutiei i, ulterior am vazut ca sirul din input reprezinta o PERMUTARE.
-----------------------------------------------------------
    Taskul 2:
- Tinand cont de faptul ca Content_Box reprezinta o permutare, atunci daca i se
gaseste intr-un ciclu implica ca i nu poate face parte din alt ciclu(matematica
garanteaza acest aspect).
-----------------------------------------------------------
    Timp de rezolvare al problemei:
    40 de minute
```


## 2. NUMERE COMPLEXE LUNGI
```
    Am folosit urmatoarea schema in rezolvarea problemei:
    Notam zi=al i-ule numar complex
    Daca avem semnul '-' urmat de zn in fisierele *.in atunci facem artificiul zn <-- -zn.
    Astfel problema se reduce la a calcula z1+z2+...+zn.
-----------------------------------------------------------
    Algoritmul in pseudocod simplificat este:
        Citeste z1 (numar complex)
        i<-1
        Cat timp i <= n executa
        |   Citeste z2 (numar complex)
        |   z1 <- z1 + z2
        |   i  <- i + 1
        |   Afisare z1
        ----
-----------------------------------------------------------
    Am avut dificulati in a implementa functia 
void operatii(int *bit_last, int *bit_current, int *last, int *current);
-----------------------------------------------------------
    Timp de rezolvare al problemei:
    2 ore
```

## 3. TRANSMISIE BRUIATA
```
    Am avut dificultati in a implementa DecodificareA si CodificareA.
-----------------------------------------------------------
    Pentru CodificareA:
    Am pornit de la exemplul 2:
cheie:              m e r e l e

text codificat:     A n a   a r
                    e   m e r e
                      m a r i

i:                  0 1 2 3 4 5
index[i]:           0 1 2 3 4 5
==>
cheie dupa sortare: e e e l m r
index dupa sortare: 1 3 5 4 0 2
    Rezultatul codificarii A reprezinta parcurgerea matricei mat pe coloane si in functie de 'index'.
-----------------------------------------------------------
    Pentru DecodificareA:
    Am procedat asemanator ca la CodificareA.
-----------------------------------------------------------
    Pentru CodificareB:
    Prima parte cu modificatul sirului a fost usoara.
    A doua parte:
-Am initializat litere_CodifB cu "abcd....xyzwABCD...XYZW";
-Se observa ca litere_CodifB are 52 de caractere (implicit litere);
-Daca vreau sa ma deplasez cu B pozitii la dreapta este suficient sa fac (deplasare + B) % 52,
unde deplasare=pozitia curenta
-----------------------------------------------------------
    Pentru DecodificareB:
    Am procedat analog cu CodificareB.
-----------------------------------------------------------
    Timp de rezolvare al problemei:
    5 ore
```


## 4. CAR DEALER
```
    Am avut dificultati in a rezolva cerinta c)
-----------------------------------------------------------
    Rezolvare cerinta a):
    Am numarat numarul de combustibili care incep cu 'b','m','h','e'
in vectorul de frecventa ans_task_a
-----------------------------------------------------------
    Rezolvare cerinta b):
    Marchez cu val toate pozitiile corespunzatoare aparitiilor aceluiasi brand de masini,
apoi cu val+1 ... , si tot asa.
    Cel mai mic i cu Aparitii[i]=val reprezinta si indicele pentru Consumul
total si Pretul total corespunzator brandului marcat cu val.
-----------------------------------------------------------
    Rezolvare cerinta c):
    Verific daca numerele sunt valide. Cel mai bine exprima acest lucru functia task3().
    Observatie:lungimea numarului e minim 6 (atunci cand avem 1litere + 2cifre + 3litere).
-----------------------------------------------------------
    Timp de rezolvare al problemei:
    3 ore
```
