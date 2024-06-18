#include <AStar.h>
#include <algorithm>

AStar::AStar(const Maze &maze) : maze_(maze) {}

std::vector<std::pair<int, int>> AStar::findPath() {
    using Cell = std::pair<int, int>;
    using Path = std::vector<Cell>;

    Cell start = maze_.getStart();
    Cell end = maze_.getEnd();

    Path nodesToExpand;
    nodesToExpand.push_back(start);

    cameFrom_.clear();
    gScore_[start] = 0;
    hScore_[start] = heuristic(start, end);

    while (!nodesToExpand.empty()) {
        Cell current = *std::min_element(nodesToExpand.begin(), nodesToExpand.end(),
                                                [this, &end](const Cell& a, const Cell& b)
                                                { return hScore_[a] > hScore_[b]; });
        if (current == end)
            break;

        nodesToExpand.erase(std::find(nodesToExpand.begin(), nodesToExpand.end(), current));

        static const std::array<std::pair<int, int>, 4> directions = {
                {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}
        };

        for (const auto& [dy, dx] : directions) {
            Cell neighbor = {current.first + dy, current.second + dx};

            if (!maze_.isValidPosition(neighbor.first, neighbor.second) ||
                maze_.getCellType(neighbor) == CellType::WALL) {
                continue;
            }

            int approximateGScore = gScore_[current] + 1;

            if (gScore_.find(neighbor) == gScore_.end() || approximateGScore < gScore_[neighbor]) {
                cameFrom_[neighbor] = current;
                gScore_[neighbor] = approximateGScore;
                hScore_[neighbor] = gScore_[neighbor] + heuristic(neighbor, end);

                if (std::find(nodesToExpand.begin(), nodesToExpand.end(), neighbor) == nodesToExpand.end())
                    nodesToExpand.push_back(neighbor);
            }
        }
    }
    path_ = reconstructPath(start, end);
    return path_;
}

int AStar::heuristic(const std::pair<int, int>& a, const std::pair<int, int>& b) {
    return std::abs(a.first - b.first) + std::abs(a.second - b.second);
}

std::vector<std::pair<int, int>> AStar::reconstructPath(std::pair<int, int>& start, std::pair<int, int>& end) {
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
