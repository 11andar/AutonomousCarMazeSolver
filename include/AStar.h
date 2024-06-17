#ifndef ASTAR_H
#define ASTAR_H

#include <Maze.h>
#include <unordered_map>

class AStar {
public:
    AStar(const Maze& maze);
    std::vector<std::pair<int, int>> findPath();
    ~AStar() = default;

private:
    int heuristic(const std::pair<int, int>& a, const std::pair<int, int>& b);
    std::unordered_map<std::pair<int, int>, std::pair<int, int>> cameFrom_;
    std::unordered_map<std::pair<int, int>, int> gScore_;
    std::unordered_map<std::pair<int, int>, int> hScore_;

    const Maze& maze_;
};

#endif
