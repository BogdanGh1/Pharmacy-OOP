#pragma once
#include "UI.h"
#include <iostream>
using namespace std;
void ConsoleUI::printMenu() {
	cout << "Comenzi disponibile:" << endl;
	cout << "1. Adauga medicament" << endl;
	cout << "2. Sterge medicamente" << endl;
	cout << "3. Modifica medicamente" << endl;
	cout << "4. Cauta medicament" << endl;
	cout << "5. Afiseaza toate medicamentele" << endl;
	cout << "6. Filtreaza dupa substanta activa" << endl;
	cout << "7. Sorteaza dupa denumire" << endl;
	cout << "8. Meniu Reteta" << endl;
	cout << "9. Undo" << endl;
	cout << "10. Exit" << endl;
}

void ConsoleUI::printMenuReteta() {
	cout << "Comenzi disponibile:" << endl;
	cout << "1. Adauga medicament in reteta" << endl;
	cout << "2. Adauga medicamente random in reteta" << endl;
	cout << "3. Goleste reteta" << endl;
	cout << "4. Afiseaza reteta curenta" << endl;
	cout << "5. Verifica pretul medicamentelor" << endl;
	cout << "6. Exporta reteta in fisier" << endl;
	cout << "7. Inapoi la meniul principal" << endl;
}
void ConsoleUI::uiUndo()
{
	try
	{
		srv.undo();
		cout << "S-a efectuat undo.\n";
	}
	catch (ServException& ex) {
		cout << ex.get_message() << "\n";
	}
}
void ConsoleUI::uiExportaFisier() {
	string fname;
	cout << "Numele fisierului este:";
	getline(cin >> ws, fname);

	srv.write_to_file(fname);
}

void ConsoleUI::uiAddToReteta() {
	string denumire, producator;
	cout << "Denumirea medicamentului este:";
	getline(cin >> ws, denumire);

	cout << "Producatorul medicamentului este:";
	getline(cin >> ws, producator);

	try {
		srv.addToReteta(denumire, producator);
		cout << "Medicamentul s-a adaugat cu succes in reteta." << endl;
	}
	catch (RepoException& re) {
		cout << re.getErrorMessage();
	}
	catch (ValidationException& ve) {
		cout << "Medicamentul nu este valid!" << endl;
		cout << ve.getErrorMessages();
	}
}
void ConsoleUI::uiAddRandomToReteta() {
	int howManyToAdd;
	cout << "Cate medicamente sa se adauge in reteta?";
	cin >> howManyToAdd;


	try {
		int howManyAdded = srv.addRandomToReteta(howManyToAdd);
		cout << "S-au adaugat " << howManyAdded << " medicamente in reteta." << endl;
	}
	catch (RepoException& re) {
		cout << re.getErrorMessage();
	}
}


void ConsoleUI::uiEmptyReteta() {
	srv.emptyReteta();
	cout << "S-au sters toate medicamentele din reteta curenta." << endl;
}
void ConsoleUI::uiVerificaPret() {
	bool ok = srv.VerificaPret();
	if (ok)
		cout << "Medicamentele nu sunt scumpe!\n";
	else cout << "Medicamentele sunt scumpe!\n";
}
void ConsoleUI::printMedicamenteReteta() {

	const vector<Medicament>& allMedicamente = srv.getAllMedicamenteDinReteta();
	if (allMedicamente.size() == 0)
		cout << "Nu exista medicamente." << endl;
	else {

		for (const auto& med : allMedicamente) {
			cout << "Denumire: " << med.getDenumire() << " | Producator: " << med.getProducator() << " | Substanta activa: " << med.getSubstantaActiva() << " | Pret: " << med.getPret() << endl;
		}
	}
}

