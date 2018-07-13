#include "stdafx.h"
#include "conio2.h"
#include <stdio.h>
#include "Funkcje.h"
#include <cstdlib>
#include <time.h>


char ** inicjalizacjaPlanszy(int wymiar)
{
	char** plansza = new char*[wymiar + BRZEGI_RAMKI];
	for (int i = 0; i < wymiar + BRZEGI_RAMKI; i++)
	{
		plansza[i] = new char[wymiar + BRZEGI_RAMKI];
	}
	return plansza;
}

char ** inicjalizacjaSzablonu(int wymiar)
{
	char** szablon = new char*[wymiar + BRZEGI_RAMKI];
	for (int i = 0; i < wymiar + BRZEGI_RAMKI; i++)
	{
		szablon[i] = new char[wymiar + BRZEGI_RAMKI];
	}
	return szablon;
}

void zwolnieniePamieci(char **plansza, char **szablon, int wymiar)
{
	for (int i = 0; i < wymiar + BRZEGI_RAMKI; i++)
	{
		delete[] szablon[i];
		delete[] plansza[i];
	}

	delete[] szablon;
	delete[] plansza;
}

void wypelnieniePlanszyKropkami(char **plansza, int wymiar)
{
	for (int i = 1; i < wymiar + 1; i++)
	{
		for (int j = 1; j < wymiar + 1; j++)
		{
			plansza[i][j] = '.';
		}
	}
}

void zrobRamke(char **plansza, int wymiar)
{
	for (int i = 0; i < wymiar + BRZEGI_RAMKI; i++)
	{
		plansza[0][i] = '#'; //pierwszy wiersz
		plansza[wymiar + 1][i] = '#'; //ostatni wiersz
	}
	for (int i = 1; i < wymiar + 1; i++)
	{
		plansza[i][0] = '#'; //pierwsza kolumna
		plansza[i][wymiar + 1] = '#'; // ostatnia kolumna
	}
}

void wypisaniePlanszy(char **plansza, int wymiar, char **szablon, int attr)
{
	for (int i = 0; i < wymiar + BRZEGI_RAMKI; i++)
	{
		for (int j = 0; j < wymiar + BRZEGI_RAMKI; j++)
		{
			if ((i <= wymiar && j <= wymiar) && (i > 0 && j > 0) && plansza[i][j] != szablon[i][j])
			{
				textcolor(LIGHTCYAN); //wprowadzone maj¹ inny kolor
			}
			else textcolor(attr);
			gotoxy(POCZATEK_RAMKI_KOLUMNA + j, POCZATEK_RAMKI_WIERSZ + i);
			putch(plansza[i][j]);
		}
	}
}

