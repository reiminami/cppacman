#include "PacMan.hpp"

PacMan::PacMan() {
    tileMap = {
        "XXXXXXXXXXXXXXXXXXX",
        "X        X        X",
        "X XX XXX X XXX XX X",
        "X                 X",
        "X XX X XXXXX X XX X",
        "X    X       X    X",
        "XXXX XXXX XXXX XXXX",
        "OOOX X       X XOOO",
        "XXXX X XXrXX X XXXX",
        "X       bpo       X",
        "XXXX X XXXXX X XXXX",
        "OOOX X       X XOOO",
        "XXXX X XXXXX X XXXX",
        "X        X        X",
        "X XX XXX X XXX XX X",
        "X  X     P     X  X",
        "XX X X XXXXX X X XX",
        "X    X   X   X    X",
        "X XXXXXX X XXXXXX X",
        "X                 X",
        "XXXXXXXXXXXXXXXXXXX"
    };

    wallTexture.loadFromFile("images/wall.png");
    ghostTexture.loadFromFile("images/redGhost.png");
    pacmanUp.loadFromFile("images/pacmanUp.png");
    pacmanDown.loadFromFile("images/pacmanDown.png");
    pacmanLeft.loadFromFile("images/pacmanLeft.png");
    pacmanRight.loadFromFile("images/pacmanRight.png");

    loadMap();
}

void PacMan::loadMap() {
    for (int r=0; r<rowCount; r++) {
        for (int c=0; c<colCount; c++) {
            char tile = tileMap[r][c];
            float y = r * tileSize;
            float x = c * tileSize;

            if (tile == 'X') {
                Block wall;
                wall.x = x;
                wall.y = y;
                wall.width  = tileSize;
                wall.height = tileSize;
                wall.sprite.setTexture(wallTexture);
                wall.sprite.setPosition(x, y);
                walls.push_back(wall);
            } else if (tile == 'P') {
                pacman.x = x;
                pacman.y = y;
                pacman.width  = tileSize;
                pacman.height = tileSize;
                pacman.startX = x;
                pacman.startY = y;
                pacman.sprite.setTexture(pacmanRight);
                pacman.sprite.setPosition(x, y);
            } else if (tile == ' ') {
                Block food;
                food.x = x + 14;
                food.y = y + 14;
                food.width  = 4;
                food.height = 4;
                foods.push_back(food);
            } else if (tile == 'r' || tile == 'b' || tile == 'p' || tile == 'o') {
                Block ghost;
                ghost.x = x;
                ghost.y = y;
                ghost.width  = tileSize;
                ghost.height = tileSize;
                ghost.startX = x;
                ghost.startY = y;
                ghost.sprite.setTexture(ghostTexture);

                int r = rand() % 4;
                char dirs[4] = {'U', 'D', 'L', 'R'};
                ghost.direction = dirs[r];

                float speed = tileSize / 4;
                if (ghost.direction == 'U') ghost.velocityY = -speed;
                if (ghost.direction == 'D') ghost.velocityY = speed;
                if (ghost.direction == 'L') ghost.velocityX = -speed;
                if (ghost.direction == 'R') ghost.velocityX = speed;

                ghosts.push_back(ghost);
            }
        }
    }
}

void PacMan::update() {
    pacman.x += pacman.velocityX;
    pacman.y += pacman.velocityY;

    for (auto& wall : walls) {
        if (collision(pacman, wall)) {
            pacman.x -= pacman.velocityX;
            pacman.y -= pacman.velocityY;
            break;
        }
    }
    for (int i=0; i<foods.size(); i++) {
        if (collision(pacman, foods[i])) {
            foods.erase(foods.begin() + i);
            break;
        }
    }
    for (auto& ghost : ghosts) {
        ghost.x += ghost.velocityX;
        ghost.y += ghost.velocityY;

        for (auto& wall : walls) {
            if (collision(ghost, wall)) {
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

        if (collision(pacman, ghost)) {
            pacman.sprite.setPosition(pacman.x, pacman.y);

            lives--;
            if (lives <= 0) {
                gameOver = true;
                return;
            }
            resetPositions();
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

void PacMan::draw(sf::RenderWindow& window) {
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

void PacMan::setDirection(char dir) {
    pacman.direction = dir;
    float speed = tileSize / 4;

    if (dir == 'U') {
        pacman.velocityX = 0;
        pacman.velocityY = -speed;
    } else if (dir == 'D') {
        pacman.velocityX = 0;
        pacman.velocityY = speed;
    } else if (dir == 'L') {
        pacman.velocityX = -speed;
        pacman.velocityY = 0;
    } else if (dir == 'R') {
        pacman.velocityX = speed;
        pacman.velocityY = 0;
    }

    if (dir == 'U') pacman.sprite.setTexture(pacmanUp);
    if (dir == 'D') pacman.sprite.setTexture(pacmanDown);
    if (dir == 'L') pacman.sprite.setTexture(pacmanLeft);
    if (dir == 'R') pacman.sprite.setTexture(pacmanRight);
}

bool PacMan::collision(const Block& a, const Block& b) {
    return a.x < b.x + b.width  && a.x + a.width  > b.x &&
           a.y < b.y + b.height && a.y + a.height > b.y;
}

void PacMan::resetPositions() {
    pacman.x = 9  * tileSize;
    pacman.y = 15 * tileSize;
    pacman.velocityX = 0;
    pacman.velocityY = 0;
    pacman.sprite.setPosition(pacman.x, pacman.y);

    for (auto& ghost : ghosts) {
        ghost.x = ghost.startX;
        ghost.y = ghost.startY;
        ghost.velocityX = 0;
        ghost.velocityY = 0;

        int r = rand() % 4;
        char dirs[4] = {'U', 'D', 'L', 'R'};
        ghost.direction = dirs[r];

        float speed = tileSize / 4;
        if (ghost.direction == 'U') ghost.velocityY = -speed;
        if (ghost.direction == 'D') ghost.velocityY = speed;
        if (ghost.direction == 'L') ghost.velocityX = -speed;
        if (ghost.direction == 'R') ghost.velocityX = speed;
        ghost.sprite.setPosition(ghost.x, ghost.y);
    }
}
