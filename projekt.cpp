#include <iostream>
#include <locale.h>
#include <Windows.h>
#include "funkcje.h"

using namespace std;

int main() {
    //pokazanie logo
    logo();

    //ustawienie polskich znaków
    setlocale(LC_CTYPE, "Polish");

    //inicjalizacja pustej planszy
    char plansza[9];
    for (int i = 0; i < 9; i++)
        plansza[i] = ' ';

    int wybor{}, odpowiedz = 1;

    do {
        //wybór gry i upewnienie się, że użytkownik podał dobrą odpowiedź
        start();
        cout << endl << "Twój wybór: ";
        cin >> wybor;
        while (cin.fail() || (wybor != 1 && wybor != 2 && wybor != 3)) {
            cout << "Wybierz poprawną opcję: ";
            cin.clear();
            cin.ignore(10000, '\n');
            cin >> wybor;
        }

        //czyszczenie ekranu
        system("cls");

        //gra w zależności od wyboru
        if (wybor == 1) {
            cout << "GRA NA DWÓCH GRACZY" << endl;
            instrukcje();
            gra_na_dwoch_graczy(plansza);
        }
        else if (wybor == 2) {
            cout << "GRA Z KOMPUTEREM" << endl;
            //wybranie poziomu trudności i upewnienie się, że użytkownik podał dobrą odpowiedź
            cout << endl << "Wybierz poziom trudności" << endl;
            cout << "1. Łatwy" << endl << "2. Trudny" << endl;
            int poziom{};
            cout << "Twój wybór: ";
            cin >> poziom;
            while (cin.fail() || (poziom != 1 && poziom != 2)) {
                cout << "Wybierz poprawną opcję: ";
                cin.clear();
                cin.ignore(10000, '\n');
                cin >> poziom;
            }
            //pytanie czy użytkownik czy zacząć i upewnienie się, że podał dobrą odpowiedź
            cout << endl << "Czy chcesz zacząć? " << endl;
            cout << "1. Tak" << endl << "2. Nie" << endl;
            int zaczynanie{};
            cout << "Twój wybór: ";
            cin >> zaczynanie;
            while (cin.fail() || (zaczynanie != 1 && zaczynanie != 2)) {
                cout << "Wybierz poprawną opcję: ";
                cin.clear();
                cin.ignore(10000, '\n');
                cin >> zaczynanie;
            }
            //wstrzymanie pracy komputera na 1 sekundę
            Sleep(1000);

            //czyszczenie ekranu 
            system("cls");

            //gra w zależności od wyborów
            if (poziom == 1 && zaczynanie == 1) {
                cout << "GRA Z KOMPUTEREM. POZIOM ŁATWY." << endl;
                cout << "Ty zaczynasz" << endl;;
                instrukcje();
                gra_latwa1(plansza);
            }
            else if (poziom == 1 && zaczynanie == 2) {
                cout << "GRA Z KOMPUTEREM. POZIOM ŁATWY." << endl;
                cout << "Ja zaczynam" << endl;;
                instrukcje();
                gra_latwa2(plansza);
            }
            else if (poziom == 2 && zaczynanie == 1) {
                cout << "GRA Z KOMPUTEREM. POZIOM TRUDNY." << endl;
                cout << "Ty zaczynasz" << endl;;
                instrukcje();
                gra_trudna1(plansza);
            }
            else if (poziom == 2 && zaczynanie == 2) {
                cout << "GRA Z KOMPUTEREM. POZIOM TRUDNY." << endl;
                cout << "Ja zaczynam" << endl;;
                instrukcje();
                gra_trudna2(plansza);
            }
        }
        //gdy gracz wybrał 3 to komputer dziękuje za grę i kończy pracę
        else if (wybor == 3) {
            cout << "Dziękuję za grę! " << (char)1 << endl;
            Sleep(2000);
            return 0;
        }

        //wstrzymanie pracy komputera na 1 sekundę
        Sleep(2000);

        //pytanie czy użytkownik chce grać dalej, jeśli wybierze '2. Nie' to komputer kończy pracę
        cout << endl << "Czy chcesz grać dalej?" << endl;
        cout << "1. Tak" << endl << "2. Nie" << endl;
        cout << "Twój wybór: ";
        cin >> odpowiedz;
        while (cin.fail() || (odpowiedz != 1 && odpowiedz != 2)) {
            cout << "Wybierz poprawną opcję: ";
            cin.clear();
            cin.ignore(10000, '\n');
            cin >> odpowiedz;
        }
        if (odpowiedz == 2) {
            system("cls");
            cout << "Dziękuję za grę! " << (char)1 << endl;
            Sleep(2000);
            return 0;
        }

        //czyszczenie planszy 
        for (int i = 0; i < 9; i++) 
            plansza[i] = ' ';

        //czyszczenie ekranu
        system("cls");
    } while (odpowiedz == 1); //jeśli użytkownik chce grać dalej

    return 0;
}

