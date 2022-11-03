#include "ModelView.h"


MyTableModel::MyTableModel(QObject* parent) :
	QAbstractTableModel(parent) {
}
int MyTableModel::rowCount(const QModelIndex& /*parent*/) const {
	return 10;
}
int MyTableModel::columnCount(const QModelIndex& /*parent*/) const {
	return 4;
}QVariant MyTableModel::data(const QModelIndex& index, int role) const {
	int row = index.row();
	int column = index.column();
	if (role == Qt::DisplayRole) {
		return QString("Row%1, Column%2").arg(row + 1).arg(column + 1);
	}
	if (role == Qt::FontRole) {
		QFont f;
		f.setItalic(row % 4 == 1);
		f.setBold(row % 2 == 1);
		return f;
	}
	if (role == Qt::BackgroundRole) {
		if (column == 1 && row % 2 == 0) {
			QBrush bg(Qt::red);
			return bg;
		}
	}
	return QVariant();
}