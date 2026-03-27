#pragma once
#include <SFML/Graphics.hpp>

class HUD {
public:
    sf::Font font;
    sf::Text text;
    sf::Texture* lifeTexture;

    HUD() {
        font.loadFromFile("fonts/Arial.ttf");
        text.setFont(font);
        text.setCharacterSize(16);
        text.setFillColor(sf::Color::White);
    };

    // ライフを描画します
    void drawLife(sf::RenderWindow& window, sf::Texture lifeTexture, int life) {
        for (int i=0; i<life; i++) {
            sf::Sprite sprite;
            sprite.setTexture(lifeTexture);
            sprite.setScale(1.2f, 1.2f);
            sprite.setPosition(10+i*20, 10);
            window.draw(sprite);
        }
    }

    // スコアを描画します
    void drawScore(sf::RenderWindow& window, int score) {
        sf::Vector2u winSize = window.getSize();
        text.setString(std::to_string(score));
        sf::FloatRect bounds = text.getLocalBounds();
        text.setPosition(winSize.x - bounds.width - 20, 10);
        window.draw(text);
    }

    // 死亡時のテキストを描画します
    void drawGameOver(sf::RenderWindow& window, bool gameOver) {
        if (gameOver) {
            text.setString("GAMEOVER");
            sf::FloatRect textRect = text.getLocalBounds();
            text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
            text.setPosition(sf::Vector2f(window.getView().getCenter()));
            window.draw(text);
        }
    }
};
