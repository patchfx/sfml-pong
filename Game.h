#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Game {
public:
    Game();
    int run();
    bool loadFont();
    bool loadImages();
    bool loadSound();
    void createPlayers();
    void createScoreboard();

    void render();

private:
    bool playing;
    sf::RenderWindow window;
    sf::Event event;
    sf::Font font;
    sf::Text score;
    sf::Texture tex_pad;
    sf::Texture tex_ball;
    sf::Texture tex_background;
    sf::SoundBuffer buf_hit;
    sf::Sound hit;
    sf::RectangleShape pad1;
    sf::RectangleShape background;
    sf::RectangleShape pad2;
    sf::RectangleShape ball;

    //States
    bool up;
    bool down;

    //Variables
    int yVelocityPad1;
    int xVelocityBall;
    int yVelocityBall;
    int yVelocityPad2;
    int pad1Score;
    int pad2Score;
};