//
// Created by Tyler Le on 4/17/24.
#include "GameState.h"
#include <fstream>
#include <iostream>
#include "Tile.h"

int GameState::getFlagCount() { return FlagCount;}

int GameState::getMineCount() { return MineCount;}

Tile* GameState::getTile(int x, int y) { return TileVector.at(y).at(x);}

GameState::PlayStatus GameState::getPlayStatus() {return status;}

void GameState::setPlayStatus(PlayStatus _status)   { status = _status;}

sf::Vector2i GameState::getDimensions() {return dimensions;}

GameState::GameState(sf::Vector2i _dimensions, int _numberOfMines) {
    dimensions = _dimensions;
    MineCount = _numberOfMines;

    sf::Texture hidden;
    hidden.loadFromFile("./images/tile_hidden.png");
    sf::Sprite hidden_sprite;
    hidden_sprite.setTexture(hidden);

    // Generate Tiles objects in TileVector
    for (int i = 0; i < dimensions.y; i++) {
        std::vector<Tile *> temp;

        for (int j = 0; j < dimensions.x; j++) {
            Tile *tile = new Tile(sf::Vector2f(j * hidden.getSize().x, i * hidden.getSize().y));
            temp.push_back(tile);


        }
        TileVector.push_back(temp);
        temp.clear();


    }
    // Generate mines

    int count = 0;


    for (int i = 0; i < getMineCount();) {
        int randx = rand() % dimensions.x;
        int randy = rand() % dimensions.y;
        if (!(TileVector.at(randy).at(randx)->getMine() == true)) {
            //std::cout << randy << " " << randx << std::endl;
            TileVector.at(randy).at(randx)->setMine();
            mineLocation.push_back(sf::Vector2i(randx, randy));
            i++;
            count++;
        } else { continue; }
    }




    for (int j = 0; j < dimensions.x; j++) {
        // Hard Code neighbor values
        // Account for neighbors on the edges and corners
        for (int row = 0; row < dimensions.y; row++) {
            //for each row

            for (int column = 0; column < dimensions.x; column++) {// for each collumn at the specified row


                std::array<Tile *, 8> Tempneighbors;
                if (column == 0) {

                    // TOP LEFT 0 1 2 3 5 out of bounds
                    if (row == 0) {
                        {   // Tile pointers are deleted after going out of scope

                            Tile *tile4 = TileVector.at(row).at(column + 1);
                            Tile *tile6 = TileVector.at(row + 1).at(column);
                            Tile *tile7 = TileVector.at(row + 1).at(column + 1);
                            Tempneighbors.at(0) = nullptr;
                            Tempneighbors.at(1) = nullptr;
                            Tempneighbors.at(2) = nullptr;
                            Tempneighbors.at(3) = nullptr;
                            Tempneighbors.at(4) = tile4;
                            Tempneighbors.at(5) = nullptr;
                            Tempneighbors.at(6) = tile6;
                            Tempneighbors.at(7) = tile7;

                        }

                    }
                        // BOTLEFT 0 3 5 6 7 NULL

                    else if (row == dimensions.y - 1) {

                        Tile *tile1 = TileVector.at(row - 1).at(column);
                        Tile *tile2 = TileVector.at(row - 1).at(column + 1);
                        Tile *tile4 = TileVector.at(row).at(column + 1);

                        Tempneighbors.at(0) = nullptr;
                        Tempneighbors.at(1) = tile1;
                        Tempneighbors.at(2) = tile2;
                        Tempneighbors.at(3) = nullptr;
                        Tempneighbors.at(4) = tile4;
                        Tempneighbors.at(5) = nullptr;
                        Tempneighbors.at(6) = nullptr;
                        Tempneighbors.at(7) = nullptr;

                    } else
                        // FIRST COLUMN 0 3 5 are NULL
                    {

                        Tile *tile1 = TileVector.at(row - 1).at(column);
                        Tile *tile2 = TileVector.at(row - 1).at(column + 1);
                        Tile *tile4 = TileVector.at(row).at(column + 1);
                        Tile *tile6 = TileVector.at(row + 1).at(column);
                        Tile *tile7 = TileVector.at(row + 1).at(column + 1);

                        Tempneighbors.at(0) = nullptr;
                        Tempneighbors.at(1) = tile1;
                        Tempneighbors.at(2) = tile2;
                        Tempneighbors.at(3) = nullptr;
                        Tempneighbors.at(4) = tile4;
                        Tempneighbors.at(5) = nullptr;
                        Tempneighbors.at(6) = tile6;
                        Tempneighbors.at(7) = tile7;
                    }
                } else if (column == (dimensions.x - 1)) { // right column
                    // Top Right 0 1 2 4 7

                    if (row == 0) {
                        Tile *tile3 = TileVector.at(row).at(column - 1);
                        Tile *tile5 = TileVector.at(row + 1).at(column - 1);
                        Tile *tile6 = TileVector.at(row + 1).at(column);
                        Tempneighbors.at(0) = nullptr;
                        Tempneighbors.at(1) = nullptr;
                        Tempneighbors.at(2) = nullptr;
                        Tempneighbors.at(3) = tile3;
                        Tempneighbors.at(4) = nullptr;
                        Tempneighbors.at(5) = tile5;
                        Tempneighbors.at(6) = tile6;
                        Tempneighbors.at(7) = nullptr;
                        // Bottom Right 2 4 5 6 7
                    } else if (row == dimensions.y - 1) {
                        Tile *tile0 = TileVector.at(row - 1).at(column - 1);
                        Tile *tile1 = TileVector.at(row - 1).at(column);
                        Tile *tile3 = TileVector.at(row).at(column - 1);
                        Tempneighbors.at(0) = tile0;
                        Tempneighbors.at(1) = tile1;
                        Tempneighbors.at(2) = nullptr;
                        Tempneighbors.at(3) = tile3;
                        Tempneighbors.at(4) = nullptr;
                        Tempneighbors.at(5) = nullptr;
                        Tempneighbors.at(6) = nullptr;
                        Tempneighbors.at(7) = nullptr;
                        // right column! 2 4 7
                    } else {
                        Tile *tile0 = TileVector.at(row - 1).at(column - 1);
                        Tile *tile1 = TileVector.at(row - 1).at(column);
                        Tile *tile3 = TileVector.at(row).at(column - 1);
                        Tile *tile5 = TileVector.at(row + 1).at(column - 1);
                        Tile *tile6 = TileVector.at(row + 1).at(column);
                        Tempneighbors.at(0) = tile0;
                        Tempneighbors.at(1) = tile1;
                        Tempneighbors.at(2) = nullptr;
                        Tempneighbors.at(3) = tile3;
                        Tempneighbors.at(4) = nullptr;
                        Tempneighbors.at(5) = tile5;
                        Tempneighbors.at(6) = tile6;
                        Tempneighbors.at(7) = nullptr;
                    }
                } // 1st row 0 1 2
                else if (row == 0) {

                    Tile *tile3 = TileVector.at(row).at(column - 1);
                    Tile *tile4 = TileVector.at(row).at(column + 1);
                    Tile *tile5 = TileVector.at(row + 1).at(column - 1);
                    Tile *tile6 = TileVector.at(row + 1).at(column);
                    Tile *tile7 = TileVector.at(row + 1).at(column + 1);
                    Tempneighbors.at(0) = nullptr;
                    Tempneighbors.at(1) = nullptr;
                    Tempneighbors.at(2) = nullptr;
                    Tempneighbors.at(3) = tile3;
                    Tempneighbors.at(4) = tile4;
                    Tempneighbors.at(5) = tile5;
                    Tempneighbors.at(6) = tile6;
                    Tempneighbors.at(7) = tile7;
                    //bottom row 5 6 7
                } else if (row == dimensions.y - 1) {

                    Tile *tile0 = TileVector.at(row - 1).at(column - 1);
                    Tile *tile1 = TileVector.at(row - 1).at(column);
                    Tile *tile2 = TileVector.at(row - 1).at(column + 1);
                    Tile *tile3 = TileVector.at(row).at(column - 1);
                    Tile *tile4 = TileVector.at(row).at(column + 1);
                    Tempneighbors.at(0) = tile0;
                    Tempneighbors.at(1) = tile1;
                    Tempneighbors.at(2) = tile2;
                    Tempneighbors.at(3) = tile3;
                    Tempneighbors.at(4) = tile4;
                    Tempneighbors.at(5) = nullptr;
                    Tempneighbors.at(6) = nullptr;
                    Tempneighbors.at(7) = nullptr;
                } else  //middle
                {

                    Tile *tile0 = TileVector.at(row - 1).at(column - 1);
                    Tile *tile1 = TileVector.at(row - 1).at(column);
                    Tile *tile2 = TileVector.at(row - 1).at(column + 1);
                    Tile *tile3 = TileVector.at(row).at(column - 1);
                    Tile *tile4 = TileVector.at(row).at(column + 1);
                    Tile *tile5 = TileVector.at(row + 1).at(column - 1);
                    Tile *tile6 = TileVector.at(row + 1).at(column);
                    Tile *tile7 = TileVector.at(row + 1).at(column + 1);
                    Tempneighbors.at(0) = tile0;
                    Tempneighbors.at(1) = tile1;
                    Tempneighbors.at(2) = tile2;
                    Tempneighbors.at(3) = tile3;
                    Tempneighbors.at(4) = tile4;
                    Tempneighbors.at(5) = tile5;
                    Tempneighbors.at(6) = tile6;
                    Tempneighbors.at(7) = tile7;
                }

                TileVector.at(row).at(column)->setNeighbors(Tempneighbors);
                // for at given row and colomn in the loop, set its Tempneighbors according to above's conditions
            }

        }
    }
}

