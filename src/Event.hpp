#pragma once
#include <SFML/Graphics.hpp>
#include "Game.hpp"

struct Event : public sf::Event {
    // ウィンドウを閉じる際のイベントを設定します
    void setClosed(sf::RenderWindow &window) {
        if (this->type == sf::Event::Closed) {
            window.close();
        }
    }

    // キー押下時のイベントを設定します
    void setKeyPressed(Game& game) {
        if (this->type == sf::Event::KeyPressed) {
            switch (this->key.code) {
                case sf::Keyboard::Up:
                case sf::Keyboard::W:
                    game.handleInput('U'); break;
                    break;
                case sf::Keyboard::Down:
                case sf::Keyboard::S:
                    game.handleInput('D'); break;
                    break;
                case sf::Keyboard::Left:
                case sf::Keyboard::A:
                    game.handleInput('L'); break;
                    break;
                case sf::Keyboard::Right:
                case sf::Keyboard::D:
                    game.handleInput('R'); break;
                    break;
                default:
                    break;
            }
            if (game.gameOver) {
                game.loadMap();
                game.score = 0;
                game.life = 3;
                game.gameOver = false;
            }
        }
    }

};
