
#ifndef PICKUPBALLS_PLAYER_H
#define PICKUPBALLS_PLAYER_H


#include <SFML/Graphics.hpp>

class Player {
private:
    sf::RectangleShape m_shape;
    float m_movementSpeed{};
    int m_hp{};
    int m_hpMax{};
    int m_points{};
    void initVars();
    void initShape();

public:
    explicit Player(float x = 0.f, float y = 0.f);
    virtual ~Player();

    // Getters
    float x();
    float y();
    sf::RectangleShape getShape() const;
    int getHp() const;
    int getMaxHp() const;
    int getPoints() const;
    void addPoints(int num);

    // Setters
    void takeDamage(const int amt);
    void gainHealth(const int amt);

    void updateWindowBoundsCollision(sf::RenderTarget *target);
    void update(sf::RenderTarget *target);
    void render(sf::RenderTarget *target);
};


#endif //PICKUPBALLS_PLAYER_H
