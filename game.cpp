#include "game.h"

// Constructors / Destructor
Game::Game(int width, int height) : m_windowWidth{width}, m_windowHeight{height} {
  initVars();
  initWindow();
  m_endGameText.setPosition(sf::Vector2f((m_window->getSize().x / 2) - m_endGameText.getGlobalBounds().width / 2, 50));
}

Game::~Game() {
  delete m_window;
}

// Private Functions
void Game::initVars() {
  m_gameRunning = true;
  m_spawnTimerMax = 10.f;
  m_spawnTimer = m_spawnTimerMax;
  m_maxSwagBalls = 15;

  m_font.loadFromFile("../Minecraft.ttf");

  m_pointsText.setFont(m_font);
  m_pointsText.setFillColor(sf::Color::White);
  m_pointsText.setPosition(sf::Vector2f(10, 10));

  m_endGameText.setFont(m_font);
  m_endGameText.setFillColor(sf::Color::Red);

  m_endGameText.setString("GAME OVER! Press \"R\" to restart.");
}

void Game::initWindow() {
  m_videoMode.width = m_windowWidth;
  m_videoMode.height = m_windowHeight;
  m_window = new sf::RenderWindow{m_videoMode, "Pickup Balls", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize};
  m_window->setFramerateLimit(60);

  m_hpBar.setup(10.f, m_window->getSize().y - 50, 400, 40, m_player.getMaxHp());
}

// Getters
bool Game::isRunning() const {
  return m_window->isOpen();
}

bool Game::isEndGame() const {
  return m_player.getHp() <= 0;
}
// Public functions
void Game::update() {
  pollEvents();
  updateMousePos();
  if (!isEndGame()) {
    updateCollision();
    spawnSwagBalls();
    m_player.update(m_window);
  }
  updateGUI();
}

void Game::updateGUI() {
  m_pointsText.setString("Points: " + std::to_string(m_player.getPoints()));
  m_hpBar.update(m_window, m_player.getHp());
}

void Game::renderGUI() {

  if (isEndGame()) m_window->draw(m_endGameText);
  else {
    m_window->draw(m_pointsText);
    m_hpBar.render(m_window);
  }
}

void Game::render() {
  m_window->clear();

  if (!isEndGame()) {
    // Draw the game
    m_player.render(m_window);
    for (auto i: m_balls) {
      i.render(m_window);
    }
  }
  renderGUI();
  m_window->display();
}


void Game::pollEvents() {
  while (m_window->pollEvent(m_ev)) {
    switch (m_ev.type) {
      case sf::Event::Closed:
        m_window->close();
        break;
      case sf::Event::KeyPressed:
        if (m_ev.key.code == sf::Keyboard::R && isEndGame()) {
          m_player.gainHealth(m_player.getMaxHp());
          m_balls.erase(m_balls.begin(), m_balls.end());
        }
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
      SwagBall::BallType type{m_balls[i].getType()};
      switch (type) {
        case SwagBall::DEFAULT:
          m_player.addPoints(1);
          break;
        case SwagBall::HEALING:
          m_player.gainHealth(1);
          break;
        case SwagBall::DAMAGING:
          m_player.takeDamage(1);
          break;
        default:
          std::cerr << "Error, ball type does not exist\n";
      }
      m_balls.erase(m_balls.begin() + i);
    }
  }
}

void Game::spawnSwagBalls() {
  if (m_spawnTimer < m_spawnTimerMax) m_spawnTimer += 1.f;
  else {
    if (m_balls.size() < m_maxSwagBalls) {
      m_balls.push_back(SwagBall{m_window, SwagBall::randomizeType()});
      m_spawnTimer = 0.f;

    }
  }
}

