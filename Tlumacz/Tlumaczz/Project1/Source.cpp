#include <iostream>
#include <string>
#include "mojef.h"
 
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif
using namespace std;
int main(int argc,char** argv)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	string spro = "";
	string spri = "";
	string sprk = "";
	string sprs = "";
	for (int i = 1; i < argc; i++)
	{
		string wywo = argv[i];
		if (wywo == "-i") {                   //Sprawdza jaki prze³¹cznik
			if ((i + 1) < argc) {             //Sprawdza czy jest kolejny parametr
				spri = argv[i + 1];           //Przypisuje kolejny parametr do nazwy pliku wejsciowego		
			}
		}
		else
		{
			if (wywo == "-o") {               //Sprawdza jaki prze³¹cznik
				if ((i + 1) < argc) {		  //Sprawdza czy jest kolejny parametr
					spro = argv[i + 1];       //Przypisuje kolejny parametr do nazwy pliku wejsciowego			
				}
		}
		else
		{
			if (wywo == "-s") {				  //Sprawdza jaki prze³¹cznik
				if ((i + 1) < argc) {		  //Sprawdza czy jest kolejny parametr
					sprs = argv[i + 1];       //Przypisuje kolejny parametr do nazwy pliku wejsciowego				
					}
		}
		else
		{
			if (wywo == "-k") {				  //Sprawdza jaki prze³¹cznik
				if ((i + 1) < argc) {         //Sprawdza czy jest kolejny parametr
					sprk = argv[i + 1];       //Przypisuje kolejny parametr do nazwy pliku wejsciowego				
					}
					}
				}
			}
		}
	}

	if (spro == "") {                           //Sprawdza czy podano "o"
		cout << "BRAK PARAMETRU PLIKU WYJSCIA! ";
		pomoc();
		return 0;
	}
	if (sprs == "") {                           //Sprawdza czy podano "s"
		cout << "BRAK PARAMETRU SLOWNIKA! ";
		pomoc();
		return 0;
	}
	if (spri == "") {                           //Sprawdza czy podano "i"
		cout << "NIE PODANO PARAMETRU PLIKU WEJSCIA! ";
		pomoc();
		return 0;
	}
	if (spri == sprs || spri == spro || spro == spri) {   //Sprawdza czy nie powtarzaja siê nazwy plikow
		cout << "TE SAME NAWZY PLIKOW! ";
		pomoc();
		return 0;
	}

	if (sprk != "plen" && sprk != "enpl") {     //Sprawdza kierunki t³umaczenia
		cout << "ZLE PARAMETRY PROGRAMU! ";
		pomoc();
		return 0;
	}

	tlumacz(spri, spro, sprs, sprk);
	return 0;
}