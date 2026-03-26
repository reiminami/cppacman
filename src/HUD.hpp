#pragma once
#include <SFML/Graphics.hpp>

class HUD {
public:
    int score;
    int lives;
    sf::Font font;
    sf::Text text;
    sf::RenderWindow window;
    sf::Texture* pacmanTexture;

    // HUD(sf::Texture* tx);
    HUD();
    void reset();
    sf::RectangleShape bgGrey(float x, float y);
    void draw(sf::RenderWindow& window, bool gameOver);
};
