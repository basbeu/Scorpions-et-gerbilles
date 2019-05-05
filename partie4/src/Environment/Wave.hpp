/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#ifndef WAVE_HPP
#define WAVE_HPP

#include <Obstacle/CircularCollider.hpp>
#include <Interface/Drawable.hpp>
#include <Interface/Updatable.hpp>
#include <Utility/Vec2d.hpp>

#include <utility>
#include <list>
#include <SFML/Graphics.hpp>

class Wave:public CircularCollider, public Drawable, public Updatable
{
public:
    Wave(Vec2d origin, double energyLevel, double initialRadius, double mu, double propagationSpeed);

    virtual ~Wave();

    virtual void draw(sf::RenderTarget& target) const;
    virtual void update(sf::Time dt);

    double getEnergy() const;
    double getIntensity() const;
private:
    const double initialEnergyLevel_;
    const double initialRadius_;
    const double mu_;
    const double propagationSpeed_;
    sf::Time timer_;
    std::list<std::pair<double,double>> arcs_;
};

#endif // WAVE_HPP
