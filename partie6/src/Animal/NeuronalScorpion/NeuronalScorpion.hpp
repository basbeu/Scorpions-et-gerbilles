/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#ifndef NEURONALSCORPION_H
#define NEURONALSCORPION_H

#include <Animal/Scorpion.hpp>
#include <Animal/NeuronalScorpion/Sensor.hpp>
#include <Utility/Vec2d.hpp>

#include <unordered_map>
#include <utility>
#include <SFML/Graphics.hpp>

/*!
 * @brief The NeuronalScorpion class represents a specialized scorpion used during a Neuronal simulation.
 */
class NeuronalScorpion:public Scorpion
{
public:
    /*!
     * @brief build an instance of NeuronalScorpion
     * @param position Vec2d representing the initial position
     * @param energyLevel initial level of the scorpion
     * @param female gender of the Scorpion instance : true => female, false => male
     */
    NeuronalScorpion(Vec2d const& position, double energyLevel, bool female);

    /*!
     * @brief build an instance of NeuronalScorpion
     * @param initial position of the scorpion (Vec2d)
     */
    NeuronalScorpion(Vec2d const& position);

    /*!
     * @brief destroy a NeuronalScorpion
     */
    virtual ~NeuronalScorpion() override;

    // see Updatable.hpp
    virtual void update(sf::Time dt) override;

    /*!
     * @brief get the position in the global coordinate system of particular sensor
     * @param sensor belonging to the instance
     * @return a Vec2d representing the sensor's position
     */
    Vec2d getPositionOfSensor(Sensor const * sensor) const;
private:
    /*!
     * @brief The State enum represents the differents internals state of the NeuronalScorpion
     */
    enum State {
        IDLE,
        WANDERING,
        TARGET_IN_SIGHT,
        MOVING
    };

    /*!
     * @brief the collections of NeuronalScorpion's sensors with their position angle
     */
    std::unordered_map<Sensor *, double> sensors_;

    /*!
     * @brief direction of the potential target, this direction is estimated with the sensors
     */
    Vec2d targetDirection_;

    /*!
     * @brief current internal state of the NeuronalScorpion
     */
    State state_;

    /*!
     * @brief elapsed time since last state transition
     */
    sf::Time stateTimer_;

    /*!
     * @brief elapsed time for the current activation
     */
    sf::Time receptionTimer_;

    /*
     * overriden methods
     */
    virtual void updateState(sf::Time dt) override;
    virtual void drawDebugState(sf::RenderTarget& targetWindow) const override;
    virtual double getMaxSpeed() const override;


    /*!
     * @brief help method to initialize the sensors and store them in the collection
     */
    void initSensors();

    /*!
     * @brief switch the internal state to the next one
     * @param next state
     */
    void switchToState(State state);

    /*!
     * @brief estimate the direction given by the sensors
     * @return Vec2d pointing to the estimated direction
     */
    Vec2d computeTargetDirection() const;

    /*!
     * @brief reset all sensors belonging to the NeuronalScorpions
     */
    void resetSensors();

    /*!
     * @brief Compute the force applied to the NeuronalScorpions during the Moving state
     * @return force vector (Vec2d)
     */
    Vec2d move();


};

#endif // NEURONALSCORPION_H