void wypisanieLegendy(int zn, int zero, int x, int y)
{
	char txt[32];
	gotoxy(POCZATEK_LEGENDY_KOLUMNA, POCZATEK_LEGENDY_WIERSZ);
	cputs("Tomasz Michalski 171890");
	gotoxy(POCZATEK_LEGENDY_KOLUMNA, POCZATEK_LEGENDY_WIERSZ + 1);
	cputs("ESC = wyjscie");
	gotoxy(POCZATEK_LEGENDY_KOLUMNA, POCZATEK_LEGENDY_WIERSZ + 2);
	cputs("strzalki = poruszanie");
	gotoxy(POCZATEK_LEGENDY_KOLUMNA, POCZATEK_LEGENDY_WIERSZ + 3);
	cputs("spacja = zmiana koloru");
	gotoxy(POCZATEK_LEGENDY_KOLUMNA, POCZATEK_LEGENDY_WIERSZ + 4);
	cputs("enter = zmiana koloru tla");
	gotoxy(POCZATEK_LEGENDY_KOLUMNA, POCZATEK_LEGENDY_WIERSZ + 5);
	cputs("n = nowa gra");
	gotoxy(POCZATEK_LEGENDY_KOLUMNA, POCZATEK_LEGENDY_WIERSZ + 6);
	cputs("o = losowe czesciowe wypelnienie");
	gotoxy(POCZATEK_LEGENDY_KOLUMNA, POCZATEK_LEGENDY_WIERSZ + 7);
	cputs("p = podpowiedz");
	gotoxy(POCZATEK_LEGENDY_KOLUMNA, POCZATEK_LEGENDY_WIERSZ + 8);
	cputs("r = zmiana rozmiaru planszy");
	gotoxy(POCZATEK_LEGENDY_KOLUMNA, POCZATEK_LEGENDY_WIERSZ + 9);
	cputs("k = sprawdzenie mozliwosci ukonczenia gry");
	gotoxy(POCZATEK_LEGENDY_KOLUMNA, POCZATEK_LEGENDY_WIERSZ + 10);
	cputs("j = podswietlenie jednoznacznych pol");
	gotoxy(POCZATEK_LEGENDY_KOLUMNA, POCZATEK_LEGENDY_WIERSZ + 11);
	cputs("w = wypelnienie podswietlonych pol");
	gotoxy(POCZATEK_LEGENDY_KOLUMNA, POCZATEK_LEGENDY_WIERSZ + 12);
	cputs("d = podpowiedz do reguly 2");
	gotoxy(POCZATEK_LEGENDY_KOLUMNA, POCZATEK_LEGENDY_WIERSZ + 13);
	cputs("a = automatyczna detekcja konca gry");
	// wypisujemy na ekranie kod ostatnio naciœniêtego klawisza
	if (zero) sprintf(txt, "kod klawisza: 0x00 0x%02x", zn);
	else sprintf(txt, "kod klawisza: 0x%02x", zn);
	gotoxy(POCZATEK_LEGENDY_KOLUMNA, POCZATEK_LEGENDY_WIERSZ + 14);
	cputs(txt);
	sprintf(txt, "Pozycja kursora: %dx%d", x - POCZATEK_RAMKI_KOLUMNA, y - POCZATEK_RAMKI_WIERSZ);
	gotoxy(POCZATEK_LEGENDY_KOLUMNA, POCZATEK_LEGENDY_WIERSZ + 15);
	cputs(txt);
	gotoxy(POCZATEK_LEGENDY_KOLUMNA, POCZATEK_LEGENDY_WIERSZ + 16);
	cputs("funkcjonalnosci od a) do m)");
}


void wstawienieLiczby(char **plansza, int wymiar, int x, int y, char liczba, char **szablon)
{
	int a = y - POCZATEK_RAMKI_WIERSZ, b = x - POCZATEK_RAMKI_KOLUMNA;

	if (sprawdzenieWszystkichRegul(plansza, wymiar, x, y, liczba, szablon) == MOZNA_WSTAWIC)
	{
		plansza[a][b] = liczba;
	}
}

int sprawdzenieReguly1(char **plansza, int wymiar, int x, int y, char liczba)
{
	if (x >= 2 && plansza[y][x - 2] == liczba && plansza[y][x - 1] == liczba) return NIE_SPELNIA_1_REGULY; //lewo lewo
	if ((x + 2) <= wymiar && plansza[y][x + 1] == liczba && plansza[y][x + 2] == liczba) return NIE_SPELNIA_1_REGULY; // prawo prawo
	if (y >= 2 && plansza[y - 2][x] == liczba && plansza[y - 1][x] == liczba) return NIE_SPELNIA_1_REGULY; //dol dol
	if ((y + 2) <= wymiar && plansza[y + 1][x] == liczba && plansza[y + 2][x] == liczba) return NIE_SPELNIA_1_REGULY; // gora gora
	if (plansza[y][x - 1] == liczba && plansza[y][x + 1] == liczba) return NIE_SPELNIA_1_REGULY; //lewo prawo
	if (plansza[y - 1][x] == liczba && plansza[y + 1][x] == liczba) return NIE_SPELNIA_1_REGULY; //gora dol

	return SPELNIA_1_REGULE;
}

int sprawdzenieReguly2(char **plansza, int wymiar, int x, int y, char liczba)
{
	int wWierszu = 0, wKolumnie = 0;
	for (int i = 1; i <= wymiar; i++)
	{
		if (plansza[y - POCZATEK_RAMKI_WIERSZ][i] == liczba)
			wWierszu++;

		if (plansza[i][x - POCZATEK_RAMKI_KOLUMNA] == liczba)
			wKolumnie++;
	}

	if (wWierszu >= wymiar / 2 || wKolumnie >= wymiar / 2)
		return NIE_SPELNIA_2_REGULY;
	else return SPELNIA_2_REGULE;
}

