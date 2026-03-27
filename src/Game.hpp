#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Block.hpp"
#include "Food.hpp"
#include "Ghost.hpp"
#include "Player.hpp"
#include "HUD.hpp"

class Game {
public:
    Game();

    HUD hud;
    bool gameOver = false;
    int life = 3;
    int score = 0;
    int colCount = 19;
    int rowCount = 21;
    int tileSize = 32;
    int width =  colCount * tileSize;
    int height = rowCount * tileSize;
    std::string appName = "PacMan";
    std::vector<std::string> tileMap;
    std::vector<Block> walls;
    std::vector<Food> foods;
    std::vector<Ghost> ghosts;
    Player player;
    sf::Texture wallTx, redGhostTx, blueGhostTx, pinkGhostTx, orangeGhostTx;
    sf::Texture playerUpTx, playerDownTx, playerLeftTx, playerRightTx;

    void loadMap();
    void update();
    void draw(sf::RenderWindow& window);
    void handleInput(char dir);
    void makeWall(float x, float y, float scaleWidth, float scaleHeight);
    void makeFood(float x, float y);
    void makeGhost(float x, float y, float scaleWidth, float scaleHeight, sf::Texture& tx);
    void makePlayer(float x, float y, float scaleWidth, float scaleHeight);
};
