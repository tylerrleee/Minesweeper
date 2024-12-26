//
// Created by Tyler Le on 4/18/24.
//
#include <SFML/Graphics.hpp>
#include "minesweeper.h"
#include "Toolbox.h"
#include "GameState.h"
#include <iostream>


sf::Sprite* setNumb(int numb, sf::Sprite* numbSprite, sf::Texture& numbTexture){
    if(numb == 0){
        numbSprite = new sf::Sprite(numbTexture, sf::IntRect(numb,numb, numbTexture.getSize().x / 10, numbTexture.getSize().y));
    }
    else if (numb > 10) {
        std::cout << "number greater than 10" << std::endl;
    }
    else{
        numbSprite = new sf::Sprite(numbTexture, sf::IntRect(numbTexture.getSize().x / 11 * numb,0,numbTexture.getSize().x/11,numbTexture.getSize().y));
    }

    return numbSprite;

}
std::vector<sf::Sprite*> getNumb(sf::Texture& digits)
{
    Toolbox& toolbox = Toolbox::getInstance();

    int firstDigit = abs((toolbox.gameState->getMineCount() - toolbox.gameState->getFlagCount())%10); //first digit place
    int secondDigit = abs(((toolbox.gameState->getMineCount() - toolbox.gameState->getFlagCount())%100)/10);
    int thirdDigit = (toolbox.gameState->getMineCount() - toolbox.gameState->getFlagCount())/100;
    //std::cout << firstDigit << ", " << secondDigit << ", " << thirdDigit << "\n";
    sf::Sprite* firstDigit_s = setNumb(firstDigit, firstDigit_s, digits);
    sf::Sprite* secondDigit_s = setNumb(secondDigit, secondDigit_s, digits);
    sf::Sprite* thirdDigit_s;
    if (toolbox.gameState->getMineCount() - toolbox.gameState->getFlagCount() < 0)
    {
        thirdDigit_s = setNumb(10, thirdDigit_s, digits);
    }
    else {
        thirdDigit_s = setNumb(thirdDigit, thirdDigit_s, digits);
    }

    sf::Texture tile;
    tile.loadFromFile("./images/tile_hidden.png");
    float y = toolbox.gameState->getDimensions().y * tile.getSize().y;
    firstDigit_s->setPosition(digits.getSize().x/11 * 2, y);
    secondDigit_s->setPosition(digits.getSize().x/11, y);
    thirdDigit_s->setPosition(0, y);

    std::vector<sf::Sprite*> digitsVector;
    digitsVector.push_back(firstDigit_s);
    digitsVector.push_back(secondDigit_s);
    digitsVector.push_back(thirdDigit_s);
    return digitsVector;
}





void restart(){
    Toolbox& toolbox = Toolbox::getInstance();
    // delete current gameState
    delete toolbox.gameState;
    toolbox.gameState = new GameState(); //create new tiles
    if (getDebugMode() == true) {
        for (int y = 0; y < toolbox.gameState->getDimensions().y; y++) {
            for (int x = 0; x < toolbox.gameState->getDimensions().x; x++) {
                if (toolbox.gameState->getTile(x,y)->getMine() == true) {
                    toolbox.gameState->getTile(x,y)->setState(Tile::EXPLODED);
                }
            }
        }
    }
    delete toolbox.newGameButton;
    sf::Texture hidden;
    sf::Texture Happybutton;
    hidden.loadFromFile("./images/tile_hidden.png");
    Happybutton.loadFromFile("./images/face_happy.png");


    // The Y-Level of where the buttons are
    float y = toolbox.gameState->getDimensions().y * hidden.getSize().y;
    float x = 800.0 / 2 - Happybutton.getSize().x / 2.0;

    toolbox.newGameButton = new Button(sf::Vector2f(x, y), &restart);
    sf::Texture newGameTexture;
    newGameTexture.loadFromFile("./images/face_happy.png");

    if (!    newGameTexture.loadFromFile("./images/face_happy.png")){
        std::cout << "File not read" << std::endl;}

    sf::Sprite* newGameSprite = new sf::Sprite(newGameTexture);
    newGameSprite->setPosition(x,y);
    toolbox.newGameButton->setSprite(newGameSprite);
}

void render(){
    Toolbox& toolbox = Toolbox::getInstance();

    int yDimensions = toolbox.gameState->getDimensions().y;
    int xDimensions = toolbox.gameState->getDimensions().x;
    // GENERATE TILES
    // Iterate through every tile in the TileVector via gameState and draws it
    for(int y = 0; y < yDimensions; y++){
        for(int x = 0; x < xDimensions; x++){
            toolbox.gameState->getTile(x,y)->draw();
        }
    }
    // GENERATE BUTTONS
    toolbox.window.draw(toolbox.debugButton->getSprite());
    toolbox.window.draw(toolbox.newGameButton->getSprite());
    toolbox.window.draw(toolbox.testButton1->getSprite());
    toolbox.window.draw(toolbox.testButton2->getSprite());


    sf::Texture numb;
    numb.loadFromFile("./images/digits.png");
    std::vector<sf::Sprite*> digitsVector = getNumb(numb);
    toolbox.window.draw(*digitsVector.at(0));
    toolbox.window.draw(*digitsVector.at(1));
    toolbox.window.draw(*digitsVector.at(2));
    toolbox.window.display();


}