int sprawdzenieReguly3(char **plansza, int wymiar, int x, int y, char liczba)
{
	int pWiersz = 0, pKolumna = 0;
	char* wiersz = new char[wymiar];
	char* kolumna = new char[wymiar];

	//lokalna kopia planszy
	char** kopiaPlanszy = new char*[wymiar + BRZEGI_RAMKI];
	for (int i = 0; i < wymiar + BRZEGI_RAMKI; i++)
	{
		kopiaPlanszy[i] = new char[wymiar + BRZEGI_RAMKI];
		for (int j = 0; j < wymiar + BRZEGI_RAMKI; j++)
		{
			kopiaPlanszy[i][j] = plansza[i][j];
		}
	}

	//wpisanie wartoœci do kopii
	kopiaPlanszy[y - POCZATEK_RAMKI_WIERSZ][x - POCZATEK_RAMKI_KOLUMNA] = liczba;
	//kopiowanie obecnego wiersza i kolumny
	for (int i = 0; i < wymiar; i++)
	{
		wiersz[i] = kopiaPlanszy[y - POCZATEK_RAMKI_WIERSZ][i + 1];
		kolumna[i] = kopiaPlanszy[i + 1][x - POCZATEK_RAMKI_KOLUMNA];
	}

	//porównanie wierszów
	for (int i = 0; i < wymiar; i++)
	{
		for (int j = 0; j < wymiar; j++)
		{
			if (wiersz[j] != '.' && (i + 1) != (y - POCZATEK_RAMKI_WIERSZ) && wiersz[j] == kopiaPlanszy[i + 1][j + 1])
				pWiersz++;
		}
		if (pWiersz == wymiar)
			return (i + 1001); //powtorzenie z wierszem i + 1
		else pWiersz = 0;
	}
	//porównanie kolumn
	for (int i = 0; i < wymiar; i++)
	{
		for (int j = 0; j < wymiar; j++)
		{
			if (kolumna[j] != '.' && (i + 1) != (x - POCZATEK_RAMKI_KOLUMNA) && kolumna[j] == kopiaPlanszy[j + 1][i + 1])
				pKolumna++;
		}
		if (pKolumna == wymiar)
			return (i + 1); //powtorzenie z kolumna i + 1
		else pKolumna = 0;
	}
	delete[] wiersz;
	delete[] kolumna;
	for (int i = 0; i < wymiar + BRZEGI_RAMKI; i++)
	{
		delete[] kopiaPlanszy[i];
	}
	delete[] kopiaPlanszy;

	return SPELNIA_3_REGULE;
}

int sprawdzenieWszystkichRegul(char **plansza, int wymiar, int x, int y, char liczba, char **szablon)
{
	int a = y - POCZATEK_RAMKI_WIERSZ, b = x - POCZATEK_RAMKI_KOLUMNA;
	if (a > 0 && a <= wymiar && b > 0 && b <= wymiar)
	{
		if (szablon[a][b] == '.') //modyfikowalne
		{
			if (sprawdzenieReguly1(plansza, wymiar, b, a, liczba) == SPELNIA_1_REGULE)
			{
				if (sprawdzenieReguly2(plansza, wymiar, x, y, liczba) == SPELNIA_2_REGULE)
				{
					if (sprawdzenieReguly3(plansza, wymiar, x, y, liczba) == SPELNIA_3_REGULE)
						return MOZNA_WSTAWIC;
				}
			}
		}
	}
	return NIE_MOZNA_WSTAWIC;
}

