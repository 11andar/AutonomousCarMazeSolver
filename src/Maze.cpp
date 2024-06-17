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

void Maze::generateRandomMaze() {
    static int generation_attempts = 0;
    if (++generation_attempts > 1000) {
        throw std::runtime_error("Exceeded maximum maze generation attempts");
    }

    std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());

    maze_[start_.first][start_.second] = CellType::START;
    maze_[end_.first][end_.second] = CellType::END;

    auto visited = std::vector<std::vector<bool>>(rows_, std::vector<bool>(cols_, false));

    std::stack<std::pair<int, int>> stack;
    stack.emplace(start_.first, start_.second);

    static const std::array<std::pair<int, int>, 4> directions = {
            {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}
    };


    while (!stack.empty()) {
        auto [y, x] = stack.top();
        stack.pop();
        visited[y][x] = true;

        std::array<std::pair<int, int>, 4> shuffled_directions = directions;
        std::shuffle(shuffled_directions.begin(), shuffled_directions.end(), rng);

        for (const auto& [dy, dx] : shuffled_directions) {
            int n_row = y + dy * 2;
            int n_col = x + dx * 2;

            if (!isValidPosition(n_row, n_col))
                continue;

            if (maze_[n_row][n_col] != CellType::WALL || visited[n_row][n_col])
                continue;

            if ((y + dx != 0 && y + dx != rows_ - 1) && (x + dx != 0 && x + dx != cols_ - 1)){
                maze_[y + dy][x + dx] = CellType::EMPTY;
                if ((n_row != 0 && n_row != rows_ - 1) && (n_col != 0 && n_col != cols_ - 1)) {
                    maze_[n_row][n_col] = CellType::EMPTY;
                    stack.emplace(n_row, n_col);
                }
            }
        }
    }

    if (!hasPathFromStartToEnd()) {
        resetMaze();
        generateRandomMaze();
    }
}
