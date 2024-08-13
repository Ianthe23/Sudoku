#include "tests.h"

void Tests::testAll() {
	testDomain();
	testRepo();
}

void Tests::testDomain() {
	vector<vector<int>> board{ { 4, 9, 6, 0, 7, 0, 0, 0, 0 },
						 { 0, 0, 8, 9, 0, 3, 0, 0, 0 },
						 { 7, 5, 0, 8, 0, 2, 0, 1, 9 },
						 { 0, 0, 0, 0, 0, 0, 0, 2, 5 },
						 { 0, 0, 1, 7, 2, 0, 4, 9, 0 },
						 { 8, 0, 7, 0, 9, 0, 3, 6, 0 },
						 { 0, 8, 0, 0, 0, 7, 9, 0, 0 },
						 { 0, 6, 0, 0, 5, 4, 0, 3, 0 },
						 { 0, 0, 0, 2, 8, 9, 1, 5, 6 } };
	Sudoku s(board);
	assert(s.getBoard() == board);
	assert(s.getFinished() == 1);
	s.setFinished(0);
	assert(s.getFinished() == 0);

	assert(s.getBoardElement(0, 0) == 4);
	s.setBoardElement(0, 0, 5);
	assert(s.getBoardElement(0, 0) == 5);
	s.setBoardElement(0, 0, 4);

	vector<vector<int>> board2{ { 4, 9, 6, 0, 7, 0, 0, 0, 0 },
						 { 0, 0, 8, 9, 0, 3, 0, 0, 0 },
						 { 7, 5, 0, 8, 0, 2, 0, 1, 9 },
						 { 0, 0, 0, 0, 0, 0, 0, 2, 5 },
						 { 0, 0, 1, 7, 2, 0, 4, 9, 0 },
						 { 8, 0, 7, 0, 9, 0, 3, 6, 0 },
						 { 0, 8, 0, 0, 0, 7, 9, 0, 0 },
						 { 0, 6, 0, 0, 5, 4, 0, 3, 0 },
						 { 0, 0, 0, 2, 8, 9, 1, 5, 6 } };
	Sudoku s2(board2);
	assert(s == s2);
	vector<vector<int>> board3{ { 4, 9, 6, 0, 7, 0, 0, 0, 0 },
						 { 0, 0, 8, 9, 0, 3, 0, 0, 0 },
						 { 7, 5, 0, 8, 0, 2, 0, 1, 9 },
						 { 0, 0, 0, 0, 0, 0, 0, 2, 5 },
						 { 0, 0, 1, 7, 2, 0, 4, 9, 0 },
						 { 8, 0, 7, 0, 9, 0, 3, 6, 0 },
						 { 0, 8, 0, 0, 0, 7, 9, 0, 0 },
						 { 0, 6, 0, 0, 5, 4, 0, 3, 0 },
						 { 0, 0, 0, 2, 8, 9, 1, 5, 4 } };
	Sudoku s3(board3);
	assert(s != s3);

	vector<vector<int>> board4{ { 4, 9, 6, 0, 7, 0, 0, 0, 0 },
						 { 0, 0, 8, 9, 0, 3, 0, 0, 0 },
						 { 7, 5, 0, 8, 0, 2, 0, 1, 9 },
						 { 0, 0, 0, 0, 0, 0, 0, 2, 5 },
						 { 0, 0, 1, 7, 2, 0, 4, 9, 0 },
						 { 8, 0, 7, 0, 9, 0, 3, 6, 0 },
						 { 0, 8, 0, 0, 0, 7, 9, 0, 0 },
						 { 0, 6, 0, 0, 5, 4, 0, 3, 0 },
						 { 0, 0, 0, 2, 8, 9, 1, 5, 6 } };
	Sudoku s4(board4);
}

void Tests::testRepo() {
	//Repo r("testRepo.txt", "easy.txt", 0);
	//r.stergeRepo(0, 0);
	//assert(r.getSudoku().getBoardElement(0, 0) == 0);
	//r.modificaRepo(0, 0, 4);
	//assert(r.getSudoku().getBoardElement(0, 0) == 4);

	//assert(r.getSudokuRezolvat().getBoardElement(5, 8) == 1);

	////clear file
	//ofstream g("testRepo.txt");
	//g.close();
}