void wczytanieNowejPlanszy(char **plansza, int wymiar, char **szablon)
{
	switch (wymiar)
	{
	case 6: {
		FILE *plik = fopen("plansza6x6.txt", "r");
		for (int i = 1; i <= wymiar; i++)
		{
			for (int j = 1; j <= wymiar; j++)
			{
				char znak = fgetc(plik);
				plansza[i][j] = znak;
				szablon[i][j] = znak;
			}
		}
		fclose(plik);
		break;
	}
	case 8: {
		FILE *plik = fopen("plansza8x8.txt", "r");
		for (int i = 1; i <= wymiar; i++)
		{
			for (int j = 1; j <= wymiar; j++)
			{
				char znak = fgetc(plik);
				plansza[i][j] = znak;
				szablon[i][j] = znak;
			}
		}
		fclose(plik);
		break;
	}
	case 10: {
		FILE *plik = fopen("plansza10x10.txt", "r");
		for (int i = 1; i <= wymiar; i++)
		{
			for (int j = 1; j <= wymiar; j++)
			{
				char znak = fgetc(plik);
				plansza[i][j] = znak;
				szablon[i][j] = znak;
			}
		}
		fclose(plik);
		break;
	}
	case 12: {
		FILE *plik = fopen("plansza12x12.txt", "r");
		for (int i = 1; i <= wymiar; i++)
		{
			for (int j = 1; j <= wymiar; j++)
			{
				char znak = fgetc(plik);
				plansza[i][j] = znak;
				szablon[i][j] = znak;
			}
		}
		fclose(plik);
		break;
	}
	case 14: {
		FILE *plik = fopen("plansza14x14.txt", "r");
		for (int i = 1; i <= wymiar; i++)
		{
			for (int j = 1; j <= wymiar; j++)
			{
				char znak = fgetc(plik);
				plansza[i][j] = znak;
				szablon[i][j] = znak;
			}
		}
		fclose(plik);
		break;
	}
	default:
	{
		losoweWypelnienie(plansza, szablon, wymiar);
		break;
	}
	}
	zrobRamke(plansza, wymiar);
}

void losoweWypelnienie(char **plansza, char **szablon, int wymiar)
{
	wypelnieniePlanszyKropkami(plansza, wymiar);
	wypelnieniePlanszyKropkami(szablon, wymiar);
	char wartosc;
	int a, b, sukces = 0;
	srand(time(NULL));

	for (int k = 0; k < PROBY_LOSOWANIA, sukces < PROCENT_WYPELNIENA * wymiar * wymiar; k++)
	{
		wartosc = rand() % 2 + 48;
		a = rand() % wymiar + 1;
		b = rand() % wymiar + 1;

		wstawienieLiczby(plansza, wymiar, a + POCZATEK_RAMKI_KOLUMNA, b + POCZATEK_RAMKI_WIERSZ, wartosc, szablon);

		for (int i = 1; i <= wymiar; i++)
			for (int j = 1; j <= wymiar; j++)
			{
				if (szablon[i][j] != plansza[i][j])
				{
					szablon[i][j] = plansza[i][j];
					sukces++;
				}
			}
	}
}

