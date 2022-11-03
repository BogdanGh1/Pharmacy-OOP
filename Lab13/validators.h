#pragma once

#include "Medicament.h"
#include <vector>
#include <string>
using std::string;
using std::vector;
class ValidationException {
	vector<string> errorMsg;
public:
	ValidationException(vector<string> errorMessages) :errorMsg{ errorMessages } {};

	string getErrorMessages() {
		string fullMsg = "";
		for (const string e : errorMsg) {
			fullMsg += e + "\n";
		}
		return fullMsg;
	}
};
/*
Clasa pentru validarea medicamentelor
Un medicament este valid daca:
	are denumirea formata din mai mult de 2 caractere
	are producatorul format din mai mult de 2 caractere
	are substanta Activa formata din mai mult de 2 caractere
	pretul medicamentului este mai mare decat 0;
*/
class MedicamentValidator {

public:
	void valideaza(const Medicament& m) {
		vector<string> errors;
		if (m.getDenumire().length() < 2)
			errors.push_back("Denumirea trebuie sa aiba cel putin 2 caractere.");
		if (m.getProducator().length() < 2)
			errors.push_back("Producatorul trebuie sa aiba cel putin 2 caractere.");
		if (m.getSubstantaActiva().length() < 2)
			errors.push_back("Substanta activa trebuie sa aiba cel putin 2 caractere.");
		if (m.getPret() <= 0)
			errors.push_back("Pretul trebuie sa fie mai mare decat 0.");

		if (errors.size() > 0)
			throw ValidationException(errors);
	}
};

inline void testValideaza() {
	Medicament med{ "Nurofen", "Reckitt Benckiser(Romania) SRL","a",-1 };
	MedicamentValidator testVal;
	testVal.valideaza(med);
}
