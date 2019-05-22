/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#ifndef ORGANICENTITY_HPP
#define ORGANICENTITY_HPP

#include <Interface/Drawable.hpp>
#include <Interface/Updatable.hpp>
#include <Obstacle/CircularCollider.hpp>
#include <Utility/Vec2d.hpp>

#include <SFML/Graphics.hpp>

class Scorpion;
class Gerbil;
class Food;

/*!
 * @brief The OrganicEntity is an abstract class that represents a organic entity in the simulation
 */
class OrganicEntity: public CircularCollider, public Drawable, public Updatable
{
public:
    /*!
     * @brief build an OrganicEntity
     * @param position Vec2d representing the initial position
     * @param size double representing the diameter of the animal
     * @param energyLevel initial level of the animal
     */
    OrganicEntity(Vec2d const& position, double size, double energyLevel);

    /*!
     * @brief destroy an OrganicEntity
     */
    virtual ~OrganicEntity();

    /*!
     * @brief draw the organic entity
     * @param targetWindow targyetWindow window on which the OrganicEntity is rendered
     */
    virtual void draw(sf::RenderTarget& targetWindow) const = 0;

    /*!
     * @brief check if other is eatable by this
     * @param other OrganicEntity to be checked
     * @return true if other is eatable by this, false otherwise
     */
    virtual bool eatable(OrganicEntity const* other) const = 0;

    /*!
     * @brief check if other is matable by this
     * @param other OrganicEntity to be checked
     * @return true if other is matable by this, false otherwise
     */
    virtual bool matable(OrganicEntity const* other) const = 0;

    /*!
     * @brief check if this is eatable by a scorpion
     * @param scorpion Scorpion
     * @return true if this is eatable by a scorpion
     */
    virtual bool eatableBy(Scorpion  const* scorpion) const = 0;

    /*!
     * @brief check if this is eatable by a gerbil
     * @param gerbil Gerbil
     * @return true if this is eatable by a gerbil
     */
    virtual bool eatableBy(Gerbil const* gerbil) const = 0;

    /*!
     * @brief check if this is eatable by a food
     * @param food Food
     * @return true if this is eatable by a food
     */
    virtual bool eatableBy(Food const* food) const = 0;

    /*!
     * @brief check if this can mate with a scorpion
     * @param scorpion Scorpion
     * @return true if this can mate with a scorpion
     */
    virtual bool canMate(Scorpion const* scorpion) const = 0;

    /*!
     * @brief check if this can mate with a gerbil
     * @param gerbil Gerbil
     * @return true if this can mate with a gerbil
     */
    virtual bool canMate(Gerbil const* gerbil) const = 0;

    /*!
     * @brief check if this can mate with a food
     * @param food Food
     * @return true if this can mate with a food
     */
    virtual bool canMate(Food const* food) const = 0;

    /*!
     * @brief update the state of the OrganicEntity at the given time
     * @param dt elapsed time since the last update
     */
    virtual void update(sf::Time dt);

    /*!
     * @return the longevity of the OrganicEntity, by default infinite (sf::seconds(1E9))
     */
    virtual sf::Time getLongevity() const;

    /*!
     * @return true if the OrganicEntity is alive, false otherwise
     */
    bool isAlive() const;

    /*!
     * @return the current energy level of the entity
     */
    double getEnergyLevel() const;

    /*!
     * @return the current age of the entity
     */
    double getAge() const;

    /*!
     * @brief kill the OrganicEntity
     */
    void eaten();
protected:
    /*!
     * @brief decrease the energy level of the entity
     * @param amount of energy that the level will be decreased
     */
    void decreaseEnergyLevel(double loss);

    /*!
     * @brief increase the energy level of the entity
     * @param amount of energy that will be added
     */
    void increaseEnergyLevel(double increase);
private:
    /*!
     * @brief Store the energy level of the OrganicEntity
     */
    double energyLevel_;

    /*!
     * @brief stores the age of the OrganicEntity
     */
    sf::Time age_;

};

#endif // ORGANICENTITY_HPP
