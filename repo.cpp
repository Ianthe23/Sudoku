#include "repo.h"

void Repo::loadFromModes(int line) {
	ifstream f(pathMode);
	Sudoku sudokuRead;
	int i = 0;

	while (f >> sudokuRead) {
		if (i == line) {
			this->sudoku = sudokuRead;
			f >> sudokuRead;
			this->sudokuRezolvat = sudokuRead;
			break;
		}
		i += 18;
	}
	saveFile();
	f.close();
}

void Repo::loadFile() {
	ifstream f(path);
	Sudoku sudokuRead;

	f >> sudokuRead;
	this->sudoku = sudokuRead;

	f.close();
}

void Repo::saveFile() {
	ofstream g(path);

	g << this->sudoku;

	g.close();
}

void Repo::adaugaRepo(int i, int j, int val) {
	if (this->sudokuRezolvat.getBoardElement(i, j) != val) {
		throw RepoException("Valoare gresita!");
	}
	this->sudoku.setBoardElement(i, j, val);
	saveFile();
}

void Repo::stergeRepo(int i, int j) {
	this->sudoku.setBoardElement(i, j, 0);
	saveFile();
}

void Repo::modificaRepo(int i, int j, int val) {
	if (this->sudokuRezolvat.getBoardElement(i, j) != val) {
		throw RepoException("Valoare gresita!");
	}
	this->sudoku.setBoardElement(i, j, val);
	saveFile();
}