#ifndef MAZE_H
#define MAZE_H

#include <CellType.h>
#include <vector>
#include <utility>
#include <random>

class Maze {
public:
    Maze(int rows, int cols);
    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeight() const;
    [[nodiscard]] std::pair<int, int>& getStart() ;
    [[nodiscard]] std::pair<int, int>& getEnd();
    [[nodiscard]] CellType getCellType(std::pair<int, int>& cell) const;
    void setCellType(std::pair<int, int>& cell, CellType& type);
    [[nodiscard]] bool isValidPosition(int row, int col) const;
    ~Maze() = default;

private:
    [[nodiscard]] bool hasPathFromStartToEnd() const;
    void resetMaze();
    void generateRandomMaze();

    int rows_;
    int cols_;
    std::vector<std::vector<CellType>> grid_;
    std::pair<int, int> start_;
    std::pair<int, int> end_;
//    bool hasPathFromStartToEnd_;
};

#endif