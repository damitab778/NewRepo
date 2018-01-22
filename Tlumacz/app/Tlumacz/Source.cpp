#include <iostream>
#include <string>
#include "funkcje.h"
using namespace std; 

int main(int argc,char** argv)
{
	string spro = "";
	string spri = "";
	string sprk = "";
	string sprs = "";
	for (int i = 1; i < argc; i++){
		string wywolanie = argv[i];
		if (wywolanie == "-i") {      //sprawdza czy to prze³¹cznik -i
	
		if ((i + 1) < argc) {         //sprawdza czy jest jakiœ kolejny parametr
			
				spri = argv[i + 1];   //do nazwy pliku wejsciowego przypisuje kolejny parametr				
	}
	}
			else
	{
		if (wywolanie == "-o") {      //sprawdza czy to prze³¹cznik -o
			
		if ((i + 1) < argc) {         //sprawdza czy jest jakiœ kolejny parametr
				
				spro = argv[i + 1];   //do nazwy pliku wejsciowego przypisuje kolejny parametr				
	}
	}
			else
	{
		if (wywolanie == "-s") {      //sprawdza czy to prze³¹cznik -s
				
		if ((i + 1) < argc) {         //sprawdza czy jest jakiœ kolejny parametr
		
				sprs = argv[i + 1];   //do nazwy pliku wejsciowego przypisuje kolejny parametr				
	}
	}
			else
	{
		if (wywolanie == "-k") {       //sprawdza czy to prze³¹cznik -k
					
		if ((i + 1) < argc) {           //sprawdza czy jest jakiœ kolejny parametr

				sprk = argv[i + 1];    //do nazwy pliku wejsciowego przypisuje kolejny parametr				
	}
	}
	}
	}
	}
	}
		if (spri == "") {                                          //sprawdza czy jest podany plik wejscia
			cout << "NIE PODANO PARAMETRU PLIKU WEJSCIA! ";
		help();
		return 0;
	}
		if (spro == "") {                                          //sprawdza czy jest podany plik wyjscia
			cout << "BRAK PARAMETRU PLIKU WYJSCIA! ";
		help();
		return 0;
	}
		if (sprs == "") {                                         //sprawdza czy jest podany plik s³ownikowy
			cout << "BRAK PARAMETRU SLOWNIKA! ";
		help();
		return 0;
	}
		if (spri == sprs || spri == spro || spro == spri) {      //sprawdza czy nazwy plików siê nie powtarzaj¹
			cout << "TE SAME NAWZY PLIKOW! ";
		help();
		return 0;
	}
		if (sprk != "plen" && sprk != "enpl") {                  //sprawdza czy s¹ poprawne kierunki t³umaczenia
			cout << "ZLE PARAMETRY PROGRAMU! ";
		help();
		return 0;
	}
	tlumacz(spri, spro, sprs, sprk);
	return 0;
}