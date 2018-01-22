#pragma once
#include<string>
using namespace std;
struct drzewo;
void pomoc();
void DODWA(drzewo *& g, drzewo *& v);
void UsunDrzewoEng(drzewo *& g); 
void tlumacz(const string & si, const string & so, const string & ss, const string & sk);
drzewo* DODW(drzewo *&g, const string & pol, const string & ang);
string enpl(drzewo *& g, const string & en);
string plen(drzewo *& g, const  string & pl);
