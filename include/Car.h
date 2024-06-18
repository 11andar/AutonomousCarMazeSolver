#ifndef CAR_H
#define CAR_H

#include <vector>
#include <utility>

class Car {
public:
    Car();
    Car(const std::pair<int, int>& position, const std::pair<int, int>& destination, const double& speed);

    [[nodiscard]] std::pair<int, int> getPosition() const;
    void setPosition(int x, int y);

    [[nodiscard]] std::pair<int, int> getDestination() const;
    void setDestination(int x, int y);

    [[nodiscard]] std::vector<std::pair<int, int>> getPath() const;
    void setPath(const std::vector<std::pair<int, int>>& path);

    [[nodiscard]] double getSpeed() const;
    void setSpeed(double speed);

private:
    std::pair<int, int> position_;
    std::pair<int, int> destination_;
    std::vector<std::pair<int, int>> path_;
    double speed_{};
};

#endif
