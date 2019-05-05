/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <Obstacle/CircularCollider.hpp>
#include <Interface/Drawable.hpp>

class Obstacle:public CircularCollider, Drawable
{
public:
    Obstacle(Vec2d position, double radius, double orientation);

    virtual ~Obstacle() override;

    virtual void draw(sf::RenderTarget& target) const override;

    virtual std::string getTexture() const = 0;

private:
    const double orientation_;
};

#endif // OBSTACLE_HPP
