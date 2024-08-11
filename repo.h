#ifndef REPO_H_
#define REPO_H_

#include "domain.h"
#include "exceptions.h"
#include <fstream>
#include <vector>

class Repo {
private:
	Sudoku sudoku;
	Sudoku sudokuRezolvat;
	string path;
	string pathMode;
	int line;
	void loadFromModes(int line);
	void loadFile();
	void saveFile();
public:
	Repo(const string& p, const string& pm, int l) : path(p), pathMode(pm), line(l) {
		loadFromModes(l);
	}

	Repo(Repo& other) = delete;

	void adaugaRepo(int i, int j, int val);
	void stergeRepo(int i, int j);
	void modificaRepo(int i, int j, int val);

	Sudoku getSudoku() const noexcept {
		return this->sudoku;
	};
};

#endif /* REPO_H_ */