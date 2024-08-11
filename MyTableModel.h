#ifndef MYTABLEMODEL_H_
#define MYTABLEMODEL_H_

#include "MyTableDelegate.h"

#include <QAbstractTableModel>
#include <QAbstractItemView>
#include <QHeaderView>
#include <QTableView>
#include <iostream>
#include <vector>

#include "domain.h"
using std::vector;

class MyTableModel : public QAbstractTableModel {
	Sudoku sudoku;
public:
	MyTableModel(Sudoku s) : sudoku{ s } {}

	int rowCount(const QModelIndex& parent = QModelIndex{}) const override {
		return 9;
	}

	int columnCount(const QModelIndex& parent = QModelIndex{}) const override {
		return 9;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			//hide the 0s
			if (sudoku.getBoardElement(index.row(), index.column()) == 0) {
				return QVariant{};
			}
			return QString::number(sudoku.getBoardElement(index.row(), index.column()));
		}
		else if (role == Qt::TextAlignmentRole) {
			return Qt::AlignCenter;
		}
		
		return QVariant{};
	}

	Sudoku getSudoku(Sudoku& s) {
		this->sudoku = s;
		QModelIndex topLeft = createIndex(0, 0);
		QModelIndex bottomRight = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomRight); // notify ca la observer
		emit layoutChanged();
	}

	//make outer border thick

};

#endif /* MYTABLEMODEL_H_ */