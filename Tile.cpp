//
// Created by Tyler Le on 4/17/24.
//
#include "Tile.h"
#include "Toolbox.h"
#include "GameState.h"
#include <string>
#include <sstream>

Tile::Tile(sf::Vector2f _position){position = _position;}

sf::Vector2f Tile::getLocation() {return position;}
//return current state of tile
Tile::State Tile::getState()     {return state;}

// set state
void Tile::setState(Tile::State _state)     {state = _state;}
// pointer to array of Tile pointers
std::array<Tile*, 8>& Tile::getNeighbors()   {return neighbors;}


//Populates / replaces the neighboring tile container
void Tile::setNeighbors(std::array<Tile*, 8> _neighbors) {neighbors = _neighbors;}

bool Tile::getMine() {return mine;}

void Tile::setMine() { mine = true;}
int Tile::getMineCount() {return mine_count;};
//sf::Sprite Tile::getSprite() {return sprite;}

void Tile::addMine() {mine_count++;}
// Define reveal behavior for tile when the left mouse button is clicked inside its boundaries
void Tile::onClickLeft() {

    if (state == HIDDEN) {
        if (getMine() == true) {
            setState(EXPLODED);
            // game is over if mine goes BOOOOM
            sf::Texture frown;
            frown.loadFromFile("./images/face_lose.png");
            sf::Sprite *lose = new sf::Sprite(frown);
            Toolbox &toolbox = Toolbox::getInstance(); //reference variable to the singleton of toolbox
            toolbox.newGameButton->setSprite((lose)); // set sprite to FROWN :(((((
            toolbox.gameState->setPlayStatus(GameState::LOSS); // FROWN == LOSE
        } else {
            setState(REVEALED);
            for (int john = 0; john < neighbors.size(); john++) {
                if (getNeighbors().at(john) != nullptr && getNeighbors().at(john)->getMine() == true) {
                    //getNeighbors().at(john)->addMine();
                    addMine();
                } else { continue; }
                // Reveal that neighbor that do not have a mine
            }
            if (getMineCount() == 0) {
                revealNeighbors();
            }
        }
    }
}

// Toggle tile's state between FLAGGED & HIDDEN
void Tile::onClickRight() {
    Toolbox &toolbox = Toolbox::getInstance();
    // Placing / Removing flags changes GameState's flag counter
    if (state == Tile::HIDDEN) {
        setState(Tile::FLAGGED);
        flag = !flag;
        toolbox.gameState->addFlag();
    } else if (state == Tile::FLAGGED) {
        setState(Tile::HIDDEN);
        flag = !flag;
        toolbox.gameState->deFlag();
    }
}

// Render tile to screen according to its state
    void Tile::draw() {
        Toolbox &toolbox = Toolbox::getInstance();
        //load textures
        sf::Texture hidden;
        sf::Texture revealed;
        sf::Texture flagTexture;
        sf::Texture mineTexture;
        sf::Texture numbText;
        hidden.loadFromFile("./images/tile_hidden.png");
        revealed.loadFromFile("./images/tile_revealed.png");
        flagTexture.loadFromFile("./images/flag.png");
        mineTexture.loadFromFile("./images/mine.png");


        if (state == HIDDEN) //HIDDEN
        {
            sf::Sprite hidden_sprite;
            hidden_sprite.setTexture(hidden);
            hidden_sprite.setPosition(position);
            toolbox.window.draw(hidden_sprite);
        } else if (state == REVEALED) //REVEALED
        {
            sf::Sprite sprite;
            sprite.setTexture(revealed);
            sprite.setPosition(position);
            toolbox.window.draw(sprite);

            if (mine_count > 0) //draw number
            {
                sf::Sprite sprite_num;
                std::stringstream ss; //convert bomb_counter from int to string
                ss << mine_count;
                std::string bomb_counter_string;
                ss >> bomb_counter_string;
                std::string fileName = "./images/number_" + bomb_counter_string + ".png"; //get correct number to draw
                numbText.loadFromFile(fileName);
                sprite_num.setTexture(numbText);
                sprite_num.setPosition(position);
                toolbox.window.draw(sprite_num);
            }
        } else if (state == FLAGGED)  //FLAGGED
        {
            sf::Sprite sprite;
            sprite.setTexture(hidden);
            sprite.setPosition(position);
            toolbox.window.draw(sprite);

            if (toolbox.isDebugOn == true && getMine() == true) { // could be simplified but for readability’s sake
                //std::cout << "check\n";
                sf::Sprite sprite_mine;
                sprite_mine.setTexture(mineTexture);
                sprite_mine.setPosition(position);

                toolbox.window.draw(sprite_mine);
            } else {
                sf::Sprite sprite_flag;
                sprite_flag.setTexture(flagTexture);
                sprite_flag.setPosition(position);
                toolbox.window.draw(sprite_flag);
            }

        } else if (state == EXPLODED) //EXPLODED
        {
            if (toolbox.isDebugOn == true) {
                //std::cout << "check\n";
                sf::Sprite sprite;
                sprite.setTexture(hidden);
                sprite.setPosition(position);

                toolbox.window.draw(sprite);
            } else {
                sf::Sprite sprite;
                sprite.setTexture(revealed);
                sprite.setPosition(position);

                toolbox.window.draw(sprite);
                toolbox.gameState->setPlayStatus(GameState::LOSS);
            }
            sf::Sprite sprite_mine;
            sprite_mine.setTexture(mineTexture);
            sprite_mine.setPosition(position);

            toolbox.window.draw(sprite_mine);
        }
    }


    void Tile::revealNeighbors() {
        Toolbox &toolbox = Toolbox::getInstance();
        sf::Texture hidden;
        hidden.loadFromFile("./images/tile_hidden.png");
        for (int i = 0; i < neighbors.size(); i++) {
            if (neighbors.at(i) != nullptr && neighbors.at(i)->getMine() == true) {
                continue;
            } else if (neighbors.at(i) != nullptr && neighbors.at(i)->getState() != REVEALED) { // tile is hidden
                neighbors.at(i)->setState(REVEALED);
                for (int j = 0; j < neighbors.size(); j++) {
                    if (neighbors.at(i)->getNeighbors().at(j) != nullptr &&
                        neighbors.at(i)->getNeighbors().at(j)->getMine() == true &&
                        neighbors.at(i)->getNeighbors().at(j)->getState() != REVEALED) {
                        neighbors.at(i)->addMine();
                    }// if current tile has neighboring mines, we add to the mine_counter
                }
                if (neighbors.at(i)->getMineCount() == 0) {
                    toolbox.gameState->getTile(neighbors.at(i)->getLocation().x / hidden.getSize().x,
                                               neighbors.at(i)->getLocation().y /
                                               hidden.getSize().y)->revealNeighbors();
                }

            }
        }
    }

