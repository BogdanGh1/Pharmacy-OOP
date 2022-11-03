#include "Gui.h"

void Gui::initializeGUIComponents() {
	

	QHBoxLayout* lyMain = new QHBoxLayout;
	this->setLayout(lyMain);


	//left part of the window
	//pentru aceasta parte setam layout vertical
	QWidget* left = new QWidget;
	QVBoxLayout* lyLeft = new QVBoxLayout;
	left->setLayout(lyLeft);

	//componente pentru functionalitatea de adaugare a unui medicament
	//folosim un QFormLayout pentru detaliile de adaugare a unui medicament
	QWidget* form = new QWidget;
	QFormLayout* lyForm = new QFormLayout;
	form->setLayout(lyForm);
	editDenumire = new QLineEdit;
	editProducator = new QLineEdit;
	editSubstantaActiva = new QLineEdit;
	editPret = new QLineEdit;

	lyForm->addRow(lblDenumire, editDenumire);
	lyForm->addRow(lblProducator, editProducator);
	lyForm->addRow(lblSubstantaActiva, editSubstantaActiva);
	lyForm->addRow(lblPret, editPret);
	btnAddMedicament = new QPushButton("Adauga medicament");
	lyForm->addWidget(btnAddMedicament);
	btnEraseMedicament = new QPushButton("Sterge medicament");
	lyForm->addWidget(btnEraseMedicament);
	btnModifyMedicament = new QPushButton("Modifica medicament");
	lyForm->addWidget(btnModifyMedicament);
	btnUndo = new QPushButton("Undo");
	lyForm->addWidget(btnUndo);

	//adaugam toate componentele legate de adaugare melodie
	//in layout-ul care corespunde partii din stanga a ferestrei
	lyLeft->addWidget(form);


	//cream un form pentru filtrarea dupa gen 
	QWidget* formFilter = new QWidget;
	QFormLayout* lyFormFilter = new QFormLayout;
	formFilter->setLayout(lyFormFilter);
	editFilterSubsAct = new QLineEdit();
	lyFormFilter->addRow(lblFilterCriteria, editFilterSubsAct);
	btnFilterMeds = new QPushButton("Filtreaza medicamentele");
	lyFormFilter->addWidget(btnFilterMeds);

	lyLeft->addWidget(formFilter);

	//Buton folosit pentru a reincarca datele
	//i.e. afisam toate melodiile in tabel, in ordinea initiala din fisier
	btnReloadData = new QPushButton("Reload data");
	lyLeft->addWidget(btnReloadData);
	btnSortData = new QPushButton("Sort data");
	lyLeft->addWidget(btnSortData);
	btnReteta = new QPushButton("Deschide Reteta");
	lyLeft->addWidget(btnReteta);
	btnRetetaReadOnly = new QPushButton("Deschide Reteta-Read Only");
	lyLeft->addWidget(btnRetetaReadOnly);


	//componenta right - contine doar tabelul cu melodii
	QWidget* right = new QWidget;
	QVBoxLayout* lyRight = new QVBoxLayout;
	right->setLayout(lyRight);

	int noLines = 10;
	int noColumns = 4;
	//this->tableMeds = new QTableWidget{ noLines, noColumns };
	//this->tableMeds = new MyTableModel{this};

	//setam header-ul tabelului
	//QStringList tblHeaderList;
	//tblHeaderList << "Denumire" << "Producator" << "Substanta activa" << "Pret";
	//this->tableMeds->setHorizontalHeaderLabels(tblHeaderList);

	//optiune pentru a se redimensiona celulele din tabel in functie de continut
	//this->tableMeds->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);


	lyRight->addWidget(tableMeds);

	lyMain->addWidget(left);
	lyMain->addWidget(right);


	srv.addMedicament("Nurofen", "Reckitt Benckiser(Romania) SRL", "Ibuprofen", 15);
	srv.addMedicament("NO-SPA", "Sanofi Romania SRL", "clorhidrat de drotaverina", 20);
	srv.addMedicament("Amoxicilina", "Antibiotice SA", "hidroxibenzoat de metil", 17.5);
	srv.addMedicament("Diazepam Terapia", "Terapia S.A.", "Diazepamum", 15);
	srv.addMedicament("Betametazona", "Fiterman Pharma S.R.L.", "Betamethasonum", 25);
}

/*void Gui::reloadMedsList(vector<Medicament> meds) {
	this->tableMeds->clearContents();
	this->tableMeds->setRowCount(meds.size());

	int lineNumber = 0;
	for (auto& med : meds) {
		this->tableMeds->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(med.getDenumire())));
		this->tableMeds->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(med.getProducator())));
		this->tableMeds->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(med.getSubstantaActiva())));
		this->tableMeds->setItem(lineNumber, 3, new QTableWidgetItem(QString::number(med.getPret())));
		lineNumber++;
	}
}*/

void Gui::reloadMedsList(vector<Medicament> meds) {
	//implement reloadSongList with model
	this->model->setMeds(meds);
}

