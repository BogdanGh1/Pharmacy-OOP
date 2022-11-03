#pragma once 

#include "Medicament.h"
#include "Observer.h"
#include <vector>
#include <random>
#include <iostream>
#include <fstream>
using std::vector;

class RetetaException
{
	string msg;
public:
	RetetaException(string m) :msg{ m }
	{}
	string get_message()
	{
		return msg;
	}
};


class Reteta : public Observable
{
private:
	vector<Medicament> lista;

public:

	Reteta(const Reteta& ot) = delete; //opreste posibilitatea de copiere
	Reteta() = default;
	virtual ~Reteta() = default;

	/*metoda care adauga un element in lista wishlist
	* input: titlu_w - string, titlul activitatii de adaugat
	*/
	void store_reteta(const Medicament& act);

	/*metoda care returneaza elementele din lista (adresa de inceput)*/
	const vector<Medicament>& getAllReteta() noexcept
	{
		return lista;
	}

	/*golire wishlist*/
	void golire_reteta() noexcept
	{
		lista.clear();
		notify();
	}

	/*umplere random wishlist
	* input: number - int, numarul de elemente de pus in wishlist
	*/
	void random_reteta(int number, const vector<Medicament>& elems);

};

/*teste pentru functionalitatea wishlist*/
void teste_reteta();

/*Functie care testeaza functia random_wish*/
void test_random_reteta();

class Reteta_file : public Reteta
{
private:
	string fname;
	void write_to_file();
	//void load_from_file();

public:
	Reteta_file(std::string fname) : Reteta(), fname{ fname }{
		//daca sarcina ar fi cerut, incarcam datele din fisier
		//load_from_file();
	}
	//metoda care seteaza numele fisierului in care se va face salvarea
	void set_file(std::string new_file) noexcept
	{
		this->fname = new_file;
	}

	//metoda getter pentru numele fisierului
	std::string get_file() const noexcept
	{
		return fname;
	}

	void salveaza_in_fisier()
	{
		std::ofstream out(fname);
		if (!out.is_open()) { throw RetetaException("Fisierul nu a putut fi deschis.\n"); }
		for (auto& med : getAllReteta())
		{
			out << med.getDenumire() << ", ";
			out << med.getProducator() << ", ";
			out << med.getSubstantaActiva() << ", ";
			out << med.getPret() << ";";
			out << "<br>";
		}
		out.close();
	}
};