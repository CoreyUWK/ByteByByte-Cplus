#include <iostream>
#include <cassert>
#include <vector>
#include <array>
using namespace std;

template <int boardSize>
class ChessBoard {
    array<array<bool, boardSize>, boardSize> board;
    
    bool nQueenCheck(int row, int col, array<bool, boardSize> &cols, 
        array<bool, 2*boardSize - 1> &diag_down, array<bool, 2*boardSize - 1> &diag_up) {
        // Check no other queen in same column
        if (cols[col]) {
            return true;
        }

        // Check no other queen in same diagonal
        /* Diag /
          0 1 2 
        0 0 1 2
        1 1 2 3
        2 2 3 4
        */
        if (diag_up[row + col]) {
            return true;
        }

        /* Diag \
           0  1  2 => +2 
        0  0  1  2        2 3 4
        1 -1  0  1        1 2 3
        2 -2 -1  0        0 1 2 
        */
        if (diag_down[col - row + boardSize - 1]) {
            return true;
        }

        return false;
    }

    int nQueenHelper(int row, array<bool, boardSize> &cols, 
        array<bool, 2*boardSize - 1> &diag_down, array<bool, 2*boardSize - 1> &diag_up) {
        if (row >= boardSize) {
            return 1;
        }

        int count = 0;
        // For each cell in row check if possible position
        for (int col = 0; col < boardSize; ++col) {
            if (nQueenCheck(row, col, cols, diag_down, diag_up)) {
                continue;
            }

            cols[col] = true;
            diag_up[row + col] = true;
            diag_down[col - row + boardSize - 1] = true;

            count += nQueenHelper(row + 1, cols, diag_down, diag_up);

            cols[col] = false;
            diag_up[row + col] = false;
            diag_down[col - row + boardSize - 1] = false;
        }
        return count;
    }

    public:
    ChessBoard() {
        for (int row = 0; row < boardSize; ++row) {
            board[row].fill(false);
        }
    }

    int nQueen() {
        int row = 0;
        array<bool, boardSize> cols; cols.fill(false);
        array<bool, 2*boardSize - 1> diag_down; diag_down.fill(false);
        array<bool, 2*boardSize - 1> diag_up; diag_up.fill(false);
        return nQueenHelper(0, cols, diag_down, diag_up);
    }
};

void nQueenMain() {
    const int size = 4;
    ChessBoard<size> b;
    cout << "Result:" << b.nQueen() << endl;
}