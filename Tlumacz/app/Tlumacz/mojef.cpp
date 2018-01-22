#include "funkcje.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
struct drzewo //struktura drzewa posiadaj�ca s�owa i ich t�umaczenia
{
	string pol;
	string ang;
	drzewo *pright;
	drzewo *pleft;
	drzewo *aright;
	drzewo *aleft;
};
void help() //funkcja wypisuj�ca pomoc
{
	cout << "Przykladowe wywolanie programu: " << endl << " -i plikwe.txt -o plikwy.txt -k enpl -s slownik.txt";
}
void Dodajang(drzewo *& g, drzewo *& wywolanie)//funkcja powi�zuj�ca angielsk� stron� drzewa ze sob�
{
	if (g != nullptr && wywolanie != nullptr)//sprawdza glowa i miejsce gdzie jest s�owo ang nie jest nuulptr
	{
		if ((wywolanie->ang) > (g->ang))//sprawdza kolejno�� w alfabecie
		{
			if (g->aleft == nullptr)//sprawdza czy jest kolejny element w drzewie
			{
				g->aleft = wywolanie;
			}
			else
			{
				Dodajang(g->aleft, wywolanie);
			}
		}
		else
			if (g->aright == nullptr)//sprawdza czy jest kolejny element w drzewie
			{
				g->aright = wywolanie;
			}
			else
			{
				Dodajang(g->aright, wywolanie);
			}
	}
}
drzewo* Dodajwyraz(drzewo *&g, const string & pol, const string & ang)//funkcja dodaje elementy do drzewa,zwraca wskazanie na utworzone drzewo
{
	if (g == nullptr)//sprawdza czy g�owa jest nullptr i wtedy tworzy nowy element
	{
		g = new drzewo;
		g->pol = pol;
		g->ang = ang;
		g->pright = nullptr;
		g->pleft = nullptr;
		g->aright = nullptr;
		g->aleft = nullptr;
		return g;
	}
	else
	{
		if (pol > (g->pol))//sprawdza kolejno�� w alfabecie i wywo�uje sam� siebie
		{
			return Dodajwyraz(g->pleft, pol, ang);
		}
		else
		{
			return Dodajwyraz(g->pright, pol, ang);
		}
	}
}

