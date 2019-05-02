/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#ifndef SCORPION_HPP
#define SCORPION_HPP

#include <Animal/Animal.hpp>


class Scorpion:public Animal
{
public:
    Scorpion(Vec2d position, double energyLevel, bool female);
    Scorpion(Vec2d position);

    virtual double getStandardMaxSpeed() const override;
    virtual double getMass() const override;
    virtual double getRandomWalkRadius() const override;
    virtual double getRandomWalkDistance() const override;
    virtual double getRandomWalkJitter() const override;
    virtual double getViewRange() const override;
    virtual double getViewDistance() const override;
    virtual std::string getTexture() const override;

};

#endif // SCORPION_HPP
