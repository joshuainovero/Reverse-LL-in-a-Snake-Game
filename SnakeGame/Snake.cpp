#include "Snake.hpp"
#include <iostream>

uint32_t Snake::snakeSize = 0;

void Snake::grow(){
    Snake *newBody = new Snake();
    Snake *headCpy = this;
    while (headCpy->next != nullptr)
        headCpy = headCpy->next;
    headCpy->next = newBody;
    headCpy->next->prev = headCpy;
    headCpy->next->body.setPosition(headCpy->prevPosition.x, headCpy->prevPosition.y);

    // Get opposite direction for the last node
    if (headCpy->prevPosition.x < headCpy->body.getPosition().x) headCpy->next->dir = "left";
    if (headCpy->prevPosition.x > headCpy->body.getPosition().x) headCpy->next->dir = "right";
    if (headCpy->prevPosition.y < headCpy->body.getPosition().y) headCpy->next->dir = "up";
    if (headCpy->prevPosition.y > headCpy->body.getPosition().y) headCpy->next->dir = "down";
}

void Snake::reverseSnake(Snake **headRef){
    Snake *ptr1 = *headRef;
    Snake *ptr2 = (*headRef)->next;

    ptr1->next = nullptr;
    ptr1->prev = ptr2;

    while (ptr2 != nullptr){
        ptr2->prev = ptr2->next;
        ptr2->next = ptr1;
        ptr1 = ptr2;
        ptr2 = ptr2->prev;
    }
    *headRef = ptr1;
}

Snake::Snake(){
    body.setSize(sf::Vector2f(25,25));
    body.setFillColor(sf::Color(255,255,0));
    this->bodySize = sf::Vector2u(this->body.getSize().x, this->body.getSize().y);
    Snake::snakeSize++;
    this->next = nullptr;
    this->tt = 0.0f;
    this->snakeHit = false;
    if (Snake::snakeSize <= 1){
        this->body.setPosition(500, 250);
        this->prev = nullptr;
        this->dir = "right";
    } 
}

void Snake::keyboardInput(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && this->dir != "left")
        this->dir = "right";
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && this->dir != "right")
        this->dir = "left";
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && this->dir != "down")
        this->dir = "up";
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && this->dir != "up")
        this->dir = "down";
}

void Snake::updateSnake(float dt, float st){
    Snake *preceedingNodes = this;

    this->tt += dt;
    if (this->tt >= st){
        this->tt = 0.0f;
        
        while (preceedingNodes != nullptr){
            preceedingNodes->prevPosition.x = preceedingNodes->body.getPosition().x;
            preceedingNodes->prevPosition.y = preceedingNodes->body.getPosition().y;
            preceedingNodes = preceedingNodes->next;
        }

        try {
            if (this->dir == "right"){
                if (this->body.getPosition().x + this->bodySize.x >= this->limitationsX.at(1))
                    throw(this->snakeHit);
                else
                    this->body.setPosition(this->body.getPosition().x + this->bodySize.x, this->body.getPosition().y);
            }
            else if (this->dir == "left"){
                if (this->body.getPosition().x - this->bodySize.x <= this->limitationsX.at(0))
                    throw(this->snakeHit);
                else 
                    this->body.setPosition(this->body.getPosition().x - this->bodySize.x, this->body.getPosition().y);
            }
            else if (this->dir == "up"){
                if (this->body.getPosition().y - this->bodySize.y <= this->limitationsY.at(0))
                    throw(this->snakeHit);
                else 
                    this->body.setPosition(this->body.getPosition().x, this->body.getPosition().y - bodySize.y);
            }
            else if (this->dir == "down"){
                if (this->body.getPosition().y + this->bodySize.y >= this->limitationsY.at(1))
                    throw(this->snakeHit);
                else
                    this->body.setPosition(this->body.getPosition().x, this->body.getPosition().y + bodySize.y);
            }

            preceedingNodes = this->next;
        
            while (preceedingNodes != nullptr){
                if (preceedingNodes->body.getPosition().x == this->body.getPosition().x && preceedingNodes->body.getPosition().y == this->body.getPosition().y)
                    this->snakeHit = true;
                preceedingNodes->body.setPosition(preceedingNodes->prev->prevPosition.x, preceedingNodes->prev->prevPosition.y);
                preceedingNodes = preceedingNodes->next;

            }

        } catch (bool threwHit){
            this->snakeHit = true;
        }

    }

    
}

void Snake::setLimitations(const std::vector<uint32_t> &&borderX, const std::vector<uint32_t> &&borderY){
    this->limitationsX.push_back(borderX.at(0));
    this->limitationsX.push_back(borderX.at(1));
    this->limitationsY.push_back(borderY.at(0));
    this->limitationsY.push_back(borderY.at(1));
}

bool Snake::ateFood(const sf::Vector2u &posFood){
    return this->body.getPosition().x == posFood.x && this->body.getPosition().y == posFood.y;
}

void Snake::deleteSnake(Snake **headRef){
    Snake *nextGuy;
    while (*headRef != nullptr){
        nextGuy = (*headRef)->next;
        delete *headRef;
        *headRef = nextGuy;
    }
}

void Snake::drawSnake(sf::RenderWindow *window){
    Snake *headCpy = this;
    while (headCpy != nullptr){
        window->draw(headCpy->body);
        headCpy = headCpy->next;
    }
}

Snake::~Snake(){ /*this->deleteSnake(&this->next->prev);*/ }