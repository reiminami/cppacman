#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Map.hpp"
#include "HUD.hpp"

Game::Game(): player(0, 0, 1, 1, playerRightTx)
{
    wallTx.loadFromFile("images/wall.png");
    redGhostTx.loadFromFile("images/redGhost.png");
    blueGhostTx.loadFromFile("images/blueGhost.png");
    pinkGhostTx.loadFromFile("images/pinkGhost.png");
    orangeGhostTx.loadFromFile("images/orangeGhost.png");
    playerUpTx.loadFromFile("images/pacmanUp.png");
    playerDownTx.loadFromFile("images/pacmanDown.png");
    playerLeftTx.loadFromFile("images/pacmanLeft.png");
    playerRightTx.loadFromFile("images/pacmanRight.png");
    loadMap();
}

// マップをロードします
void Game::loadMap() {
    walls.clear();
    foods.clear();
    ghosts.clear();
    Map map;
    float scaleWidth = width / (tileSize * colCount / 2.0f);
    float scaleHeight = height / (tileSize * rowCount / 2.0f);
    float size = tileSize * 1.0f;
    float offset = (tileSize - size) / 3;

    for (int r=0; r<rowCount; r++) {
        for (int c=0; c<colCount; c++) {
            char tile = map.data[r][c];
            float x = c * tileSize;
            float y = r * tileSize;

            switch (tile) {
                case 'X': makeWall(x+offset, y+offset, size, size); break;
                case ' ': makeFood(x+offset, y+offset); break;
                case 'r': makeGhost(x+offset, y+offset, size, size, redGhostTx); break;
                case 'b': makeGhost(x+offset, y+offset, size, size, blueGhostTx); break;
                case 'p': makeGhost(x+offset, y+offset, size, size, pinkGhostTx); break;
                case 'o': makeGhost(x+offset, y+offset, size, size, orangeGhostTx); break;
                case 'P': player = Player(x+offset, y+offset, size, size, playerRightTx); break;
            }
        }
    }
}

// 更新
void Game::update() {
    // 方向変更を試みる
    if (player.desiredDirection != 0 && player.desiredDirection != player.direction) {
        player.setDirection(player.desiredDirection, tileSize / 4.0f);
        float nextX = player.x + player.velocityX;
        float nextY = player.y + player.velocityY;
        bool canChange = true;
        for (auto& wall : walls) {
            if (player.collision(wall, nextX, nextY)) {
                canChange = false;
                break;
            }
        }
        if (canChange) {
            player.direction = player.desiredDirection;
            switch (player.direction) {
                case 'U': player.sprite.setTexture(playerUpTx); break;
                case 'D': player.sprite.setTexture(playerDownTx); break;
                case 'L': player.sprite.setTexture(playerLeftTx); break;
                case 'R': player.sprite.setTexture(playerRightTx); break;
            }
        } else {
            player.setDirection(player.direction, tileSize / 4.0f);
        }
    }

    // 現在の方向で移動
    float nextX = player.x + player.velocityX;
    float nextY = player.y + player.velocityY;
    bool canMove = true;
    for (auto& wall : walls) {
        if (player.collision(wall, nextX, nextY)) {
            canMove = false;
            break;
        }
    }
    if (canMove) {
        player.x = nextX;
        player.y = nextY;
    } else {
        player.resetVelocity();
    }

    for (int i=0; i<foods.size(); i++) {
        if (player.collision(foods[i])) {
            score += 10;
            foods.erase(foods.begin() + i);
            break;
        }
    }

    for (auto& ghost : ghosts) {
        // 交差点などでランダムに方向転換を試みる
        ghost.ai(tileSize, walls);

        ghost.x += ghost.velocityX;
        ghost.y += ghost.velocityY;

        for (auto& wall : walls) {
            if (ghost.collision(wall)) {
                ghost.x -= ghost.velocityX;
                ghost.y -= ghost.velocityY;
                ghost.resetVelocity();
                ghost.ai(tileSize, walls);
            }
        }

        if (player.collision(ghost) && !gameOver) {
            life--;
            if (life <= 0) {
                gameOver = true;
                player.resetVelocity();
                return;
            }
            player.resetPosition();
            player.resetVelocity();
            return;
        }

        ghost.sprite.setPosition(ghost.x, ghost.y);
    }

    player.sprite.setPosition(player.x, player.y);
}

// 画面にテクスチャを描画します
void Game::draw(sf::RenderWindow& window) {
    for (auto& wall : walls)   { window.draw(wall.sprite); }
    for (auto& food : foods)   { window.draw(Food::foodRect(food)); }
    for (auto& ghost : ghosts) { window.draw(ghost.sprite); }
    window.draw(player.sprite);

    hud.drawLife(window, playerRightTx, life);
    hud.drawScore(window, score);
    hud.drawGameOver(window, gameOver);
}

void Game::makeWall(float x, float y, float scaleWidth, float scaleHeight) {
    Block wall(x, y, scaleWidth, scaleHeight, wallTx);
    walls.push_back(wall);
}

void Game::makeFood(float x, float y) {
    Food food(x+tileSize/2-2, y+tileSize/2-2, 4, 4);
    foods.push_back(food);
}

void Game::makeGhost(float x, float y, float scaleWidth, float scaleHeight, sf::Texture& tx) {
    Ghost ghost(x, y, scaleWidth, scaleHeight, tx);
    ghost.ai(tileSize, walls);
    ghosts.push_back(ghost);
}
