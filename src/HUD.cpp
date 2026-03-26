#include "HUD.hpp"

// HUD::HUD(sf::Texture& tx): pacmanTexture(&tx) {
HUD::HUD() {
    reset();

    font.loadFromFile("fonts/Arial.ttf");
    text.setFont(font);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::White);
}

void HUD::reset() {
    score = 0;
    lives = 3;
}

void HUD::draw(sf::RenderWindow& window, bool gameOver) {
    if (gameOver) {
        // ゲームオーバー表示
        // NOT WORK
        text.setString("YOU ARE DEAD\nScore: " + std::to_string(score));
        text.setPosition(100, 150);
        window.draw(text);
    } else {
        // ライフ表示
        for (int i=0; i<lives; i++) {
            sf::Sprite sprite;
            sprite.setTexture(*pacmanTexture);
            sprite.setScale(1.2f, 1.2f);
            float x = 10 + i * 20;
            float y = 0;
            sprite.setPosition(x, y);
            window.draw(sprite);
        }

        // スコア表示
        sf::Vector2u winSize = window.getSize();
        text.setString(std::to_string(score));
        sf::FloatRect bounds = text.getLocalBounds();
        text.setPosition(winSize.x - bounds.width - 20, 0);
        window.draw(text);
    }
}

// 背景を暗くし、sf::RectangleShapeとして返します。
sf::RectangleShape bgGrey(float x, float y) {
    sf::RectangleShape bg;
    bg.setSize(sf::Vector2f(x, y));
    bg.setFillColor(sf::Color(0, 0, 0, 150));
    bg.setPosition(0, 0);
    return bg;
}
