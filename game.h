#ifndef PICKUPGAME_GAME_H
#define PICKUPGAME_GAME_H
#include <SFML/Graphics.hpp>

#include <vector>

#include "player.h"
#include "swagball.h"

class Game {
private:
    // Window
    int m_windowWidth{};
    int m_windowHeight{};
    sf::RenderWindow *m_window;
    sf::VideoMode m_videoMode;
    sf::Event m_ev;

    // Mouse pos
    sf::Vector2i m_mousePosWindow;
    sf::Vector2f m_mousePosView;

    // Game logic
    bool m_gameRunning{};
    Player m_player{};
    std::vector<SwagBall> m_balls;
    float m_spawnTimerMax{};
    float m_spawnTimer{};
    int m_maxSwagBalls{};

    // Resources
    sf::Font m_font{};
    sf::Text m_pointsText{};

    // Private functions
    void initVars();
    void initWindow();

public:
    // Constructors / Destructors
    Game(int width, int height);
    virtual ~Game();

    // Getters
    bool isRunning() const;

    // Functions
    void update();
    void updateGUI();
    void render();
    void renderGUI();
    void updateMousePos();
    void updateCollision();
    void pollEvents();
    void spawnSwagBalls();

};


#endif //PICKUPGAME_GAME_H