void ConsoleUI::uiAdd() {
	string denumire, producator, substantaActiva;
	double pret;
	cout << "Denumirea medicamentului este:";
	getline(cin >> ws, denumire);

	cout << "Producatorul medicamentului este:";
	getline(cin >> ws, producator);
	cout << "Substanta activa a medicamentului este:";
	getline(cin >> ws, substantaActiva);

	cout << "Pretul medicamentului este:";
	cin >> pret;
	try {
		srv.addMedicament(denumire, producator, substantaActiva, pret);
	}
	catch (RepoException& re) {
		cout << re.getErrorMessage();
	}
	catch (ValidationException& ve) {
		cout << "Medicamentul nu este valid!" << endl;
		cout << ve.getErrorMessages();
	}

}
void ConsoleUI::uiErase() {
	string denumire, producator;
	cout << "Denumirea medicamentului este:";
	getline(cin >> ws, denumire);

	cout << "Producatorul medicamentului este:";
	getline(cin >> ws, producator);
	try {
		srv.eraseMedicament(denumire, producator);
	}
	catch (RepoException& re) {
		cout << re.getErrorMessage();
	}

}
void ConsoleUI::uiModify() {
	string denumire, producator, substantaActiva;
	double pret;
	cout << "Denumirea medicamentului este:";
	getline(cin >> ws, denumire);

	cout << "Producatorul medicamentului este:";
	getline(cin >> ws, producator);
	cout << "Substanta activa noua a medicamentului este:";
	getline(cin >> ws, substantaActiva);

	cout << "Pretul nou al medicamentului este:";
	cin >> pret;
	try {
		srv.modifyMedicament(denumire, producator, substantaActiva, pret);
	}
	catch (RepoException& re) {
		cout << re.getErrorMessage();
	}
	catch (ValidationException& ve) {
		cout << "Medicamentul nu este valid!" << endl;
		cout << ve.getErrorMessages();
	}

}
void ConsoleUI::uiFind() {
	string denumire, producator;
	cout << "Denumirea medicamentului este:";
	getline(cin >> ws, denumire);

	cout << "Producatorul medicamentului este:";
	getline(cin >> ws, producator);
	try {
		const Medicament& med = srv.findMedicament(denumire, producator);
		cout << "Denumire: " << med.getDenumire() << " | Producator: " << med.getProducator() << " | Substanta activa: " << med.getSubstantaActiva() << " | Pret: " << med.getPret() << endl;
	}
	catch (RepoException) {
		cout << "Medicamentul nu exita in lista.";
	}
}
void ConsoleUI::uiFiltrare() {
	string  substantaActiva;
	cout << "Substanta activa dupa care se va filtra este:";
	getline(cin >> ws, substantaActiva);
	const vector<Medicament>& Meds = srv.filterMedicament(substantaActiva);
	if (Meds.size() == 0)
		cout << "Nu exista medicamente." << endl;
	else
		for (const auto& med : Meds) {
			cout << "Denumire: " << med.getDenumire() << " | Producator: " << med.getProducator() << " | Substanta activa: "<<med.getSubstantaActiva()<<" | Pret: " << med.getPret() << endl;
		}
}

void ConsoleUI::uiSortare() {
	const vector<Medicament>& Meds = srv.sortMedicamente();
	if (Meds.size() == 0)
		cout << "Nu exista medicamente." << endl;
	else
		for (const auto& med : Meds) {
			cout << "Denumire: " << med.getDenumire() << " | Producator: " << med.getProducator() << " | Substanta activa: " << med.getSubstantaActiva() << " | Pret: " << med.getPret() << endl;
		}
}

void ConsoleUI::printAllMedicamente() {
	const vector<Medicament>& allMeds = srv.getAllMedicamente();
	if (allMeds.size() == 0)
		cout << "Nu exista medicamente." << endl;
	else
		for (const auto& med : allMeds) {
			cout << "Denumire: " << med.getDenumire() << " | Producator: " << med.getProducator() << " | Substanta activa: "<<med.getSubstantaActiva()<<" | Pret: " << med.getPret() << endl;
		}
}

void ConsoleUI::runReteta() {
	int running = 1;
	int cmd;
	while (running) {
		printMenuReteta();
		cout << "Comanda este:";
		cin >> cmd;
		switch (cmd)
		{
		case 1:
			uiAddToReteta();
			break;
		case 2:
			uiAddRandomToReteta();
			break;
		case 3:
			uiEmptyReteta();
			break;
		case 4:
			printMedicamenteReteta();
			break;
		case 5:
			uiVerificaPret();
			break;
		case 6:
			uiExportaFisier();
			break;
		case 7:
			running = 0;
			break;
		default:
			break;
		}
	}
}
void ConsoleUI::run() {
	int running = 1;
	int cmd;
	while (running) {
		printMenu();
		cout << "Comanda este:";
		cin >> cmd;
		switch (cmd)
		{
		case 1:
			uiAdd();
			break;
		case 2:
			uiErase();
			break;
		case 3:
			uiModify();
			break;
		case 4:
			uiFind();
			break;
		case 5:
			printAllMedicamente();
			break;
		case 6:
			uiFiltrare();
			break;
		case 7:
			uiSortare();
			break;
		case 8:
			runReteta();
			break;
		case 9:
			uiUndo();
			break;
		case 10:
			running = 0;
			break;
		default:
			break;
		}

	}
}