void podpowiedz(char **plansza, int wymiar, int x, int y, char **szablon)
{
	char wiadomosc[128];
	int a = y - POCZATEK_RAMKI_WIERSZ, b = x - POCZATEK_RAMKI_KOLUMNA;

	//sprawdzenie czy mozna wstawic 0
	int wiersz = 0;
	char liczba = '0';
	if (sprawdzenieWszystkichRegul(plansza, wymiar, x, y, liczba, szablon) == MOZNA_WSTAWIC)
	{
		gotoxy(POCZATEK_LEGENDY_KOLUMNA, POCZATEK_PODPOWIEDZI + wiersz);
		sprintf(wiadomosc, "Mozna wstawic %c", liczba);
		cputs(wiadomosc);
		wiersz++;
	}
	else if (szablon[a][b] != '.')
	{
		gotoxy(POCZATEK_LEGENDY_KOLUMNA, POCZATEK_PODPOWIEDZI + wiersz);
		sprintf(wiadomosc, "Pole jest niemodyfikowalne!");
		cputs(wiadomosc);
		wiersz++;
	}
	else
	{
		gotoxy(POCZATEK_LEGENDY_KOLUMNA, POCZATEK_PODPOWIEDZI);
		sprintf(wiadomosc, "Nie mozna wstawic %c poniewaz: ", liczba);
		cputs(wiadomosc);
		wiersz++;

		if (sprawdzenieReguly1(plansza, wymiar, b, a, liczba) == NIE_SPELNIA_1_REGULY)
		{
			gotoxy(POCZATEK_LEGENDY_KOLUMNA, POCZATEK_PODPOWIEDZI + wiersz);
			sprintf(wiadomosc, "Nie moga byc wiecej niz dwie takie same cyfry obok siebie!");
			cputs(wiadomosc);
			wiersz++;
		}

		if (sprawdzenieReguly2(plansza, wymiar, x, y, liczba) == NIE_SPELNIA_2_REGULY)
		{
			gotoxy(POCZATEK_LEGENDY_KOLUMNA, POCZATEK_PODPOWIEDZI + wiersz);
			sprintf(wiadomosc, "Ilosc %c bedzie przekraczac polowe rozmiaru planszy!", liczba);
			cputs(wiadomosc);
			wiersz++;
		}
		if (sprawdzenieReguly3(plansza, wymiar, x, y, liczba) != SPELNIA_3_REGULE)
		{
			int numer = sprawdzenieReguly3(plansza, wymiar, x, y, liczba);
			gotoxy(POCZATEK_LEGENDY_KOLUMNA, POCZATEK_PODPOWIEDZI + wiersz);
			if (numer < 1000)
			{
				sprintf(wiadomosc, "Wpisanie cyfry %c spowoduje, ze kolumna bedzie identyczna z kolumna numer %d!", liczba, numer);
				cputs(wiadomosc);
				wiersz++;
			}
			else
			{
				sprintf(wiadomosc, "Wpisanie cyfry %c spowoduje, ze wiersz bedzie identyczny z wierszem numer %d!", liczba, numer - 1000);
				cputs(wiadomosc);
				wiersz++;
			}
		}
	}
	//sprawdzenie czy mozna wstawic 1
	liczba = '1';
	if (sprawdzenieWszystkichRegul(plansza, wymiar, x, y, liczba, szablon) == MOZNA_WSTAWIC)
	{
		gotoxy(POCZATEK_LEGENDY_KOLUMNA, POCZATEK_PODPOWIEDZI + wiersz);
		sprintf(wiadomosc, "Mozna wstawic %c", liczba);
		cputs(wiadomosc);
		wiersz++;
	}
	else if (szablon[a][b] == '.')
	{
		gotoxy(POCZATEK_LEGENDY_KOLUMNA, POCZATEK_PODPOWIEDZI + wiersz);
		sprintf(wiadomosc, "Nie mozna wstawic %c poniewaz: ", liczba);
		cputs(wiadomosc);
		wiersz++;

		if (sprawdzenieReguly1(plansza, wymiar, b, a, liczba) == NIE_SPELNIA_1_REGULY)
		{
			gotoxy(POCZATEK_LEGENDY_KOLUMNA, POCZATEK_PODPOWIEDZI + wiersz);
			sprintf(wiadomosc, "Nie moga byc wiecej niz dwie takie same cyfry obok siebie!");
			cputs(wiadomosc);
			wiersz++;
		}
		if (sprawdzenieReguly2(plansza, wymiar, x, y, liczba) == NIE_SPELNIA_2_REGULY)
		{
			gotoxy(POCZATEK_LEGENDY_KOLUMNA, POCZATEK_PODPOWIEDZI + wiersz);
			sprintf(wiadomosc, "Ilosc %c bedzie przekraczac polowe rozmiaru planszy!", liczba);
			cputs(wiadomosc);
			wiersz++;
		}
		if (sprawdzenieReguly3(plansza, wymiar, x, y, liczba) != SPELNIA_3_REGULE)
		{
			int numer = sprawdzenieReguly3(plansza, wymiar, x, y, liczba);
			gotoxy(POCZATEK_LEGENDY_KOLUMNA, POCZATEK_PODPOWIEDZI + wiersz);
			if (numer < 1000)
			{
				sprintf(wiadomosc, "Wpisanie cyfry %c spowoduje, ze kolumna bedzie identyczna z kolumna numer %d!", liczba, numer);
				cputs(wiadomosc);
				wiersz++;
			}
			else
			{
				sprintf(wiadomosc, "Wpisanie cyfry %c spowoduje, ze wiersz bedzie identyczny z wierszem numer %d!", liczba, numer - 1000);
				cputs(wiadomosc);
				wiersz++;
			}
		}
	}
	getch();
}

