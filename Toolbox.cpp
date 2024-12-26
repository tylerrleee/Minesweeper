// Created by Tyler Le on 4/17/24.

#include <fstream>
#include "Toolbox.h"
#include <iostream>
#include "minesweeper.h"
Toolbox& Toolbox::getInstance(){
    static Toolbox instance; // Create the instance on first use
    return instance;
};
void Test1(){
    // Once CLicked: new game by loading test board, face of Game Status is renewed, check for debug is on or off
    Toolbox& toolbox = Toolbox::getInstance();

    delete toolbox.gameState;
    toolbox.gameState = new GameState("./boards/testboard1.brd");

    // Set gameState VISUALS for this test board to be PLAYING
    sf::Texture newGame;
    newGame.loadFromFile("./images/face_happy.png");

    sf::Sprite* happy = new sf::Sprite(newGame);
    toolbox.newGameButton->setSprite(happy);



    if (toolbox.isDebugOn == true) {
        // Goes through every tile and set the mines to EXPLODED
        for (int y = 0; y < toolbox.gameState->getDimensions().y; y++) {
            for (int x = 0; x < toolbox.gameState->getDimensions().x; x++) {
                // this GameState sets the predetermined mines values to TRUE, we just need to set their Tiles' states to EXPLODED

                if (toolbox.gameState->getTile(x,y)->getMine() == true) {
                    std::cout << "Set to EXPLODED" << std::endl;
                    toolbox.gameState->getTile(x,y)->setState(Tile::EXPLODED);
                }
            }
        }
    }

}
// Same instructions as Test 1
void Test2(){
    Toolbox& toolbox = Toolbox::getInstance();

// New Predetermined Gamestate
    delete toolbox.gameState;
    toolbox.gameState = new GameState("./boards/testboard2.brd");

    // Set gameState VISUALS for this test board to be PLAYING
    sf::Texture newGame;
    newGame.loadFromFile("./images/face_happy.png");

    sf::Sprite* happy = new sf::Sprite(newGame);
    toolbox.newGameButton->setSprite(happy);


    if (toolbox.isDebugOn == true) {
        // Goes through every tile and set the mines to EXPLODED
        for (int y = 0; y < toolbox.gameState->getDimensions().y; y++) {
            for (int x = 0; x < toolbox.gameState->getDimensions().x; x++) {
                // this GameState sets the predetermined mines values to TRUE, we just need to set their Tiles' states to EXPLODED

                if (toolbox.gameState->getTile(x,y)->getMine() == true) {
                    toolbox.gameState->getTile(x,y)->setState(Tile::EXPLODED);

                }
            }
        }
    }

}






Toolbox::Toolbox() {

    window.create(sf::VideoMode(800,600), "P4 - Minesweeper, Tyler Le", sf::Style::Default);
    // initialize the ELEMENTS necessary to play the game

    gameState = new GameState();

    sf::Texture tile;
    sf::Texture buttonTexture;
    tile.loadFromFile("./images/tile_hidden.png");
    buttonTexture.loadFromFile("./images/face_lose.png");
    // Standardize size of button
    float buttonSize = buttonTexture.getSize().x;
    // The Y-Level of where the buttons are
    float y_buttons = gameState->getDimensions().y * tile.getSize().y;
    // 800 / 2 represent the middle slit, subtract by half of the button, therefore the centerpoint of the button is in the very middle
    float x_newGameButton = 800.0 / 2.0 - buttonSize / 2.0;
    // From the new_game Button, shift to the right two times of the of that button's size
    float x_debug = x_newGameButton + 2.0 * buttonSize;
    // Shift Right once
    float x_testButton1 = x_debug + buttonSize;
    // Shift right once and it is next to Testbutton1
    float x_testButton2 = x_testButton1 + buttonSize;

    // Initialize Buttons by creating new Button objects
    // Set the visualization for these buttons

    // debugButton
    debugButton = new Button(sf::Vector2f(x_debug, y_buttons), &toggleDebugMode);
    sf::Texture debugTexture;
    debugTexture.loadFromFile("./images/debug.png");
    if (!    debugTexture.loadFromFile("./images/debug.png")){
        std::cout << "File not read" << std::endl;
    }
    sf::Sprite* debugSprite = new sf::Sprite(debugTexture);
    debugSprite->setPosition(x_debug,y_buttons);
    debugButton->setSprite(debugSprite);


    // newGameButton
    newGameButton = new Button(sf::Vector2f(x_newGameButton, y_buttons), &restart);
    sf::Texture newGameTexture;
    newGameTexture.loadFromFile("./images/face_happy.png");
    if (!    newGameTexture.loadFromFile("./images/face_happy.png")){
        std::cout << "File not read" << std::endl;
    }
    sf::Sprite* newGameSprite = new sf::Sprite(newGameTexture);
    newGameSprite->setPosition(x_newGameButton,y_buttons);
    newGameButton->setSprite(newGameSprite);


    // testButton1
    testButton1 = new Button(sf::Vector2f(x_testButton1, y_buttons), &Test1);
    sf::Texture testbuttonTexture;
    testbuttonTexture.loadFromFile("./images/test_1.png");
    if (!    testbuttonTexture.loadFromFile("./images/test_1.png")){
        std::cout << "File not read" << std::endl;
    }
    sf::Sprite* testButton1_s = new sf::Sprite(testbuttonTexture);
    testButton1_s->setPosition(x_testButton1,y_buttons);
    testButton1->setSprite(testButton1_s);


    // testButton2
    testButton2 = new Button(sf::Vector2f(x_testButton2, y_buttons), &Test2);
    sf::Texture testbutton2Texture;
    testbutton2Texture.loadFromFile("./images/test_2.png");
    if (!    testbutton2Texture.loadFromFile("./images/test_2.png")){
        std::cout << "File not read" << std::endl;
    }
    sf::Sprite* testButton2_s = new sf::Sprite(testbutton2Texture);
    testButton2_s->setPosition(x_testButton2,y_buttons);
    testButton2->setSprite(testButton2_s);
}







