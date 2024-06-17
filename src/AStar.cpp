#include <AStar.h>

AStar::AStar(const Maze &maze) : maze_(maze) {}

int AStar::heuristic(const std::pair<int, int> &a, const std::pair<int, int> &b) {
    return std::abs(a.first - b.first) + std::abs(a.second - b.second);
}



