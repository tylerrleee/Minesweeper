// Created by Tyler Le on 4/17/24.
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
using namespace std;
#ifndef UNTITLED5_BUTTON_H
#define UNTITLED5_BUTTON_H

class Button
{
    std::function<void()> clicked;  // this stores the function that we want to invoke for respective buttons
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f position; // floating point pos

public:
    Button(sf::Vector2f _position, std::function<void(void)> _onClick);
    sf::Vector2f getPosition();
    sf::Sprite getSprite();
    void setSprite(sf::Sprite* _sprite);
    void onClick();
};


#endif //UNTITLED5_BUTTON_H;


