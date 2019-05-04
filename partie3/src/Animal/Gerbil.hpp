/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#ifndef GERBIL_HPP
#define GERBIL_HPP

#include <Animal/Animal.hpp>

class Gerbil: public Animal
{
public:
    Gerbil(Vec2d position, double energyLevel, bool female);
    Gerbil(Vec2d position);

    virtual ~Gerbil() override;
private:
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

    virtual bool matable(OrganicEntity const* other) const override;
    virtual bool canMate(Scorpion const* scorpion) const override;
    virtual bool canMate(Gerbil const* gerbil) const override;
    virtual bool canMate(Food const* food) const override;

    virtual double getMinimumMatingEnergy() const override;
    virtual double getMinAgeMating()const override;

    virtual int getMinChildren() const override;
    virtual int getMaxChildren() const override;
    virtual double getEnergyLossFemalePerChild() const override;
    virtual double getEnergyLossMatingMale() const override;
    virtual double getGestationTime() const override;
    virtual sf::Time getGivingBirthBreak() const override;
    virtual Animal* giveBirth() override;
};

#endif // GERBIL_HPP
