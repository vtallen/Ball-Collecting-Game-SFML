#include "game.h"

// Constructors / Destructor
Game::Game(int width, int height) : m_windowWidth{width}, m_windowHeight{height} {
  initVars();
  initWindow();
}

Game::~Game() {
  delete m_window;
}

// Private Functions
void Game::initVars() {
  m_gameRunning = true;
  m_spawnTimerMax = 0.f;
  m_spawnTimer = m_spawnTimerMax;
  m_maxSwagBalls = 100000;

  m_font.loadFromFile("../Minecraft.ttf");
  m_pointsText.setFont(m_font);
  m_pointsText.setFillColor(sf::Color::White);
  m_pointsText.setPosition(sf::Vector2f(10, 10));

  m_pointsText.setString("Points: " + std::to_string(m_player.getPoints()));
}

void Game::initWindow() {
  m_videoMode.width = m_windowWidth;
  m_videoMode.height = m_windowHeight;
  m_window = new sf::RenderWindow{m_videoMode, "Pickup Balls", sf::Style::Titlebar | sf::Style::Close };
  m_window->setFramerateLimit(60);
}

// Getters
bool Game::isRunning() const {
  return m_window->isOpen();
}

// Public functions
void Game::update() {
  pollEvents();
  updateMousePos();
  updateCollision();
  spawnSwagBalls();
  m_player.update(m_window);
  updateGUI();
}

void Game::updateGUI() {
  m_pointsText.setString("Points: " + std::to_string(m_player.getPoints()));
}

void Game::render() {
  m_window->clear();

  // Draw the game
  m_player.render(m_window);
  for (auto i : m_balls) {
    i.render(m_window);
  }
  renderGUI();
  m_window->display();
}

void Game::renderGUI() {
  m_window->draw(m_pointsText);
}

void Game::pollEvents() {
  while (m_window->pollEvent(m_ev)) {
    switch (m_ev.type) {
      case sf::Event::Closed:
        m_window->close();
        break;
      case sf::Event::KeyPressed:
        break;
    }
  }
}

void Game::updateMousePos() {
  m_mousePosWindow = sf::Mouse::getPosition(*m_window);
  m_mousePosView = m_window->mapPixelToCoords(m_mousePosWindow);
}

void Game::updateCollision() {
  // Check the collision
  for (size_t i{0}; i < m_balls.size(); ++i) {
    if (m_player.getShape().getGlobalBounds().intersects(m_balls[i].getShape().getGlobalBounds())) {
      m_balls.erase(m_balls.begin() + i);
      m_player.addPoints(1);
    }
  }
}

void Game::spawnSwagBalls() {
  if (m_spawnTimer < m_spawnTimerMax) m_spawnTimer += 1.f;
  else {
    if (m_balls.size() < m_maxSwagBalls) {
      m_balls.push_back(SwagBall{m_window, rand()%SwagBall::BallType::MAX_TYPES});
      m_spawnTimer = 0.f;

    }
  }
}

