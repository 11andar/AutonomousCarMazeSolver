#include <Maze.h>
#include <stdexcept>
#include <chrono>
#include <array>
#include <stack>
#include <algorithm>
#include <queue>

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

bool Maze::isValidPosition(int row, int col) const {
    return (0 <= row && row <= rows_-1 && 0 <= col && col <= cols_-1);
}

bool Maze::hasPathFromStartToEnd() const {
    std::queue<std::pair<int, int>> queue;
    std::vector<std::vector<bool>> visited(rows_, std::vector<bool>(cols_, false));

    queue.push(start_);
    visited[start_.first][start_.second] = true;

    while (!queue.empty()) {
        auto [y, x] = queue.front();
        queue.pop();

        if (std::make_pair(y, x) == end_) {
            return true;
        }

        static const std::array<std::pair<int, int>, 4> directions = {
                {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}
        };

        for (const auto& [dy, dx] : directions) {
            int ny = y + dy;
            int nx = x + dx;

            if (isValidPosition(ny, nx) && !visited[ny][nx] && maze_[ny][nx] != CellType::WALL) {
                queue.emplace(ny, nx);
                visited[ny][nx] = true;
            }
        }
    }
    return false;
}

void Maze::resetMaze() {
    maze_ = std::vector<std::vector<CellType>>(rows_, std::vector<CellType>(cols_, CellType::WALL));
}
