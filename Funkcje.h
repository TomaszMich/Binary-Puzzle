#pragma once
#define POCZATEK_LEGENDY_WIERSZ 2
#define POCZATEK_LEGENDY_KOLUMNA 1
#define POCZATEK_RAMKI_WIERSZ  3
#define POCZATEK_RAMKI_KOLUMNA  62
#define POCZATEK_PODPOWIEDZI 24
#define BRZEGI_RAMKI 2
#define ESC 27
#define ENTER 13
#define ASCII 48
#define P_W_ASCII 50
#define NIE_SPELNIA_1_REGULY 0
#define SPELNIA_1_REGULE 1
#define NIE_SPELNIA_2_REGULY 0
#define SPELNIA_2_REGULE 1
#define SPELNIA_3_REGULE 0
#define MOZNA_WSTAWIC 1
#define NIE_MOZNA_WSTAWIC 0
#define PROCENT_WYPELNIENA 0.3
#define PROBY_LOSOWANIA 100
#define WLACZONY 1
#define WYLACZONY 0

//alokowanie pamieci dla planszy
char ** inicjalizacjaPlanszy(int wymiar);

//alokowanie pamieci dla szablonu
char ** inicjalizacjaSzablonu(int wymiar);

//zwolnienie pamiêci z planszy i z szablonu
void zwolnieniePamieci(char **plansza, char **szablon, int wymiar);

//utworzenie ramki ze znaków #
void zrobRamke(char **plansza, int wymiar);

void wypelnieniePlanszyKropkami(char **plansza, int wymiar);

void wypisaniePlanszy(char **plansza, int wymiar, char **szablon, int attr);

void wypisanieLegendy(int zn, int zero, int x, int y);

void wstawienieLiczby(char **plansza, int wymiar, int x, int y, char liczba, char** szablon);

int sprawdzenieReguly1(char **plansza, int wymiar, int x, int y, char liczba);

int sprawdzenieReguly2(char **plansza, int wymiar, int x, int y, char liczba);

int sprawdzenieReguly3(char **plansza, int wymiar, int x, int y, char liczba);

int sprawdzenieWszystkichRegul(char **plansza, int wymiar, int x, int y, char liczba, char **szablon);

void wczytanieNowejPlanszy(char **plansza, int wymiar, char** szablon);

void losoweWypelnienie(char **plansza, char **szablon, int wymiar);

void podpowiedz(char **plansza, int wymiar, int x, int y, char **szablon);

int zmianaRozmiaruPlanszy();

//sprawdzenie czy pole jest puste i czy wstawienie dowolnej liczby nie naruszy zasad
int sprawdzenieMozliwosciUkonczeniaGry(char **plansza, char **szablon, int wymiar);

//wypisanie iloœci zer i jedynek w ka¿dej kolumnie i wierszu
void wskazowkaDoReguly2(char **plansza, int wymiar, int attr);

//podœwietlenie pól, na których mo¿na wstawiæ tylko jedn¹ z liczb
void podswietlenieJednoznacznychPol(char **plansza, char **szablon, int wymiar);