/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#ifndef ORGANICENTITY_HPP
#define ORGANICENTITY_HPP

#include <Interface/Drawable.hpp>
#include <Interface/Updatable.hpp>
#include <Obstacle/CircularCollider.hpp>
#include <Utility/Vec2d.hpp>


#include <SFML/Graphics.hpp>

class Scorpion;
class Gerbil;
class Food;

class OrganicEntity: public CircularCollider, public Drawable, public Updatable
{
public:
    OrganicEntity(Vec2d position, double size, double energyLevel);

    virtual ~OrganicEntity();

    virtual void update(sf::Time dt) = 0;
    virtual void draw(sf::RenderTarget& targetWindow) const = 0;

    virtual bool eatable(OrganicEntity const* other) = 0;
    virtual bool eatableBy(Scorpion  const* scorpion) const = 0;
    virtual bool eatableBy(Gerbil const* gerbil) const = 0;
    virtual bool eatableBy(Food const* food) const = 0;

private:
    double energyLevel_;
};

#endif // ORGANICENTITY_HPP
