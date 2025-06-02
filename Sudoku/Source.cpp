#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std;

const int SIZE = 9;

class Sudoku {
private:
    vector<vector<int>> board;
    vector<vector<int>> solution;

    bool isSafe(int row, int col, int num) {
        for (int x = 0; x < SIZE; x++) {
            if (board[row][x] == num || board[x][col] == num)
                return false;
        }

        int startRow = row - row % 3;
        int startCol = col - col % 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i + startRow][j + startCol] == num)
                    return false;
            }
        }
        return true;
    }

    bool solveSudoku() {
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                if (board[row][col] == 0) {
                    for (int num = 1; num <= SIZE; num++) {
                        if (isSafe(row, col, num)) {
                            board[row][col] = num;
                            if (solveSudoku())
                                return true;
                            board[row][col] = 0;
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }

    void removeDigits(int count) {
        while (count > 0) {
            int row = rand() % SIZE;
            int col = rand() % SIZE;
            if (board[row][col] != 0) {
                board[row][col] = 0;
                count--;
            }
        }
    }

public:
    Sudoku() {
        board = vector<vector<int>>(SIZE, vector<int>(SIZE, 0));
    }

    void generatePuzzle(string difficulty) {
        srand(time(0));

        solveSudoku();
        solution = board;

        int clues;
        if (difficulty == "easy") clues = 40;
        else if (difficulty == "middle") clues = 30;
        else clues = 20;

        board = solution;
        removeDigits(SIZE * SIZE - clues);
    }

    void printBoard() {
        cout << "\n    1 2 3   4 5 6   7 8 9" << endl;
        for (int i = 0; i < SIZE; i++) {
            if (i % 3 == 0 && i != 0)
                cout << "   -------+-------+------\n";
            cout << i + 1 << " | ";
            for (int j = 0; j < SIZE; j++) {
                if (j % 3 == 0 && j != 0) cout << "| ";
                if (board[i][j] == 0)
                    cout << ". ";
                else
                    cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool isCellEditable(int row, int col) {
        return board[row][col] == 0;
    }

    bool makeMove(int row, int col, int num) {
        if (solution[row][col] == num) {
            board[row][col] = num;
            return true;
        }
        return false;
    }

    bool isComplete() {
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                if (board[i][j] == 0)
                    return false;
        return true;
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    string difficulty;
    cout << "Выберите уровень сложности (easy, middle, hard): ";
    cin >> difficulty;

    Sudoku game;
    game.generatePuzzle(difficulty);

    int lives = 3;
    while (lives > 0) {
        game.printBoard();

        if (game.isComplete()) {
            cout << "Поздравляем! Вы решили судоку!\n";
            break;
        }

        int row, col, num;
        cout << "Введите ваш ход (строка [1-9] столбец [1-9] число [1-9]): ";
        cin >> row >> col >> num;
        row--; col--;

        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE || num < 1 || num > 9) {
            cout << "Неверный ввод. Попробуйте снова.\n";
            continue;
        }

        if (!game.isCellEditable(row, col)) {
            cout << "Ячейка не доступна для изменения.\n";
            continue;
        }

        if (game.makeMove(row, col, num)) {
            cout << "Ход принят!\n";
        }
        else {
            lives--;
            cout << "Неправильный ход! Осталось жизней: " << lives << "\n";
        }
    }

    if (lives == 0) {
        cout << "Игра окончена! У вас не осталось жизней.\n";
    }

    return 0;
}
