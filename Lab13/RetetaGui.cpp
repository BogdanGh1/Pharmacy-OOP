#include "RetetaGui.h"

void RetetaGui::initGUI() {
	lyMain = new QHBoxLayout{};
	this->setLayout(lyMain);

	QWidget* leftSide = new QWidget{};
	QVBoxLayout* lyLeft = new QVBoxLayout{};
	leftSide->setLayout(lyLeft);

	QWidget* formW = new QWidget{};
	QFormLayout* lyEdits = new QFormLayout{};
	lblDenumire = new QLabel{ "Denumire" };
	lblProducator = new QLabel{ "Producator" };
	editDenumire = new QLineEdit{};
	editProducator = new QLineEdit{};

	lblNrGenerare = new QLabel{ "Nr. melodii de generat" };
	editNrGenerare = new QLineEdit{};

	lblFile = new QLabel{ "Nume fisier" };
	editFile = new QLineEdit{};

	lyEdits->addRow(lblDenumire, editDenumire);
	lyEdits->addRow(lblProducator, editProducator);
	lyEdits->addRow(lblNrGenerare, editNrGenerare);
	lyEdits->addRow(lblFile, editFile);
	formW->setLayout(lyEdits);


	btnAdd = new QPushButton{ "Adauga in reteta" };
	btnGenerate = new QPushButton{ "Genereaza random" };
	btnEmpty = new QPushButton{ "Goleste reteta" };
	btnExport = new QPushButton{ "Export reteta" };
	btnClose = new QPushButton{ "Inchide" };

	/*btnLabelWindow = new QPushButton{ "Fereastra label" };
	btnLabelWindow->setStyleSheet("background-color: cyan");

	btnTableWindow = new QPushButton{ "Fereastra playlist tabel" };
	btnTableWindow->setStyleSheet("background-color: magenta");

	btnDrawWindow = new QPushButton{ "Fereastra desen" };
	btnDrawWindow->setStyleSheet("background-color: yellow");*/


	lyLeft->addWidget(formW);
	lyLeft->addWidget(btnAdd);
	lyLeft->addWidget(btnGenerate);
	lyLeft->addWidget(btnEmpty);
	lyLeft->addWidget(btnExport);
	lyLeft->addWidget(btnClose);

	QWidget* rightSide = new QWidget{};
	QVBoxLayout* lyRight = new QVBoxLayout{};
	rightSide->setLayout(lyRight);

	medList = new QListWidget{};
	medList->setFixedWidth(320);
	medList->setSelectionMode(QAbstractItemView::SingleSelection);

	lyRight->addWidget(medList);

	lyMain->addWidget(leftSide);
	lyMain->addWidget(rightSide);
}

void RetetaGui::connectSignalsSlots() {
	QObject::connect(btnAdd, &QPushButton::clicked, this, &RetetaGui::addToReteta);
	QObject::connect(btnGenerate, &QPushButton::clicked, [&]() {
		srv.emptyReteta();
		this->reloadReteta();
		int noMeds = editNrGenerare->text().toInt();
		srv.addRandomToReteta(noMeds);
		editNrGenerare->clear();
		this->reloadReteta();
		});
	QObject::connect(btnEmpty, &QPushButton::clicked, [&]() {
		srv.emptyReteta();
		this->reloadReteta();
		});
	QObject::connect(btnExport, &QPushButton::clicked, [&]() {
		string fname = editFile->text().toStdString();
		editFile->clear();
		srv.write_to_file(fname);
		});
	QObject::connect(btnClose, &QPushButton::clicked, this, &RetetaGui::close);


}

void RetetaGui::reloadReteta() {

	this->medList->clear();

	const vector<Medicament>& meds = srv.getAllMedicamenteDinReteta();
	for (auto& med : meds) {
		QString currentItem = QString::fromStdString(med.getDenumire() + "\t" + med.getProducator() + "\t" + med.getSubstantaActiva() + "\t" + to_string(med.getPret()));
		this->medList->addItem(currentItem);
	}

}


void RetetaGui::addToReteta() {
	try {
		string denumire = editDenumire->text().toStdString();
		string producator = editProducator->text().toStdString();

		editDenumire->clear();
		editProducator->clear();


		this->srv.addToReteta(denumire, producator);
		this->reloadReteta();

		QMessageBox::information(this, "Info", QString::fromStdString("Medicament adaugat cu succes."));

	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
	catch (ValidationException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMessages()));
	}

}