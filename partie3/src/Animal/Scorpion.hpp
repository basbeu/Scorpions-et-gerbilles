/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#ifndef SCORPION_HPP
#define SCORPION_HPP

#include <Animal/Animal.hpp>

/*!
 * @brief The Scorpion class represents a Scorpion in the simulation
 */
class Scorpion:public Animal
{
public:
    /*!
     * @brief build an instance of Scorpion
     * @param position Vec2d representing the initial position
     * @param energyLevel initial level of the scorpion
     * @param female gender of the Scorpion instance : true => female, false => male
     */
    Scorpion(Vec2d position, double energyLevel, bool female);

    /*!
     * @brief build an instance of Scorpion
     * @param initial position of the scorpion (Vec2d)
     */
    Scorpion(Vec2d position);

    /*!
     * @brief destroy a Scorpion
     */
    virtual ~Scorpion() override;
private:
    /*
     * Virtual methods that are inherited from OrganicEntity
     * see OrganiEntity.hpp for the corresponding documentation
     */
    virtual bool eatable(OrganicEntity const* entity) override;
    virtual bool eatableBy(Scorpion  const* scorpion) const override;
    virtual bool eatableBy(Gerbil const* gerbil) const override;
    virtual bool eatableBy(Food const* food) const override;

    virtual bool matable(OrganicEntity const* other) const override;
    virtual bool canMate(Scorpion const* scorpion) const override;
    virtual bool canMate(Gerbil const* gerbil) const override;
    virtual bool canMate(Food const* food) const override;

    /*
     * Virtual methods that are inherited from Animal
     * see Animal.hpp for the corresponding documentation
     */
    virtual double getStandardMaxSpeed() const override;
    virtual double getMass() const override;
    virtual double getRandomWalkRadius() const override;
    virtual double getRandomWalkDistance() const override;
    virtual double getRandomWalkJitter() const override;
    virtual double getViewRange() const override;
    virtual double getViewDistance() const override;
    virtual std::string getTexture() const override;
    virtual sf::Time getLongevity() const override;
    virtual double getEnergyLossFactor() const override;
    virtual double getTiredMaxSpeed() const override;
    virtual sf::Time getFeedingBreak() const override;
    virtual double getFeedingEfficiency() const override;
    virtual double getMinimumMatingEnergy() const override;
    virtual double getMinAgeMating()const override;
    virtual int getMinChildren() const override;
    virtual int getMaxChildren() const override;
    virtual double getEnergyLossFemalePerChild() const override;
    virtual double getEnergyLossMatingMale() const override;
    virtual double getGestationTime() const override;
    virtual sf::Time getGivingBirthBreak() const override;
    virtual Animal* giveBirth() const override;
};

#endif // SCORPION_HPP
