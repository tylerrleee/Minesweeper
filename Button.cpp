//
// Created by Tyler Le on 4/21/24.
//
#include "Button.h"

Button::Button(sf::Vector2f _position, std::function<void(void)> _onClick) {
    position = _position;
    clicked = _onClick;
}
void Button::onClick() {
    clicked();
}

sf::Vector2f Button::getPosition() { return position;}

sf::Sprite Button::getSprite() { return sprite;}

void Button::setSprite(sf::Sprite *_sprite) {
    texture = *_sprite->getTexture();
    sprite.setTexture(texture); // Sprite is set to Texture's container 1 to 1 e.g.
    sprite.setPosition(position); // Set sprite position to the texture's container
}
