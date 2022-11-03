#pragma once
#include "Service.h"
#include <assert.h>
void MedicamentStore::addMedicament(string denumire, string producator, string substantaActiva, double pret) {
	Medicament m1{denumire, producator, substantaActiva, pret};
	val.valideaza(m1);
	repo.store(m1);
	undoActions.push_back(std::make_unique<UndoAdauga>(repo, m1));
}

void MedicamentStore::eraseMedicament(string denumire, string producator) {
	const Medicament& med = repo.find(denumire, producator);
	undoActions.push_back(std::make_unique<UndoSterge>(repo, med));
	repo.erase(denumire, producator);
	
}
void MedicamentStore::modifyMedicament(string denumire, string producator, string substantaActiva_noua, double pret_nou) {
	
	Medicament m1{ denumire, producator, substantaActiva_noua, pret_nou };
	val.valideaza(m1);
	const Medicament& med = repo.find(denumire, producator);
	undoActions.push_back(std::make_unique<UndoModifica>(repo, med));

	repo.modify(denumire, producator, substantaActiva_noua, pret_nou);
}
const Medicament& MedicamentStore::findMedicament(string denumire, string producator) {
	return repo.find(denumire, producator);
}
void MedicamentStore::addToReteta(string titlu, string artist) {

	const auto& med = repo.find(titlu, artist);
	RetetaCurenta.store_reteta(med);

}
int MedicamentStore::addRandomToReteta(int howMany) {
	RetetaCurenta.random_reteta(howMany, this->getAllMedicamente());
	return (int)RetetaCurenta.getAllReteta().size();
}
void MedicamentStore::emptyReteta() {
	RetetaCurenta.golire_reteta();
}
bool MedicamentStore::VerificaPret() {
	const vector<Medicament>meds = RetetaCurenta.getAllReteta();
	if (std::all_of(meds.cbegin(), meds.cend(), [](Medicament med) { return med.getPret() <= 50; }))
	{
		return 1;
	}
	return 0;
}
const vector<Medicament>& MedicamentStore::getAllMedicamenteDinReteta() {
	return RetetaCurenta.getAllReteta();
}

void MedicamentStore::write_to_file(string fname)
{
	std::ofstream  out(fname);
	if (!out.is_open()) { throw RepoException("Fisierul nu a putut fi deschis!\n"); }
	for (auto& med : getAllMedicamenteDinReteta())
	{
		out << med.getDenumire() << ",";
		out << med.getProducator() << ",";
		out << med.getSubstantaActiva() << ",";
		out << med.getPret() << std::endl;
	}
	out.close();
}

void MedicamentStore::undo()
{
	if (undoActions.empty())
	{
		throw ServException("Nu se mai poate face undo!\n");
	}
	undoActions.back()->doUndo();
	undoActions.pop_back();
}

void testAddService() {
	MedicamentRepository testRepo;
	MedicamentValidator testVal;
	MedicamentStore testService{ testRepo,testVal};

	testService.addMedicament("Nurofen", "Reckitt Benckiser(Romania) SRL","Ibuprofen",15 );
	testService.addMedicament("NO-SPA", "Sanofi Romania SRL", "clorhidrat de drotaverina", 20 );
	testService.addMedicament("Amoxicilina", "Antibiotice SA", "hidroxibenzoat de metil", 17.5 );

	assert(testService.getAllMedicamente().size() == 3);
	try {
		testService.addMedicament("Nurofen", "Reckitt Benckiser(Romania) SRL", "Ibuprofen", 15);
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}

	try {
		testService.addMedicament("abc", "def", "qwerty", 56);
		assert(true);
	}
	catch (ValidationException&) {
		assert(false);
	}
	
	try {
		testService.addMedicament("", "gdh", "jhjk", 78);
		assert(false);
	}
	catch (ValidationException& ve) {
		assert(ve.getErrorMessages()=="Denumirea trebuie sa aiba cel putin 2 caractere.\n");
	}

	try {
		testService.addMedicament("", "", "",-1 );
		assert(false);
	}
	catch (ValidationException& ve) {
		string v = ve.getErrorMessages();
		assert(true);
	}

}

void testEraseService() {
	MedicamentRepository testRepo;
	MedicamentValidator testVal;
	MedicamentStore testService{ testRepo,testVal };

	testService.addMedicament("Nurofen", "Reckitt Benckiser(Romania) SRL", "Ibuprofen", 15);
	testService.addMedicament("NO-SPA", "Sanofi Romania SRL", "clorhidrat de drotaverina", 20);
	testService.addMedicament("Amoxicilina", "Antibiotice SA", "hidroxibenzoat de metil", 17.5);
	testService.eraseMedicament("Amoxicilina", "Antibiotice SA");
	assert(testService.getAllMedicamente().size() == 2);

}

void testModifyService() {
	MedicamentRepository testRepo;
	MedicamentValidator testVal;
	MedicamentStore testService{ testRepo,testVal };

	testService.addMedicament("Nurofen", "Reckitt Benckiser(Romania) SRL", "Ibuprofen", 15);
	testService.addMedicament("NO-SPA", "Sanofi Romania SRL", "clorhidrat de drotaverina", 20);
	testService.addMedicament("Amoxicilina", "Antibiotice SA", "hidroxibenzoat de metil", 17.5);
	testService.modifyMedicament("Amoxicilina", "Antibiotice SA", "abc", 50);

	assert(testService.getAllMedicamente().size() == 3);
	assert(testService.findMedicament("Amoxicilina", "Antibiotice SA").getSubstantaActiva() == "abc");
	assert(testService.findMedicament("Amoxicilina", "Antibiotice SA").getPret() == 50);

}