int zmianaRozmiaruPlanszy()
{
	int rozmiar;
	char pierwszaCyfra, drugaCyfra;
	gotoxy(POCZATEK_LEGENDY_KOLUMNA, POCZATEK_LEGENDY_WIERSZ + 20);
	cputs("Podaj nowy rozmiar planszy: ");
	pierwszaCyfra = getch();
	putch(pierwszaCyfra);
	drugaCyfra = getch();
	putch(drugaCyfra);
	if (drugaCyfra != ENTER)
	{
		char liczba[] = { pierwszaCyfra, drugaCyfra, '\0' };
		rozmiar = atoi(liczba);
		getch();
	}
	else if (drugaCyfra == ENTER)
	{
		char liczba[] = { pierwszaCyfra, '\0' };
		rozmiar = atoi(liczba);
	}

	return rozmiar;
}

int sprawdzenieMozliwosciUkonczeniaGry(char **plansza, char **szablon, int wymiar)
{
	int brak = 0;
	for (int i = 1; i <= wymiar; i++)
	{
		for (int j = 1; j <= wymiar; j++)
		{
			if (plansza[i][j] == '.' && sprawdzenieWszystkichRegul(plansza, wymiar, j + POCZATEK_RAMKI_KOLUMNA, i + POCZATEK_RAMKI_WIERSZ, '1', szablon) == NIE_MOZNA_WSTAWIC && sprawdzenieWszystkichRegul(plansza, wymiar, j + POCZATEK_RAMKI_KOLUMNA, i + POCZATEK_RAMKI_WIERSZ, '0', szablon) == NIE_MOZNA_WSTAWIC)
			{
				textbackground(RED);
				gotoxy(POCZATEK_RAMKI_KOLUMNA + j, POCZATEK_RAMKI_WIERSZ + i);
				putch(plansza[i][j]);
				brak++;
			}
		}
	}
	return brak;
}

void wskazowkaDoReguly2(char **plansza, int wymiar, int attr)
{
	int jedynki = 0, zera = 0;
	char liczba[3];
	//sprawdzenie wierszy
	for (int i = 1; i <= wymiar; i++)
	{
		for (int j = 1; j <= wymiar; j++)
		{
			if (plansza[i][j] == '1')
				jedynki++;

			if (plansza[i][j] == '0')
				zera++;
		}
		if (jedynki < 10)
		{
			gotoxy(POCZATEK_RAMKI_KOLUMNA - 1, POCZATEK_RAMKI_WIERSZ + i);
			putch(jedynki + ASCII);
		}
		else if (jedynki >= 10)
		{
			_itoa(jedynki, liczba, 10);
			gotoxy(POCZATEK_RAMKI_KOLUMNA - 2, POCZATEK_RAMKI_WIERSZ + i);
			cputs(liczba);
		}
		if (zera < 10)
		{
			gotoxy(POCZATEK_RAMKI_KOLUMNA + BRZEGI_RAMKI + wymiar, POCZATEK_RAMKI_WIERSZ + i);
			putch(zera + ASCII);
		}
		else if (zera >= 10)
		{
			_itoa(zera, liczba, 10);
			gotoxy(POCZATEK_RAMKI_KOLUMNA + BRZEGI_RAMKI + wymiar, POCZATEK_RAMKI_WIERSZ + i);
			cputs(liczba);
		}
		jedynki = 0;
		zera = 0;
	}
	//sprawdzenie kolumn
	for (int i = 1; i <= wymiar; i++)
	{
		for (int j = 1; j <= wymiar; j++)
		{
			if (plansza[j][i] == '1')
				jedynki++;
			if (plansza[j][i] == '0')
				zera++;
		}
		if (jedynki < 10)
		{
			gotoxy(POCZATEK_RAMKI_KOLUMNA + i, POCZATEK_RAMKI_WIERSZ - 1);
			putch(jedynki + ASCII);
		}
		else if (jedynki >= 10)
		{
			_itoa(jedynki, liczba, 10);
			gotoxy(POCZATEK_RAMKI_KOLUMNA + i, POCZATEK_RAMKI_WIERSZ - 2);
			putch(liczba[0]);
			gotoxy(POCZATEK_RAMKI_KOLUMNA + i, POCZATEK_RAMKI_WIERSZ - 1);
			putch(liczba[1]);
		}
		if (zera < 10)
		{
			gotoxy(POCZATEK_RAMKI_KOLUMNA + i, POCZATEK_RAMKI_WIERSZ + BRZEGI_RAMKI + wymiar);
			putch(zera + ASCII);
		}
		else if (zera >= 10)
		{
			_itoa(zera, liczba, 10);
			gotoxy(POCZATEK_RAMKI_KOLUMNA + i, POCZATEK_RAMKI_WIERSZ + BRZEGI_RAMKI + wymiar);
			putch(liczba[0]);
			gotoxy(POCZATEK_RAMKI_KOLUMNA + i, POCZATEK_RAMKI_WIERSZ + BRZEGI_RAMKI + wymiar + 1);
			putch(liczba[1]);
		}
		jedynki = 0;
		zera = 0;
	}
	//wypisanie sta³ych elementów
	textcolor(LIGHTGREEN);
	gotoxy(POCZATEK_RAMKI_KOLUMNA - 1, POCZATEK_RAMKI_WIERSZ - 1);
	putch('1');
	gotoxy(POCZATEK_RAMKI_KOLUMNA - 1, POCZATEK_RAMKI_WIERSZ);
	putch('|');
	gotoxy(POCZATEK_RAMKI_KOLUMNA, POCZATEK_RAMKI_WIERSZ - 1);
	putch('-');
	textcolor(YELLOW);
	gotoxy(POCZATEK_RAMKI_KOLUMNA + BRZEGI_RAMKI + wymiar, POCZATEK_RAMKI_WIERSZ + wymiar + BRZEGI_RAMKI);
	putch('0');
	gotoxy(POCZATEK_RAMKI_KOLUMNA + BRZEGI_RAMKI + wymiar - 1, POCZATEK_RAMKI_WIERSZ + wymiar + BRZEGI_RAMKI);
	putch('-');
	gotoxy(POCZATEK_RAMKI_KOLUMNA + BRZEGI_RAMKI + wymiar, POCZATEK_RAMKI_WIERSZ + wymiar + BRZEGI_RAMKI - 1);
	putch('|');

	textcolor(attr);
}

