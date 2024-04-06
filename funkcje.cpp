#include <iostream>
#include <locale.h>
#include <random>
#include <Windows.h>
#include "funkcje.h"
using namespace std;

//funckcja wywo�uj�ca pocz�tkowe logo gry
void logo() {
	cout << "\xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb" << endl;
	cout << "\xba                   \xba" << endl;
	cout << "\xba  K\xe0\x9dKO I KRZY\xbdYK  \xba" << endl;
	cout << "\xba                   \xba" << endl;
	cout << "\xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc" << endl << endl;
}

//funkcja wywo�uj�ca menu z wyborem gry i wyj�cia
void start() {
	setlocale(LC_CTYPE, "Polish");
	cout << "Wybierz opcj�: " << endl;
	cout << "1. Gra na dw�ch graczy." << endl;
	cout << "2. Gra z komputerem" << endl;
	cout << "3. Wyj�cie" << endl;
}

//funkcja wywo�uj�ca instrukcj� do gry
void instrukcje() {
	setlocale(LC_CTYPE, "Polish");
	char plansza[9] = { '1','2','3','4','5','6','7','8','9' };
	cout << endl << "INSTRUKCJA: " << endl;
	cout << "Aby zagra� wybierz numer pola i wci�nij ENTER" << endl;
	rysuj_plansze(plansza);
}

//funkcja pokazuj�ca plansz�
void rysuj_plansze(char p[]) {
	for (int i = 0; i < 9; i++) {
		cout << " " << p[i] << " ";
		if ((i + 1) % 3 == 0 && i != 8)
			cout << endl << "---|---|---" << endl;
		else if (i != 8)
			cout << "|";
		else
			cout << endl;
	}
}

//funkcja sprawdzaj�ca czy konkretny znak wygra�
bool czy_wygrana(char p[], char z) {
	bool wynik = false;
	for (int i = 0; i < 9; i += 3)
		if (p[i] == z && p[i + 1] == z && p[i + 2] == z)
			wynik = true;
	for (int i = 0; i < 3; i++)
		if (p[i] == z && p[i + 3] == z && p[i + 6] == z)
			wynik = true;
	if ((p[0] == z && p[4] == z && p[8] == z) || (p[2] == z && p[4] == z && p[6] == z))
		wynik = true;
	return wynik;
}

//funkcja sprawdzaj�ca czy gra zako�czy�a si� remisem
bool czy_remis(char p[]) {
	bool wynik = true;
	for (int i = 0; i < 9; i++) {
		if (p[i] == ' ') {
			wynik = false;
			return wynik;
		}
	}
	return wynik;
}

//funkcja pobieraj�ca od u�ytkownika pole, upewniaj�c si� �e takie pole istnieje i nie jest zaj�te
int wczytaj_pole(char p[], int a) {
	setlocale(LC_CTYPE, "Polish");
	cin >> a;
	while (cin.fail() || a < 1 || a > 9) {
		cout << "Nie ma takiego pola. Wprowad� ponownie: ";
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> a;
		while (p[a - 1] == 'X' || p[a - 1] == 'O') {
			cout << "To pole jest zaj�te. Wprowad� ponownie: ";
			cin >> a;
		}
	}
	while (p[a - 1] == 'X' || p[a - 1] == 'O') {
		cout << "To pole jest zaj�te. Wprowad� ponownie: ";
		cin >> a;
		while (cin.fail() || a < 1 || a > 9) {
			cout << "Nie ma takiego pola. Wprowad� ponownie: ";
			cin.clear();
			cin.ignore(10000, '\n');
			cin >> a;
		}
	}
	return a;
}

//funckja losuj�ca pole od 1 do 9, upewniaj�c si� �e nie jest zaj�te
int losuj_pole(char p[]) {
	int pole{};
	mt19937 generator(time(nullptr));
	uniform_int_distribution<int> distribution(1, 9);
	do {
		pole = distribution(generator);
	} while (p[pole - 1] != ' ');
	return pole;
}

