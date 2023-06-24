#ifndef PICKUPBALLS_HPBAR_H
#define PICKUPBALLS_HPBAR_H
#include <SFML/Graphics.hpp>

class HpBar {
private:
   sf::RectangleShape m_outerRect;
   sf::RectangleShape m_healthRect;

   float m_x{};
   float m_y{};
   float m_width{};
   float m_height{};

   int m_maxHp;
   int m_hp;


public:
    HpBar(float x, float y, float width, float height, int maxHP);
    HpBar();

    ~HpBar();

    void setup(float x, float y, float width, float height, int maxHP);

    void setPosition(float x, float y);
    void setSize(float width, float height);

    void update(sf::RenderTarget *target, int hp);
    void render(sf::RenderTarget *target);

private:
    void initShapes();

};


#endif //PICKUPBALLS_HPBAR_H
