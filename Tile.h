// Created by Tyler Le on 4/17/24.
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#ifndef UNTITLED5_TILE_H
#define UNTITLED5_TILE_H

class Tile {


public:
    // Tile's current UI state:
    enum State{ REVEALED, HIDDEN, FLAGGED, EXPLODED };
    // Constructor
    Tile(sf::Vector2f _position);
    sf::Vector2f getLocation();

    //return current state of tile
    State getState();

    // pointer to array of Tile pointers
    std::array<Tile*, 8>& getNeighbors();

    // set state of tile triggr other behaviors depending on the state change
    void setState(State _state);

    //Populates / replaces the neighboring tile container
    void setNeighbors(std::array<Tile*, 8> _neighbors);

    // Define reveal behavior for tile when the left mouse button is clicked inside its boundaries
    void onClickLeft();

    // Toggle tile's state between FLAGGED & HIDDEN
    void onClickRight();

    // Render tile to screen according to its state
    void draw();
    bool getMine();
    void setMine();
    void addMine();
    int getMineCount();

protected:
    void revealNeighbors();

private:
    sf::Vector2f position;// Tile's current position in the vector
    std::array<Tile*, 8> neighbors; // Tile's neighbor vector
    State state = HIDDEN; // Tile's current State
    bool mine = false;
    unsigned int mine_count = 0;
    bool flag = false;


};
#endif //UNTITLED5_TILE_H
