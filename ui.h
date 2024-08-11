#ifndef UI_H_
#define UI_H_

#include "repo.h"
#include "MyTableModel.h"

#include <QMainWindow>
#include <QTableView>
#include <QTableWidget>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>
#include <iostream>
#include <random>

class MainWindow : public QWidget {
public:
	MainWindow() {
		this->initMainWindow();
		this->connectSignalsMain();
	}
private:
	QPushButton* btn_easy = new QPushButton("Easy");
	QPushButton* btn_medium = new QPushButton("Medium");
	QPushButton* btn_hard = new QPushButton("Hard");
	QPushButton* btn_expert = new QPushButton("Expert");

	void initMainWindow();
	void connectSignalsMain();
	int generateRandomNumber();
};

class CentralWindow : public QWidget {
	Q_OBJECT
public:
	CentralWindow(Repo& repo) : repo{ repo } {
		this->initCentralWindow();
		loadTable(repo.getSudoku());
		//this->connectSignalsCentral();
	}
private:
	Repo& repo;
	MyTableModel* model;
	QTableView* table = new QTableView;
	MyTableDelegate* delegate = new MyTableDelegate;

	QPushButton* btn_1 = new QPushButton("1");
	QPushButton* btn_2 = new QPushButton("2");
	QPushButton* btn_3 = new QPushButton("3");
	QPushButton* btn_4 = new QPushButton("4");
	QPushButton* btn_5 = new QPushButton("5");
	QPushButton* btn_6 = new QPushButton("6");
	QPushButton* btn_7 = new QPushButton("7");
	QPushButton* btn_8 = new QPushButton("8");
	QPushButton* btn_9 = new QPushButton("9");

	void initCentralWindow();
	void loadTable(Sudoku sudoku);
	//void connectSignalsCentral();

signals:
	void resized();

protected:
	void resizeEvent(QResizeEvent* event) override {
		emit resized();
		QWidget::resizeEvent(event);

		qDebug() << "Sudoku window size:" << this->width() << "x" << this->height();
	}

private slots:
	void adjustSizes() {
		int totalWidth = table->viewport()->width();
		int totalHeight = table->viewport()->height();

		for (int i = 0; i < model->columnCount(); ++i) {
			table->setColumnWidth(i, totalWidth / 9);
		}

		for (int i = 0; i < model->rowCount(); ++i) {
			table->setRowHeight(i, totalHeight / 9);
		}
	}
};


#endif /* UI_H_ */