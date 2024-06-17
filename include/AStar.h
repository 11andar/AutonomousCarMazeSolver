#ifndef ASTAR_H
#define ASTAR_H

#include <Maze.h>
#include <unordered_map>

struct PairHash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& pair) const {
        auto hash1 = std::hash<T1>{}(pair.first);
        auto hash2 = std::hash<T2>{}(pair.second);
        return hash1 ^ (hash2 << 1);
    }
};

class AStar {
public:
    AStar(const Maze& maze);
    std::vector<std::pair<int, int>> findPath();
    ~AStar() = default;

private:
    int heuristic(const std::pair<int, int>& a, const std::pair<int, int>& b);
    std::vector<std::pair<int, int>>  reconstructPath(std::pair<int, int> start, std::pair<int, int> end);
    std::unordered_map<std::pair<int, int>, std::pair<int, int>, PairHash> cameFrom_;
    std::unordered_map<std::pair<int, int>, int, PairHash> gScore_;
    std::unordered_map<std::pair<int, int>, int, PairHash> hScore_;

    const Maze& maze_;
};

#endif
