/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#include <Animal/Animal.hpp>
#include <Obstacle/CircularCollider.hpp>
#include <Utility/Constants.hpp>
#include <Utility/Utility.hpp>
#include <Utility/Vec2d.hpp>
#include <Application.hpp>

#include <math.h>

#include <SFML/Graphics.hpp>

Animal::Animal(Vec2d position)
:CircularCollider (position, ANIMAL_RADIUS)
,direction_(1,0)
,speed_(0)
,targetPosition_(0,0)
{
    setDeceleration(DECELERATION_MEDIUM);
}

Animal::~Animal()
{

}

double Animal::getStandardMaxSpeed() const
{
    return ANIMAL_MAX_SPEED;
}

double Animal::getMass() const
{
    return ANIMAL_MASS;
}

void Animal::setTargetPosition(Vec2d targetPosition)
{
    targetPosition_ = targetPosition;
}

Vec2d Animal::getSpeedVector() const
{
    return direction_*speed_;
}

void Animal::update(sf::Time dt)
{
    update(computeForce(), dt);
}

void Animal::draw(sf::RenderTarget& targetWindow) const
{
    targetWindow.draw(buildCircle(targetPosition_, 5, sf::Color(255,0,0)));
    sf::Texture& texture = getAppTexture(GHOST_TEXTURE);
    auto image_to_draw(buildSprite(getPosition(), 2*getRadius(),texture));
    targetWindow.draw(image_to_draw);
    drawVision(targetWindow);
}

void Animal::setDeceleration(Deceleration deceleration){
    switch (deceleration) {
        case DECELERATION_STRONG:
            deceleration_ = 0.9;
            break;
        case DECELERATION_MEDIUM:
            deceleration_ = 0.6;
            break;
        case DECELERATION_WEAK:
            deceleration_ = 0.3;
            break;
    }
}

double Animal::getViewRange() const
{
    return ANIMAL_VIEW_RANGE;
}

double Animal::getViewDistance() const
{
    return ANIMAL_VIEW_DISTANCE;
}

double Animal::getRotation() const
{
    return direction_.angle();
}

bool Animal::isTargetInSight(Vec2d const& target)
{
    Vec2d d = target - getPosition();

    return isEqual(d.lengthSquared(), 0.0) ||
           (d.lengthSquared() <= getViewDistance()*getViewDistance() && direction_.dot(d.normalised()) >= cos((getViewRange() + 0.001)/2));
}

void Animal::setRotation(double angle)
{
   direction_.x = cos(angle);
   direction_.y = sin(angle);
}

Vec2d Animal::computeForce() const
{
    Vec2d toTarget(targetPosition_ - getPosition());
    double speed(std::min(toTarget.length() / deceleration_, getStandardMaxSpeed()));

    return toTarget.normalised() * speed - getSpeedVector();
}

void Animal::update(Vec2d force, sf::Time dt)
{
    Vec2d acceleration = force / getMass();
    Vec2d newSpeed = getSpeedVector() + acceleration * dt.asSeconds();
    direction_ = newSpeed.normalised();
    speed_ = std::min(newSpeed.length(), getStandardMaxSpeed());
    move(newSpeed * dt.asSeconds());
}

void Animal::drawVision(sf::RenderTarget& targetWindow) const
{
    sf::Color color = sf::Color::Black;
    color.a = 16; // light, transparent grey
    Arc arc(buildArc(-getViewRange()/(DEG_TO_RAD*2), getViewRange()/(DEG_TO_RAD * 2), getViewDistance(), getPosition(), color, direction_.angle()/DEG_TO_RAD));
    targetWindow.draw(arc);
}
