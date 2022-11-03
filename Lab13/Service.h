#pragma once
#include "Repository.h"
#include "validators.h"
#include "Undo.h"
#include "Reteta.h"
#include <algorithm>
#include <memory>
using std::unique_ptr;

inline bool cmp_denumire(const Medicament& m1, const Medicament& m2) noexcept
{
	return m1.getDenumire() < m2.getDenumire();
}

class ServException {
	string msg;
public:
	ServException(string m) :msg{ m }
	{}
	string get_message()
	{
		return msg;
	}
};

class MedicamentStore {
private:
	MedicamentRepository& repo;
	MedicamentValidator& val;

	Reteta RetetaCurenta;

	vector<unique_ptr<ActiuneUndo>> undoActions;

	
public:
	MedicamentStore(MedicamentRepository& medicamentRepo, MedicamentValidator& val) :repo{ medicamentRepo }, val{ val }{};

	//constructor de copiere
	//punem delete fiindca nu vrem sa se faca nicio copie la Service
	//(in aplicatie avem 1 singur Service)
	MedicamentStore(const MedicamentStore& ot) = delete;

	/*
	Adauga un medicament cu denumirea denumire, producatorul producator, substanta activa substantaActiva si pretul pret
	*@param denumire: denumirea medicamentului care se adauga (string)
	*@param producator: producatorul medicamentului care se adauga (string)
	*@param substantaActiva: substanta activa a medicamentului care se adauga (string)
	*@durata pret: pretul medicamentului care se adauga (double)
	* 
	* @throws: 
	*	RepoException daca mai exista medicamente cu denumirea si producatorul dat
	*	ValidationException daca medicamentul nu este valid
	*/

	void addMedicament(string denumire, string producator, string substantaActiva, double pret);
	/*
	Sterge un medicament cu denumirea denumire si producatorul producator din lista
	*/
	void eraseMedicament(string denumire, string producator);
	/*
	Modifica un medicament cu denumirea denumire si producatorul producator din lista
	*/
	void modifyMedicament(string denumire, string producator, string substantaActiva_noua, double pret_nou);
	/*
	Returneaza un vector cu toate medicamentele disponibile
	
	@return: lista cu toate medicamentele disponibile (vector cu obiecte de tip Medicament)
	*/
	const vector<Medicament> getAllMedicamente() {
		return this->repo.getAllMedicamente();
	}
	/*
	Returneaza o referinta catre un medicament cu denumirea denumire si producatorul producator din lista

	@return: referinta catre un medicament(Medicament&)
	*/
	const Medicament& findMedicament(string denumire, string producator);
	/*
	Returneaza un vector cu toate medicamentele ce au o anumita substanta activa

	@return: lista cu medicamentele disponibile ce au o anumita substanta activa (vector cu obiecte de tip Medicament)
	*/
	const vector<Medicament> filterMedicament(string substantaActiva) {
		/*vector<Medicament> meds = this->repo.getAllMedicamente();
		vector<Medicament> filtered_meds;
		for (auto med : meds)
			if (med.getSubstantaActiva() == substantaActiva)
				filtered_meds.push_back(med);
		return filtered_meds;*/

		const vector<Medicament>& allMedicamente = this->getAllMedicamente();
		vector<Medicament> filteredMedicamente;
		std::copy_if(allMedicamente.begin(), allMedicamente.end(), back_inserter(filteredMedicamente),
			[substantaActiva](const Medicament& m) {
				return m.getSubstantaActiva() == substantaActiva;
			});

		return filteredMedicamente;
	}
	/*
	Returneaza un vector cu toate medicamentele, sortate alfabetic dupa denumire

	@return: lista cu toate medicamentele, sortate alfabetic dupa denumire (vector cu obiecte de tip Medicament)
	*/
	const vector<Medicament> sortMedicamente() {
		vector<Medicament> meds = this->repo.getAllMedicamente();
		sort(meds.begin(), meds.end(), cmp_denumire);
		return meds;
	}
	/*
	* Adauga un medicament cu denumirea denumire si producatorul producator in reteta
	*
	* @param denumire: denumirea medicamentului care se adauga (string)
	* @param producator: producatorul medicamentului care se adauga (string)
	*
	* post: medicamentul este adaugata in reteta
	* @throws: RepoException daca nu exista medicament cu denumirea si producatorul dat
	*/
	void addToReteta(string denumire, string producator);
	/*
	* Adauga un numar random de medicamnte in reteta
	*
	* @param howMany: cate medicamente se adauga (int)
	*
	* @return: numarul de medicamente adaugate in reteta
	* post: se adauga un numar random de medicamente in reteta
	*/
	int addRandomToReteta(int howMany);
	/*
	* Elimina toate medicamentele din reteta
	* post: reteta nu contine niciun medicament
	*/
	void emptyReteta();
	/*
	* Verifica daca pretul tuturor medicamentele din reteta este accesibil(<=50)
	*
	* @return: True daca toate medicamentele din retesa au pretul accesibil, False altfel(bool)
	*/
	bool VerificaPret();
	/*
	* Returneaza un vector cu toate medicamentele din reteta
	*/
	const vector<Medicament>& getAllMedicamenteDinReteta();

	/*
	* Functie care scrie in fisier
	*/
	void write_to_file(string fname);

	/*
	* Functie care executa undo
	*/
	void undo();

	Reteta& getReteta() {
		return this->RetetaCurenta;
	}
};



void testAddService();
void testEraseService();
void testModifyService();
void testFilterService();
void testSortService();
void testRetetaService();
void testUndo();
void testWriteToFile();