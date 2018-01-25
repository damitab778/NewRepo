#include "mojef.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
struct drzewo //Glowna struktura drzewa, posiadaj¹ca s³owa i ich t³umaczenia
{
	string pol;
	drzewo *pright;
	drzewo *pleft;
	string ang;
	drzewo *aright;
	drzewo *aleft;
};

drzewo*  DODW(drzewo *&glowa, const string & pol, const string & ang) {     //Funkcja dodaje wyrazy ang i pl do drzewa i zwraca wskaznik na nowo utworzone drzewo
	if (glowa == nullptr) {												  //Sprawdza czy g³owa nullptr jeœli tak to tworzy nowy element
		glowa = new drzewo;
		glowa->pol = pol;
		glowa->ang = ang;
		glowa->pright = nullptr;
		glowa->pleft = nullptr;
		glowa->aright = nullptr;
		glowa->aleft = nullptr;
			return glowa;
	}
	else
	{
		if (pol > (glowa->pol)) {											  //Rekurencja która sprawdza kolejnoœæ alfabetyczna
			return DODW(glowa->pleft, pol, ang);
	}
	else
	{
			return DODW(glowa->pright, pol, ang);
		}
	}
}
void DODWA(drzewo *& glowa, drzewo *& y)								//funkcja powi¹zuj¹ca angielsk¹ stronê drzewa ze sob¹
{
	if (glowa != nullptr && y != nullptr) {								//Sprawdzamy miejsce gdzie jest slowo ang i glowa czy nie sa jest nullptr
		if ((y->ang) > (glowa->ang)) {								//Sprawdzamy kolejnosc alfabetyczna
			if (glowa->aleft == nullptr) {								//Sprawdzamy czy jest kolejny element w drzewie, czy to ostatni element
				glowa->aleft = y;
	}
	else
	{
				DODWA(glowa->aleft, y);
		}
	}
	else
		if (glowa->aright == nullptr) {								//Sprawdzamy czy jest kolejny element w drzewie, czy to ostatni element
				glowa->aright = y;
	}
	else
	{
				DODWA(glowa->aright, y);
			}
	}
}


