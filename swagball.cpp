//
// Created by Vincent Allen on 6/22/23.
//

#include "swagball.h"

SwagBall::SwagBall(sf::RenderWindow *target, BallType type) : m_type{type} {
 initShape(target);
}

SwagBall::~SwagBall() {

}

void SwagBall::initShape(sf::RenderWindow *target) {
  m_shape.setRadius(static_cast<float>(rand()%10 + 10));
  sf::Color color(rand()%255 + 1, rand()%255 + 1, rand()%255 + 1);
  m_shape.setFillColor(color);

  m_shape.setPosition(rand()%target->getSize().x - m_shape.getGlobalBounds().width, rand()%target->getSize().y - m_shape.getGlobalBounds().height);
}

void SwagBall::update(sf::RenderTarget *target) {
}

void SwagBall::render(sf::RenderTarget *target) {
  target->draw(m_shape);
}

sf::CircleShape SwagBall::getShape() {
  return m_shape;
}

SwagBall::BallType SwagBall::getType() const {
  return m_type;
}
