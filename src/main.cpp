#include "Game.hpp"
#include "Event.hpp"

int main() {
    Game game;
    sf::VideoMode videoMode(game.width, game.height);
    sf::RenderWindow window(videoMode, game.appName);
    window.setFramerateLimit(30);

    while (window.isOpen()) {
        Event event;

        // イベント設定
        while (window.pollEvent(event)) {
            event.setClosed(window);
            event.setKeyPressed(game);
        }

        // 更新
        game.update();

        // 描画
        window.clear();
        game.draw(window);

        // 反映
        window.display();
    }

    return 0;
}
