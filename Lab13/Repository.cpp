#pragma once
#include "Repository.h"
#include <assert.h>
bool MedicamentRepository::exists(const Medicament& m) {
	try {
		find(m.getDenumire(), m.getProducator());
		return true;
	}
	catch (RepoException) {
		return false;
	}
}
const Medicament& MedicamentRepository::find(string denumire, string producator) {
	/*for (const Medicament& s : this->allMedicamente) {
		if (s.getDenumire() == denumire && s.getProducator() == producator) {
			return s;
		}
	}
	throw RepoException("Medicamentul cu denumirea "+denumire+" si producatorul "+producator +" nu exista in lista");*/

	vector<Medicament>::iterator f = std::find_if(this->allMedicamente.begin(), this->allMedicamente.end(),
		[=](const Medicament& s) {
			return s.getDenumire() == denumire && s.getProducator() == producator;
		});

	if (f != this->allMedicamente.end())
		return (*f);
	else
		throw RepoException("Medicamentul cu denumirea " + denumire + " si producatorul " + producator + " nu exista in lista\n");
}
void MedicamentRepository::store(const Medicament& m) {
	if (exists(m)) {
		throw RepoException("Medicament cu denumirea " + m.getDenumire() + " si producatorul " + m.getProducator() + " nu exista in lista");
	}
	this->allMedicamente.push_back(m);
}

void MedicamentRepository::erase(string denumire, string producator){
	/*int nr = 0;
	const Medicament& med = find(denumire,producator);
	this->allMedicamente.erase(med);
	throw RepoException("Medicamentul cu denumirea " + denumire + " si producatorul " + producator + " nu exista in lista\n");
	*/
	auto iterator = std::find_if(this->allMedicamente.begin(), this->allMedicamente.end(), [denumire,producator](const Medicament& med_verif) noexcept
		{ return med_verif.getDenumire() == denumire && med_verif.getProducator() == producator; });
	if (iterator == this->allMedicamente.end())
		throw RepoException("Element inexistent! :<\n");
	else
		this->allMedicamente.erase(iterator);
	}
void MedicamentRepository::modify(string denumire, string producator, string substanta_activa_noua, double pret_nou) {
	for (Medicament& s : this->allMedicamente) {

		if (s.getDenumire() == denumire && s.getProducator() == producator) {
			s.setSubstantaActiva(substanta_activa_noua);
			s.setPret(pret_nou);
			return;
		}
	}
	throw RepoException("Medicamentul cu denumirea " + denumire + " si producatorul " + producator + " nu exista in lista\n");
}
const vector<Medicament> MedicamentRepository::getAllMedicamente() {
	vector <Medicament> v;
	for (auto s : allMedicamente) {
		v.push_back(s);
	}
	return v;
}

void testAddRepo() {
	MedicamentRepository testRepo;
	Medicament med1{ "Nurofen", "Reckitt Benckiser(Romania) SRL","Ibuprofen",15 };
	testRepo.store(med1);
	assert(testRepo.getAllMedicamente().size() == 1);

	Medicament med2{ "NO-SPA", "Sanofi Romania SRL", "clorhidrat de drotaverina", 20 };
	testRepo.store(med2);
	Medicament med3{ "NO-SPA", "Sanofi Romania SRL", "hidroxibenzoat de metil", 17.5 };


	try {
		testRepo.store(med3);
		assert(false);
	}
	catch (RepoException) {
		assert(true);
	}
	
}
void testEraseRepo() {
	MedicamentRepository testRepo;
	Medicament med1{ "Nurofen", "Reckitt Benckiser(Romania) SRL","Ibuprofen",15 };
	testRepo.store(med1);
	assert(testRepo.getAllMedicamente().size() == 1);

	Medicament med2{ "NO-SPA", "Sanofi Romania SRL", "clorhidrat de drotaverina", 20 };
	testRepo.store(med2);
	
	assert(testRepo.getAllMedicamente().size() == 2);

	testRepo.erase("NO-SPA", "Sanofi Romania SRL");
	assert(testRepo.getAllMedicamente().size() == 1);
	try {
		testRepo.erase("NO", "Sanofi");
		assert(false);
	}
	catch (RepoException) {
		assert(true);
	}

}
void testFindRepo() {
	MedicamentRepository testRepo;

	Medicament med1{ "Nurofen", "Reckitt Benckiser(Romania) SRL","Ibuprofen",15 };
	Medicament med2{ "NO-SPA", "Sanofi Romania SRL", "clorhidrat de drotaverina", 20 };
	Medicament med3{ "Amoxicilina", "Antibiotice SA", "hidroxibenzoat de metil", 17.5 };
	testRepo.store(med1);
	testRepo.store(med2);

	assert(testRepo.exists(med1));
	assert(!testRepo.exists(med3));

	auto foundMed = testRepo.find("NO-SPA", "Sanofi Romania SRL");
	assert(foundMed.getDenumire() == "NO-SPA");
	assert(foundMed.getPret() == 20);
	assert(foundMed.getSubstantaActiva() == "clorhidrat de drotaverina");


	try {
		testRepo.find("abc", "def");
		assert(false);
	}
	catch (RepoException& ve) {
		assert(ve.getErrorMessage()== "Medicamentul cu denumirea abc si producatorul def nu exista in lista\n");
	}

	try {
		testRepo.modify("abc", "def","gfh",20);
		assert(false);
	}
	catch (RepoException& ve) {
		assert(ve.getErrorMessage() == "Medicamentul cu denumirea abc si producatorul def nu exista in lista\n");
	}
}



void testeRepo() {
	testAddRepo();
	testEraseRepo();
	testFindRepo();
}