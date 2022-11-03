#pragma once
#include <string>
#include <iostream>
using std::string;
using std::cout;
using std::endl;
class Medicament {
private:
	string denumire;
	string producator;
	string substantaActiva;
	double pret;
public:
	Medicament() = default;
	Medicament(string denumire, string producator, string substantaActiva, double pret) :denumire{ denumire }, producator{ producator }, substantaActiva{ substantaActiva }, pret{ pret }{};
	Medicament(const Medicament& ot) :denumire{ ot.denumire }, producator{ ot.producator }, substantaActiva{ ot.substantaActiva }, pret{ ot.pret }{
		//cout << "[Medicament] Copy constructor called." << endl;
	}
	string getDenumire() const;
	string getProducator() const;
	string getSubstantaActiva() const;
	double getPret() const;

	void setDenumire(string denumireNoua);
	void setProducator(string producatorNou);
	void setSubstantaActiva(string substantaActivaNoua);
	void setPret(double pretNou);
};

void testeDomain();