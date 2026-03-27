#pragma once
#include "Block.hpp"

struct Entity : public Block {
    float velocityX = 0;
    float velocityY = 0;
    char direction = 'U';
    char desiredDirection = 0;
    float startX;
    float startY;

    Entity(float x, float y, float width, float height, sf::Texture& tx)
    : Block(x, y, width, height, tx), startX(x), startY(y)
    {}

    // 現在の位置から向かう方向を決めます
    void setDirection(char dir, const float speed) {
        velocityX = 0;
        velocityY = 0;
        if (dir == 'U') velocityY = -speed;
        if (dir == 'D') velocityY = speed;
        if (dir == 'L') velocityX = -speed;
        if (dir == 'R') velocityX = speed;
    }

    // 位置をリセットします
    void resetPosition() {
        x = startX;
        y = startY;
    }

    // 方向を初期化します
    void resetVelocity() {
        velocityX = 0;
        velocityY = 0;
    }
};
