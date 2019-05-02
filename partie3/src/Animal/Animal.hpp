/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#ifndef ANIMAL_H
#define ANIMAL_H
#include <Environment/OrganicEntity.hpp>
#include <Utility/Vec2d.hpp>

#include <SFML/Graphics.hpp>

/*!
 * @brief The Animal class
 */
class Animal:public OrganicEntity
{
public:
    /*!
    * @brief The Deceleration enum represent the differents magnitude that a Animal can be set
    */
    enum Deceleration {
        DECELERATION_STRONG,
        DECELERATION_MEDIUM,
        DECELERATION_WEAK
    };

    /*!
     * @brief Animal build a a ChasinAutomaton
     * @param position Vec2d representing the initial position
     * @param size double representing the diameter of the animal
     * @param energyLevel initial level of the animal
     * @param female gender of the animal instance : true => female, false => male
     */
    Animal(Vec2d position, double size, double energyLevel, bool female);

    /*!
     * @brief Destroy a Animal
     */
    virtual ~Animal();

    /*!
     * @return the max speed of the Animal
     */
    virtual double getStandardMaxSpeed() const = 0;

    /*!
     * @return the mass of the Animal
     */
    virtual double getMass() const = 0;

    /*!
     * @return radius of the circle on which random targets are generated
     */
    virtual double getRandomWalkRadius() const = 0;

    /*!
     * @return the distance at which the random targets are generated
     */
    virtual double getRandomWalkDistance() const = 0;

    /*!
     * @return jitter coeficient for random targets generation
     */
    virtual double getRandomWalkJitter() const = 0;

    /*!
     * @return the view range of the Animal
     */
    virtual double getViewRange() const = 0;

    /*!
     * @return the max distance that the animal can see
     */
    virtual double getViewDistance() const = 0;

    virtual std::string getTexture() const = 0;

    /*!
      * @brief set the position of the Animal's target
      * @param targetPosition Vec2d representing the position of the target
      */
    void setTargetPosition(Vec2d targetPosition);

    /*!
     * @return the current speed vector of the Animal
     */
    Vec2d getSpeedVector() const;

    /*!
     * @brief update the state of the Animal at the given time
     * @param dt elapsed time since the last update
     */
    void update(sf::Time dt);

    /*!
     * @brief draw the automaton on given render target
     * @param targetWindow The window on which the Animal has to be rendered
     */
    void draw(sf::RenderTarget& targetWindow) const;

    /*!
    * @brief Set the deceleration level for the Animal
    * @param deceleration Deceleretation level
    */
    void setDeceleration(Deceleration deceleration);

    /*!
     * @return the angle (in radians) of the polar coordinate of the direction vector of the animal
     */
    double getRotation() const;

    /*!
     * @brief test if a terget is in sight of the animal
     * @param target to test
     * @return true if the target is in sight of the animal
     */
    bool isTargetInSight(Vec2d const& target);

    bool isFemale() const;

protected:
    /*!
     * @brief Rotate the direction of the animal
     * @param rotation angle (in radians)
     */
    void setRotation(double angle);

private:

    /*!
     * @brief direction_ vector of the Animal
     */
    Vec2d direction_;

    /*!
     * @brief speed_ magnitude of the Animal
     */
    double speed_;

    /*!
     * @brief targetPosition_ position vector of the real target
     */
    Vec2d targetPosition_;

    /*!
     * @brief currentTarget_ position vector of the randomly generated target
     */
    Vec2d currentTarget_;

    /*!
     * @brief deceleration_ value of the Animal
     */
    double deceleration_;

    /*!
     * @brief female : true => the animal is a female, false => the animal is a male
     */
    bool female_;

    /*!
     * @brief Compute the attraction force between Animal and its target
     * @return the force vector (Vec2d)
     */
    Vec2d computeForce() const;

    /*!
     * @brief update its attribute given a force and a time
     * @param force Vec2d representing the current attraction force
     * @param dt elapsed time since the last update
     */
    void update(Vec2d force, sf::Time dt);

    /*!
     * @brief Render the view range of the Animal
     * @param targetWindow on which the view range is rendered
     */
    void drawVision(sf::RenderTarget& targetWindow) const;

    /*!
     * @brief Algorithm that randomly generate a next target
     * @return the attraction force for the generated target
     */
    Vec2d randomWalk();

    /*!
     * @brief Convert a Vec2d from the local animal centered coordinate system to the global coordinate system
     * @param local Vec2d
     * @return Vec2d corresponding to the local point in the global coordinate system
     */
    Vec2d convertToGlobalCoord(Vec2d local) const;

    /*!
     * @brief Render the current generated target on the generation circle
     * @param targetWindow window on which the target is rendered
     */
    void drawRandomWalkTarget(sf::RenderTarget& targetWindow) const;
};

#endif
