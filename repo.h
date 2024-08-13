#ifndef REPO_H_
#define REPO_H_

#include "domain.h"
#include "exceptions.h"
#include <fstream>
#include <vector>
#include <qDebug>

// Singleton pattern implementation for Repo class
class Repo {
private:
    Sudoku sudoku;
    Sudoku sudokuRezolvat;
    string path;
    string pathMode;
    int line;
    int mistakes = 0;
    static Repo* instance;

    // Private constructor to prevent multiple instances
    Repo(const string& p, const string& pm, int l)
        : path(p), pathMode(pm), line(l) {
        loadFromModes(l);
    }

    void loadFromModes(int line);
    void loadFile();
    void saveFile();

public:
    Repo(Repo& other) = delete; // Prevent copying

    static Repo* getInstance(const string& p = "", const string& pm = "", int l = 0) {
        if (instance == nullptr) {
            instance = new Repo(p, pm, l);
        }
        return instance;
    }

    void stergeRepo(int i, int j);
    void modificaRepo(int i, int j, int val);

    Sudoku& getSudoku() noexcept {
        return this->sudoku;
    };

    Sudoku& getSudokuRezolvat() noexcept {
        return this->sudokuRezolvat;
    };

    int getMistakes() noexcept {
		return this->mistakes;
	}

    bool isGameOver() noexcept {
		return this->mistakes == 3;
	}

    bool isGameWon() noexcept {
        return this->sudoku == this->sudokuRezolvat;
    }

    static void resetInstance() {
        delete instance;
        instance = nullptr;
    }
};

#endif /* REPO_H_ */