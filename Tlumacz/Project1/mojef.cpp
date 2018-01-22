#include "mojef.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
struct drzewo //struktura drzewa posiadaj¹ca s³owa i ich t³umaczenia
{
	string pol;
	string ang;
	drzewo *pright;
	drzewo *pleft;
	drzewo *aright;
	drzewo *aleft;
};

void pomoc() //funkcja wypisuj¹ca pomoc
{
	cout << "Przykladowe wywolanie programu:" << endl << "-i plikwe.txt -o plikwy.txt -k enpl -s slownik.txt";
}
void DODWA(drzewo *& glowa, drzewo *& y)//funkcja powi¹zuj¹ca angielsk¹ stronê drzewa ze sob¹
{
	if (glowa != nullptr && y != nullptr)//sprawdza glowa i miejsce gdzie jest s³owo ang nie jest nuulptr
	{
		if ((y->ang) > (glowa->ang))//sprawdza kolejnoœæ w alfabecie
		{
			if (glowa->aleft == nullptr)//sprawdza czy jest kolejny element w drzewie
			{
				glowa->aleft = y;
			}
			else
			{
				DODWA(glowa->aleft, y);
			}
		}
		else
			if (glowa->aright == nullptr)//sprawdza czy jest kolejny element w drzewie
			{
				glowa->aright = y;
			}
			else
			{
				DODWA(glowa->aright, y);
			}
	}
}
drzewo*  DODW(drzewo *&glowa, const string & pol, const string & ang)//funkcja dodaje elementy do drzewa,zwraca wskazanie na utworzone drzewo
{
	if (glowa == nullptr)//sprawdza czy g³owa jest nullptr i wtedy tworzy nowy element
	{
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
		if (pol > (glowa->pol))//sprawdza kolejnoœæ w alfabecie i wywo³uje sam¹ siebie
		{
			return DODW(glowa->pleft, pol, ang);
		}
		else
		{
			return DODW(glowa->pright, pol, ang);
		}
	}
}

