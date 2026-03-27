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

    // キーイベントを設定します
    void setKeyEvent(Game& game) {
        if (this->type == sf::Event::KeyPressed) {
            switch (this->key.code) {
                case sf::Keyboard::Up:
                case sf::Keyboard::W:
                    game.player.desiredDirection = 'U'; break;
                case sf::Keyboard::Down:
                case sf::Keyboard::S:
                    game.player.desiredDirection = 'D'; break;
                case sf::Keyboard::Left:
                case sf::Keyboard::A:
                    game.player.desiredDirection = 'L'; break;
                case sf::Keyboard::Right:
                case sf::Keyboard::D:
                    game.player.desiredDirection = 'R'; break;
                default:
                    break;
            }
        } else if (this->type == sf::Event::KeyReleased) {
            switch (this->key.code) {
                case sf::Keyboard::Up:
                case sf::Keyboard::W:
                case sf::Keyboard::Down:
                case sf::Keyboard::S:
                case sf::Keyboard::Left:
                case sf::Keyboard::A:
                case sf::Keyboard::Right:
                case sf::Keyboard::D:
                    game.player.desiredDirection = 0; break;
                default:
                    break;
            }
        }
        if (this->type == sf::Event::KeyPressed) {
            if (game.gameOver) {
                game.loadMap();
                game.score = 0;
                game.life = 3;
                game.gameOver = false;
            }
            if (game.foods.size() == 0) {
                game.loadMap();
            }
        }
    }

};
