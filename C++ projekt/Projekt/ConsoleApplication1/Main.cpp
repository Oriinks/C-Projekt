/*
Napisać aplikację która będzie ,,zarządzać'' kolekcją
prostych danych o osobach (wystarczy imię i nazwisko)
czyli na przykład tak:
struct TOsoba {
  string imie,nazwisko;
};
i dalej na przykład tak: std::vector<TOsoba> kolekcja;
Powinny być dostępne trzy opcje:
1. Przeglądanie: po jej uruchomieniu powinna
być wyświetlona lista osób z kolekcji (odpowiednio, z bazy danych)
proponowana postać listy to:
<lp><imię><nazwisko>
itd...
2. Dopisanie: po wywołaniu tej opcji program powinien zapytać
o imię osoby, jej nazwisko a potem umożliwić dopisanie
następnej, i tak w pętli. Wyjście z tej pętli powinno się
dać osiągnąć ot na przykład poprzez podanie pustego imienia i nazwiska
(tutaj zostawiam dowolność - i liczę na Państwa pomysłowość).
3. Usuwanie: na początek wyświetlamy listę jak w punkcie 1.
a potem pytamy o liczbę porządkową osoby do usunięcia.
W punktach 1. i 3. można ewentualne (to będzie dodatkowo punktowane!)
zadbać o ,,scrollowanie'' w przypadku kiedy lista nie będzie
w stanie zmieścić się w całości na ekranie.
Na ocenę bdb należy zamiast kolekcji użyć bazy danych
(dowolność wyboru - można sqlite3 albo połączyć się
przez ODBC z zainstalowaną, do wyboru, aby
tylko program funkcjonował w tym przypadku poprzez SQL).
*/

#include "pch.h"
#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <fstream>
#include "conio.h"
using namespace std;

struct TOsoba {
	string imie, nazwisko;
};


int main()
{
	int liczba = 0, licznik = 0;
	int menu;
	vector<TOsoba> os;
	menu = 1;
	while (menu != 0) {
		cout << "1: Dodaj" << endl;
		cout << "2: Wyświetl" << endl;
		cout << "3: Usun" << endl;
		cout << "4: Zapisz do pliku" << endl;
		cout << "5: Wczytaj z pliku" << endl;
		liczba = 0;
		cin >> menu;
		ofstream zapis("baza.txt");
		switch (menu)
		{
		case 1:
			while (liczba == 0) {
				string imietmp, nazwiskotmp;
				os.push_back(TOsoba());
				cout << "Podaj Imie: " << endl;
				cin >> imietmp;
				cout << "Podaj Nazwisko: " << endl;
				cin >> nazwiskotmp;
				cout << endl;
				if ((imietmp != ".") && (nazwiskotmp != ".")) {
					os[licznik].imie = imietmp;
					os[licznik].nazwisko = nazwiskotmp;
					licznik++;
				}
				else { liczba = 1; }
			}
			system("cls");
			break;
		case 2:
			for (int i = 0; i < licznik; i++) {
				cout << i + 1 << ": " << os[i].imie << " " << os[i].nazwisko << endl;
			}
			system("pause");
			system("cls");
			break;
		case 3:
			int usun;
			cout << "Wpisz id Osoby do usunięcia" << endl;
			cin >> usun;
			if (usun <= licznik) {
				os.erase(os.begin() + usun+1);
				licznik = licznik - 1;
			}
			else {
				cout << "Przekroczono wielkosc wektora." << endl;
			}
			break;
		case 4:
			for (int i = 0; i < licznik; i++) {
				zapis << os[i].imie << endl;
				zapis << os[i].nazwisko << endl;
			}
			zapis.close();
			break;
		case 5:
			ifstream  odczyt("baza.txt");
			while (!odczyt.eof()) {
				string tmpimie, tmpnazwisko;
				os.push_back(TOsoba());
				licznik = 0;
				os.clear();
				getline(odczyt,tmpimie);
				getline(odczyt,tmpnazwisko);
				cout << tmpimie<<endl;
				cout << tmpnazwisko<<endl;
				os[licznik].imie = tmpimie;
				os[licznik].nazwisko = tmpnazwisko;
				licznik++;
				cout << licznik << endl;
			}
			odczyt.close();
			break;
		}
	}
	return 0;
}