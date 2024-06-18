#ifndef ASTAR_H
#define ASTAR_H

#include <Maze.h>
#include <unordered_map>
#include <queue>

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
    void step();
    bool isFinished() const;
    std::vector<std::pair<int, int>> getPath();
    ~AStar() = default;

private:
    int heuristic(const std::pair<int, int>& a, const std::pair<int, int>& b);
    std::vector<std::pair<int, int>> reconstructPath(std::pair<int, int>& start, std::pair<int, int>& end);

    Maze maze_;
    bool finished_;
    std::vector<std::pair<int, int>> path_;
    std::unordered_map<std::pair<int, int>, int, PairHash> gScore_;
    std::unordered_map<std::pair<int, int>, int, PairHash> hScore_;
    std::unordered_map<std::pair<int, int>, std::pair<int, int>, PairHash> cameFrom_;

    using Node = std::pair<int, std::pair<int, int>>;
    using PriorityQueue = std::priority_queue<Node, std::vector<Node>, std::greater<>>;
    PriorityQueue nodesToExpand_;

};

#endif
