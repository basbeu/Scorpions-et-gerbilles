/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#ifndef CHASINGAUTOMATON_HPP
#define CHASINGAUTOMATON_HPP

#include <Obstacle/CircularCollider.hpp>
#include <Utility/Vec2d.hpp>

#include <SFML/Graphics.hpp>

class ChasingAutomaton : public CircularCollider
{
public:
    enum Deceleration{
        DECELERATION_STRONG,
        DECELERATION_MEDIUM,
        DECELERATION_WEAK
    };

    ChasingAutomaton(Vec2d position);
    ~ChasingAutomaton();
    double getStandardMaxSpeed() const;
    double getMass() const;
    void setTargetPosition(Vec2d targetPosition);
    Vec2d getSpeedVector() const;
    void update(sf::Time dt);
    void draw(sf::RenderTarget& targetWindow) const;
    void setDeceleration(Deceleration deceleration);

private:
    Vec2d direction_;
    double speed_;
    Vec2d targetPosition_;
    double deceleration_;

    Vec2d computeForce() const;
    void update(Vec2d force, sf::Time dt);
};

#endif // CHASINGAUTOMATON_HPP
