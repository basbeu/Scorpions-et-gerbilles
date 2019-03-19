/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#ifndef ANIMAL_H
#define ANIMAL_H
#include <Obstacle/CircularCollider.hpp>
#include <Utility/Vec2d.hpp>

#include <SFML/Graphics.hpp>

class Animal:public CircularCollider
{
public:
    enum Deceleration{
        DECELERATION_STRONG,
        DECELERATION_MEDIUM,
        DECELERATION_WEAK
    };

    Animal(Vec2d position);
    ~Animal();
    double getStandardMaxSpeed() const;
    double getMass() const;
    void setTargetPosition(Vec2d targetPosition);
    Vec2d getSpeedVector() const;
    void update(sf::Time dt);
    void draw(sf::RenderTarget& targetWindow) const;
    void setDeceleration(Deceleration deceleration);
    double getViewRange() const;
    double getViewDistance() const;
    double getRotation() const;
    bool isTargetInSight(Vec2d const& target);

protected:
    void setRotation(double angle);

private:
    Vec2d direction_;
    double speed_;
    Vec2d targetPosition_;
    double deceleration_;

    Vec2d computeForce() const;
    void update(Vec2d force, sf::Time dt);
    void drawVision(sf::RenderTarget& targetWindow) const;
};

#endif
