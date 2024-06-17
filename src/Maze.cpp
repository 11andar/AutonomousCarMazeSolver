#include <Maze.h>
#include <stdexcept>

Maze::Maze(const int rows, const int cols) : rows_(rows), cols_(cols) {
    start_ = {rows_ - 2, 1};
    end_ = {1, cols_-2};
    maze_= std::vector<std::vector<CellType>>(rows_, std::vector<CellType>(cols_, CellType::WALL));
    generateRandomMaze();
}

int Maze::getWidth() const {
    return cols_;
}

int Maze::getHeight() const {
    return rows_;
}

std::pair<int, int> Maze::getStart() const {
    return start_;
}

std::pair<int, int> Maze::getEnd() const {
    return end_;
}

CellType Maze::getCellType(const int row, const int col) const {
    if (!isValidPosition(row, col))
        throw std::out_of_range("Invalid position, check coordinates");
    return maze_[row][col];
}

void Maze::setCellType(int row, int col, CellType& type) {
    if (!isValidPosition(row, col))
        throw std::out_of_range("Invalid position, check coordinates");
    maze_[row][col] = type;
}
