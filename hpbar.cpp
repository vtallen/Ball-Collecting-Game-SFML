//
// Created by Vincent Allen on 6/24/23.
//

#include "hpbar.h"

HpBar::HpBar(float x, float y, float width, float height, int maxHP): m_x{x}, m_y{y}, m_width{width}, m_height{height}, m_maxHp{maxHP} {
  m_hp = m_maxHp;
  initShapes();
}

HpBar::HpBar() {

}

HpBar::~HpBar() {

}
void HpBar::setPosition(float x, float y) {
  m_x = x;
  m_y = y;

  initShapes();
}

void HpBar::setSize(float width, float height) {
  m_width = width;
  m_height = height;

  initShapes();
}

void HpBar::setup(float x, float y, float width, float height, int maxHP) {
  m_x = x;
  m_y = y;
  m_width = width;
  m_height = height;

  m_maxHp = maxHP;

  initShapes();
}

void HpBar::initShapes() {
  m_outerRect.setFillColor(sf::Color::White);
  m_outerRect.setPosition(m_x, m_y);
  m_outerRect.setSize(sf::Vector2f(m_width, m_height));

  m_healthRect.setFillColor(sf::Color::Red);
  m_healthRect.setPosition(m_x + 10.f, m_y + 10.f);
  m_healthRect.setSize(sf::Vector2f(m_width - 20.f, m_height - 20.f));
}

void HpBar::update(sf::RenderTarget *target, int hp) {
  m_hp = hp;
  float pxPerHp{(m_width - 20.f) / m_maxHp};
  m_healthRect.setSize(sf::Vector2f(m_hp * pxPerHp, m_height - 20.f));
}

void HpBar::render(sf::RenderTarget *target) {
  target->draw(m_outerRect);
  target->draw(m_healthRect);
}


