/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#ifndef CHASINGAUTOMATON_HPP
#define CHASINGAUTOMATON_HPP

#include <Obstacle/CircularCollider.hpp>
#include <Utility/Vec2d.hpp>

#include <SFML/Graphics.hpp>

/*!
 * @brief The ChasingAutomaton class represent an automaton chasing a target
 */
class ChasingAutomaton : public CircularCollider
{
public:
    /*!
     * @brief The Deceleration enum represent the differents magnitude that a ChasingAutomaton can be set
     */
    enum Deceleration{
        DECELERATION_STRONG,
        DECELERATION_MEDIUM,
        DECELERATION_WEAK
    };

    /*!
     * @brief ChasingAutomaton build a a ChasinAutomaton
     * @param position Vec2d representing the initial position
     */
    ChasingAutomaton(Vec2d position);

    /*!
     * @brief Destroy a ChasingAutomaton
     */
    ~ChasingAutomaton();

    /*!
     * @return the max speed of the ChasingAutomaton
     */
    double getStandardMaxSpeed() const;

    /*!
     * @return the mass of the ChasingAutomaton
     */
    double getMass() const;

    /*!
     * @brief set the position of the ChasingAutomaton's target
     * @param targetPosition Vec2d representing the position of the target
     */
    void setTargetPosition(Vec2d targetPosition);

    /*!
     * @return the current speed vector of the ChasingAutomaton
     */
    Vec2d getSpeedVector() const;

    /*!
     * @brief update the state of the ChasingAutomaton at the given time
     * @param dt elapsed time since the last update
     */
    void update(sf::Time dt);

    /*!
     * @brief draw the automaton on given render target
     * @param targetWindow The window on which the ChasingAutomaton has to be rendered
     */
    void draw(sf::RenderTarget& targetWindow) const;

    /*!
     * @brief Set the deceleration level for the ChasingAutomaton
     * @param deceleration Deceleretation level
     */
    void setDeceleration(Deceleration deceleration);

private:
    /*!
     * @brief direction_ vector of the ChasingAutomaton
     */
    Vec2d direction_;

    /*!
     * @brief speed_ magnitude of the ChasingAutomaton
     */
    double speed_;

    /*!
     * @brief targetPosition_ target position vector of the ChasingAutomaton
     */
    Vec2d targetPosition_;

    /*!
     * @brief deceleration_ value of the ChasingAutomaton
     */
    double deceleration_;

    /*!
     * @brief Compute the attraction force between ChasingAutomaton and its target
     * @return the force vector (Vec2d)
     */
    Vec2d computeForce() const;

    /*!
     * @brief update its attribute given a force and a time
     * @param force Vec2d representing the current attraction force
     * @param dt elapsed time since the last update
     */
    void update(Vec2d force, sf::Time dt);
};

#endif // CHASINGAUTOMATON_HPP
