#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class PacMan {
public:
    PacMan();

    void update();
    void draw(sf::RenderWindow& window);
    void setDirection(char dir);
    int lives = 3;
    bool gameOver = false;

    void loadMap();
    void resetPositions();

// private:
    struct Block {
        float x, y;
        float width, height;
        float startX, startY;
        float velocityX = 0;
        float velocityY = 0;
        char direction = 'R';

        sf::Sprite sprite;
    };

    int colCount = 19;
    int rowCount = 21;
    int tileSize = 32;

    std::vector<std::string> tileMap;
    std::vector<Block> walls;
    std::vector<Block> foods;
    std::vector<Block> ghosts;
    Block pacman;
    sf::Texture wallTexture;
    sf::Texture ghostTexture;
    sf::Texture pacmanUp, pacmanDown, pacmanLeft, pacmanRight;

    bool collision(const Block& a, const Block& b);
};