void podswietlenieJednoznacznychPol(char **plansza, char **szablon, int wymiar)
{
	char** flaga = new char*[wymiar];
	for (int i = 0; i < wymiar; i++)
	{
		flaga[i] = new char[wymiar];
	}

	for (int i = 1; i <= wymiar; i++)
	{
		for (int j = 1; j <= wymiar; j++)
		{
			if (plansza[i][j] == '.' && sprawdzenieWszystkichRegul(plansza, wymiar, j + POCZATEK_RAMKI_KOLUMNA, i + POCZATEK_RAMKI_WIERSZ, '1', szablon) == MOZNA_WSTAWIC && sprawdzenieWszystkichRegul(plansza, wymiar, j + POCZATEK_RAMKI_KOLUMNA, i + POCZATEK_RAMKI_WIERSZ, '0', szablon) == NIE_MOZNA_WSTAWIC)
			{
				textbackground(LIGHTGREEN);
				gotoxy(POCZATEK_RAMKI_KOLUMNA + j, POCZATEK_RAMKI_WIERSZ + i);
				putch(plansza[i][j]);
				flaga[i - 1][j - 1] = '1';
			}
			if (plansza[i][j] == '.' && sprawdzenieWszystkichRegul(plansza, wymiar, j + POCZATEK_RAMKI_KOLUMNA, i + POCZATEK_RAMKI_WIERSZ, '0', szablon) == MOZNA_WSTAWIC && sprawdzenieWszystkichRegul(plansza, wymiar, j + POCZATEK_RAMKI_KOLUMNA, i + POCZATEK_RAMKI_WIERSZ, '1', szablon) == NIE_MOZNA_WSTAWIC)
			{
				textbackground(YELLOW);
				gotoxy(POCZATEK_RAMKI_KOLUMNA + j, POCZATEK_RAMKI_WIERSZ + i);
				putch(plansza[i][j]);
				flaga[i - 1][j - 1] = '0';
			}
		}
	}
	char klawisz = getch();
	if (klawisz == 'w')
	{
		for (int i = 1; i <= wymiar; i++)
		{
			for (int j = 1; j <= wymiar; j++)
			{
				if (flaga[i - 1][j - 1] == '1')
				{
					plansza[i][j] = '1';
				}
				if (flaga[i - 1][j - 1] == '0')
				{
					plansza[i][j] = '0';
				}
			}
		}
	}
	for (int i = 0; i < wymiar; i++)
	{
		delete[] flaga[i];
	}
	delete[] flaga;
}