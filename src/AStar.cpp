#include <AStar.h>
#include <algorithm>

AStar::AStar(const Maze &maze) : maze_(maze) {}

int AStar::heuristic(const std::pair<int, int> &a, const std::pair<int, int> &b) {
    return std::abs(a.first - b.first) + std::abs(a.second - b.second);
}

std::vector<std::pair<int, int>> AStar::reconstructPath(std::pair<int, int> start, std::pair<int, int> end) {
    using Cell = std::pair<int, int>;
    using Path = std::vector<std::pair<int, int>>;

    Path path;
    Cell current = end;

    while (current != start) {
        path.push_back(current);
        current = cameFrom_[current];
    }

    std::reverse(path.begin(), path.end());

    return path;
}
