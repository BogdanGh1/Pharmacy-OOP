#pragma once
#include "Service.h"
class ConsoleUI {
private:
	MedicamentStore& srv;
public:
	ConsoleUI(MedicamentStore& srv) :srv{ srv } {};
	ConsoleUI(const ConsoleUI& ot) = delete;
	void printMenu();
	void printMenuReteta();
	void uiAdd();
	void uiErase();
	void uiModify();
	void uiFind();
	void printAllMedicamente();
	void uiFiltrare();
	void uiSortare();
	void run();
	void runReteta();
	void uiAddToReteta();
	void uiAddRandomToReteta();
	void uiEmptyReteta();
	void uiVerificaPret();
	void printMedicamenteReteta();
	void uiExportaFisier();
	void uiUndo();
};
