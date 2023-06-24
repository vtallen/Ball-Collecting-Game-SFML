#include "player.h"
#include <iostream>
Player::Player(float x, float y) {
  m_shape.setPosition(x, y);
  initVars();
  initShape();
}

Player::~Player() {

}

void Player::initVars() {
  m_movementSpeed = 5.f;
  m_hpMax = 10;
  m_hp = m_hpMax;
  m_points = 0;
}

void Player::initShape() {
  m_shape.setFillColor(sf::Color::Green);
  m_shape.setSize(sf::Vector2f(50.f, 50.f));
}

// Getters
float Player::x() {
  return m_shape.getGlobalBounds().left;
}

float Player::y() {
  return m_shape.getGlobalBounds().top;
}

sf::RectangleShape Player::getShape() const {
  return m_shape;
}

int Player::getHp() const {
  return m_hp;
}

int Player::getMaxHp() const {
  return m_hpMax;
}

int Player::getPoints() const {
  return m_points;
}

void Player::addPoints(int num) {
  m_points += num;
}

// Setters
void Player::takeDamage(const int amt) {
  if (m_hp > 0) {
    m_hp -= amt;
  }

  if (m_hp < 0) m_hp = 0;
}

void Player::gainHealth(const int amt) {
  if (m_hp < m_hpMax) m_hp += amt;

  if (m_hp > m_hpMax) m_hp = m_hpMax;
}

// Private functions
void Player::updateWindowBoundsCollision(sf::RenderTarget *target) {
  //Left
  sf::FloatRect pBounds{m_shape.getGlobalBounds()};
  if (pBounds.left <= 0.f) {
    m_shape.setPosition(0, 0);
  } else if (pBounds.left  + pBounds.width >= target->getSize().x) {
    m_shape.setPosition(target->getSize().x - pBounds.width, pBounds.top);
  }

  if (pBounds.top <= 0.f) {
    m_shape.setPosition(pBounds.left, 0.f);
  } else if (pBounds.top + pBounds.height >= target->getSize().y) {
    m_shape.setPosition(pBounds.left, target->getSize().y - pBounds.height);
  }

  std::cout << "x: " << pBounds.left << " y: " << pBounds.top << '\n';
}

void Player::update(sf::RenderTarget *target) {
  // Keyboard input
  sf::FloatRect pBounds{m_shape.getGlobalBounds()};
  // Left and right
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    if (pBounds.left > 0) m_shape.move(-m_movementSpeed, 0.f);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    if (pBounds.left + pBounds.width < target->getSize().x) m_shape.move(m_movementSpeed, 0.f);
  }

  // Up and down
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    if (pBounds.top > 0) m_shape.move(0.f, -m_movementSpeed);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    if (pBounds.top + pBounds.height < target->getSize().y) m_shape.move(0.f, m_movementSpeed);
  }

}

void Player::render(sf::RenderTarget *target) {
  target->draw(m_shape);
}


