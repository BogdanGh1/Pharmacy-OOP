#pragma once
#include "Medicament.h"
#include "fstream"
#include <vector>
using std::vector;
/*
Clasa de exceptii specifice Repo
*/
class RepoException {
private:
	string errorMsg;
public:
	RepoException(string errorMsg) :errorMsg{ errorMsg } {};
	string getErrorMessage() {
		return this->errorMsg;
	}
};


class MedicamentRepository  {
private:
	vector<Medicament> allMedicamente;
public:
	
	MedicamentRepository() = default;
	//constructor de copiere
	//punem delete fiindca nu vrem sa se faca nicio copie la Repository
	//(in aplicatie avem 1 singur Repo)
	MedicamentRepository(const MedicamentRepository& ot) = delete;
	/*
	Adauga un medicament in lista
	@param m: medicamentul care se adauga (Medicament)
	@return -
	post: medicamentul va fi adaugata in lista

	@throws: RepoException daca un medicament cu aceeasi denumire si acelasi producator
			 exista deja 
	*/
	void store(const Medicament& m);
	/*
	Sterge un medicament din lista
	@param denumire: denumirea medicamentului (string)
	@param producator: producatorul medicamentului (string)
	@return -
	post: medicamentul va fi sters din lista

	@throws: RepoException daca un medicament cu aceasta denumire si acest producator nu exista
	*/
	void erase(string denumire, string producator);
	/*
	Modifica un medicament din lista
	@param denumire: denumirea medicamentului (string)
	@param producator: producatorul medicamentului (string)
	@param substanta_Activa_noua: substanta activa a medicamentului dupa modificare (string)
	@param pret_nou: pretul medicamentului dupa modificare (double)
	@return -
	post: medicamentul va fi modificat

	@throws: RepoException daca un medicament cu aceasta denumire si acest producator nu exista
	*/
	void modify(string denumire, string producator, string substanta_activa_noua, double pret_nou);
	/*
	Returneaza o lista cu toate medicamentele
	@return: lista cu medicamente (vector of Medicament objects)
	*/
	const vector<Medicament> getAllMedicamente();

	/*
	Cauta un medicament cu denumirea si producatorul dat

	@param denumire: denumirea dupa care se cauta
	@param producator: producatorul dupa care se cauta 
	@returns: entitatea Medicament cu denumirea si producatorul dat (daca aceasta exista)
	@throws: RepoException daca nu exista medicament cu denumirea si producatorul dat*/
	const Medicament& find(string denumire, string producator);

	/*
	Verifica daca un medicaemnt dat exista in lista
	
	@param m: medicamentul care se cauta in lista
	@return: true daca medicamentul exista, false altfel
	*/
	bool exists(const Medicament& m);

};


void testeRepo();