void Gui::connectSignalsSlots() {
	QObject::connect(btnAddMedicament, &QPushButton::clicked, this, &Gui::guiAddMedicament);
	QObject::connect(btnEraseMedicament, &QPushButton::clicked, this, &Gui::guiEraseMedicament);
	QObject::connect(btnModifyMedicament, &QPushButton::clicked, this, &Gui::guiModifyMedicament);
	QObject::connect(btnUndo, &QPushButton::clicked, this, &Gui::guiUndo);

	QObject::connect(btnFilterMeds, &QPushButton::clicked, [&]() {
		string filterC = this->editFilterSubsAct->text().toStdString();
		this->reloadMedsList(srv.filterMedicament(filterC));
		});

	QObject::connect(btnReloadData, &QPushButton::clicked, [&]() {
		this->reloadMedsList(srv.getAllMedicamente());
		});
	QObject::connect(btnSortData, &QPushButton::clicked, [&]() {
		this->reloadMedsList(srv.sortMedicamente());
		});
	QObject::connect(btnReteta, &QPushButton::clicked, [&]() {
		//retetaWindow.show();
		auto Window = new RetetaGui{ srv,srv.getReteta() };
		Window->show();
		});
	QObject::connect(btnRetetaReadOnly, &QPushButton::clicked, [&]() {
		auto drawWindow = new RetetaGuiDraw{ srv.getReteta() };
		drawWindow->show();
		});
	QObject::connect(tableMeds->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		if (tableMeds->selectionModel()->selectedIndexes().isEmpty()) {
			editDenumire->setText("");
			editProducator->setText("");
			editFilterSubsAct->setText("");
		}
		else {
			auto index = tableMeds->selectionModel()->selectedIndexes().at(0);
			auto denumireIndex = tableMeds->model()->index(index.row(), 0);
			auto producatorIndex = tableMeds->model()->index(index.row(), 1);
			auto substActivaIndex = tableMeds->model()->index(index.row(), 2);
			auto denumire = tableMeds->model()->data(denumireIndex, Qt::DisplayRole).toString();
			auto producator = tableMeds->model()->data(producatorIndex, Qt::DisplayRole).toString();
			auto substActiva = tableMeds->model()->data(substActivaIndex, Qt::DisplayRole).toString();
			editDenumire->setText(denumire);
			editProducator->setText(producator);
			editFilterSubsAct->setText(substActiva);
		}
		});

}


void Gui::guiAddMedicament() {
	try {
		//preluare detalii din QLineEdit-uri
		string denumire = editDenumire->text().toStdString();
		string producator = editProducator->text().toStdString();
		string subs_activa = editSubstantaActiva->text().toStdString();
		double pret = editPret->text().toDouble();

		//optional - golim QLineEdit-urile dupa apasarea butonului
		editDenumire->clear();
		editProducator->clear();
		editSubstantaActiva->clear();
		editPret->clear();

		this->srv.addMedicament(denumire, producator, subs_activa, pret);
		this->reloadMedsList(this->srv.getAllMedicamente());

		//afisam un mesaj pentru a anunta utilizatorul ca melodia s-a adaugat
		QMessageBox::information(this, "Info", QString::fromStdString("Medicament adaugat cu succes."));

	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
	catch (ValidationException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMessages()));
	}
}

void Gui::guiEraseMedicament() {
	try {
		//preluare detalii din QLineEdit-uri
		string denumire = editDenumire->text().toStdString();
		string producator = editProducator->text().toStdString();
		//optional - golim QLineEdit-urile dupa apasarea butonului
		editDenumire->clear();
		editProducator->clear();
		editSubstantaActiva->clear();
		editPret->clear();

		this->srv.eraseMedicament(denumire, producator);
		this->reloadMedsList(this->srv.getAllMedicamente());

		//afisam un mesaj pentru a anunta utilizatorul ca melodia s-a adaugat
		QMessageBox::information(this, "Info", QString::fromStdString("Medicament sters cu succes."));

	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
}

void Gui::guiModifyMedicament() {
	try {
		//preluare detalii din QLineEdit-uri
		string denumire = editDenumire->text().toStdString();
		string producator = editProducator->text().toStdString();
		string subs_activa = editSubstantaActiva->text().toStdString();
		double pret = editPret->text().toDouble();

		//optional - golim QLineEdit-urile dupa apasarea butonului
		editDenumire->clear();
		editProducator->clear();
		editSubstantaActiva->clear();
		editPret->clear();

		this->srv.modifyMedicament(denumire, producator, subs_activa, pret);
		this->reloadMedsList(this->srv.getAllMedicamente());

		//afisam un mesaj pentru a anunta utilizatorul ca melodia s-a adaugat
		QMessageBox::information(this, "Info", QString::fromStdString("Medicament modificat cu succes."));

	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
	catch (ValidationException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMessages()));
	}
}

void Gui::guiUndo() {
	try {

		this->srv.undo();
		this->reloadMedsList(this->srv.getAllMedicamente());

		//afisam un mesaj pentru a anunta utilizatorul ca melodia s-a adaugat
		QMessageBox::information(this, "Info", QString::fromStdString("Undo efectuat cu succes."));

	}
	catch (ServException& se) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(se.get_message()));
	}
}