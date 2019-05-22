/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <Obstacle/CircularCollider.hpp>
#include <Interface/Drawable.hpp>

/**
 * @brief The Obstacle class represents a solid obstacle in the simulation
 */
class Obstacle:public CircularCollider, Drawable
{
public:
    /**
     * @brief build an Obstacle instance
     * @param position position of the obstacle
     * @param radius of the circularCollider of the obstacle
     * @param orientation of the obstacle
     */
    Obstacle(Vec2d const& position, double radius, double orientation);

    /**
     * @brief destroy an Obstacle instance
     */
    virtual ~Obstacle() override;

    /*
     * Overriden methods
     */
    virtual void draw(sf::RenderTarget& target) const override;
    virtual std::string getTexture() const = 0;

private:
    /**
     * @brief orientation of the obstacle
     */
    const double orientation_;
};

#endif // OBSTACLE_HPP
