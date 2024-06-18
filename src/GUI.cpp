#include "GUI.h"

GUI::GUI(int rows, int cols, int cellSize): rows_(rows), cols_(cols),
                                            maze_(Maze(rows, cols)),
                                            aStar_(AStar(maze_)),
                                            cellSize_(cellSize), runAStar_(false) {
    windowWidth_ = cols_ * cellSize_;
    windowHeight_ = rows_ * cellSize_ + 60;
    buttonWidth_ = 100;
    buttonHeight_ = 50;
    spaceBtwnBttns_ = 30;

    window_.create(sf::VideoMode(windowWidth_, windowHeight_), "Maze");

    buttonAStar_.setSize(sf::Vector2f(buttonWidth_, buttonHeight_));
    buttonAStar_.setPosition(cellSize_, windowHeight_ - buttonHeight_ - 10);
    buttonAStar_.setFillColor(sf::Color::Magenta);
    buttonAStar_.setOutlineColor(sf::Color::White);
    buttonAStar_.setOutlineThickness(4);

    if (!font_.loadFromFile("/home/jedrek/C++/MazeSolver/fonts/Roboto-Italic.ttf")) {
        std::exit(-1);
    }

    textAStar_.setFont(font_);
    textAStar_.setString("A*");
    textAStar_.setCharacterSize(20);
    textAStar_.setFillColor(sf::Color::Black);
    textAStar_.setPosition(cellSize_ + buttonWidth_ / 2 - 10, windowHeight_ - buttonHeight_);
}

void GUI::run() {
    while (window_.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void GUI::processEvents() {
    sf::Event event{};
    while (window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window_.close();
        if (event.type == sf::Event::MouseButtonPressed) {
            if (buttonAStar_.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                runAStar_ = true;
            }
        }
    }
}

void GUI::update() {
    if (runAStar_ && !aStar_.isFinished()) {
        aStar_.step();
    }
}

void GUI::render() {
    window_.clear();
    drawMaze();
    drawButtons();
    if (aStar_.isFinished()) {
        drawPath();
    }
    window_.display();
}

void GUI::drawMaze() {
    for (int y = 0; y < maze_.getHeight(); ++y) {
        for (int x = 0; x < maze_.getWidth(); ++x) {
            sf::RectangleShape cell(sf::Vector2f(cellSize_, cellSize_));
            cell.setPosition(x * cellSize_, y * cellSize_);

            std::pair<int, int> position = {y, x};
            auto cellType = maze_.getCellType(position);

            if (cellType == CellType::WALL) {
                cell.setFillColor(sf::Color::Black);
            } else if (cellType == CellType::START) {
                cell.setFillColor(sf::Color::Green);
            } else if (cellType == CellType::END) {
                cell.setFillColor(sf::Color::Red);
            } else if (cellType == CellType::CURRENT) {
                cell.setFillColor(sf::Color::Cyan);
            } else if (cellType == CellType::EXPLORING) {
                cell.setFillColor(sf::Color::Magenta);
            } else {
                cell.setFillColor(sf::Color::White);
            }

            window_.draw(cell);
        }
    }
}

void GUI::drawButtons() {
    window_.draw(buttonAStar_);
    window_.draw(textAStar_);
}

void GUI::drawPath() {
    path_ = aStar_.getPath();
    for (const auto& pos : path_) {
        sf::RectangleShape cell(sf::Vector2f(cellSize_, cellSize_));
        cell.setPosition(pos.second * cellSize_, pos.first * cellSize_);

        if (maze_.getCellType(const_cast<std::pair<int, int> &>(pos)) == CellType::START)
            cell.setFillColor(sf::Color::Green);
        else if (maze_.getCellType(const_cast<std::pair<int, int> &>(pos)) == CellType::END)
            cell.setFillColor(sf::Color::Red);
        else
            cell.setFillColor(sf::Color::Cyan);
        window_.draw(cell);
    }
}
