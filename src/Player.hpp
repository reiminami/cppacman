#pragma once
#include "Entity.hpp"

struct Player : public Entity {
    Player(float x, float y, float width, float height, sf::Texture& texture) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->startX = x;
        this->startY = y;

        sprite.setTexture(texture);
        sprite.setPosition(x, y);
    }
};
