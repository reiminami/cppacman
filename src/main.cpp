#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "HUD.hpp"

int main() {
    Game game;
    bool gameOver;
    int width  = game.colCount * game.tileSize;
    int height = game.rowCount * game.tileSize;
    sf::RenderWindow window(sf::VideoMode(width, height), "PacMan");    // ウィンドウ生成
    window.setFramerateLimit(20);   // fps

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            // ウィンドウクローズイベント
            if (event.type == sf::Event::Closed) window.close();

            // キー押下イベント
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Up:    game.handleInput('U'); break;
                    case sf::Keyboard::Down:  game.handleInput('D'); break;
                    case sf::Keyboard::Left:  game.handleInput('L'); break;
                    case sf::Keyboard::Right: game.handleInput('R'); break;
                    default: break;
                }
                if (game.gameOver) {
                    game.loadMap();
                    // game.lives = 3;
                    game.hud.reset();
                    game.gameOver = false;
                }
            }
        }

        // 更新
        if (!game.gameOver) game.update();

        // 描画
        window.clear();
        game.draw(window);
        game.hud.draw(window, gameOver);
        window.display();
    }

    return 0;
}


