/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#ifndef ORGANICENTITY_HPP
#define ORGANICENTITY_HPP

#include <Obstacle/CircularCollider.hpp>

#include <Utility/Vec2d.hpp>

#include <SFML/Graphics.hpp>

class OrganicEntity: public CircularCollider
{
public:
    OrganicEntity(Vec2d position, double size, double energyLevel);

    virtual ~OrganicEntity();

    virtual void update(sf::Time dt) = 0;
    virtual void draw(sf::RenderTarget& targetWindow) const = 0;
private:
    double energyLevel_;
};

#endif // ORGANICENTITY_HPP