//funkcja sprawdzaj�ca czy komputer mo�e blokowa�, je�li tak to zwraca pola gdzie ma tak� mo�liwo��, je�li nie to zwraca 10
int blok(char p[]) {
	//sprawdzenie mo�liwo�ci poziomo
	for (int i = 0; i < 9; i += 3) {
		if (p[i] == p[i + 1] && p[i + 2] == ' ' && p[i] == 'O')
			return (i + 2);
		else if (p[i] == p[i + 2] && p[i + 1] == ' ' && p[i] == 'O')
			return (i + 1);
		else if (p[i + 1] == p[i + 2] && p[i] == ' ' && p[i + 1] == 'O')
			return i;
	}
	//sprawdzenie mo�liwo�ci pionowo
	for (int i = 0; i < 3; i++) {
		if (p[i] == p[i + 3] && p[i + 6] == ' ' && p[i] == 'O')
			return (i + 6);
		else if (p[i] == p[i + 6] && p[i + 3] == ' ' && p[i] == 'O')
			return (i + 3);
		else if (p[i + 3] == p[i + 6] && p[i] == ' ' && p[i + 3] == 'O')
			return i;
	}
	//sprawdzenie przek�tnej
	if (p[0] == p[4] && p[8] == ' ' && p[0] == 'O')
		return 8;
	else if (p[0] == p[8] && p[4] == ' ' && p[0] == 'O')
		return 4;
	else if (p[4] == p[8] && p[0] == ' ' && p[4] == 'O')
		return 0;
	//sprawdzenie antyprzek�tnej
	if (p[2] == p[4] && p[6] == ' ' && p[2] == 'O')
		return 6;
	else if (p[2] == p[6] && p[4] == ' ' && p[2] == 'O')
		return 4;
	else if (p[4] == p[6] && p[2] == ' ' && p[4] == 'O')
		return 2;
	return 10;
}

//funkcja sprawdzaj�ca czy komputer mo�e wygra�, je�li tak to zwraca pola gdzie ma tak� mo�liwo��, je�li nie to zwraca 10
int wygrana(char p[]) {
	//sprawdzenie mo�liwo�ci poziomo
	for (int i = 0; i < 9; i += 3) {
		if (p[i] == p[i + 1] && p[i + 2] == ' ' && p[i] == 'X')
			return (i + 2);
		else if (p[i] == p[i + 2] && p[i + 1] == ' ' && p[i] == 'X')
			return (i + 1);
		else if (p[i + 1] == p[i + 2] && p[i] == ' ' && p[i + 1] == 'X')
			return i;
	}
	//sprawdzenie mo�liwo�ci pionowo
	for (int i = 0; i < 3; i++) {
		if (p[i] == p[i + 3] && p[i + 6] == ' ' && p[i] == 'X')
			return (i + 6);
		else if (p[i] == p[i + 6] && p[i + 3] == ' ' && p[i] == 'X')
			return (i + 3);
		else if (p[i + 3] == p[i + 6] && p[i] == ' ' && p[i + 3] == 'X')
			return i;
	}
	//sprawdzenie przek�tnej
	if (p[0] == p[4] && p[8] == ' ' && p[0] == 'X')
		return 8;
	else if (p[0] == p[8] && p[4] == ' ' && p[0] == 'X')
		return 4;
	else if (p[4] == p[8] && p[0] == ' ' && p[4] == 'X')
		return 0;
	//sprawdzenie antyprzek�tnej
	if (p[2] == p[4] && p[6] == ' ' && p[2] == 'X')
		return 6;
	else if (p[2] == p[6] && p[4] == ' ' && p[2] == 'X')
		return 4;
	else if (p[4] == p[6] && p[2] == ' ' && p[4] == 'X')
		return 2;
	return 10;
}

//funkcja z gr� na dw�ch u�ytkownik�w
void gra_na_dwoch_graczy(char p[]) {
	//ustawienie polskich znakow
	setlocale(LC_CTYPE, "Polish");
	int liczba_ruchow{};
	do {
		int pole{};
		//gracze zmieniaj� si� co ruch
		//pobierane jest pole i rysowana plansza dop�ki nikt nie wygra� ani nie ma remisu
		if (liczba_ruchow % 2 == 0) {
			cout << endl << "Gracz I: ";
			pole = wczytaj_pole(p, pole);
			p[pole - 1] = 'X';
		}
		else {
			cout << endl << "Gracz II: ";
			pole = wczytaj_pole(p, pole);
			p[pole - 1] = 'O';
		}
		rysuj_plansze(p);
		liczba_ruchow++;
	} while (!czy_wygrana(p, 'X') && !czy_wygrana(p, 'O') && !czy_remis(p));
	cout << endl;
	//wy�wietlenie wyniku
	if (czy_wygrana(p, 'X')) {
		cout << "Wygra� gracz I." << endl;
	}
	else if (czy_wygrana(p, 'O')) {
		cout << "Wygra� gracz II." << endl;
	}
	else {
		cout << "Remis. Nikt nie wygra�." << endl;
	}
}

