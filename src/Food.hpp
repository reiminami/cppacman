#pragma once
#include "Block.hpp"

struct Food : public Block {
    Food(float x, float y, float width, float height)
    : Block(x, y, width, height)
    {}

    // food の描画用のオブジェクトを返します
    static sf::RectangleShape foodRect(Block food) {
        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(food.width, food.height));
        rect.setFillColor(sf::Color::White);
        rect.setPosition(food.x, food.y);
        return rect;
    }
};
