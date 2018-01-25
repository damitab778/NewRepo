#pragma once
#include<string>
using namespace std;
struct drzewo;
void pomoc();
void DODWA(drzewo *& glowa, drzewo *& y);
void DeleteEng(drzewo *& glowa); 
void translate(const string & spri, const string & spro, const string & sprs, const string & sprk);
drzewo* DODW(drzewo *&glowa, const string & pol, const string & ang);
string enpl(drzewo *& glowa, const string & en);
string plen(drzewo *& glowa, const  string & pl);
