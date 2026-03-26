#pragma once
#include <SFML/Graphics.hpp>

struct Block {
    float x;
    float y;
    float width;
    float height;
    sf::Sprite sprite;

    Block()
    {}

    // テクスチャなし
    Block(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height)
    {}

    // テクスチャあり
    Block(float x, float y, float width, float height, sf::Texture& texture)
    : x(x), y(y), width(width), height(height)
    {
        sprite.setTexture(texture);
        sprite.setPosition(x, y);
    }

    // 衝突判定を行います
    bool collision(const Block& other) {
        return this->x < other.x + other.width &&
               this->x + this->width > other.x &&
               this->y < other.y + other.height &&
               this->y + this->height > other.y;
    }
};