//funkcja z gr� z komputerem, gdzie u�ytkownik zaczyna a komputer losuje pola, w kt�rych stawia znak
void gra_latwa1(char p[]) {
	//ustawienie polskich znakow
	setlocale(LC_CTYPE, "Polish");
	int liczba_ruchow{};
	//ruchy komputera, pobieranie pola od u�ytkownika i rysowana plansza dop�ki nikt nie wygra� ani nie ma remisu
	do {
		int pole{};
		//zmiana kolejki komputera z u�ytkownikiem co 2 ruchy
		if (liczba_ruchow % 2 == 1) {
			//wstrzymanie pracy komputera na 1 sekund�
			Sleep(1000);
			pole = losuj_pole(p);
			cout << endl << "M�j ruch: " << pole << endl;
			p[pole - 1] = 'X';
		}
		else {
			cout << endl << "Tw�j ruch: ";
			pole = wczytaj_pole(p, pole);
			p[pole - 1] = 'O';
		}
		rysuj_plansze(p);
		liczba_ruchow++;
	} while (!czy_wygrana(p, 'X') && !czy_wygrana(p, 'O') && !czy_remis(p));
	cout << endl;
	//wy�wietlenie wyniku
	if (czy_wygrana(p, 'X')) {
		cout << "Wygra�em!";
	}
	else if (czy_wygrana(p, 'O')) {
		cout << "Gratulacje! Wygra�e�!" << endl;
	}
	else {
		cout << "Remis. Nikt nie wygra�." << endl;
	}
}

//funkcja z gr� z komputerem, gdzie komputer zaczyna i losuje pola, w kt�rych stawia znak
void gra_latwa2(char p[]) {
	//ustawienie polskich znakow
	setlocale(LC_CTYPE, "Polish");
	int liczba_ruchow{};
	//ruchy komputera, pobieranie pola od u�ytkownika i rysowana plansza dop�ki nikt nie wygra� ani nie ma remisu
	do {
		int pole{};
		//zmiana kolejki komputera z u�ytkownikiem co 2 ruchy
		if (liczba_ruchow % 2 == 0) {
			//wstrzymanie pracy komputera na 1 sekund�
			Sleep(1000);
			pole = losuj_pole(p);
			cout << endl << "M�j ruch: " << pole << endl;
			p[pole - 1] = 'X';
		}
		else {
			cout << endl << "Tw�j ruch: ";
			pole = wczytaj_pole(p, pole);
			p[pole - 1] = 'O';
		}
		rysuj_plansze(p);
		liczba_ruchow++;
	} while (!czy_wygrana(p, 'X') && !czy_wygrana(p, 'O') && !czy_remis(p));
	cout << endl;
	//wy�wietlenie wyniku
	if (czy_wygrana(p, 'X')) {
		cout << "Wygra�em!";
	}
	else if (czy_wygrana(p, 'O')) {
		cout << "Gratulacje! Wygra�e�!" << endl;
	}
	else {
		cout << "Remis. Nikt nie wygra�." << endl;
	}
}

