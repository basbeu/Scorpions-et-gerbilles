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
#include <Random/Uniform.hpp>

#include <math.h>

#include <SFML/Graphics.hpp>

Animal::Animal(Vec2d position)
    :CircularCollider (position, ANIMAL_RADIUS)
    ,direction_(1,0)
    ,speed_(0)
    ,targetPosition_(0,0)
    ,currentTarget_(1,0)
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
    std::list<Vec2d> targetsInsight(getAppEnv().getTargetsInSightForAnimal(this));
    Vec2d force(0,0);
    if(!targetsInsight.empty()) {
        targetPosition_ = targetsInsight.front();
        force = computeForce();
    } else {
        targetPosition_ = Vec2d(0,0);
        force = randomWalk();
    }

    update(force, dt);
}

void Animal::draw(sf::RenderTarget& targetWindow) const
{
    //targetWindow.draw(buildCircle(targetPosition_, 5, sf::Color(255,0,0)));
    sf::Texture& texture = getAppTexture(ANIMAL_TEXTURE);
    auto image_to_draw(buildSprite(getPosition(), 2*getRadius(),texture, getRotation()/DEG_TO_RAD));
    targetWindow.draw(image_to_draw);
    drawVision(targetWindow);
    if(targetPosition_ == Vec2d(0,0)) {
        drawRandomWalkTarget(targetWindow);
    }
}

void Animal::setDeceleration(Deceleration deceleration)
{
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

double Animal::getRandomWalkRadius() const
{
    return ANIMAL_RANDOM_WALK_RADIUS;
}

double Animal::getRandomWalkDistance() const
{
    return ANIMAL_RANDOM_WALK_DISTANCE;
}

double Animal::getRandomWalkJitter() const
{
    return ANIMAL_RANDOM_WALK_JITTER;
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
    Arc arc(buildArc(-getViewRange()/(DEG_TO_RAD*2), getViewRange()/(DEG_TO_RAD * 2), getViewDistance(), getPosition(), color, getRotation()/DEG_TO_RAD));
    targetWindow.draw(arc);
}

Vec2d Animal::randomWalk()
{
    Vec2d random_vec(uniform(-1.0, 1.0), uniform(-1.0, 1.0));
    currentTarget_ += random_vec * getRandomWalkJitter();
    currentTarget_  = currentTarget_.normalised() * getRandomWalkRadius();
    return convertToGlobalCoord(currentTarget_ + Vec2d(getRandomWalkDistance(), 0)) - getPosition();
}

Vec2d Animal::convertToGlobalCoord(Vec2d local) const
{
    sf::Transform matTransform;
    matTransform.translate(getPosition());
    matTransform.rotate(getRotation()/DEG_TO_RAD);
    return matTransform.transformPoint(local);
}

void Animal::drawRandomWalkTarget(sf::RenderTarget& targetWindow) const
{
    targetWindow.draw(buildAnnulus(getPosition()+getRandomWalkDistance()*direction_, getRandomWalkRadius(),sf::Color(255, 150, 0),2));
    targetWindow.draw(buildCircle(convertToGlobalCoord(currentTarget_ + Vec2d(getRandomWalkDistance(), 0)), 5, sf::Color(0,0,255)));
}
