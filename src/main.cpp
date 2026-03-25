#include <SFML/Graphics.hpp>
#include "PacMan.hpp"

int main() {
    int colCount = 19;
    int rowCount = 21;
    int tileSize = 32;
    int boardWidth  = colCount * tileSize;
    int boardHeight = rowCount * tileSize;

    // ウィンドウ生成
    sf::RenderWindow window(sf::VideoMode(boardWidth, boardHeight), "PacMan");
    window.setFramerateLimit(30);

    PacMan game;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    game.setDirection('U');
                } else if (event.key.code == sf::Keyboard::Down) {
                    game.setDirection('D');
                } else if (event.key.code == sf::Keyboard::Left) {
                    game.setDirection('L');
                } else if (event.key.code == sf::Keyboard::Right) {
                    game.setDirection('R');
                }
                if (game.gameOver) {
                    game.loadMap();
                    game.resetPositions();
                    game.lives = 3;
                    game.gameOver = false;
                }
            }
        }

        // 更新
        if (!game.gameOver) {
            game.update();
        }

        // 描画
        window.clear();
        game.draw(window);
        window.display();
    }

    return 0;
}