//funkcja z gr� z komputerem, gdzie u�ytkownik zaczyna a komputer blokuje jego ruchy i pr�buje wygra�
void gra_trudna1(char p[]) {
	//ustawienie polskich znakow
	setlocale(LC_CTYPE, "Polish");
	int pierwszy_ruch{}, pole{}, liczba_ruchow{};

	//pobieranie pierwszego ruchu od u�ytkownika
	cout << endl << "Tw�j ruch: ";
	pole = wczytaj_pole(p, pole);
	p[pole - 1] = 'O';
	rysuj_plansze(p);

	//wstrzymanie pracy komputera na 1 sekund�
	Sleep(1000);
	//pierwszy ruch komputera w zale�no�ci od ruchu u�ytkownika
	cout << endl << "M�j ruch: ";
	//je�li u�ytkownik wybra� �rodek to komputer wybiera jeden z rog�w, w innym przypadku to komputer wybiera �rodek
	if (pole == 5) {
		mt19937 generator(time(nullptr));
		uniform_int_distribution<int> distribution(1, 4);
		pierwszy_ruch = distribution(generator);
		switch (pierwszy_ruch) {
		case 1:
			pierwszy_ruch = 1;
			break;
		case 2:
			pierwszy_ruch = 3;
			break;
		case 3:
			pierwszy_ruch = 7;
			break;
		case 4:
			pierwszy_ruch = 9;
			break;
		}
	}
	else
		pierwszy_ruch = 5;
	//wy�wietlenie ruchu komputera
	p[pierwszy_ruch - 1] = 'X';
	cout << pierwszy_ruch << endl;
	rysuj_plansze(p);

	//pobranie drugiego ruchu u�ytkownika
	cout << endl << "Tw�j ruch: ";
	pole = wczytaj_pole(p, pole);
	p[pole - 1] = 'O';
	rysuj_plansze(p);

	//drugi ruch komputera w zalezno�ci od wyboru p�l przez u�ytkownika
	Sleep(1000);
	cout << endl << "M�j ruch: ";
	//sprawdzenie czy u�ytkownik nie wybra� dw�ch rog�w, je�li tak to komputer wybiera kt�ry� ze �rodk�w bok�w
	if ((p[0] == 'O' && p[8] == 'O') || (p[2] == 'O' && p[6] == 'O'))
		pole = 1;
	//zabezpieczenie przed przegran�, komputer wybiera rogi w zale�no�ci od ustawienia p�l u�ytkownika
	else if ((p[1] == 'O' && p[6] == 'O') || (p[2] == 'O' && p[3] == 'O'))
		pole = 0;
	else if ((p[0] == 'O' && p[5] == 'O') || (p[1] == 'O' && p[8] == 'O'))
		pole = 2;
	else if ((p[3] == 'O' && p[8] == 'O') || (p[0] == 'O' && p[7] == 'O'))
		pole = 6;
	else if ((p[5] == 'O' && p[6] == 'O') || (p[2] == 'O' && p[7] == 'O'))
		pole = 8;
	else if (blok(p) < 10)
		pole = blok(p);
	else 
		pole = losuj_pole(p) - 1;
	cout << pole + 1 << endl;
	p[pole] = 'X';
	rysuj_plansze(p);

	//reszta ruch�w u�ytkownika i komputera dop�ki komputer nie wygra lub nie b�dzie remisu (u�ytkownik nie ma mo�liwo�ci wygranej)
	do {
		int pole{};
		if (liczba_ruchow % 2 == 0) {
			cout << endl << "Tw�j ruch: ";
			pole = wczytaj_pole(p, pole);
			p[pole - 1] = 'O';
		}
		else {
			//komputer sprawdza czy wygra� lub czy mo�e blokowa�, je�li nie to losuje pole i stawia tam 'X'
			if (wygrana(p) < 10)
				pole = wygrana(p);
			else if (blok(p) < 10)
				pole = blok(p);
			else {
				pole = losuj_pole(p) - 1;
			}
			Sleep(1000);
			cout << endl << "M�j ruch: " << pole + 1 << endl;
			p[pole] = 'X';
		}
		rysuj_plansze(p);
		liczba_ruchow++;
	} while (!czy_wygrana(p, 'X') && !czy_wygrana(p, 'O') && !czy_remis(p));
	if (czy_wygrana(p, 'X')) {
		cout << endl << "Wygra�em!" << endl;
	}
	else {
		cout << endl << "Remis. Nikt nie wygra�." << endl;
	}
}

