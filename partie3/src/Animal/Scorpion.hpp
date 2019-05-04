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

    virtual ~Scorpion() override;

    virtual double getStandardMaxSpeed() const override;
    virtual double getMass() const override;
    virtual double getRandomWalkRadius() const override;
    virtual double getRandomWalkDistance() const override;
    virtual double getRandomWalkJitter() const override;
    virtual double getViewRange() const override;
    virtual double getViewDistance() const override;
    virtual std::string getTexture() const override;

    virtual bool eatable(OrganicEntity const* entity) override;
    virtual bool eatableBy(Scorpion  const* scorpion) const override;
    virtual bool eatableBy(Gerbil const* gerbil) const override;
    virtual bool eatableBy(Food const* food) const override;

    virtual sf::Time getLongevity() const override;
    virtual double getEnergyLossFactor() const override;
    virtual double getTiredMaxSpeed() const override;
    virtual sf::Time getFeedingBreak() const override;
    virtual double getFeedingEfficiency() const override;
};

#endif // SCORPION_HPP
