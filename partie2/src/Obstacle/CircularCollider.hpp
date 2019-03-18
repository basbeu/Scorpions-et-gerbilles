/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#ifndef CIRCULAR_COLLIDER_H
#define CIRCULAR_COLLIDER_H

#include <Utility/Vec2d.hpp>
#include <iostream>

/*!
 * @brief The CircularCollider class represents a circular body in a toric world
 */
class CircularCollider
{
public:
    /*!
     * @brief Build a CircularCollider instance
     * @param position vector of the center of the CircularCollider
     * @param radius of the CircularCollider
     */
    CircularCollider(Vec2d position, double radius);

    /*!
     * @brief CircularCollider's copy constructor
     * @param other CircularCollider to copy
     */
    CircularCollider(CircularCollider const& other);

    /*!
     * @brief Get the position of the center of the CircularCollider body
     * @return Vec2d vector representing the position of the center
     */
    Vec2d const& getPosition() const;

    /*!
     * @brief Get the radius of the CircularCollider Body
     * @return CircularCollider's radius
     */
    double getRadius() const;

    /*!
     * @brief Compute the vector from the center to the "to" vector in the toric world
     * @param vector with which the direction is computed
     * @return the vector between the center and the "to" vector
     */
    Vec2d directionTo(Vec2d const& to) const;

    /*!
     * @brief Compute the vector from the center to the center of the "to" instance in the toric world
     * @param CircularCollider with which the direction is computed
     * @return the vector between the center and the "to" instance
     */
    Vec2d directionTo(CircularCollider const& to) const;

    /*!
     * @brief Compute the distance from the center to the "to" vector in the toric world
     * @param vector with which the distance is computed
     * @return the distance between the center and the "to" vector
     */
    double distanceTo(Vec2d const& to) const;

    /*!
     * @brief Compute the distance from the center to the center of the "to" instance in the toric world
     * @param CircularCollider with which the distance is computed
     * @return the distance between the center and the "to" instance
     */
    double distanceTo(CircularCollider const& to) const;

    /*!
     * @brief Move the center of the body by a vector
     * @param dx Vector along which the current instance is moved
     */
    void move(Vec2d const& dx);

    /*!
     * @brief Check if the other CircularCollider is inside the current instance
     * @param other CircularCollider
     * @return true if other is inside the current instance
     */
    bool isCircularColliderInside(CircularCollider const& other) const;

    /*!
     * @brief Check if the other CircularCollider is colliding the curren instance
     * @param other CircularCollider
     * @return true if other is colliding the current instance
     */
    bool isColliding(CircularCollider const& other) const;

    /*!
     * @brief Check if a point is inside the current instance
     * @param point Vector point to check
     * @return true if the point is inside the current instance
     */
    bool isPointInside(Vec2d const& point) const;

    /*!
     * @brief Overload of the operator = (affectation) for CircularCollection
     * @param source to copy in the current instance
     * @return the updated current instance
     */
    CircularCollider& operator=(CircularCollider source);

    /*!
     * @brief operator += that move the current instance by a vector
     * @param dx Vector along which the current instance is moved
     * @return the updated current instance
     */
    CircularCollider& operator+=(Vec2d const& dx);

private:
    Vec2d position_;
    double radius_;

    /*!
     * @brief Apply the "clamp algorithm" to the position
     */
    void clampPosition();

    /*!
     * @brief "Clamp" a value in a interval
     * @param value to "clamp"
     * @param maxValue of the interval
     * @param minValue of the interval
     */
    void clamp(double& value, double maxValue, double minValue = 0.0);
};

/*!
 * @brief Overload the operator > for CircularCollider
 * @param body1 CircularCollider
 * @param body2 CircularCollider
 * @return true if body2 is inside body1
 */
bool operator>(CircularCollider const& body1, CircularCollider const& body2);

/*!
 * @brief Overload the operator | for CircularCollider
 * @param body1 CircularCollider
 * @param body2 CircularCollider
 * @return true if body1 and body2 are colliding
 */
bool operator|(CircularCollider const& body1, CircularCollider const& body2);

/*!
 * @brief Overload the operator > for CircularCollider and Vec2d
 * @param body1 CircularCollider
 * @param point Vec2d
 * @return true if point is inside body1
 */
bool operator>(CircularCollider const& body1, Vec2d const& point);

/*!
 * @brief Overload the operator << for std::ostream and CircularCollider
 * @param out stream on which the CircularCollider should be put
 * @param body CircularCollider
 * @return the updated out stream
 */
std::ostream& operator<<(std::ostream& out , CircularCollider const& body);

#endif
