#pragma once
#include "Entity.hpp"

struct Ghost : public Entity {
    using Entity::Entity;

    Ghost(float x, float y, float width, float height, sf::Texture& texture) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->startX = x;
        this->startY = y;

        sprite.setTexture(texture);
        sprite.setPosition(x, y);
    }

    // ゴーストが行動を開始します
    void ai(int tileSize) {
        int r = rand() % 4;
        char dirs[4] = {'U', 'D', 'L', 'R'};
        this->direction = dirs[r];
        int speed = tileSize / 4;
        this->setDirection(this->direction, speed);
    }

};
