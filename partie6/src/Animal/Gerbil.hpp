/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#ifndef GERBIL_HPP
#define GERBIL_HPP

#include <Animal/Animal.hpp>

/*!
 * @brief The Gerbil class represents a gerbil in the simulation
 */
class Gerbil: public Animal
{
public:
    /*!
     * @brief build an instance of Gerbil
     * @param position Vec2d representing the initial position
     * @param energyLevel initial level of the gerbil
     * @param female gender of the Gerbil instance : true => female, false => male
     */
    Gerbil(Vec2d const& position, double energyLevel, bool female);

    /*!
     * @brief build an instance of Gerbil
     * @param initial position of the gerbil (Vec2d)
     */
    Gerbil(Vec2d const& position);

    /*!
     * @brief destroy the Gerbil instance
     */
    virtual ~Gerbil() override;
private:
    /*
     * Virtual methods that are inherited from OrganicEntity
     * see OrganiEntity.hpp for the corresponding documentation
     */
    virtual bool eatable(OrganicEntity const* entity) const override;
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

#endif // GERBIL_HPP
