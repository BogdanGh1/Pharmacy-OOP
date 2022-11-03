#pragma once
#include "Reteta.h"
#include <assert.h>

/*metoda care adauga un element in lista wishlist
	* input: act - activitatea de adaugat
	*/
void Reteta::store_reteta(const Medicament& med)
{
	for (const auto& m : lista)
	{
		if (m.getDenumire() == med.getDenumire() && m.getProducator() == med.getProducator())
		{
			throw RetetaException("Element existent!\n");
		}
	}
	lista.push_back(med);
	notify();
}

/*umplere random wishlist
	* input: number - int, numarul de elemente de pus in wishlist
	*/
void Reteta::random_reteta(int number, const vector<Medicament>& elems)
{
	std::mt19937 mt{ std::random_device{}() };
	const size_t n = elems.size();
	const int nr = (int)n;
	const std::uniform_int_distribution<> dist(0, nr - 1);
	bool* viz = new bool[n];
	for (int i = 0; i < n; i++)
	{
		viz[i] = false;
	}
	while (number != 0)
	{
		const int rndNr = dist(mt);// numar aleator intre [0,size-1]
		if (viz[rndNr] == false)
		{
			number--;
			viz[rndNr] = true;
			store_reteta(elems[rndNr]);
		}
	}
	delete[] viz;
	notify();
}


/*teste pentru functionalitatea wishlist*/
void teste_reteta()
{
	Reteta r;

	Medicament med1{ "aa","bb","c",20 };
	Medicament med2{ "bb","bb","c",30 };
	Medicament med3{ "cc","bb","a",40 };


	auto& reteta = r.getAllReteta();

	assert(reteta.size() == 0);

	//adaugam un element in lista
	r.store_reteta(med1);
	assert(reteta.size() == 1);

	//incercam sa adaugam un element deja existent in wishlist
	try {
		r.store_reteta(med1);
		assert(false);
	}
	catch (RetetaException& ex) {
		assert(ex.get_message() == "Element existent!\n");
	}

	r.store_reteta(med2);
	assert(reteta.size() == 2);

	r.golire_reteta();
	assert(reteta.size() == 0);
}

/*Functie care testeaza functia random_wish*/
void test_random_reteta()
{
	Reteta r;

	vector<Medicament> elems;
	Medicament med1{ "aa", "a1", "a2", 20 };
	Medicament med2{ "bb", "a1", "a2", 20 };
	Medicament med3{ "cc", "a1", "a2", 20 };
	Medicament med4{ "dd", "a1", "a2", 20 };
	Medicament med5{ "ee", "a1", "a2", 20 };
	elems.push_back(med1);
	elems.push_back(med2);
	elems.push_back(med3);
	elems.push_back(med4);
	elems.push_back(med5);

	r.random_reteta(4, elems);
	const auto& reteta = r.getAllReteta();
	assert(reteta.size() == 4);
}