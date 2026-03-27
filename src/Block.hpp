#pragma once
#include <SFML/Graphics.hpp>
#include "Game.hpp"

class Block {
public:
    float x;
    float y;
    float width;
    float height;
    sf::Sprite sprite;

    Block()
    {}

    Block(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height)
    {}

    Block(float x, float y, float width, float height, sf::Texture& texture)
    : x(x), y(y), width(width), height(height)
    {
        sprite.setTexture(texture);
        sprite.setPosition(x, y);
        sprite.setScale(getScaleSize());
    }

    // 衝突判定を行います
    bool collision(const Block& other) {
        return this->x < other.x + other.width  && this->x + this->width > other.x &&
               this->y < other.y + other.height && this->y + this->height > other.y;
    }

    // scale用のサイズを返します
    sf::Vector2f getScaleSize() {
        auto textureSize = sprite.getTexture()->getSize();
        float scaleX = width / textureSize.x;
        float scaleY = height / textureSize.y;
        return sf::Vector2f(scaleX, scaleY);
    }

};
