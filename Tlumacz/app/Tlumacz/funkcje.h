#pragma once
#include<string>

struct drzewo;
void help();
void Dodajang(drzewo *& g, drzewo *& v);
drzewo* Dodajwyraz(drzewo *&g, const std::string & pol, const std::string & ang);
void UsunDrzewoEng(drzewo *& g);
std::string enpl(drzewo *& g, const std::string & en);
std::string plen(drzewo *& g, const  std::string & pl);
void tlumacz(const std::string & si, const std::string & so, const std::string & ss, const std::string & sk);