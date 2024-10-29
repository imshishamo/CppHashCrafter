/**
 *  A simple class that implements an 8x8 game checker board with three possible values
 *  for each cell:  0, 1 or 2.
 *
 **/

/**
 *  Invariants:
 *  (1) grid.length == DIMENSION.
 *  (2) for all 0 <= i < DIMENSION, grid[i].length == DIMENSION.
 *  (3) for all 0 <= i, j < DIMENSION, grid[i][j] >= 0 and grid[i][j] <= 2.
 **/

#include "CheckerBoard.h"
using namespace std;

/**
 *  Construct a new board in which all cells are zero.
 */
CheckerBoard::CheckerBoard() {
    for (int i = 0; i < DIMENSION; i++)
        for (int j = 0; j < DIMENSION; j++)
            grid[i][j] = 0;
}

/**
 *  Set the cell (x, y) in the board to the given value mod 3.
 *  @param value to which the element should be set (normally 0, 1, or 2).
 *  @param x is the x-index.
 *  @param y is the y-index.
 *  @exception ArrayIndexOutOfBoundsException is thrown if an invalid index
 *  is given.
 **/
void CheckerBoard::setElementAt(int x, int y, int value) {
    grid[x][y] = value % 3;
    if (grid[x][y] < 0) {
        grid[x][y] += 3;
    }
}

/**
 *  Get the valued stored in cell (x, y).
 *  @param x is the x-index.
 *  @param y is the y-index.
 *  @return the stored value (between 0 and 2).
 *  @exception ArrayIndexOutOfBoundsException is thrown if an invalid index
 *  is given.
 */
int CheckerBoard::elementAt(int x, int y) const {
    return grid[x][y];
}

/**
 *  Returns true if "this" CheckerBoard and "board" have identical values in
 *    every cell.
 *  @param board is the second CheckerBoard.
 *  @return true if the boards are equal, false otherwise.
 */
bool CheckerBoard::equals(const CheckerBoard& board) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (grid[i][j] != board.elementAt(i,j)) {
                return false;
            }
        }
    }
    return true;
}

/**
 *  Returns a hash code for this CheckerBoard.
 *  @return a number between Integer.MIN_VALUE and Integer.MAX_VALUE.
 */
int CheckerBoard::hashCode() {
    string boardString = toString();  // 取得棋盤的字串表示
    int hash = 0;
    int base = 31;  // 使用 31 作為雜湊的基數（常用質數）
    for (char c : boardString) {
        hash = base * hash + (c - '0');  // 轉換字元回整數後累積雜湊值
    }
    return hash;
}

// 將棋盤的內容轉換成長度為 64 的字串
string CheckerBoard::toString(){
    string result;
    result.reserve(64);  // 預留空間，避免多次分配
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            result += to_string(grid[i][j]);  // 將數值轉為字元
        }
    }
    return result;
}

