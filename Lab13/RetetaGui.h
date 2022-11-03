#pragma once
#include <QWidget>
#include <QBoxLayout>
#include <QlistWidget>
#include <QLabel>
#include <QPushButton>
#include <QFormLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QPainter>
#include "Service.h"
#include "Observer.h"

using std::to_string;
using std::vector;

class RetetaGui : public QWidget, public Observer {
private:
	MedicamentStore& srv;
	Reteta& reteta;
	QHBoxLayout* lyMain;
	QListWidget* medList;

	QLabel* lblDenumire;
	QLabel* lblProducator;
	QLineEdit* editDenumire;
	QLineEdit* editProducator;

	QPushButton* btnAdd;
	QPushButton* btnGenerate;
	QPushButton* btnEmpty;
	QPushButton* btnExport;
	QPushButton* btnClose;

	QLabel* lblNrGenerare;
	QLineEdit* editNrGenerare;

	QLabel* lblFile;
	QLineEdit* editFile;

	
	void connectSignalsSlots();
	void initGUI();
	void reloadReteta();
	
	void addToReteta();
	void update() override {
		reloadReteta();
	}

public:
	
	RetetaGui(MedicamentStore& srv, Reteta& reteta) : srv{ srv }, reteta{ reteta } {
		reteta.addObserver(this);
		initGUI();
		connectSignalsSlots();
		update();
	}
	~RetetaGui() {
		reteta.removeObserver(this);
	}

};

class RetetaGuiDraw :public QWidget, public Observer {
private:
	Reteta& reteta;
	void paintEvent(QPaintEvent*) override {
		QPainter p{ this };
		int x = 0;
		int y = 0;
		for (auto med : reteta.getAllReteta()) {
			//p.drawRect(x, y, 10, song.getDurata() * 10);
			x = rand() % 400 + 1;
			y = rand() % 400 + 1;
			qDebug() << x << " " << y;
			QRectF target(x, y, 100, 94);
			QRectF source(0, 0, 732, 720);
			QImage image("two-pills.jpg");

			p.drawImage(target, image, source);

			x += 40;

		}
	}

	void update() override {
		repaint();
	};
	~RetetaGuiDraw() {
		reteta.removeObserver(this);
	}

public:
	RetetaGuiDraw(Reteta& reteta) :reteta{ reteta } {
		reteta.addObserver(this);
	};

};