void UsunDrzewoEng(drzewo *& g)//funkcja usuwa drzewo
{
	if (g != nullptr)
	{
		UsunDrzewoEng(g->aleft);
		UsunDrzewoEng(g->aright);
		delete g;
	}
}
string enpl(drzewo *& g, const string & en)//funkcja zamienia s�owo z ang na pol
{
	if (g != nullptr)
	{
		if (en == g->ang)
		{
			return g->pol;//zwraca t�umaczenie
		}
		if (en > g->ang)//sprawdza kolejno�� w alfabecie
		{
			return enpl(g->aleft, en);
		}
		else
		{
			return enpl(g->aright, en);
		}
	}
	else//wykonuje si� jak nie znajdzie t�umaczenia
	{
		string pl;
		pl = "[" + en + "]";
		return pl;
	}
}
string plen(drzewo *& g, const  string & pl)//funkcja zamienia s�owo z pol na ang
{
	if (g != nullptr)
	{
		if (pl == g->pol)
		{
			return g->ang;//zwraca t�umaczenie
		}
		if (pl > g->pol)//sprawdza kolejno�� w alfabecie
		{
			return plen(g->pleft, pl);
		}
		else
		{
			return plen(g->pright, pl);
		}
	}
	else//wykonuje si� jak nie znajdzie t�umaczenia
	{
		string en;
		en = "[" + pl + "]";
		return en;
	}
}
void tlumacz(const string & spri, const string & spro, const string & sprs, const string & sprk)//g��wna funkcja t�umacz�ca tekst
{
	ifstream pli;//plik wejsciowy
	ofstream plo;//plik wyjsciowy
	ifstream pls;//plik slownika
	pli.open(spri);//otwiera plik wejsciowy
	plo.open(spro);//otwiera plik wyjsciowy
	pls.open(sprs);//otwiera plik slownika
	string s, w1, w2;//s- jest linia z pliku,
	drzewo *g = nullptr;
	drzewo *wywolanie = nullptr;
	if (!pli.is_open())//wykonuje si� je�li nie powiod�o si� otwieranie
	{
		cout << "Blad pliku WEJSCIOWEGO"<<endl;
		pli.close();
		plo.close();
		help();
		return;
	}
	if (!plo.is_open())//wykonuje si� je�li nie powiod�o sie otwieranie
	{
		cout << "Blad pliku WYJSCIOWEGO" << endl;
		pli.close();
		plo.close();
		help();
		return;
	}
	if (!pls.is_open())//wykonuje si� je�li nie powiod�o si� otwieranie
	{
		cout << "Blad slownika" << endl;
		pli.close();
		plo.close();
		help();
		return;
	}
	getline(pls, s);//pobiera linie z pliku do zmiennej s
	if (!pls.good())//je�li b��d przy pobieraniu z pliku to sie wykonuje
	{
		cout << "brak danych" << endl;
		pls.close();
		pli.close();
		plo.close();
		help();
		return;
	}
	istringstream is(s);
	is >> w1 >> w2;//przypisuje zmiennym w1 w2 wyrazy z pliku
	if (is.fail())//wykonuje sie jak nie uda�a si� operacja przypisania wyraz�w z pliku
	{
		cout << "Zle dane" << endl;
		pli.close();
		plo.close();
		pls.close();
		help();
		return;
	}
	Dodajwyraz(g, w1, w2);//dodaje wyraz wraz z t�umaczeniem do drzewa
	while (pls.good())
	{
		getline(pls, s);	//pobiera linie z pliku do zmiennej s	
		istringstream iss(s);
		iss >> w1 >> w2;//przypisuje zmiennym s1 s2 wyrazy z pliku
		if (iss.fail())//wykonuje sie jak nie uda�a si� operacja przypisania wyraz�w z pliku
		{
			cout << "bledne dane"<<endl;
			pli.close();
			plo.close();
			pls.close();
			UsunDrzewoEng(g);//usuwa drzewo
			help();
			return;
		}
		wywolanie = Dodajwyraz(g, w1, w2);//dodaje wyraz z t�umaczeniem na drzewo
		Dodajang(g, wywolanie);//umieszcza wskazanie na angielski wyraz
	}
	pls.close();
	if (sprk == "plen")
	{
		if (!pli.good())//je�li b��d przy pobieraniu z pliku to sie wykonuje
		{
			pli.close();
			plo.close();
			UsunDrzewoEng(g);//usuwa drzewo
			return;
		}

		while (!pli.eof())
		{
			getline(pli, s);//pobiera linie z pliku do zmiennej s	
			int i = 0;//deklaracja licznika
			while (i < s.length())//sprawdza czy licznik nie jest wy�szy od d�ugo�ci wyrazu
			{
				if ((s[i] > 64 && s[i] < 91) || (s[i] > 96 && s[i] < 123))//sprawdza czy jest litera
				{
					int pomi = i;//pom licznik zapamietuje poczatkowe miejsce znaku
					while ((s[i] > 64 && s[i] < 91) || (s[i] > 96 && s[i] < 123))//dodaje i tak d�ugo az sa litery 
					{
						i++;
					}
					string wyraz = s.substr(pomi, (i - pomi));//wycina wyraz z linii
					if (wyraz[0] > 64 && wyraz[0] < 91)//sprawdza czy du�a litera
					{
						string s1 = plen(g, wyraz);//szuka t�umaczenia
						char z1 = s1[0];
						if (z1 == '[')//je�li nie znalaz�o t�umaczenia
						{
							wyraz[0] = wyraz[0] + 32;//zamienia pierwsz� liter� na ma��
							string s2 = plen(g, wyraz);//szuka t�umaczenia z ma�� liter�
							char z2 = s2[0];
							if (z2 == '[')//sprawdza czy znalaz� t�umaczenie dla ma�ej litery
							{
								plo << s1;//je�li nie znalaz�o to pisze bez t�umaczenia z du�a liter�
							}
							else
							{
								if (z2 > 64 && z2 < 91)//je�li znalaz�o to sprawdza czy pierwsza litera jest du�a
								{
									plo << s2;//jesli tak przepisuje t�umaczenie
								}
								else
								{
									s2[0] = s2[0] - 32;//je�li nie zmienia pierwsz� litere na du��
									plo << s2;
								}
							}
						}
						else//je�li znalaz�o t�umaczenie dla du�ej litery 
						{
							if (s1[0] > 64 && s1[0] < 91)//sprawdza czy t�umaczenie te� ma du�� litere
							{
								plo << s1;//jesli tak przepisuje bez zmian
							}
							else
							{
								s1[0] = s1[0] - 32;//je�li nie zamienia j� na du��
								plo << s1;
							}
						}
					}
					else
					{
						string s1 = plen(g, wyraz);//tworzy t�umaczenie dla ma�ej litery
						plo << s1;
					}
				}
				else
				{
					plo << s[i];//przepisuje gdy brak litery
					i++;
				}
			}
			plo << endl;
		}
	}
	else
	{
		if (!pli.good())//je�li b��d przy pobieraniu z pliku to sie wykonuje
		{
			pli.close();
			plo.close();
			UsunDrzewoEng(g);//usuwa drzewo
			return;
		}

		while (!pli.eof())
		{
			getline(pli, s);//pobiera linie z pliku do zmiennej s	
			int i = 0;//deklaracja licznika
			while (i < s.length())//sprawdza czy licznik nie jest wy�szy od d�ugo�ci wyrazu
			{
				if ((s[i] > 64 && s[i] < 91) || (s[i] > 96 && s[i] < 123))//sprawdza czy jest litera
				{
					int pomi = i;//pom licznik zapamietuje poczatkowe miejsce znaku
					while ((s[i] > 64 && s[i] < 91) || (s[i] > 96 && s[i] < 123))//dodaje i tak d�ugo az sa litery 
					{
						i++;
					}
					string wyraz = s.substr(pomi, (i - pomi));//wycina wyraz z linii
					if (wyraz[0] > 64 && wyraz[0] < 91)//sprawdza czy du�a litera
					{
						string s1 = enpl(g, wyraz);//szuka t�umaczenia
						char z1 = s1[0];
						if (z1 == '[')//je�li nie znalaz�o t�umaczenia
						{
							wyraz[0] = wyraz[0] + 32;//zamienia pierwsz� liter� na ma��
							string s2 = enpl(g, wyraz);//szuka t�umaczenia z ma�� liter�
							char z2 = s2[0];
							if (z2 == '[')//sprawdza czy znalaz� t�umaczenie dla ma�ej litery
							{
								plo << s1;//je�li nie znalaz�o to pisze bez t�umaczenia z du�a liter�
							}
							else
							{
								if (z2 > 64 && z2 < 91)//je�li znalaz�o to sprawdza czy pierwsza litera jest du�a
								{
									plo << s2;//jesli tak przepisuje t�umaczenie
								}
								else
								{
									s2[0] = s2[0] - 32;//je�li nie zmienia pierwsz� litere na du��
									plo << s2;
								}
							}
						}
						else//je�li znalaz�o t�umaczenie dla du�ej litery 
						{
							if (s1[0] > 64 && s1[0] < 91)//sprawdza czy t�umaczenie te� ma du�� litere
							{
								plo << s1;//jesli tak przepisuje bez zmian
							}
							else
							{
								s1[0] = s1[0] - 32;//je�li nie zamienia j� na du��
								plo << s1;
							}
						}
					}
					else
					{
						string s1 = enpl(g, wyraz);//tworzy t�umaczenie dla ma�ej litery
						plo << s1;
					}
				}
				else
				{
					plo << s[i];//przepisuje gdy brak litery
					i++;
				}
			}
			plo << endl;
		}
	}
	plo.close();
	pli.close();
	UsunDrzewoEng(g);//usuwa drzewo
	return;
}