//funkcja z gr� z komputerem, gdzie komputer zaczyna i p�niej wygrywa lub blokuje ruchy u�ytkownika
void gra_trudna2(char p[]) {
	//ustawienie polskich znakow
	setlocale(LC_CTYPE, "Polish");

	int pierwszy_ruch{}, pole{};

	//losowanie pierwszego ruchu komputera, jeden z rog�w
	mt19937 generator(time(nullptr));
	uniform_int_distribution<int> distribution(1, 4);
	pierwszy_ruch = distribution(generator);

	//wstrzymanie pracy komputera na 1 sekund� i rysowanie planszy z ruchem komputera
	Sleep(1000);
	cout << endl << "M�j ruch: ";
	switch (pierwszy_ruch) {
	case 1:
		pierwszy_ruch = 1;
		break;
	case 2:
		pierwszy_ruch = 3;
		break;
	case 3:
		pierwszy_ruch = 7;
		break;
	case 4:
		pierwszy_ruch = 9;
		break;
	}
	p[pierwszy_ruch - 1] = 'X';
	cout << pierwszy_ruch << endl;
	rysuj_plansze(p);

	//pobieranie pierwszego ruchu u�ytkownika
	cout << endl << "Tw�j ruch: ";
	pole = wczytaj_pole(p, pole);
	p[pole - 1] = 'O';
	rysuj_plansze(p);

	Sleep(1000);
	cout << endl << "M�j ruch: ";

	//dalsza gra w zale�no�ci od pierwszego ruchu u�ytkownika
	//pierwsza opcja: u�ytkownik wybra� jeden ze �rodk�w bok�w, to komputer wybiera �rodek
	if (pole == 2 || pole == 4 || pole == 6 || pole == 8) {
		cout << 5 << endl;
		p[4] = 'X';
		rysuj_plansze(p);

		//drugi ruch u�ytkownika
		cout << endl << "Tw�j ruch: ";
		pole = wczytaj_pole(p, pole);
		p[pole - 1] = 'O';
		rysuj_plansze(p);
		
		Sleep(1000);
		cout << endl << "M�j ruch: ";

		//komputer sprawdza czy wygra� lub czy mo�e blokowa�, je�li nie to wybiera kt�ry� z wolnych rog�w, czym umo�liwia sobie wygran�
		if (wygrana(p) < 10) 
			pole = wygrana(p);
		else if (blok(p) < 10)
			pole = blok(p);
		else {
			if (p[0] == ' ' && p[1] == ' ' && p[3] == ' ')
				pole = 0;
			else if (p[2] == ' ' && p[1] == ' ' && p[5] == ' ')
				pole = 2;
			else if (p[6] == ' ' && p[3] == ' ' && p[7] == ' ')
				pole = 6;
			else if (p[8] == ' ' && p[5] == ' ' && p[7] == ' ')
				pole = 8;
		}
		p[pole] = 'X';
		cout << pole + 1 << endl;
		rysuj_plansze(p);
		
		//je�li komputer wygra� to ko�czy gr�
		if (czy_wygrana(p, 'X')) {
			cout << endl << "Wygra�em!" << endl;
			return;
		}

		//pobieranie trzeciego ruchu u�ytkownika
		cout << endl << "Tw�j ruch: ";
		pole = wczytaj_pole(p, pole);
		p[pole - 1] = 'O';
		rysuj_plansze(p);

		//ostatni i wygrywaj�cy ruch komputera
		Sleep(1000);
		cout << endl << "M�j ruch: ";
		pole = wygrana(p);
		cout << pole + 1 << endl;
		p[pole] = 'X';
		rysuj_plansze(p);
		if (czy_wygrana(p, 'X')) {
			cout << endl << "Wygra�em!" << endl;
			return;
		}
		
	}

	//druga opcja: u�ytkownik wybra� jeden z rog�w, to komputer wybiera jeden z pozosta�ych rog�w
	else if (pole == 1 || pole == 3 || pole == 7 || pole == 9) {
		if (p[0] == ' ')
			pole = 0;
		else if (p[2] == ' ')
			pole = 2;
		else if (p[6] == ' ')
			pole = 6;
		p[pole] = 'X';
		cout << pole << endl;
		rysuj_plansze(p);

		//pobranie drugiego ruchu u�ytkownika
		cout << endl << "Tw�j ruch: ";
		pole = wczytaj_pole(p, pole);
		p[pole - 1] = 'O';
		rysuj_plansze(p);

		//trzeci ruch komputera: wygrywa i ko�czy gr� albo ustawia X w ostatnim rogu umo�liwiaj�c sobie wygran�
		Sleep(1000);
		cout << endl << "M�j ruch: ";
		if (wygrana(p) < 10)
			pole = wygrana(p);
		else if (p[2] == ' ')
			pole = 2;
		else if (p[6] == ' ')
			pole = 6;
		else if (p[8] == ' ')
			pole = 8;
		p[pole] = 'X';
		cout << pole << endl;
		rysuj_plansze(p);
		if (czy_wygrana(p, 'X')) {
			cout << endl << "Wygra�em!" << endl;
			return;
		}

		//trzeci ruch u�ytkownika, je�li komputer jeszcze nie wygra�
		cout << endl << "Tw�j ruch: ";
		pole = wczytaj_pole(p, pole);
		p[pole - 1] = 'O';
		rysuj_plansze(p);

		//ostatni i wygrywaj�cy ruch komputera
		Sleep(1000);
		cout << endl << "M�j ruch: ";
		pole = wygrana(p);
		p[pole] = 'X';
		cout << pole << endl;
		rysuj_plansze(p);
		cout << endl << "Wygra�em!" << endl;
		return;
	}
	
	//trzecia opcja: u�ytkownik wybra� �rodek, to komputer wybiera przeciwleg�y r�g
	else {
		if (pierwszy_ruch == 1)
			pole = 9;
		else if (pierwszy_ruch == 3)
			pole = 7;
		else if(pierwszy_ruch == 7)
			pole = 3;
		else if (pierwszy_ruch == 9)
			pole = 1;
		cout << pole << endl;
		p[pole - 1] = 'X';
		rysuj_plansze(p);
	
		//drugi ruch u�ytkownika
		cout << endl << "Tw�j ruch: ";
		pole = wczytaj_pole(p, pole);
		p[pole - 1] = 'O';
		rysuj_plansze(p);

		Sleep(1000);
		cout << endl << "M�j ruch: ";
		//trzeci ruch komputera w zaleznosci od drugiego ruchu u�ytkownika
		//je�li u�ytkownik wybral r�g, to komputer wybiera ostatni r�g i wygrywa
		if (pole == 1 || pole == 3 || pole == 7 || pole == 9) {
			if (p[0] == ' ')
				pole = 1;
			else if (p[2] == ' ')
				pole = 3;
			else if (p[6] == ' ')
				pole = 7;
			else if (p[8] == ' ')
				pole = 9;
			cout << pole << endl;
			p[pole - 1] = 'X';
			rysuj_plansze(p);

			cout << endl << "Tw�j ruch: ";
			pole = wczytaj_pole(p, pole);
			p[pole - 1] = 'O';
			rysuj_plansze(p);

			Sleep(1000);
			cout << endl << "M�j ruch: ";
			pole = wygrana(p);
			p[pole] = 'X';
			cout << pole << endl;
			rysuj_plansze(p);
			cout << endl << "Wygra�em!" << endl;
			return;
		}
		//gdy komputer nie wygra� to blokuje
		else {
			pole = blok(p);
			cout << pole << endl;
			p[pole] = 'X';
			rysuj_plansze(p);

			//trzeci ruch u�ytkownika
			cout << endl << "Tw�j ruch: ";
			pole = wczytaj_pole(p, pole);
			p[pole - 1] = 'O';
			rysuj_plansze(p);

			//komputer sprawdza czy wygra�, je�li nie to blokuje			
			Sleep(1000);
			cout << endl << "M�j ruch: ";
			if (wygrana(p) < 10)
				pole = wygrana(p);
			else
				pole = blok(p);
			p[pole] = 'X';
			cout << pole << endl;
			rysuj_plansze(p);
			if (czy_wygrana(p, 'X')) {
				cout << endl << "Wygra�em!" << endl;
				return;
			}

			//ostatni ruch u�ytkownika
			cout << endl << "Tw�j ruch: ";
			pole = wczytaj_pole(p, pole);
			p[pole - 1] = 'O';
			rysuj_plansze(p);

			//ostatni ruch komputera, wygrywa lub zajmuje ostatnie wolne pole
			Sleep(1000);
			cout << endl << "M�j ruch: ";
			if (wygrana(p) < 10)
				pole = wygrana(p);
			else
				for (int i = 0; i < 9; i++)
					if (p[i] == ' ')
						pole = i;
			p[pole] = 'X';
			cout << pole << endl;
			rysuj_plansze(p);

			//wy�wietlenie wyniku
			if (czy_wygrana(p, 'X'))
				cout << endl << "Wygra�em!" << endl;
			else
				cout << endl << "Remis. Nikt nie wygra�." << endl;
			return;

		}
	}
	
}