void toggleDebugMode(){ //toggle debug mode
    Toolbox& toolbox = Toolbox::getInstance();
    // debug Button clicked, turn it off GIVEN that it is on
    if (getDebugMode() == true) {
        //iterate through every Tile in gameState's TileVector
        for (int y = 0; y < toolbox.gameState->getDimensions().y; y++) {
            for (int x = 0; x < toolbox.gameState->getDimensions().x; x++) {
                // Find Mines and change its state to HIDDEN
                if (toolbox.gameState->getTile(x,y)->getMine() == true) {

                    // flagged spaces cannot be revealed
                    if(toolbox.gameState->getTile(x,y)->getState() != Tile::FLAGGED) {
                        toolbox.gameState->getTile(x,y)->setState(Tile::HIDDEN);
                    }
                    else{ continue; }
                }
            }
        }
    }
        // Turning on debug
    else if (!(getDebugMode() == true)) {
        for (int y = 0; y < toolbox.gameState->getDimensions().y; y++) {
            for (int x = 0; x < toolbox.gameState->getDimensions().x; x++) {

                if (toolbox.gameState->getTile(x,y)->getMine() == true) {
                    // set Mine Tiles to EXPLODED to reveal its visual on the window
                    if (toolbox.gameState->getTile(x,y)->getState() != Tile::FLAGGED) {
                        toolbox.gameState->getTile(x,y)->setState(Tile::EXPLODED);
                    }
                }
                else{ continue;}
            }
        }
    }
    // change boolean value of debug to its counter value whenever the button is clocked
    toolbox.isDebugOn = !toolbox.isDebugOn;
};


bool getDebugMode(){
    return Toolbox::getInstance().isDebugOn;
};

bool Win(){
    Toolbox& toolbox = Toolbox::getInstance();
    int unrevealedMines = 0;
    for (int y = 0; y < toolbox.gameState->getDimensions().y; y++){
        for (int x = 0; x < toolbox.gameState->getDimensions().x; x++){
            if (!(toolbox.gameState->getTile(x,y)->getMine() == true) && (toolbox.gameState->getTile(x,y)->getState() == Tile::REVEALED)){
                unrevealedMines++;}
        }}
    if (unrevealedMines == (toolbox.gameState->getDimensions().x * toolbox.gameState->getDimensions().y) - toolbox.gameState->getMineCount())
    { // Total tiles - Total Mines = SafeTiles
        //std::cout << " you WON!!!" << std::endl;
        return true;}
    else{
        return false;}
};
int gameLoop() {

    Toolbox& toolbox = Toolbox::getInstance();
    sf::Event event;
    int map_size_y = toolbox.gameState->getDimensions().y;
    int map_size_x = toolbox.gameState->getDimensions().x;

    //get dimensions

    sf::Texture tile;
    sf::Texture button;
    tile.loadFromFile("./images/tile_hidden.png");
    button.loadFromFile("./images/face_happy.png");
    float y_buttons = toolbox.gameState->getDimensions().y * tile.getSize().y;
    float x_newGameButton = 800.0 / 2.0 - button.getSize().x/2.0;
    float x_debug = x_newGameButton + 2.0 * button.getSize().x;
    float x_testButton1 = x_debug + button.getSize().x;
    float x_testButton2 = x_testButton1 + button.getSize().x;
    while (toolbox.window.isOpen())
    {

        while (toolbox.window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
            {
                toolbox.window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                int x = (int) (event.mouseButton.x / tile.getSize().x);
                int y = (int) (event.mouseButton.y / tile.getSize().y);

                if (x < map_size_x && x >= 0 && y >= 0 && y < map_size_y)
                { //click is on a tile
                    if (toolbox.gameState->getPlayStatus() == GameState::PLAYING) { //tiles should only be edited if game is in session
                        if (event.mouseButton.button == sf::Mouse::Right)
                        {
                            toolbox.gameState->getTile(x, y)->onClickRight();
                        }
                        else if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            toolbox.gameState->getTile(x, y)->onClickLeft();
                        }
                    }

                }
                else if (event.mouseButton.y >= y_buttons) //click is below tiles
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (event.mouseButton.x > x_newGameButton &&
                            event.mouseButton.x < x_newGameButton + button.getSize().x)
                        {
                            std::cout << "newGame button clicked\n";

                            toolbox.newGameButton->onClick();
                        }
                        else if (event.mouseButton.x > x_debug && event.mouseButton.x < x_debug + button.getSize().x)
                        { //debug
                            std::cout << "debug button clicked\n";
                            toolbox.debugButton->onClick();
                        }
                        else if (event.mouseButton.x > x_testButton1 &&
                                 event.mouseButton.x < x_testButton1 + button.getSize().x)
                        { //testB 1
                            std::cout << "Test1 button clicked\n";
                            toolbox.testButton1->onClick();
                        }
                        else if (event.mouseButton.x > x_testButton2 &&
                                 event.mouseButton.x < x_testButton2 + button.getSize().x)
                        {
                            std::cout << "Test2 button clicked\n";

                            toolbox.testButton2->onClick();
                        }
                    }
                }
            }

        }



        toolbox.window.clear(sf::Color::White);
        sf::Texture win_face;
        if (Win()){
            toolbox.gameState->setPlayStatus(GameState::WIN);
            // WON so we indicate the sunglasses face that we won
            win_face.loadFromFile("./images/face_win.png");
            if (!    win_face.loadFromFile("./images/face_win.png")){
                std::cout << "File not read" << std::endl;}
            sf::Sprite* win = new sf::Sprite(win_face);
            toolbox.newGameButton->setSprite(win);
            delete win;
        }

        render();
    }
    return 0;
}

int launch(){
    gameLoop();
    return 0;
}


int main() { return launch(); }
