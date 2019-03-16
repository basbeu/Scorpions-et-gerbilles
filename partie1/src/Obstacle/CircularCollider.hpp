/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#ifndef CIRCULAR_COLLIDER_H
#define CIRCULAR_COLLIDER_H

#include <iostream>
#include <Utility/Vec2d.hpp>

class CircularCollider
{
public:
    /*!
     * @brief CircularCollider
     * @param position
     * @param radius
     */
    CircularCollider(Vec2d position, double radius);

    /*!
     * \brief CircularCollider
     * \param other
     */
    CircularCollider(CircularCollider const& other);

    /*!
     * @brief getPosition
     * @return
     */
    Vec2d const& getPosition() const;

    /*!
     * \brief getRadius
     * \return
     */
    double getRadius() const;

    /*!
     * \brief directionTo
     * \param to
     * \return
     */
    Vec2d directionTo(Vec2d const& to) const;

    /*!
     * \brief directionTo
     * \param to
     * \return
     */
    Vec2d directionTo(CircularCollider const& to) const;

    /*!
     * \brief distanceTo
     * \param to
     * \return
     */
    double distanceTo(Vec2d const& to) const;

    /*!
     * \brief distanceTo
     * \param to
     * \return
     */
    double distanceTo(CircularCollider const& to) const;

    /*!
     * \brief move
     * \param dx
     */
    void move(Vec2d const& dx);

    /*!
     * \brief isCircularColliderInside
     * \param other
     * \return
     */
    bool isCircularColliderInside(CircularCollider const& other) const;

    /*!
     * \brief isColliding
     * \param other
     * \return
     */
    bool isColliding(CircularCollider const& other) const;

    /*!
     * \brief isPointInside
     * \param point
     * \return
     */
    bool isPointInside(Vec2d const& point) const;

    /*!
     * \brief operator =
     * \param source
     * \return
     */
    CircularCollider& operator=(CircularCollider source);

    /*!
     * \brief operator +=
     * \param dx
     * \return
     */
    CircularCollider& operator+=(Vec2d const& dx);

private:
    Vec2d position_;
    double radius_;

    void clampPosition();
    void clamp(double& value, double maxValue, double minValue = 0.0);
};

/*!
 * \brief operator >
 * \param other
 * \return
 */
bool operator>(CircularCollider const& body1, CircularCollider const& body2);

/*!
 * \brief operator |
 * \param other
 * \return
 */
bool operator|(CircularCollider const& body1, CircularCollider const& body2);

/*!
 * \brief operator >
 * \param other
 * \return
 */
bool operator>(CircularCollider const& body1, Vec2d const& point);

/*!
 * \brief operator <<
 * \param out
 * \param body
 * \return
 */
std::ostream& operator<<(std::ostream& out , CircularCollider const& body);

#endif
