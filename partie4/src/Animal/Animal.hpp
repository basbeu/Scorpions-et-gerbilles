/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#ifndef ANIMAL_H
#define ANIMAL_H
#include <Environment/OrganicEntity.hpp>
#include <Utility/Vec2d.hpp>

#include <list>
#include <SFML/Graphics.hpp>

/*!
 * @brief The Animal class is an abstract class that represents an OrganicEntity of type animal.
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
     * @brief Animal build an animal
     * @param position Vec2d representing the initial position
     * @param size double representing the diameter of the animal
     * @param energyLevel initial level of the animal
     * @param female gender of the animal instance : true => female, false => male
     */
    Animal(Vec2d position, double size, double energyLevel, bool female);

    /*!
     * @brief Destroy a Animal
     */
    virtual ~Animal() override;

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
    * @brief Set the deceleration level for the Animal
    * @param deceleration Deceleretation level
    */
    void setDeceleration(Deceleration deceleration);

    /*!
     * @return the angle (in radians) of the polar coordinate of the direction vector of the animal
     */
    double getRotation() const;

    /*!
     * @brief test if a target is in sight of the animal
     * @param target to test
     * @return true if the target is in sight of the animal
     */
    bool isTargetInSight(Vec2d const& target);

    /*!
     * @brief test if the animal is a female or male
     * @return true if the animal is a female, false otherwise
     */
    bool isFemale() const;

    /*!
     * @brief get the max speed depending on the current state of the animal
     * @return the current max speed
     */
    double getMaxSpeed() const;

    /*!
     * @brief test if the animal is pregnant
     * @return true if the animal is pregnant
     */
    bool isPregnant() const;

    /*!
     * @brief test if the animal is giving birth
     * @return true if the animal is giving birth
     */
    bool isGivingBirth() const;

    /*!
     * @brief update the state of the Animal at the given time
     * @param dt elapsed time since the last update
     */
    virtual void update(sf::Time dt) override;

    /*!
     * @brief draw the automaton on given render target
     * @param targetWindow The window on which the Animal has to be rendered
     */
    virtual void draw(sf::RenderTarget& targetWindow) const override;

protected:
    /*!
     * @brief analyse the environment of the animal. This methods analyse all OrganicEntities that are visible for the animal
     */
    void analyzeEnvironment();

    OrganicEntity* getNearestEatable() const;

    /*!
     * @brief update its attribute given a force and a time
     * @param force Vec2d representing the current attraction force
     * @param dt elapsed time since the last update
     */
    void update(Vec2d force, sf::Time dt);

    /*!
     * @brief Compute the attraction force between Animal and its target
     * @return the force vector (Vec2d)
     */
    Vec2d computeAttractionForce() const;

    /*!
     * @brief Compute the force that will stop the animal
     * @return the force vector (Vec2d)
     */
    Vec2d computeForceDecelerate() /*const*/;

    /*!
     * @brief Algorithm that randomly generate a next target
     * @return the attraction force for the generated target
     */
    Vec2d randomWalk();

    /*!
     * @brief Rotate the direction of the animal
     * @param rotation angle (in radians)
     */
    void setRotation(double angle);

    /*!
     * @brief Convert a Vec2d from the local animal centered coordinate system to the global coordinate system
     * @param local Vec2d
     * @return Vec2d corresponding to the local point in the global coordinate system
     */
    Vec2d convertToGlobalCoord(Vec2d local) const;

