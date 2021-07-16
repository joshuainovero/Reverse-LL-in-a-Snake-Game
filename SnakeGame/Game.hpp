#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <ctime>
#include "Snake.hpp"

class Game{
private:
    sf::RenderWindow *window;
    sf::RectangleShape food;
    Snake *head;
    sf::Event evnt;
    sf::Clock dtClock;
    float dt;
    bool purpleApple = false;
    bool keydown = false;

    sf::RectangleShape verticalLine;
    sf::RectangleShape horizontalLine;
    sf::Vector2u boardDimensons;
    const unsigned int borderLeft = 250;
    const unsigned int borderTop = 75;

    sf::Text scoreUI;
    sf::Font font;
    uint32_t score;

    void updateEvents();
    void update();
    void drawGrid();
    void spawnFood();
    void restartGame();
    void render();

public:
    Game();
    ~Game();
    void run();
};

#endif // GAME_H