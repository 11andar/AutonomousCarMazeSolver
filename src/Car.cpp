#include "Car.h"
#include <utility>

Car::Car() {}

Car::Car(const std::pair<int, int>& position, const std::pair<int, int>& destination, const double& speed) :
        position_(position),  destination_(destination), speed_(speed) {}

std::pair<int, int> Car::getPosition() const {
    return position_;
}

void Car::setPosition(int x, int y) {
    position_ = {x, y};
}

std::pair<int, int> Car::getDestination() const {
    return destination_;
}

void Car::setDestination(int x, int y) {
    destination_ = {x, y};
}

std::vector<std::pair<int, int>> Car::getPath() const {
    return path_;
}

void Car::setPath(const std::vector<std::pair<int, int>>& path) {
    path_ = path;
}

double Car::getSpeed() const {
    return speed_;
}

void Car::setSpeed(double speed) {
    speed_ = speed;
}