void testFilterService() {
	MedicamentRepository testRepo;
	MedicamentValidator testVal;
	MedicamentStore testService{ testRepo,testVal };

	testService.addMedicament("Nurofen", "Reckitt Benckiser(Romania) SRL", "Ibuprofen", 15);
	testService.addMedicament("NO-SPA", "Sanofi Romania SRL", "clorhidrat de drotaverina", 20);
	testService.addMedicament("Amoxicilina", "Antibiotice SA", "hidroxibenzoat de metil", 17.5);

	vector<Medicament> filtered_meds = testService.filterMedicament("Ibuprofen");
	assert(filtered_meds.size() == 1);
	assert(filtered_meds[0].getDenumire() == "Nurofen");
	assert(filtered_meds[0].getProducator() == "Reckitt Benckiser(Romania) SRL");
	assert(filtered_meds[0].getPret() == 15);

}

void testSortService() {
	MedicamentRepository testRepo;
	MedicamentValidator testVal;
	MedicamentStore testService{ testRepo,testVal };

	testService.addMedicament("Nurofen", "Reckitt Benckiser(Romania) SRL", "Ibuprofen", 15);
	testService.addMedicament("NO-SPA", "Sanofi Romania SRL", "clorhidrat de drotaverina", 20);
	testService.addMedicament("Amoxicilina", "Antibiotice SA", "hidroxibenzoat de metil", 17.5);

	vector<Medicament> sorted_meds = testService.sortMedicamente();
	assert(sorted_meds.size() == 3);
	assert(sorted_meds[0].getDenumire() == "Amoxicilina");
	assert(sorted_meds[0].getProducator() == "Antibiotice SA");
	assert(sorted_meds[0].getPret() == 17.5);

}

void testRetetaService() {
	MedicamentRepository testRepo;
	MedicamentValidator testVal;
	MedicamentStore testService{ testRepo,testVal };

	testService.addMedicament("Nurofen", "Reckitt Benckiser(Romania) SRL", "Ibuprofen", 15);
	testService.addMedicament("NO-SPA", "Sanofi Romania SRL", "clorhidrat de drotaverina", 20);
	testService.addMedicament("Amoxicilina", "Antibiotice SA", "hidroxibenzoat de metil", 17.5);

	testService.addToReteta("Nurofen", "Reckitt Benckiser(Romania) SRL");
	testService.addToReteta("NO-SPA", "Sanofi Romania SRL");

	assert(testService.getAllMedicamenteDinReteta().size() == 2);
	assert(testService.VerificaPret() == 1);

	testService.emptyReteta();
	assert(testService.getAllMedicamenteDinReteta().size() == 0);
	testService.addRandomToReteta(3);
	assert(testService.getAllMedicamenteDinReteta().size() == 3);

}
void testWriteToFile() {
	MedicamentRepository testRepo;
	MedicamentValidator testVal;
	MedicamentStore testService{ testRepo,testVal };

	testService.addMedicament("Nurofen", "Reckitt Benckiser(Romania) SRL", "Ibuprofen", 15);
	testService.addMedicament("NO-SPA", "Sanofi Romania SRL", "clorhidrat de drotaverina", 20);
	testService.addMedicament("Amoxicilina", "Antibiotice SA", "hidroxibenzoat de metil", 17.5);

	testService.addToReteta("Nurofen", "Reckitt Benckiser(Romania) SRL");
	testService.addToReteta("NO-SPA", "Sanofi Romania SRL");

	testService.write_to_file("test.csv");
}
void testUndo()
{
	MedicamentRepository testRepo;
	MedicamentValidator testVal;
	MedicamentStore testService{ testRepo,testVal };

	//testam undo cu lista goala
	try
	{
		testService.undo();
		assert(false);
	}
	catch (ServException& ex)
	{
		assert(ex.get_message() == "Nu se mai poate face undo!\n");
	}

	//adaugam un element in repo si apoi facem undo
	testService.addMedicament("Nurofen", "Reckitt Benckiser(Romania) SRL", "Ibuprofen", 15);
	const auto& meds = testRepo.getAllMedicamente();
	assert(meds.size() == 1);
	testService.undo();
	const auto& meds2 = testRepo.getAllMedicamente();
	assert(meds2.size() == 0);
	try
	{
		testService.undo();
		assert(false);
	}
	catch (ServException& ex)
	{
		assert(ex.get_message() == "Nu se mai poate face undo!\n");
	}

	testService.addMedicament("NO-SPA", "Sanofi Romania SRL", "clorhidrat de drotaverina", 20);
	testService.addMedicament("Amoxicilina", "Antibiotice SA", "hidroxibenzoat de metil", 17.5);

	testService.eraseMedicament("NO-SPA", "Sanofi Romania SRL");
	const auto& meds3 = testRepo.getAllMedicamente();
	assert(meds3.size() == 1);
	testService.undo();
	const auto& meds4 = testRepo.getAllMedicamente();
	assert(meds4.size() == 2);

	//modificam un element si facem undo
	testService.modifyMedicament("Amoxicilina", "Antibiotice SA", "abc", 10);
	testService.undo();
	Medicament gasit = testService.findMedicament("Amoxicilina", "Antibiotice SA");
	assert(gasit.getSubstantaActiva() == "hidroxibenzoat de metil");
	assert(gasit.getPret() == 17.5);
}