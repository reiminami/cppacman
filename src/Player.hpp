#pragma once
#include "Entity.hpp"

struct Player : public Entity {
    Player(float x, float y, float width, float height, sf::Texture& texture)
    : Entity(x, y, width, height, texture)
    {}
};