private:
    /*!
     * @brief The State enum represents the differents internal states of an animal
     */
    enum State {
        FOOD_IN_SIGHT, // nourriture en vue
        FEEDING,       // en train de manger (là en principe il arrête de se déplacer)
        RUNNING_AWAY,  // en fuite
        MATE_IN_SIGHT, // partenaire en vue
        MATING,        // vie privée (rencontre avec un partenaire!)
        GIVING_BIRTH,  // donne naissance
        WANDERING      // déambule
    };

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
     * @brief female_ : true => the animal is a female, false => the animal is a male
     */
    bool female_;

    /*!
     * @brief state_ represents the animal's internal state
     */
    State state_;

    /*!
     * @brief break_ : counter for break time, count the break elapsing time, when the animal is not in a break the value is sf::Time::zero
     */
    sf::Time break_;

    /*!
     * @brief nearestFood_ points to the nearest entity eatable by the animal
     */
    OrganicEntity* nearestFood_;

    /*!
     * @brief nearestMate_ points to the nearest entity matable with the animal
     */
    OrganicEntity* nearestMate_;

    /*!
     * @brief enemies_ registers predators in the field of view
     */
    std::list<OrganicEntity*> enemies_;

    /*!
     * @brief childrenPending_ counts the future number of child, when the animal is not pregnant the value is 0
     */
    int childrenPending_;

    /*!
     * @brief gestation_ counts the elapsing time before that the animal gives birth
     */
    sf::Time gestation_;

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

    /*!
     * @return the path of the texture of the animal
     */
    virtual std::string getTexture() const = 0;

    /*!
     * @return the speed when the animal is below the tired threshold
     */
    virtual double getTiredMaxSpeed() const = 0;

    /*!
     * @return the amount of time that the animal breaks after feeding
     */
    virtual sf::Time getFeedingBreak() const = 0;

    /*!
     * @return the ratio of energy that the animal get from the prey
     */
    virtual double getFeedingEfficiency() const = 0;

    /*!
     * @return the minimum amount of energy required to mate
     */
    virtual double getMinimumMatingEnergy() const = 0;

    /*!
     * @return the minimum age required to mate
     */
    virtual double getMinAgeMating()const = 0;

    /*!
     * @return the energy loss factor of the animal
     */
    virtual double getEnergyLossFactor() const = 0;

    /*!
     * @return the minimum number of children that the animal can give birth
     */
    virtual int getMinChildren() const = 0;

    /*!
     * @return the maximum number of children that the animal can give birth
     */
    virtual int getMaxChildren() const = 0;

    /*!
     * @return the amount of energy that is lost when the female give birth to a child
     */
    virtual double getEnergyLossFemalePerChild() const = 0;

    /*!
     * @return the amount of energy that is lost when a male mates
     */
    virtual double getEnergyLossMatingMale() const = 0;

    /*!
     * @return the gestation duration
     */
    virtual double getGestationTime() const = 0;

    /*!
     * @return the amount of time that the break last after the animal gives birth
     */
    virtual sf::Time getGivingBirthBreak() const = 0;

    /*!
     * @return a new Animal representing the child
     */
    virtual Animal* giveBirth() const = 0;

    /*!
     * @return the amount of time during which the animals mate
     */
    virtual sf::Time getMatingTime() const;

    /*!
     * @brief update the internal state of the animal
     * @param dt elapsed time since the last update
     */
    virtual void updateState(sf::Time dt);

    /*!
     * @brief Compute the force with which the animal runs away when he see predators
     * @return the force vector (Vec2d)
     */
    Vec2d computeForceRunningAway() const;

    /*!
     * @brief manage the meeting with the entity
     * @param entity that the animal meet, nothing is done if entity is from a different type than this
     */
    void meet(OrganicEntity * entity);

    /*!
     * @brief makeChildren
     */
    void makeChildren() const;

    /*!
     * @brief Render the current generated target on the generation circle
     * @param targetWindow window on which the target is rendered
     */
    void drawRandomWalkTarget(sf::RenderTarget& targetWindow) const;


    /*!
     * @brief Render the view range of the Animal
     * @param targetWindow on which the view range is rendered
     */
    void drawVision(sf::RenderTarget& targetWindow) const;

    /*!
     * @brief Draw text that shows the current internal state of the animal
     * @param targetWindow on which the text is rendered
     */
    virtual void drawDebugState(sf::RenderTarget& targetWindow) const;

    /*!
     * @brief Decrease the energy level of the animal for the elapsed time
     * @param dt elapsed time since the last update
     */
    void decreaseEnergyLevel(sf::Time dt);
};

#endif
