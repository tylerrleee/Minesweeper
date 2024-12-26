// Created by Tyler Le on 4/17/24.
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "Tile.h"

#ifndef UNTITLED5_GAMESTATE_H
#define UNTITLED5_GAMESTATE_H
class GameState {

public:
    enum PlayStatus {WIN, LOSS, PLAYING};
    GameState(sf::Vector2i _dimensions = sf::Vector2i(25, 16), int _numberOfMines = 50);
    // Constructs game state based on size, mine replacement & mine number specified at filepath
    GameState(const char* filepath);
    int getFlagCount();
    void addFlag();
    void deFlag();
    int getMineCount();
    Tile *getTile(int x, int y);
    PlayStatus getPlayStatus();
    void setPlayStatus(PlayStatus _status);
    sf::Vector2i getDimensions();
    //~GameState();


private:
    std::vector<std::vector<Tile*>> TileVector;
    std::vector<sf::Vector2i> mineLocation;
    int FlagCount = 0;
    int MineCount;
    PlayStatus status = PLAYING;
    sf::Vector2i dimensions;



};
#endif //UNTITLED5_GAMESTATE_H