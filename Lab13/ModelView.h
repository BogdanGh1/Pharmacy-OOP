#pragma once
#include <QAbstractTableModel>
#include <QBrush>
#include <Qt>
#include "Medicament.h"
#include <vector>
#include <qdebug.h>
using std::vector;


class MyTableModel :public QAbstractTableModel {
	std::vector<Medicament> meds;
public:
	MyTableModel(const std::vector<Medicament>& meds) :meds{ meds } {
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return meds.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}

	//Returns the data stored under the given role for the item referred to by the index.
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			auto med = this->meds[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(med.getDenumire());
			}
			else if (index.column() == 1) {
				return QString::fromStdString(med.getProducator());
			}
			else if (index.column() == 2) {
				return QString::fromStdString(med.getSubstantaActiva());
			}
			else {
				return QString::fromStdString(std::to_string(med.getPret()));
			}
		}
		else if (role == Qt::BackgroundRole) {
			auto med = this->meds[index.row()];
			if (med.getProducator() == "Terapia S.A.") {
				return QBrush(Qt::magenta);
			}
		}
		else if (role == Qt::FontRole) {
			auto med = this->meds[index.row()];
			if (index.row()%2==1) {
				auto font = QFont();
				font.setBold(true);
				return font;
			}
			else {
				auto font = QFont();
				font.setUnderline(true);
				return font;
			}
		}
		else if (role == Qt::ForegroundRole) {
			auto med = this->meds[index.row()];
			if (med.getPret() >= 20) {
				return QBrush(Qt::blue);
			}
		}

		return QVariant{};
	}

	void setMeds(const vector<Medicament> meds) {
		this->meds = meds;
		auto topIndex = createIndex(0, 0);
		auto bottomIndex = createIndex(meds.size(), 4);
		emit dataChanged(topIndex, bottomIndex);
		emit layoutChanged();
	}

	Qt::ItemFlags flags(const QModelIndex& /*index*/) const {
		return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
	}

	bool insertRows(int row, int count, const QModelIndex& parent) override
	{
		beginInsertRows(parent, row, row + count - 1);
		endInsertRows();
		return true;
	}
	
};
