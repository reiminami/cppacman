#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
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
        float thisX = std::floor(this->x);
        float thisY = std::floor(this->y);
        float otherX = std::floor(other.x);
        float otherY = std::floor(other.y);
        return thisX < otherX + other.width  && thisX + this->width > otherX &&
               thisY < otherY + other.height && thisY + this->height > otherY;
    }

    // 指定位置での衝突判定を行います
    bool collision(const Block& other, float testX, float testY) const {
        float thisX = std::floor(testX);
        float thisY = std::floor(testY);
        float otherX = std::floor(other.x);
        float otherY = std::floor(other.y);
        return thisX < otherX + other.width  && thisX + this->width > otherX &&
               thisY < otherY + other.height && thisY + this->height > otherY;
    }

    // scale用のサイズを返します
    sf::Vector2f getScaleSize() {
        auto textureSize = sprite.getTexture()->getSize();
        float scaleX = width / textureSize.x;
        float scaleY = height / textureSize.y;
        return sf::Vector2f(scaleX, scaleY);
    }

};
