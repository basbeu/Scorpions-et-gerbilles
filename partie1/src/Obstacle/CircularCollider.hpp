#ifndef CIRCULAR_COLLIDER_H
#define CIRCULAR_COLLIDER_H

#include <iostream>
#include <Utility/Vec2d.hpp>

class CircularCollider{
public:
    CircularCollider(Vec2d, double);
    CircularCollider(CircularCollider const&) = default;
    Vec2d getPosition();
    Vec2d getRadius();
    Vec2d directionTo(Vec2d);
    Vec2d directionTo(CircularCollider);
    double distanceTo(Vec2d);
    double distanceTo(CircularCollider);
    void move(Vec2d);
    bool isCircularColliderInside(CircularCollider);
    bool isColliding(CircularCollider);
    bool isPointInside(Vec2d);

    CircularCollider& operator+=(Vec2d const&);
    bool operator>(CircularCollider);
    bool operator|(CircularCollider);
    bool operator>(Vec2d);
private:
    Vec2d center;
    double radius;
};
std::ostream& operator<<(std::ostream& ,const CircularCollider& );

#endif
