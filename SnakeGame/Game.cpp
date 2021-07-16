#include "Game.hpp"
#include <iostream>
#include <string>

Game::Game(){
    this->window = new sf::RenderWindow(sf::VideoMode(1025, 525), "Snake", sf::Style::Close);
    boardDimensons = sf::Vector2u(525, 375);
    this->verticalLine.setSize(sf::Vector2f(2, 375));
    this->horizontalLine.setSize(sf::Vector2f(525, 2));
    this->horizontalLine.setFillColor(sf::Color::Green);
    this->verticalLine.setFillColor(sf::Color(178, 190, 181));
    this->horizontalLine.setFillColor(sf::Color(178, 190, 181));

    this->food.setSize(sf::Vector2f(25,25));
    this->food.setFillColor(sf::Color::Red);
    food.setPosition(250 + (25 * (rand() % 21)), 75 + (25 * (rand() % 15)));

    this->score = 0;
    font.loadFromFile("../../font/Crossten-ExtraBold.ttf");
    this->scoreUI.setFont(this->font);
    this->scoreUI.setString("Score : " + std::to_string(this->score));
    this->scoreUI.setCharacterSize(30);
    this->scoreUI.setPosition(this->scoreUI.getPosition().x + 12, this->scoreUI.getPosition().y + 3);

    this->window->setVerticalSyncEnabled(true);
    this->dt = 0.0f;
    this->head = new Snake();
    this->head->setLimitations({225,250+this->boardDimensons.x}, {50,75+this->boardDimensons.y});
    
}

void Game::updateEvents(){
    while (this->window->pollEvent(this->evnt)){
        switch(this->evnt.type){
            case sf::Event::Closed:
                this->window->close();
            break;
            default:break;
        }
    }
}

void Game::spawnFood(){
    if (1 == rand() % 4){
        purpleApple = true;
        food.setFillColor(sf::Color(255,0,255));
    } else {
        purpleApple = false;
        food.setFillColor(sf::Color::Red);
    }
    food.setPosition(250 + (25 * (rand() % 21)), 75 + (25 * (rand() % 15)));
}

void Game::update(){
    this->dt = dtClock.restart().asSeconds();
    this->head->keyboardInput();
    
    if (!(this->head->snakeHit)){
        this->head->updateSnake(this->dt, 0.09f);
        
        if (this->head->ateFood(sf::Vector2u(this->food.getPosition().x, this->food.getPosition().y))){
            this->head->grow();
            if (purpleApple){
                this->head->reverseSnake(&this->head);
                this->head->setLimitations({225,250+this->boardDimensons.x}, {50,75+this->boardDimensons.y});
            }
            this->score++;
            this->scoreUI.setString("Score : " + std::to_string(this->score));
            this->spawnFood();
        }
    } else this->restartGame();

    this->updateEvents();
}

void Game::drawGrid(){
    unsigned int verticalX = 0;
    unsigned int horizontalY = 0;

    verticalLine.setPosition(this->borderLeft, this->borderTop);
    horizontalLine.setPosition(this->borderLeft, this->borderTop);
    this->window->draw(this->verticalLine);   
    this->window->draw(this->horizontalLine);
    for (uint32_t i = 0; i < this->boardDimensons.x/25; ++i){
        verticalX += 25;
        this->verticalLine.setPosition(this->borderLeft + verticalX, this->borderTop);
        this->window->draw(verticalLine);
    }

    for (uint32_t i = 0; i < this->boardDimensons.y/25; ++i){
        horizontalY += 25;
        this->horizontalLine.setPosition(this->borderLeft, this->borderTop + horizontalY);
        this->window->draw(this->horizontalLine);
    }
}

void Game::restartGame(){
    this->score = 0;
    this->scoreUI.setString("Score : " + std::to_string(this->score));
    this->head->deleteSnake(&this->head);
    Snake::snakeSize = 0;
    this->head = new Snake();
    this->head->setLimitations({225,250+this->boardDimensons.x}, {50,75+this->boardDimensons.y});
    this->spawnFood();
}

void Game::render(){
    this->window->clear(sf::Color(54, 69, 79));
    this->window->draw(this->food);
    this->head->drawSnake(window);
    this->drawGrid();
    this->window->draw(this->scoreUI);
    this->window->display();
}

void Game::run(){
    while (this->window->isOpen()){
        this->update();
        this->render();
    }
}

Game::~Game(){ 
    this->head->deleteSnake(&this->head);
    delete this->window; 
}