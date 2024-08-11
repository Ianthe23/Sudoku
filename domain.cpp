#include "domain.h"

Sudoku::Sudoku() {
	vector <int> row;
	for (int i = 0; i < 9; i++) {
		row.push_back(0);
	}
	for (int i = 0; i < 9; i++) {
		this->board.push_back(row);
	}
}

Sudoku::Sudoku(vector<vector <int>> board) {
	this->board = board;
}

Sudoku::Sudoku(const Sudoku& s) {
	this->board = s.board;
	this->finished = s.finished;
}

vector<vector <int>> Sudoku::getBoard() const noexcept {
	return this->board;
}

int Sudoku::getBoardElement(int i, int j) const noexcept {
	return this->board[i][j];
}

bool Sudoku::getFinished() const noexcept {
	return this->finished;
}

void Sudoku::setBoard(vector<vector <int>> board) {
	this->board = board;
}

void Sudoku::setBoardElement(int i, int j, int val) {
	this->board[i][j] = val;
}

void Sudoku::setFinished(bool finished) {
	this->finished = finished;
}

bool Sudoku::operator==(const Sudoku& s) const {
	return this->board == s.board;
}

bool Sudoku::operator!=(const Sudoku& s) const {
	return this->board != s.board;
}

vector<string> splitLine(const string& line, char delimiter) {
	vector<string> atributes;
	stringstream stream(line);
	string object;

	while (getline(stream, object, delimiter)) {
		atributes.push_back(object);
	}

	return atributes;
}

istream& operator>>(istream& is, Sudoku& s) {
	string line;
	vector<vector<int>> board;
	for (int i = 0; i < 9; i++) {
		vector<int> row;
		getline(is, line);
		vector<string> atributes = splitLine(line, ' ');
		for (int j = 0; j < 9; j++) {
			row.push_back(stoi(atributes[j]));
		}
		board.push_back(row);
	}
	s.setBoard(board);
	return is;
}

ostream& operator<<(ostream& os, const Sudoku& s) {
	vector<vector<int>> board = s.getBoard();
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			os << board[i][j] << " ";
		}
		os << endl;
	}
	return os;
}