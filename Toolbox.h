// Created by Tyler Le on 4/17/24.
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Button.h"
#include "GameState.h"

#ifndef UNTITLED5_TOOLBOX_H
#define UNTITLED5_TOOLBOX_H

class Toolbox {
    // DEFAULT constructor : accessible only within class , initialize the toolbox necessary to play the game
private:
    Toolbox();


public:
    //Primary game state representation
    GameState* gameState;
    Button* debugButton;
    Button* newGameButton;
    Button* testButton1;
    Button* testButton2;
    static Toolbox& getInstance();
    bool isDebugOn = false;
    sf::RenderWindow window;







};
#endif //UNTITLED5_TOOLBOX_H
