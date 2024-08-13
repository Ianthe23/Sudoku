#include "repo.h"

// Initialize static member
Repo* Repo::instance = nullptr;

void Repo::loadFromModes(int line) {
	ifstream f(pathMode);
	if (!f.is_open()) {
		throw runtime_error("Failed to open file: " + pathMode);
	}
	Sudoku sudokuRead;
	int i = 0;

	while (f >> sudokuRead) {
		if (i == line) {
			this->sudoku = sudokuRead;
			f >> sudokuRead;
			this->sudokuRezolvat = sudokuRead;
			qDebug() << "Loaded sudoku and sudokuRezolvat successfully.";
			break;
		}
		i += 18;
	}

	if (i != line) {
		throw runtime_error("The specified line was not found in the file.");
	}

	qDebug() << "Sudoku board size after loading: " << this->sudoku.getBoard().size();

	saveFile();
	f.close();
}

void Repo::loadFile() {
	ifstream f(path);
	if (!f.is_open()) {
		throw runtime_error("Failed to open file: " + path);
	}

	Sudoku sudokuRead;

	f >> sudokuRead;
	this->sudoku = sudokuRead;

	qDebug() << "Sudoku board size after loadFile: " << this->sudoku.getBoard().size();

	f.close();
}

void Repo::saveFile() {
	ofstream g(path);

	g << this->sudoku;

	g.close();
}

void Repo::stergeRepo(int i, int j) {
	this->sudoku.setBoardElement(i, j, 0);
	saveFile();
}

void Repo::modificaRepo(int i, int j, int val) {
	qDebug() << "Indices: " << i << ", " << j << " Value: " << val;
	qDebug() << "Sudoku board size in modificaRepo method: " << this->sudoku.getBoard().size();

	if (this->sudoku.getBoard().size() == 0) {
		qDebug() << "Error: Sudoku board is empty.";
		return;  // Early return in case of an unexpected empty board
	}

	for (int lin = 0; lin < 9; ++lin) {
		QString rowStr;
		for (int col = 0; col < 9; ++col) {
			rowStr += QString::number(this->getSudoku().getBoardElement(lin, col)) + " ";
		}
		qDebug() << rowStr;
	}

	if (i < 0 || i >= 9 || j < 0 || j >= 9) {
		throw std::out_of_range("Index out of range.");
	}

	if (this->getSudokuRezolvat().getBoardElement(i, j) != val) {
		this->mistakes++;
		throw RepoException("Wrong number!");
	}

	this->getSudoku().setBoardElement(i, j, val);
	saveFile();
}