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

/**
 * @brief The Wave class represents a wave in the simulation
 */
class Wave:public CircularCollider, public Drawable, public Updatable
{
public:
    /**
     * @brief build a Wave instance
     * @param origin's position
     * @param energyLevel of the wave
     * @param initial radius of the wave
     * @param mu electromagnetic constant
     * @param propagation speed
     */
    Wave(Vec2d const& origin, double energyLevel, double initialRadius, double mu, double propagationSpeed);

    /**
     * @brief destroy a Wave
     */
    virtual ~Wave() override;

    /*
     * overriden methods
     */
    virtual void draw(sf::RenderTarget& target) const override;
    virtual void update(sf::Time dt) override;

    /**
     * @return the current wave energy
     */
    double getEnergy() const;

    /**
     * @return the current wave intensity
     */
    double getIntensity() const;

    /**
     * @brief Compute the wave intensity at a given position
     * @param position in the simulation world
     * @return the intensity of the wave at the given point
     */
    double getIntensityAt(Vec2d const& position) const;
private:
    /**
     * @brief Internal type representing an arc belonging to the wave
     */
    typedef std::pair<double,double> Arc;

    /**
     * @brief initial energy level
     */
    const double initialEnergyLevel_;

    /**
     * @brief initial radius
     */
    const double initialRadius_;

    /**
     * @brief mu electromagnetic constant
     */
    const double mu_;

    /**
     * @brief propagation speed
     */
    const double propagationSpeed_;

    /**
     * @brief elapsed time since emission
     */
    sf::Time timer_;

    /**
     * @brief collection of arcs making the wave
     */
    std::list<Arc> arcs_;

    /**
     * @brief findArcColliding
     * @param obstacleAngle
     * @return
     */
    Arc findArcColliding(double obstacleAngle) const;

    /**
     * @brief compute the angle between a point and the origin point
     * @param position in the simulation world
     * @return the angle betwen the point and the origin point of the wave
     */
    double computeRelativeAngle(Vec2d const& position) const;
};

#endif // WAVE_HPP