GameState::GameState(const char *filepath) {

    std::ifstream inStream(filepath);
    if(inStream.fail()){
        std::cout << "FAILED" << std::endl;
    }
    else if (inStream.is_open()){
        std::cout << "OPENED" << std::endl;

    }
    std::string line;
    size_t length;


    int x_dim;
    int y_dim = 0;
    //MineCount = 0;
    // look for dimensions and mines ( 1 binary)
    // ADD MINE LOCATIONS

    while(inStream >> line)
    {
        x_dim = line.length();
        for(int i=0;i<line.length();i++)
        {
            if(line[i] == 49)
            {
                mineLocation.push_back(sf::Vector2i(i,y_dim));
            }
        }
        y_dim++;
    }
    dimensions = sf::Vector2i(x_dim,y_dim);





dimensions = sf::Vector2i(x_dim, y_dim);

    sf::Texture hidden;
    hidden.loadFromFile("./images/tile_hidden.png");
    sf::Sprite tileSprite;
    tileSprite.setTexture(hidden);
    std::vector<Tile*> temp;

    // Generate tiles according to file
    // SET MINE LOCATIONS TO TILES AND COUNT THEM
    for (int row = 0; row < dimensions.y; row++)
    {
        for (int column = 0; column < dimensions.x; column++)
        {
            Tile* newTile = new Tile(sf::Vector2f(hidden.getSize().x * column, hidden.getSize().y * row)); //create hidden object
            for (int i=0; i < mineLocation.size();i++)
            {
                if(row == mineLocation.at(i).y && column == mineLocation.at(i).x) {
                    newTile->setMine();
                    MineCount++;
                    //std::cout << "Mine Set" << std::endl;
                }
            }
            temp.push_back(newTile);
        }
        TileVector.push_back(temp);
        temp.clear();
    }
    // SAME AS ABOVE

    // Account for neighbors on the edges and corners
    for(int row = 0; row < dimensions.y; row++){ //for each row
        for (int column = 0; column < dimensions.x; column++) { // for each collumn at the specified row

            std::array<Tile*, 8> neighborsTemp;
            if (column == 0) {
                // TOP LEFT 0 1 2 3 5 out of bounds
                if (row == 0) {
                    {   // Tile pointers are deleted after going out of scope
                        Tile *tile4 = TileVector.at(row).at(column + 1);
                        Tile *tile6 = TileVector.at(row + 1).at(column);
                        Tile *tile7 = TileVector.at(row + 1).at(column + 1);
                        neighborsTemp.at(0) = nullptr;
                        neighborsTemp.at(1) = nullptr;
                        neighborsTemp.at(2) = nullptr;
                        neighborsTemp.at(3) = nullptr;
                        neighborsTemp.at(4) = tile4;
                        neighborsTemp.at(5) = nullptr;
                        neighborsTemp.at(6) = tile6;
                        neighborsTemp.at(7) = tile7;
                    }
                }
                    // BOTLEFT 0 3 5 6 7 NULL
                else if (row == dimensions.y - 1) {
                    Tile *tile1 = TileVector.at(row - 1).at(column);
                    Tile *tile2 = TileVector.at(row - 1).at(column + 1);
                    Tile *tile4 = TileVector.at(row).at(column + 1);

                    neighborsTemp.at(0) = nullptr;
                    neighborsTemp.at(1) = tile1;
                    neighborsTemp.at(2) = tile2;
                    neighborsTemp.at(3) = nullptr;
                    neighborsTemp.at(4) = tile4;
                    neighborsTemp.at(5) = nullptr;
                    neighborsTemp.at(6) = nullptr;
                    neighborsTemp.at(7) = nullptr;
                } else
                    // FIRST COLUMN 0 3 5 are NULL
                {
                    Tile *tile1 = TileVector.at(row - 1).at(column);
                    Tile *tile2 = TileVector.at(row - 1).at(column + 1);
                    Tile *tile4 = TileVector.at(row).at(column + 1);
                    Tile *tile6 = TileVector.at(row + 1).at(column);
                    Tile *tile7 = TileVector.at(row + 1).at(column + 1);

                    neighborsTemp.at(0) = nullptr;
                    neighborsTemp.at(1) = tile1;
                    neighborsTemp.at(2) = tile2;
                    neighborsTemp.at(3) = nullptr;
                    neighborsTemp.at(4) = tile4;
                    neighborsTemp.at(5) = nullptr;
                    neighborsTemp.at(6) = tile6;
                    neighborsTemp.at(7) = tile7;
                }
            } else if (column == (dimensions.x - 1)) {
                // Top Right 0 1 2 4 7
                if (row == 0)
                {
                    Tile *tile3 = TileVector.at(row).at(column - 1);
                    Tile *tile5 = TileVector.at(row + 1).at(column - 1);
                    Tile *tile6 = TileVector.at(row + 1).at(column);
                    neighborsTemp.at(0) = nullptr;
                    neighborsTemp.at(1) = nullptr;
                    neighborsTemp.at(2) = nullptr;
                    neighborsTemp.at(3) = tile3;
                    neighborsTemp.at(4) = nullptr;
                    neighborsTemp.at(5) = tile5;
                    neighborsTemp.at(6) = tile6;
                    neighborsTemp.at(7) = nullptr;
                    // Bottom Right 2 4 5 6 7
                } else if (row == dimensions.y - 1)
                {
                    Tile *tile0 = TileVector.at(row - 1).at(column - 1);
                    Tile *tile1 = TileVector.at(row - 1).at(column);
                    Tile *tile3 = TileVector.at(row).at(column - 1);
                    neighborsTemp.at(0) = tile0;
                    neighborsTemp.at(1) = tile1;
                    neighborsTemp.at(2) = nullptr;
                    neighborsTemp.at(3) = tile3;
                    neighborsTemp.at(4) = nullptr;
                    neighborsTemp.at(5) = nullptr;
                    neighborsTemp.at(6) = nullptr;
                    neighborsTemp.at(7) = nullptr;
                    // right column! 2 4 7
                } else
                {
                    Tile *tile0 = TileVector.at(row - 1).at(column - 1);
                    Tile *tile1 = TileVector.at(row - 1).at(column);
                    Tile *tile3 = TileVector.at(row).at(column - 1);
                    Tile *tile5 = TileVector.at(row + 1).at(column - 1);
                    Tile *tile6 = TileVector.at(row + 1).at(column);
                    neighborsTemp.at(0) = tile0;
                    neighborsTemp.at(1) = tile1;
                    neighborsTemp.at(2) = nullptr;
                    neighborsTemp.at(3) = tile3;
                    neighborsTemp.at(4) = nullptr;
                    neighborsTemp.at(5) = tile5;
                    neighborsTemp.at(6) = tile6;
                    neighborsTemp.at(7) = nullptr;
                }
            } // 1st row 0 1 2
            else if (row == 0)
            {
                Tile *tile3 = TileVector.at(row).at(column - 1);
                Tile *tile4 = TileVector.at(row).at(column + 1);
                Tile *tile5 = TileVector.at(row + 1).at(column - 1);
                Tile *tile6 = TileVector.at(row + 1).at(column);
                Tile *tile7 = TileVector.at(row + 1).at(column + 1);
                neighborsTemp.at(0) = nullptr;
                neighborsTemp.at(1) = nullptr;
                neighborsTemp.at(2) = nullptr;
                neighborsTemp.at(3) = tile3;
                neighborsTemp.at(4) = tile4;
                neighborsTemp.at(5) = tile5;
                neighborsTemp.at(6) = tile6;
                neighborsTemp.at(7) = tile7;
                //bottom row 5 6 7
            } else if (row == dimensions.y - 1)
            {
                Tile *tile0 = TileVector.at(row - 1).at(column - 1);
                Tile *tile1 = TileVector.at(row - 1).at(column);
                Tile *tile2 = TileVector.at(row - 1).at(column + 1);
                Tile *tile3 = TileVector.at(row).at(column - 1);
                Tile *tile4 = TileVector.at(row).at(column + 1);
                neighborsTemp.at(0) = tile0;
                neighborsTemp.at(1) = tile1;
                neighborsTemp.at(2) = tile2;
                neighborsTemp.at(3) = tile3;
                neighborsTemp.at(4) = tile4;
                neighborsTemp.at(5) = nullptr;
                neighborsTemp.at(6) = nullptr;
                neighborsTemp.at(7) = nullptr;
            } else //middle
            {
                Tile *tile0 = TileVector.at(row - 1).at(column - 1);
                Tile *tile1 = TileVector.at(row - 1).at(column);
                Tile *tile2 = TileVector.at(row - 1).at(column + 1);
                Tile *tile3 = TileVector.at(row).at(column - 1);
                Tile *tile4 = TileVector.at(row).at(column + 1);
                Tile *tile5 = TileVector.at(row + 1).at(column - 1);
                Tile *tile6 = TileVector.at(row + 1).at(column);
                Tile *tile7 = TileVector.at(row + 1).at(column + 1);
                neighborsTemp.at(0) = tile0;
                neighborsTemp.at(1) = tile1;
                neighborsTemp.at(2)= tile2;
                neighborsTemp.at(3) = tile3;
                neighborsTemp.at(4) = tile4;
                neighborsTemp.at(5) = tile5;
                neighborsTemp.at(6) = tile6;
                neighborsTemp.at(7) = tile7;
            }

            TileVector.at(row).at(column)->setNeighbors(neighborsTemp);
            // for at given row and colomn in the loop, set its neighborsTemp according to above's conditions
        }
    }
}

void GameState::addFlag(){
    FlagCount++;
};
void GameState::deFlag(){
    FlagCount--;
};






