#ifndef SNAKE_H
#define SNAKE_H
#include <SFML/Graphics.hpp>
#include <vector>

class Snake{
private:
    Snake *next;
    Snake *prev;
    sf::RectangleShape body;
    sf::Vector2i prevPosition;
    sf::Vector2u bodySize;
    float tt;
    
    std::vector<uint32_t> limitationsX;
    std::vector<uint32_t> limitationsY;

public:
    Snake();
    ~Snake();
    void grow();
    void reverseSnake(Snake **headRef);
    void deleteSnake(Snake **headRef);
    void drawSnake(sf::RenderWindow *window);
    void updateSnake(float dt, float st);
    void setLimitations(const std::vector<uint32_t> &&borderX, const std::vector<uint32_t> &&borderY);
    bool ateFood(const sf::Vector2u &posFood);
    void keyboardInput();
   
    bool snakeHit;
    std::string dir;
    static uint32_t snakeSize;
};

#endif // SNAKE_H