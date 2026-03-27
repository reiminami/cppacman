#pragma once
#include "Entity.hpp"

struct Ghost : public Entity {
    Ghost(float x, float y, float width, float height, sf::Texture& tx)
    : Entity(x, y, width, height, tx)
    {
    }

    // ゴーストが行動を開始します
    void ai(int tileSize) {
        int r = rand() % 4;
        char dirs[4] = {'U', 'D', 'L', 'R'};
        direction = dirs[r];
        int speed = tileSize / 4;
        setDirection(direction, speed);
    }
};
