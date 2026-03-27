#pragma once
#include "Entity.hpp"

struct Ghost : public Entity {
    Ghost(float x, float y, float width, float height, sf::Texture& tx)
    : Entity(x, y, width, height, tx)
    {
    }

    bool isAligned(int tileSize) const {
        float rx = fmodf(x, tileSize);
        float ry = fmodf(y, tileSize);
        return (fabs(rx) < 1.0f || fabs(rx - tileSize) < 1.0f) &&
               (fabs(ry) < 1.0f || fabs(ry - tileSize) < 1.0f);
    }

    bool canMove(char dir, const std::vector<Block>& walls, int tileSize) const {
        float speed = tileSize / 4.0f;
        float testX = x;
        float testY = y;

        if (dir == 'U') testY -= speed;
        if (dir == 'D') testY += speed;
        if (dir == 'L') testX -= speed;
        if (dir == 'R') testX += speed;

        for (auto& wall : walls) {
            if (collision(wall, testX, testY)) return false;
        }
        return true;
    }

    void ai(int tileSize, const std::vector<Block>& walls) {
        int speed = tileSize / 4;
        std::vector<char> candidates;

        for (char d : {'U','D','L','R'}) {
            if (canMove(d, walls, tileSize)) {
                candidates.push_back(d);
            }
        }

        if (!candidates.empty()) {
            // 壁に当たった場合は必ずどれかの方向へ
            if (!canMove(direction, walls, tileSize)) {
                direction = candidates[rand() % candidates.size()];
            }
            // 交差点で確率的に曲がる
            else if (isAligned(tileSize) && candidates.size() >= 3) {
                if ((rand() % 100) < 30) { // 30%で曲がる
                    std::vector<char> turnOptions;
                    for (char d : candidates) {
                        if (d != direction && d != (direction == 'U' ? 'D' : direction == 'D' ? 'U' : direction == 'L' ? 'R' : 'L')) {
                            turnOptions.push_back(d);
                        }
                    }
                    if (!turnOptions.empty()) {
                        direction = turnOptions[rand() % turnOptions.size()];
                    }
                }
            }
            setDirection(direction, speed);
        } else {
            // 進めない場合はその場で停止
            resetVelocity();
        }
    }
};
