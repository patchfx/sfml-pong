#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include "Game.h"

Game::Game() {
    playing = true;
    window.create(sf::VideoMode(800,600), "Pong - 1gam");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    yVelocityPad1 = 0;
    xVelocityBall = -4;
    yVelocityBall = -4;
    yVelocityPad2 = 0;
    pad1Score = 0;
    pad2Score = 0;

    up = false;
    down = false;

    loadImages();
    createPlayers();
    loadFont();
    loadSound();
    createScoreboard();
}

bool Game::loadFont() {
    if (!font.loadFromFile("Data/Krungthep.ttf")) {
        return false;
    }
    return true;
}

bool Game::loadImages() {
    if(!tex_pad.loadFromFile("Data/pad.png")) {
        return false;
    }

    if(!tex_ball.loadFromFile("Data/ball.png")) {
        return false;
    }

    if(!tex_background.loadFromFile("Data/background.png")) {
        return false;
    }

    return true;
}

bool Game::loadSound() {
    if (!buf_hit.loadFromFile("Data/hit.wav")) {
        return false;
    }

    hit.setBuffer(buf_hit);
    return true;
}

void Game::createPlayers() {

    background.setSize(sf::Vector2f(800,600));
    background.setPosition(0,0);
    background.setTexture(&tex_background);

    pad1.setSize(sf::Vector2f(50,100));
    pad1.setPosition(50,200);
    pad1.setTexture(&tex_pad);

    pad2.setSize(sf::Vector2f(50,100));
    pad2.setPosition(700,200);
    pad2.setTexture(&tex_pad);

    ball.setSize(sf::Vector2f(50,50));
    ball.setPosition(375,200);
    ball.setTexture(&tex_ball);
}

void Game::createScoreboard() {
    score.setFont(font);
    score.setCharacterSize(30);
    score.setColor(sf::Color::Red);
    score.setPosition(350, 10);
    score.setString("0 : 0");
}

void Game::render() {
    //Rendering
    window.clear();
    window.draw(background);
    window.draw(pad1);
    window.draw(pad2);
    window.draw(ball);

    std::stringstream text;
    text << pad1Score << " : " << pad2Score;
    score.setString(text.str());
    window.draw(score);

    window.display();
}

int Game::run() {
    while (playing) {
        //events
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                playing = false;
            }
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
            up = true;
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
            down = true;
        }

        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up) {
            up = false;
        }


        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down) {
            down = false;
        }

        //Logic
        if (up) {
            yVelocityPad1 = -5;
        }

        if (down) {
            yVelocityPad1 = 5;
        }

        if (up && down) {
            yVelocityPad1 = 0;
        }

        if (!up && !down) {
            yVelocityPad1 = 0;
        }

        pad1.move(0, yVelocityPad1);
        pad2.move(0, yVelocityPad2);

        //Ball
        ball.move(xVelocityBall, yVelocityBall);

        //Out of bounds check
        if (pad1.getPosition().y < 0) {
            pad1.setPosition(50, 0);
        }

        if (pad1.getPosition().y > 500) {
            pad1.setPosition(50, 500);
        }

        if (ball.getPosition().y < 0) {
            yVelocityBall = -yVelocityBall;
        }

        if (ball.getPosition().y > 550) {
            yVelocityBall = -yVelocityBall;
        }

        if (ball.getPosition().x < -50) {
            pad2Score++;
            ball.setPosition(300, 200);
        }

        if (ball.getPosition().x > 800) {
            pad1Score++;
            ball.setPosition(300, 200);
        }

        //Pad2 - AI
        if (ball.getPosition().y < pad2.getPosition().y) {
            yVelocityPad2 = -2;
        }

        if (ball.getPosition().y > pad2.getPosition().y) {
            yVelocityPad2 = 2;
        }

        if (ball.getGlobalBounds().intersects(pad1.getGlobalBounds())) {
            if (ball.getPosition().y + 50 > pad1.getPosition().y && ball.getPosition().x < pad1.getPosition().x + 49) {
                ball.setPosition(ball.getPosition().x, ball.getPosition().y - 3);
                yVelocityBall = -yVelocityBall;
            }

            if (ball.getPosition().y + 50 > pad1.getPosition().y + 100 && ball.getPosition().x < pad1.getPosition().x + 49) {
                ball.setPosition(ball.getPosition().x, ball.getPosition().y + 3);
                yVelocityBall = +yVelocityBall;
            }
            else {
                xVelocityBall = -xVelocityBall;
                yVelocityBall = -yVelocityBall;
            }
            hit.play();
        }

        if (ball.getGlobalBounds().intersects(pad2.getGlobalBounds())) {
            if (ball.getPosition().y + 50 > pad2.getPosition().y && ball.getPosition().x > pad2.getPosition().x - 49) {
                ball.setPosition(ball.getPosition().x, ball.getPosition().y - 10);
                yVelocityPad2 = 0;
                yVelocityBall = -yVelocityBall;
            }

            if (ball.getPosition().y + 50 > pad2.getPosition().y + 100 && ball.getPosition().x > pad2.getPosition().x - 49) {
                ball.setPosition(ball.getPosition().x, ball.getPosition().y + 10);
                yVelocityPad2 = 0;
                yVelocityBall = +yVelocityBall;
            }

            else {
                xVelocityBall = -xVelocityBall;
            }
            hit.play();
        }

        render();
    }

    window.close();
    return 0;
}