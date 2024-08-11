#ifndef DOMAIN_H_
#define DOMAIN_H_

#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<string> splitLine(const string& line, char delimiter);

class Sudoku {
private:
	vector <vector <int>> board;
	bool finished = 1;

public:
	//constructor implicit
	Sudoku();

	//constructor cu parametri
	Sudoku(vector<vector <int>> board);

	//destructor
	~Sudoku() = default;

	//copia constructorului
	Sudoku(const Sudoku& s);

	//GETTERS
	vector<vector <int>> getBoard() const noexcept;
	int getBoardElement(int i, int j) const noexcept;
	bool getFinished() const noexcept;

	//SETTERS
	void setBoard(vector<vector <int>> board);
	void setBoardElement(int i, int j, int val);
	void setFinished(bool finished);

	//OPERATORS
	Sudoku& operator=(const Sudoku& s) = default;
	bool operator==(const Sudoku& s) const;
	bool operator!=(const Sudoku& s) const;

	friend istream &operator>>(istream &is, Sudoku &s);
};

ostream &operator<<(ostream &os, const Sudoku &s);

#endif /* DOMAIN_H_ */