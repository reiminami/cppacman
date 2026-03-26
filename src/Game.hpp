#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Block.hpp"
#include "Player.hpp"
#include "Ghost.hpp"
#include "HUD.hpp"

class Game {
public:
    Game();

    bool gameOver = false;


    void update();
    void draw(sf::RenderWindow& window);
    void handleInput(char dir);
    void loadMap();

    int colCount = 19;
    int rowCount = 21;
    int tileSize = 32;

    std::vector<std::string> tileMap;
    std::vector<Block> walls;
    std::vector<Block> foods;
    std::vector<Ghost> ghosts;
    sf::Texture wallTexture;
    sf::Texture redGhost, blueGhost, orangeGhost, pinkGhost;
    sf::Texture pacmanUp, pacmanDown, pacmanLeft, pacmanRight;
    Player pacman;
    HUD hud;

};
