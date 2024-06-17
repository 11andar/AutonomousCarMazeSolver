#include <Maze.h>

Maze::Maze(const int rows, const int cols) : rows_(rows), cols_(cols) {
    start_ = {rows_ - 2, 1};
    end_ = {1, cols_-2};
    maze_= std::vector<std::vector<CellType>>(rows_, std::vector<CellType>(cols_, CellType::WALL));
    generateRandomMaze();
}
