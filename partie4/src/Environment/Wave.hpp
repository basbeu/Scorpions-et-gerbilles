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

    virtual ~Wave() override;

    virtual void draw(sf::RenderTarget& target) const override;
    virtual void update(sf::Time dt) override;

    double getEnergy() const;
    double getIntensity() const;

    double getIntensityAt(Vec2d position) const;
private:
    typedef std::pair<double,double> Arc;

    const double initialEnergyLevel_;
    const double initialRadius_;
    const double mu_;
    const double propagationSpeed_;
    sf::Time timer_;
    std::list<Arc> arcs_;

    Arc findArcColliding(double obstacleAngle) const;
    double computeRelativeAngle(Vec2d position) const;
};

#endif // WAVE_HPP
