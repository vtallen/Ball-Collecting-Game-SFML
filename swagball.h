//
// Created by Vincent Allen on 6/22/23.
//

#ifndef PICKUPBALLS_SWAGBALL_H
#define PICKUPBALLS_SWAGBALL_H
#include <SFML/Graphics.hpp>

#include <iostream>

#include "player.h"

class SwagBall {
public:
    enum BallType {
      DEFAULT,
      DAMAGING,
      HEALING,
      MAX_TYPES,
    };
private:
  sf::CircleShape m_shape;
  BallType m_type;

  void initShape(sf::RenderWindow *target);
public:
    explicit SwagBall(sf::RenderWindow *target, BallType type);
    virtual ~SwagBall();
    //Getters
    sf::CircleShape getShape();
    BallType getType() const;
    // Functions
    void update(sf::RenderTarget *target);
    void render(sf::RenderTarget *target);
};


#endif //PICKUPBALLS_SWAGBALL_H
