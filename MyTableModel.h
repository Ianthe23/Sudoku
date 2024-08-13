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
    std::vector<std::vector<bool>> initialDataFlags; // Marks if the data is initial
    std::vector<std::vector<bool>> wasZeroFlags; // Marks if the initial value was 0

public:
    MyTableModel(Sudoku s) : sudoku{ s } {
        // Initialize the initial data flags
        initialDataFlags.resize(9, std::vector<bool>(9, false));
        wasZeroFlags.resize(9, std::vector<bool>(9, false)); // Initialize wasZeroFlags

        // Mark the initial data cells and zero cells
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                if (sudoku.getBoardElement(row, col) != 0) {
                    initialDataFlags[row][col] = true;
                }
                else {
                    wasZeroFlags[row][col] = true;
                }
            }
        }
    }

    int rowCount(const QModelIndex& parent = QModelIndex{}) const override {
        return 9;
    }

    int columnCount(const QModelIndex& parent = QModelIndex{}) const override {
        return 9;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole || role == Qt::EditRole) {
            int value = sudoku.getBoardElement(index.row(), index.column());
            return (value == 0) ? QVariant{} : QString::number(value);
        }
        else if (role == Qt::TextAlignmentRole) {
            return Qt::AlignCenter;
        }
        else if (role == Qt::ForegroundRole) {
            if (wasZeroFlags[index.row()][index.column()]) {
                return QColor("#8026b6");
            }
        }
        return QVariant{};
    }

    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override {
        if (role == Qt::EditRole) {
            bool ok;
            int intValue = value.toInt(&ok);
            if (ok && intValue >= 1 && intValue <= 9) {
                sudoku.setBoardElement(index.row(), index.column(), intValue);
                wasZeroFlags[index.row()][index.column()] = true; // Mark as wasZero if it's being edited
                emit dataChanged(index, index, { Qt::DisplayRole, Qt::EditRole });
                return true;
            }
        }
        return false;
    }

    void updateSudoku(const Sudoku& s) {
        this->sudoku = s;
        QModelIndex topLeft = createIndex(0, 0);
        QModelIndex bottomRight = createIndex(rowCount() - 1, columnCount() - 1);
        emit dataChanged(topLeft, bottomRight); // notify observer
        emit layoutChanged();
    }

    Qt::ItemFlags flags(const QModelIndex& index) const override {
        if (initialDataFlags[index.row()][index.column()]) {
            return Qt::ItemIsSelectable | Qt::ItemIsEnabled; // Non-editable initial data
        }
        return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled; // Editable new data
    }
};

#endif /* MYTABLEMODEL_H_ */