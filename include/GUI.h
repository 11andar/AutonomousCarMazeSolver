#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include "Maze.h"
#include "AStar.h"
#include "MazeObserver.h"

class GUI : public MazeObserver {
public:
    GUI(int rows, int cols, int cellSize);
    void run();

private:
    void processEvents();
    void update();
    void render();
    void drawMaze();
    void drawButtons();
    void drawPath();
    void onMazeUpdate() override;

    sf::RenderWindow window_;
    Maze maze_;
    AStar aStar_;
    int rows_;
    int cols_;
    int cellSize_;
    int windowWidth_;
    int windowHeight_;
    int buttonWidth_;
    int buttonHeight_;
    int spaceBtwnBttns_;
    bool runAStar_;
    std::vector<std::pair<int, int>> path_;
    sf::RectangleShape buttonAStar_;
    sf::Text textAStar_;
    sf::Font font_;
};

#endif