void UsunDrzewoEng(drzewo *& glowa)//funkcja usuwa drzewo
{
	if (glowa != nullptr)
	{
		UsunDrzewoEng(glowa->aleft);
		UsunDrzewoEng(glowa->aright);
		delete glowa;
	}
}
string enpl(drzewo *& glowa, const string & en)//funkcja zamienia s³owo z ang na pol
{
	if (glowa != nullptr)
	{
		if (en == glowa->ang)
		{
			return glowa->pol;//zwraca t³umaczenie
		}
		if (en > glowa->ang)//sprawdza kolejnoœæ w alfabecie
		{
			return enpl(glowa->aleft, en);
		}
		else
		{
			return enpl(glowa->aright, en);
		}
	}
	else//wykonuje siê jak nie znajdzie t³umaczenia
	{
		string pl;
		pl = "[" + en + "]";
		return pl;
	}
}
string plen(drzewo *& glowa, const  string & pl)//funkcja zamienia s³owo z pol na ang
{
	if (glowa != nullptr)
	{
		if (pl == glowa->pol)
		{
			return glowa->ang;//zwraca t³umaczenie
		}
		if (pl > glowa->pol)//sprawdza kolejnoœæ w alfabecie
		{
			return plen(glowa->pleft, pl);
		}
		else
		{
			return plen(glowa->pright, pl);
		}
	}
	else//wykonuje siê jak nie znajdzie t³umaczenia
	{
		string en;
		en = "[" + pl + "]";
		return en;
	}
}
void tlumacz(const string & si, const string & so, const string & ss, const string & sk)//g³ówna funkcja t³umacz¹ca tekst
{
	ifstream pli;//plik wejsciowy
	ofstream plo;//plik wyjsciowy
	ifstream pls;//plik slownika
	pli.open(si);//otwiera plik wejsciowy
	plo.open(so);//otwiera plik wyjsciowy
	pls.open(ss);//otwiera plik slownika
	string s, w1, w2;//s- jest linia z pliku,
	drzewo *glowa = nullptr;
	drzewo *v = nullptr;
	if (!pli.is_open())//wykonuje siê jeœli nie powiod³o siê otwieranie
	{
		cout << "Blad pliku WEJSCIOWEGO"<<endl;
		pli.close();
		plo.close();
		pomoc();
		return;
	}
	if (!plo.is_open())//wykonuje siê jeœli nie powiod³o sie otwieranie
	{
		cout << "Blad pliku WYJSCIOWEGO" << endl;
		pli.close();
		plo.close();
		pomoc();
		return;
	}
	if (!pls.is_open())//wykonuje siê jeœli nie powiod³o siê otwieranie
	{
		cout << "Brak SLOWNIKA" << endl;
		pli.close();
		plo.close();
		pomoc();
		return;
	}
	getline(pls, s);//pobiera linie z pliku do zmiennej s
	if (!pls.good())//jeœli b³¹d przy pobieraniu z pliku to sie wykonuje
	{
		cout << "Blad slownika" << endl;
		pls.close();
		pli.close();
		plo.close();
		pomoc();
		return;
	}
	istringstream is(s);
	is >> w1 >> w2;//przypisuje zmiennym w1 w2 wyrazy z pliku
	if (is.fail())//wykonuje sie jak nie uda³a siê operacja przypisania wyrazów z pliku
	{
		cout << "Zle dane" << endl;
		pli.close();
		plo.close();
		pls.close();
		pomoc();
		return;
	}
	DODW(glowa, w1, w2);//dodaje wyraz wraz z t³umaczeniem do drzewa
	while (pls.good())
	{
		getline(pls, s);	//pobiera linie z pliku do zmiennej s	
		istringstream iss(s);
		iss >> w1 >> w2;//przypisuje zmiennym s1 s2 wyrazy z pliku
		if (iss.fail())//wykonuje sie jak nie uda³a siê operacja przypisania wyrazów z pliku
		{
			cout << "Zle dane" << endl;
			pli.close();
			plo.close();
			pls.close();
			UsunDrzewoEng(glowa);//usuwa drzewo
			pomoc();
			return;
		}
		v = DODW(glowa, w1, w2);//dodaje wyraz z t³umaczeniem na drzewo
		DODWA(glowa, v);//umieszcza wskazanie na angielski wyraz
	}
	pls.close();
	if (sk == "plen")
	{
		if (!pli.good())//jeœli b³¹d przy pobieraniu z pliku to sie wykonuje
		{
			pli.close();
			plo.close();
			UsunDrzewoEng(glowa);//usuwa drzewo
			return;
		}

		while (!pli.eof())
		{
			getline(pli, s);//pobiera linie z pliku do zmiennej s	
			int i = 0;//deklaracja licznika
			while (i < s.length())//sprawdza czy licznik nie jest wy¿szy od d³ugoœci wyrazu
			{
				if ((s[i] > 64 && s[i] < 91) || (s[i] > 96 && s[i] < 123))//sprawdza czy jest litera
				{
					int pomi = i;//pom licznik zapamietuje poczatkowe miejsce znaku
					while ((s[i] > 64 && s[i] < 91) || (s[i] > 96 && s[i] < 123))//dodaje i tak d³ugo az sa litery 
					{
						i++;
					}
					string wyraz = s.substr(pomi, (i - pomi));//wycina wyraz z linii
					if (wyraz[0] > 64 && wyraz[0] < 91)//sprawdza czy du¿a litera
					{
						string s1 = plen(glowa, wyraz);//szuka t³umaczenia
						char z1 = s1[0];
						if (z1 == '[')//jeœli nie znalaz³o t³umaczenia
						{
							wyraz[0] = wyraz[0] + 32;//zamienia pierwsz¹ literê na ma³¹
							string s2 = plen(glowa, wyraz);//szuka t³umaczenia z ma³¹ liter¹
							char z2 = s2[0];
							if (z2 == '[')//sprawdza czy znalaz³ t³umaczenie dla ma³ej litery
							{
								plo << s1;//jeœli nie znalaz³o to pisze bez t³umaczenia z du¿a liter¹
							}
							else
							{
								if (z2 > 64 && z2 < 91)//jeœli znalaz³o to sprawdza czy pierwsza litera jest du¿a
								{
									plo << s2;//jesli tak przepisuje t³umaczenie
								}
								else
								{
									s2[0] = s2[0] - 32;//jeœli nie zmienia pierwsz¹ litere na du¿¹
									plo << s2;
								}
							}
						}
						else//jeœli znalaz³o t³umaczenie dla du¿ej litery 
						{
							if (s1[0] > 64 && s1[0] < 91)//sprawdza czy t³umaczenie te¿ ma du¿¹ litere
							{
								plo << s1;//jesli tak przepisuje bez zmian
							}
							else
							{
								s1[0] = s1[0] - 32;//jeœli nie zamienia j¹ na du¿¹
								plo << s1;
							}
						}
					}
					else
					{
						string s1 = plen(glowa, wyraz);//tworzy t³umaczenie dla ma³ej litery
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
		if (!pli.good())//jeœli b³¹d przy pobieraniu z pliku to sie wykonuje
		{
			pli.close();
			plo.close();
			UsunDrzewoEng(glowa);//usuwa drzewo
			return;
		}

		while (!pli.eof())
		{
			getline(pli, s);//pobiera linie z pliku do zmiennej s	
			int i = 0;//deklaracja licznika
			while (i < s.length())//sprawdza czy licznik nie jest wy¿szy od d³ugoœci wyrazu
			{
				if ((s[i] > 64 && s[i] < 91) || (s[i] > 96 && s[i] < 123))//sprawdza czy jest litera
				{
					int pomi = i;//pom licznik zapamietuje poczatkowe miejsce znaku
					while ((s[i] > 64 && s[i] < 91) || (s[i] > 96 && s[i] < 123))//dodaje i tak d³ugo az sa litery 
					{
						i++;
					}
					string wyraz = s.substr(pomi, (i - pomi));//wycina wyraz z linii
					if (wyraz[0] > 64 && wyraz[0] < 91)//sprawdza czy du¿a litera
					{
						string s1 = enpl(glowa, wyraz);//szuka t³umaczenia
						char z1 = s1[0];
						if (z1 == '[')//jeœli nie znalaz³o t³umaczenia
						{
							wyraz[0] = wyraz[0] + 32;//zamienia pierwsz¹ literê na ma³¹
							string s2 = enpl(glowa, wyraz);//szuka t³umaczenia z ma³¹ liter¹
							char z2 = s2[0];
							if (z2 == '[')//sprawdza czy znalaz³ t³umaczenie dla ma³ej litery
							{
								plo << s1;//jeœli nie znalaz³o to pisze bez t³umaczenia z du¿a liter¹
							}
							else
							{
								if (z2 > 64 && z2 < 91)//jeœli znalaz³o to sprawdza czy pierwsza litera jest du¿a
								{
									plo << s2;//jesli tak przepisuje t³umaczenie
								}
								else
								{
									s2[0] = s2[0] - 32;//jeœli nie zmienia pierwsz¹ litere na du¿¹
									plo << s2;
								}
							}
						}
						else//jeœli znalaz³o t³umaczenie dla du¿ej litery 
						{
							if (s1[0] > 64 && s1[0] < 91)//sprawdza czy t³umaczenie te¿ ma du¿¹ litere
							{
								plo << s1;//jesli tak przepisuje bez zmian
							}
							else
							{
								s1[0] = s1[0] - 32;//jeœli nie zamienia j¹ na du¿¹
								plo << s1;
							}
						}
					}
					else
					{
						string s1 = enpl(glowa, wyraz);//tworzy t³umaczenie dla ma³ej litery
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
	UsunDrzewoEng(glowa);//usuwa drzewo
	return;
}
