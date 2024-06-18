#include <AStar.h>
#include <algorithm>

AStar::AStar(const Maze &maze) : maze_(maze), finished_(false) {
    nodesToExpand_.emplace(0, maze_.getStart());
}

std::vector<std::pair<int, int>> AStar::getPath() {
    if (!finished_)
        return {};
    return reconstructPath(maze_.getStart(), maze_.getEnd());
}

void AStar::step() {
    if (finished_ || nodesToExpand_.empty()) {
        return;
    }

    using Cell = std::pair<int, int>;

    Cell current = nodesToExpand_.top().second;
    nodesToExpand_.pop();

    if (current == maze_.getEnd()) {
        finished_ = true;
        return;
    }

    static const std::array<std::pair<int, int>, 4> directions = {
            {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}
    };

    for (const auto& [dy, dx] : directions) {
        Cell neighbor = {current.first + dy, current.second + dx};

        if (!maze_.isValidPosition(neighbor.first, neighbor.second) ||
            maze_.getCellType(neighbor) == CellType::WALL)
            continue;

        int approximateGScore = gScore_[current] + 1;

        if (gScore_.find(neighbor) == gScore_.end() || approximateGScore < gScore_[neighbor]) {
            cameFrom_[neighbor] = current;
            gScore_[neighbor] = approximateGScore;
            hScore_[neighbor] = gScore_[neighbor] + heuristic(neighbor, maze_.getEnd());

            nodesToExpand_.emplace(hScore_[neighbor], neighbor);
        }
    }
}

bool AStar::isFinished() const {
    return finished_;
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

    path.push_back(maze_.getStart());
    std::reverse(path.begin(), path.end());

    return path;
}


