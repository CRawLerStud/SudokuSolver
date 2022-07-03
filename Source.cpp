#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

ifstream fin("fisier.in");
ofstream fout("fisier.out");

//reading the matrix (sudoku table) from the file above
void citire(int A[][10]) {
	for (int i = 1; i <= 9; i++)
		for (int j = 1; j <= 9; j++)
			fin >> A[i][j];
}

/*
* Search for the first free element after the position (i, j)
* Param A: the matrix
* Param i: the line where the before element appear
* Param j: the column where the before element appear
* Return:	a pair of two integers -> next free position in matrix
*			the pair has no elements if there is no free position
*/
vector<int> firstFreePosition(int A[][10]) {
	vector<int> solution;
	for(int i=1; i<=9; i++)
		for(int j=1; j<=9; j++)
			if (A[i][j] == 0) {
				solution.push_back(i);
				solution.push_back(j);
				return solution;
			}
	return solution;
}

void possibilitiesSquare(int A[][10], bool (&a)[10], int i, int j) {
	int startI, endI, startJ, endJ;
	startI = endI = startJ = endJ = 0;
	if (i <= 3) {
		startI = 1;
		endI = 3;
	}
	else if (i <= 6) {
		startI = 4;
		endI = 6;
	}
	else if (i <= 9) {
		startI = 7;
		endI = 9;
	}

	if (j <= 3) {
		startJ = 1;
		endJ = 3;
	}
	else if (j <= 6) {
		startJ = 4;
		endJ = 6;
	}
	else if (j <= 9) {
		startJ = 7;
		endJ = 9;
	}

	for (int x = startI; x <= endI; x++)
		for (int y = startJ; y <= endJ; y++)
			if (A[x][y] != 0)
				a[A[x][y]] = false;
}

void possibilitiesColumn(int A[][10], bool (&a)[10], int j) {
	for (int i = 1; i <= 9; i++)
		if (A[i][j] != 0)
			a[A[i][j]] = false;
}

void possibilitiesLine(int A[][10], bool (&a)[10], int i) {
	for (int j = 1; j <= 9; j++)
		if (A[i][j] != 0)
			a[A[i][j]] = false;
}

vector<int> possibilities(int A[][10], int i, int j) {
	//i - number's line
	//j - number's column
	//A - matrix
	bool all[10] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	possibilitiesSquare(A, all, i, j);
	possibilitiesColumn(A, all, j);
	possibilitiesLine(A, all, i);
	vector<int> solution;
	for (int i = 1; i <= 9; i++)
		if (all[i])
			solution.push_back(i);
	return solution;
}

bool solveSudoku(int (&A)[10][10]) {

	vector<int> freePos = firstFreePosition(A);
	if (freePos.size() == 0)
		return true;
	int x = freePos[0];
	int y = freePos[1];
	vector<int> pos = possibilities(A, x, y);
	for (auto i : pos) {
		A[x][y] = i;
		if (solveSudoku(A) == true)
			return true;
	}
	A[x][y] = 0;
	return false;
}

int main() {

	int A[10][10] = { 0 };
	citire(A);

	/*
	* The number must not be repeating on the line
	* The number must not be repeating on the column
	* The number must not be repeating in the box(3x3 square)
	*/

	if (solveSudoku(A) == true)
		cout << "Rezolvat!\n";
	else
		cout << "Imposibil!\n";

	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++)
			fout << A[i][j] << ' ';
		fout << endl;
	}
	fout << endl;

	return 0;
}