void DeleteEng(drzewo *& glowa) {										//Funkcja dzieki której zwolnimy pamiec programu
	if (glowa != nullptr) {
		DeleteEng(glowa->aleft);
		DeleteEng(glowa->aright);
		delete glowa;
	}
}
void pomoc() {															 //Funkcja z pomoca która uruchamia siê w momecie gdy wpisujemy zle parametru uruchomienia programu badz braku plikow
	cout << "Jak uruchomic program:" << endl << "-o plikwy.txt -k enpl -s slownik.txt -i plikwe.txt";
}
string enpl(drzewo *& glowa, const string & en) {						//Funkcja która zamienia slowa z EN na PL jezyk
	if (glowa != nullptr) {
		if (en == glowa->ang) {
			return glowa->pol;											//Zwraca t³umaczenie z EN na Pl
		}
		if (en > glowa->ang) {											//Sprawdzamy kolejnosc alfabetyczna
			return enpl(glowa->aleft, en);
	}
	else
	{
			return enpl(glowa->aright, en);
		}
	}
	else																//Wykonuje jeœli nie posiadamy tlumaczenia
	{
		string pl;
		pl = "[" + en + "]";
		return pl;
	}
}
string plen(drzewo *& glowa, const  string & pl) {						//Funkcja która zamienia slowa z PL na EN jezyk
	if (glowa != nullptr) {
		if (pl == glowa->pol) {
			return glowa->ang;											//Zwraca t³umaczenie z PL na EN
		}
		if (pl > glowa->pol) {											//Sprawdzamy kolejnosc alfabetyczna
			return plen(glowa->pleft, pl);
	}
	else
	{
			return plen(glowa->pright, pl);
	}
	}
	else                                                               //Wykonuje jeœli nie posiadamy tlumaczenia
	{
		string en;
		en = "[" + pl + "]";
		return en;
	}
}
void translate(const string & si, const string & so, const string & ss, const string & sk) {  //G³owna funkcja t³umaczy tekst
	ifstream pli;			//WEJ
	ofstream plo;			//WYJ
	ifstream pls;			//slownika
	pli.open(si);			
	plo.open(so);			
	pls.open(ss);			
	string linia, slowo1, slowo2;		//"linia" Zmienna ktora przechowuje linie z pliku
	drzewo *glowa = nullptr;
	drzewo *wsk = nullptr;
	if (!pli.is_open()) {     //Kontrola czy uda³o sie otworzyc plik
		cout << "Blad pliku WEJSCIOWEGO"<<endl;
		pli.close();
		plo.close();
		pomoc();
		return;
	}
	if (!plo.is_open()) {		//Kontrola czy uda³o sie otworzyc plik
		cout << "Blad pliku WYJSCIOWEGO" << endl;
		pli.close();
		plo.close();
		pomoc();
		return;
	}
	if (!pls.is_open()) {	//Kontrola czy uda³o sie otworzyc plik
		cout << "Brak SLOWNIKA" << endl;
		pli.close();
		plo.close();
		pomoc();
		return;
	}
	getline(pls, linia);		//Pobiera linie z pliku do zmiennej linia
	if (!pls.good()) {		//Kontrola czy istnieje slownik
		cout << "Blad slownika" << endl;
		pls.close();
		pli.close();
		plo.close();
		pomoc();
		return;
	}
	istringstream is(linia);
	is >> slowo1 >> slowo2;			//Przypisuje zmiennym slowo1, slowo2 wyrazy z pliku
	if (is.fail()) {				//Komunikat, ze nie udalo sie przypisanie wyrazow do zmiennych slowo1, slowo2
		cout << "Zle dane" << endl;
		pli.close();
		plo.close();
		pls.close();
		pomoc();
		return;
	}
	DODW(glowa, slowo1, slowo2);	//dodaje wyraz wraz z t³umaczeniem do drzewa
	while (pls.good()) {
		getline(pls, linia);		//pobiera linie z pliku do zmiennej linia	
		istringstream iss(linia);
		iss >> slowo1 >> slowo2;	//przypisuje zmiennym slowo1 slowo2 wyrazy z pliku
		if (iss.fail()) {			//wykonuje sie jak nie uda³a siê operacja przypisania wyrazów z pliku
			cout << "Zle dane" << endl;
			pli.close();
			plo.close();
			pls.close();
			DeleteEng(glowa);
			pomoc();
			return;
		}
		wsk = DODW(glowa, slowo1, slowo2);		//dodaje wyraz z t³umaczeniem na drzewo
		DODWA(glowa, wsk);						//umieszcza wskazanie na angielski wyraz
	}
	pls.close();
	if (sk == "plen") {
		if (!pli.good()) {						//Kontrola czy istnieje plik wejscia
			pli.close();
			plo.close();
			DeleteEng(glowa);
			return;
		}
		while (!pli.eof()) {
			getline(pli, linia);				
			int i = 0;							//deklaracja licznika
		while (i < linia.length()) {			//sprawdza czy licznik nie jest wy¿szy od d³ugoœci wyrazu
			if ((linia[i] > 64 && linia[i] < 91) || (linia[i] > 96 && linia[i] < 123)) {    //Sprawdzamy dzieki ascii czy to litera
			int pomi = i;						//pomocniczy licznik zapamietuje poczatkowe miejsce znaku
		while ((linia[i] > 64 && linia[i] < 91) || (linia[i] > 96 && linia[i] < 123)) {		//Dodaje i do czasu gdy bd litery
						i++;
		}
		string wyraz = linia.substr(pomi, (i - pomi));				//wycina wyraz z linii substr-Zwraca podci¹g ³añcucha znaków
			if (wyraz[0] > 64 && wyraz[0] < 91) {					//sprawdza czy du¿a litera
				string s1 = plen(glowa, wyraz);						//szuka t³umaczenia
					char z1 = s1[0];
			if (z1 == '[') {									//jeœli nie znalaz³o t³umaczenia
				wyraz[0] = wyraz[0] + 32;						//zamienia pierwsz¹ literê na ma³¹
				string s2 = plen(glowa, wyraz);					//szuka t³umaczenia z ma³¹ liter¹
					char z2 = s2[0];
			if (z2 == '[') {									//sprawdza czy znalaz³ t³umaczenie dla ma³ej litery
				plo << s1;										//jeœli nie znalaz³o to pisze bez t³umaczenia z du¿a liter¹
		}
		else
	    {
			if (z2 > 64 && z2 < 91) {					//jeœli znalaz³o to sprawdza czy pierwsza litera jest du¿a
				plo << s2;								//jesli tak przepisuje t³umaczenie
		}
		else
		{
			s2[0] = s2[0] - 32;							//jeœli nie zmienia pierwsz¹ litere na du¿¹
			plo << s2;
				}
			}
		}
		else                                                //jeœli znalaz³o t³umaczenie dla du¿ej litery 
		{
			if (s1[0] > 64 && s1[0] < 91) {					//sprawdza czy t³umaczenie te¿ ma du¿¹ litere
				plo << s1;									//jesli tak przepisuje bez zmian
		}
		else
		{
			s1[0] = s1[0] - 32;								//jeœli nie zamienia j¹ na du¿¹
			plo << s1;
				}
			}
		}
		else
		{
			string s1 = plen(glowa, wyraz);					//tworzy t³umaczenie dla ma³ej litery
			plo << s1;
			}
		}
		else
		{
			plo << linia[i];								//przepisuje gdy brak litery
			i++;
			}
		}
			plo << endl;
		}
	}
	else
	{
		if (!pli.good())									//jeœli b³¹d przy pobieraniu z pliku to sie wykonuje
		{
			pli.close();
			plo.close();
			DeleteEng(glowa);							
			return;
		}

		while (!pli.eof()) {
			getline(pli, linia);												
			int i = 0;										//deklaracja licznika
		while (i < linia.length()) {						//sprawdza czy licznik nie jest wy¿szy od d³ugoœci wyrazu
			if ((linia[i] > 64 && linia[i] < 91) || (linia[i] > 96 && linia[i] < 123)) {	//Sprawdzamy dzieki ascii czy to litera
			int pomi = i;																	//pomocniczy licznik zapamietuje poczatkowe miejsce znaku
		while ((linia[i] > 64 && linia[i] < 91) || (linia[i] > 96 && linia[i] < 123)) {		//Dodaje i do czasu gdy bd litery
			i++;
	}
		string wyraz = linia.substr(pomi, (i - pomi));				//wycina wyraz z linii
			if (wyraz[0] > 64 && wyraz[0] < 91) {					//sprawdza czy du¿a litera
				string s1 = enpl(glowa, wyraz);						//szuka t³umaczenia
				char z1 = s1[0];
			if (z1 == '[') {									//jeœli nie znalaz³o t³umaczenia
				wyraz[0] = wyraz[0] + 32;						//zamienia pierwsz¹ literê na ma³¹
				string s2 = enpl(glowa, wyraz);					//szuka t³umaczenia z ma³¹ liter¹
				char z2 = s2[0];
			if (z2 == '[') {									//sprawdza czy znalaz³ t³umaczenie dla ma³ej litery
				plo << s1;										//jeœli nie znalaz³o to pisze bez t³umaczenia z du¿a liter¹
		}
		else
		{
			if (z2 > 64 && z2 < 91) {						//jeœli znalaz³o to sprawdza czy pierwsza litera jest du¿a
				plo << s2;									//jesli tak przepisuje t³umaczenie
		}
		else
		{
				s2[0] = s2[0] - 32;							//jeœli nie zmienia pierwsz¹ litere na du¿¹
				plo << s2;
				}
			}
		}
		else															//jeœli znalaz³o t³umaczenie dla du¿ej litery 
		{
			if (s1[0] > 64 && s1[0] < 91) {								//sprawdza czy t³umaczenie te¿ ma du¿¹ litere
				plo << s1;												//jesli tak przepisuje bez zmian
		}
		else
		{
				s1[0] = s1[0] - 32;										//jeœli nie zamienia j¹ na du¿¹
				plo << s1;
				}
			}
		}
		else
		{
				string s1 = enpl(glowa, wyraz);							//tworzy t³umaczenie dla ma³ej litery
				plo << s1;
			}
		}
		else
		{
				plo << linia[i];										//przepisuje gdy brak litery
				i++;
			}
		}
			    plo << endl;
		}
	}
	plo.close();
	pli.close();
	DeleteEng(glowa);
	return;
}
