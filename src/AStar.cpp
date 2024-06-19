#include <AStar.h>
#include <algorithm>
#include <utility>

AStar::AStar(const Maze &maze, std::function<void()> updateCallback) : maze_(maze), finished_(false),
expansionOccurred_(false), updateCallback_(std::move(updateCallback)) {
    nodesToExpand_.emplace(0, maze_.getStart());
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
        expansionOccurred_ = false;
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

            CellType cellType = CellType::VISITED;
            maze_.setCellType(neighbor, cellType);
            maze_.setCellType(current, cellType);
            expansionOccurred_ = true;
        }

        if (expansionOccurred_ && updateCallback_) {
            updateCallback_();
        }
    }
}

bool AStar::isFinished() const {
    return finished_;
}

bool AStar::expansionOccurred() const {
    return expansionOccurred_;
}

std::vector<std::pair<int, int>> AStar::getPath() {
    if (!finished_)
        return {};
    return reconstructPath(maze_.getStart(), maze_.getEnd());
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
