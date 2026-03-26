#include "Game.hpp"
#include "Map.hpp"

Game::Game(): pacman(0, 0, 0, 0, pacmanRight) {
    wallTexture.loadFromFile("images/wall.png");
    redGhost.loadFromFile("images/redGhost.png");
    blueGhost.loadFromFile("images/blueGhost.png");
    pinkGhost.loadFromFile("images/pinkGhost.png");
    orangeGhost.loadFromFile("images/orangeGhost.png");
    pacmanUp.loadFromFile("images/pacmanUp.png");
    pacmanDown.loadFromFile("images/pacmanDown.png");
    pacmanLeft.loadFromFile("images/pacmanLeft.png");
    pacmanRight.loadFromFile("images/pacmanRight.png");

    hud.reset();
    hud.pacmanTexture = &pacmanRight;

    loadMap();
}

void Game::loadMap() {
    walls.clear();
    foods.clear();
    ghosts.clear();
    float size = tileSize * 0.8f;
    float offset = (tileSize - size) / 3;

    for (int r=0; r<rowCount; r++) {
        for (int c=0; c<colCount; c++) {
            Map map;
            char tile = map.data[r][c];
            float y = r * tileSize;
            float x = c * tileSize;

            if (tile == 'X') {
                Block wall(x+offset, y+offset, size, size, wallTexture);
                wall.sprite.setPosition(x, y);
                walls.push_back(wall);
            } else if (tile == 'P') {
                pacman = Player(x, y, tileSize, tileSize, pacmanRight);
                pacman.sprite.setTexture(pacmanRight);
                pacman.sprite.setPosition(x, y);
            } else if (tile == ' ') {
                Block food(x+7, y+7, 4, 4);
                foods.push_back(food);
            } else if (tile == 'r' || tile == 'b' || tile == 'p' || tile == 'o') {
                sf::Texture* texture;
                switch (tile) {
                    case 'r': texture = &redGhost; break;
                    case 'b': texture = &blueGhost; break;
                    case 'p': texture = &pinkGhost; break;
                    case 'o': texture = &orangeGhost; break;
                    default: break;
                }
                Ghost ghost = Ghost(x+offset, y+offset, size, size, *texture);
                ghost.sprite.setPosition(ghost.x, ghost.y);
                ghost.ai(tileSize);
                ghosts.push_back(ghost);

            }
        }
    }
}

void Game::update() {
    pacman.x += pacman.velocityX;
    pacman.y += pacman.velocityY;

    for (auto& wall : walls) {
        if (pacman.collision(wall)) {
            pacman.x -= pacman.velocityX;
            pacman.y -= pacman.velocityY;
            break;
        }
    }
    for (int i=0; i<foods.size(); i++) {
        if (pacman.collision(foods[i])) {
            hud.score += 10;
            foods.erase(foods.begin() + i);
            break;
        }
    }
    for (auto& ghost : ghosts) {
        ghost.x += ghost.velocityX;
        ghost.y += ghost.velocityY;

        for (auto& wall : walls) {
            if (ghost.collision(wall)) {
                ghost.x -= ghost.velocityX;
                ghost.y -= ghost.velocityY;
                ghost.velocityX = 0;
                ghost.velocityY = 0;

                int r = rand() % 4;
                char dirs[4] = {'U', 'D', 'L', 'R'};
                char dir = dirs[r];

                float speed = tileSize / 4;
                if (dir == 'U') ghost.velocityY = -speed;
                if (dir == 'D') ghost.velocityY = speed;
                if (dir == 'L') ghost.velocityX = -speed;
                if (dir == 'R') ghost.velocityX = speed;
            }
        }

        if (pacman.collision(ghost)) {
            pacman.sprite.setPosition(pacman.x, pacman.y);

            // lives--;
            hud.lives--;
            if (hud.lives <= 0) {
                gameOver = true;
                return;
            }
            pacman.reset();
            return;
        }

        ghost.sprite.setPosition(ghost.x, ghost.y);

        // ワープ
        // if (pacman.x < 0) {
        //     pacman.x = width - tileSize;
        // } else if (pacman.x + tileSize > width) {
        //     pacman.x = 0;
        // }
    }

    pacman.sprite.setPosition(pacman.x, pacman.y);

}

void Game::draw(sf::RenderWindow& window) {
    for (auto& wall : walls) {
        window.draw(wall.sprite);
    }
    for (auto& food : foods) {
        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(food.width, food.height));
        rect.setFillColor(sf::Color::White);
        rect.setPosition(food.x, food.y);
        window.draw(rect);
    }
    for (auto& ghost : ghosts) {
        window.draw(ghost.sprite);
    }
    window.draw(pacman.sprite);
}

void Game::handleInput(char dir) {
    pacman.setDirection(dir, tileSize / 4);
    if (dir == 'U') pacman.sprite.setTexture(pacmanUp);
    if (dir == 'D') pacman.sprite.setTexture(pacmanDown);
    if (dir == 'L') pacman.sprite.setTexture(pacmanLeft);
    if (dir == 'R') pacman.sprite.setTexture(pacmanRight);
}
