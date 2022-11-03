#pragma once
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QHeaderView>
#include <QMessageBox>
#include "Service.h"
#include "RetetaGui.h"
#include "ModelView.h"
class Gui : public QWidget {
private:
	MedicamentStore& srv;

	//RetetaGui retetaWindow{ srv };
	QLabel* lblDenumire = new QLabel{"Denumire medicament:"};
	QLabel* lblProducator = new QLabel{"Producator medicament:"};
	QLabel* lblSubstantaActiva = new QLabel{"Substanta activa medicament:"};
	QLabel* lblPret = new QLabel{"Pret medicament:"};

	QLineEdit* editDenumire = new QLineEdit;
	QLineEdit* editProducator = new QLineEdit;
	QLineEdit* editSubstantaActiva = new QLineEdit;
	QLineEdit* editPret = new QLineEdit;

	QPushButton* btnAddMedicament;
	QPushButton* btnEraseMedicament;
	QPushButton* btnModifyMedicament;
	QPushButton* btnUndo;

	QLabel* lblFilterCriteria = new QLabel{ "Substanta activa dupa care se filtreaza:" };
	QLineEdit* editFilterSubsAct;
	QPushButton* btnFilterMeds;

	QPushButton* btnReloadData;
	QPushButton* btnSortData;

	//QTableWidget* tableMeds;
	MyTableModel* model;
	QTableView * tableMeds = new QTableView;

	QPushButton* btnReteta;
	QPushButton* btnRetetaReadOnly;


	void initializeGUIComponents();

	void connectSignalsSlots();
	void reloadMedsList(vector<Medicament> meds);

public:
	Gui(MedicamentStore& medSrv) : srv{ medSrv } {
		initializeGUIComponents();
		this->model = new MyTableModel{ this->srv.getAllMedicamente() };
		tableMeds->setModel(this->model);
		connectSignalsSlots();
		reloadMedsList(srv.getAllMedicamente());
	}
	void guiAddMedicament();
	void guiEraseMedicament();
	void guiModifyMedicament();
	void guiUndo();

};