/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#include <Obstacle/CircularCollider.hpp>
#include <Utility/Vec2d.hpp>

#include <Application.hpp>

//#include <utility>
#include <limits>

CircularCollider::CircularCollider(Vec2d position, double radius)
:position_(position)
,radius_(radius)
{
    if(radius < 0.0){
        throw std::string("Radius cannot be less than 0");
    }
    clampPosition();
}

CircularCollider::CircularCollider(CircularCollider const& other)
:CircularCollider(other.position_, other.radius_)
{

}

Vec2d const& CircularCollider::getPosition() const
{
    return position_;
}

double CircularCollider::getRadius() const
{
    return radius_;
}

Vec2d CircularCollider::directionTo(Vec2d const& to) const
{
    double worldSize = getAppConfig().simulation_world_size;
    auto width  = worldSize;
    auto height = worldSize;

    Vec2d h(0, height);
    Vec2d w(width, 0);
    Vec2d min(0 , 0);
    double dMin(std::numeric_limits<double>::max());

    for(int i = -1; i <= 1; ++i){
        for(int j = -1; j <= 1; ++j){
            Vec2d temp(to + i * h + j * w);
            double dTemp = distance(temp, position_);

            if(dTemp < dMin){
                min = temp;
                dMin = dTemp;
            }
        }
    }
    return min-position_;
}

Vec2d CircularCollider::directionTo(CircularCollider const& to) const
{
    return directionTo(to.position_);
}

double CircularCollider::distanceTo(Vec2d const& to) const
{
    return directionTo(to).length();
}

double CircularCollider::distanceTo(CircularCollider const& to) const
{
    return distanceTo(to.position_);
}

void CircularCollider::move(Vec2d const& dx)
{
    position_ += dx;
    clampPosition();
}

bool CircularCollider::isCircularColliderInside(CircularCollider const& other) const
{
    return other.radius_ <= radius_ and distanceTo(other) <= radius_ - other.radius_;
}

bool CircularCollider::isColliding(CircularCollider const& other) const
{
    return distanceTo(other) <= radius_ + other.radius_;
}

bool CircularCollider::isPointInside(Vec2d const& point) const
{
    return distanceTo(point) <= radius_;
}

CircularCollider& CircularCollider::operator=(CircularCollider source){
    //swap(*this, source);
    position_ = source.position_;
    radius_ = source.radius_;
    return *this;
}

CircularCollider& CircularCollider::operator+=(Vec2d const& dx)
{
    move(dx);
    return *this;
}

void CircularCollider::clampPosition()
{
    double worldSize = getAppConfig().simulation_world_size;
    auto width  = worldSize;
    auto height = worldSize;

    clamp(position_.x, width);
    clamp(position_.y, height);
}

void CircularCollider::clamp(double& value, double maxValue, double minValue)
{
    while(value < minValue){
        value += maxValue;
    }

    while(value > maxValue){
        value -= maxValue;
    }
}

bool operator>(CircularCollider const& body1, CircularCollider const& body2)
{
    return body1.isCircularColliderInside(body2);
}

bool operator|(CircularCollider const& body1, CircularCollider const& body2)
{
    return body1.isColliding(body2);
}

bool operator>(CircularCollider const& body1, Vec2d const& point)
{
    return body1.isPointInside(point);
}

std::ostream& operator<<(std::ostream& out , CircularCollider const& body)
{
    out << "CircularCollider: position = " << body.getPosition() << " radius " << body.getRadius();
    return out;
}
