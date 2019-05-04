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

Animal::Animal(Vec2d position, double size, double energyLevel, bool female)
    :OrganicEntity (position, size, energyLevel)
    ,direction_(1,0)
    ,speed_(0)
    ,targetPosition_(0,0)
    ,currentTarget_(1,0)
    ,female_(female)
    ,state_(WANDERING)
    ,feedingBreak_(sf::Time::Zero)
{
    setDeceleration(DECELERATION_MEDIUM);
}

Animal::~Animal()
{

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
    OrganicEntity::update(dt);
    updateState(dt);
    Vec2d force(0,0);
    switch (state_) {
    case FEEDING:
        force = computeForceFeeding();
        break;
    case FOOD_IN_SIGHT:
        force = computeForce(targetPosition_);
        break;
    case WANDERING:
        force = randomWalk();
        break;
    default:
        break;
    }
    update(force, dt);
    decreaseEnergyLevel(dt);
}

void Animal::draw(sf::RenderTarget& targetWindow) const
{
    //targetWindow.draw(buildCircle(targetPosition_, 5, sf::Color(255,0,0)));
    sf::Texture& texture = getAppTexture(getTexture());
    auto image_to_draw(buildSprite(getPosition(), 2*getRadius(),texture, getRotation()/DEG_TO_RAD));
    targetWindow.draw(image_to_draw);

    if(isDebugOn()) {
        drawVision(targetWindow);
        if(targetPosition_ == Vec2d(0,0)) {
            drawRandomWalkTarget(targetWindow);
        }
        drawDebugState(targetWindow);
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

bool Animal::isFemale() const
{
    return female_;
}

double Animal::getMaxSpeed() const
{
    double maxSpeed = getStandardMaxSpeed();
    if(getEnergyLevel() < getAppConfig().animal_tired_threshold)
        maxSpeed = getTiredMaxSpeed();

    switch (state_) {
    case FOOD_IN_SIGHT:
        return 3 * maxSpeed;
    case MATE_IN_SIGHT:
        return 2 * maxSpeed;
    case RUNNING_AWAY:
        return 4 * maxSpeed;
    default:
        return maxSpeed;
    }
}

bool Animal::isPregnant() const{
    return false;
}

bool Animal::isGivingBirth() const
{
    return state_ == GIVING_BIRTH;
}

void Animal::setRotation(double angle)
{
    direction_.x = cos(angle);
    direction_.y = sin(angle);
}

Vec2d Animal::computeForce(Vec2d target) const
{
    Vec2d toTarget(target - getPosition());
    double speed(std::min(toTarget.length() / deceleration_, getMaxSpeed()));

    return toTarget.normalised() * speed - getSpeedVector();
}

void Animal::update(Vec2d force, sf::Time dt)
{
    Vec2d acceleration = force / getMass();
    Vec2d newSpeed = getSpeedVector() + acceleration * dt.asSeconds();
    direction_ = newSpeed.normalised();
    speed_ = std::min(newSpeed.length(), getMaxSpeed());
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

void Animal::updateState(sf::Time dt)
{
    std::list<OrganicEntity*> entitiesInSight(getAppEnv().getEntitiesInSightForAnimal(this));
    Vec2d maxVector(std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
    Vec2d target(maxVector);
    OrganicEntity* targetEntity(nullptr);
    for(auto& entity:entitiesInSight) {
        if(eatable(entity) && entity->distanceTo(getPosition()) < distanceTo(target)){
            target = entity->getPosition();
            targetEntity = entity;
        }
    }

    if(feedingBreak_ <= sf::Time::Zero){
        state_ = WANDERING;
        feedingBreak_ = sf::Time::Zero;
    }

    if(state_ == FEEDING){
        feedingBreak_ -= dt;
    }else if(target != maxVector){
        state_ = FOOD_IN_SIGHT;
        targetPosition_ = target;
        if(isColliding(*targetEntity)){
            state_= FEEDING;
            feedingBreak_ = getFeedingBreak();
            OrganicEntity::increaseEnergyLevel(getFeedingEfficiency() * targetEntity->getEnergyLevel());
            targetEntity->eaten();
        }
    }else{
        state_ = WANDERING;
        targetPosition_ = Vec2d(0,0);
    }
}

void Animal::drawDebugState(sf::RenderTarget& targetWindow) const
{
    std::string debugText("");
    switch (state_) {
    case FOOD_IN_SIGHT:
        debugText = "FOOD_IN_SIGHT";
        break;
    case FEEDING:
        debugText = "FEEDING";
        break;
    case RUNNING_AWAY:
        debugText = "RUNNING_AWAY";
        break;
    case MATE_IN_SIGHT:
        debugText = "MATE_IN_SIGHT";
        break;
    case MATING:
        debugText = "MATING";
        break;
    case GIVING_BIRTH:
        debugText = "GIVING_BIRTH";
        break;
    case WANDERING:
        debugText = "WANDERING";
        break;
    }

    if(isFemale())
        debugText += "\nFemale";
    else
        debugText += "\nMale";

    debugText += "\n" ;
    debugText += std::to_string(getEnergyLevel());
    targetWindow.draw(buildText(debugText,
                                convertToGlobalCoord(Vec2d(getRandomWalkDistance(), 0)),
                                getAppFont(),
                                getAppConfig().default_debug_text_size,
                                getAppConfig().debug_text_color,
                                getRotation() / DEG_TO_RAD + 90
                               ));
}

void Animal::decreaseEnergyLevel(sf::Time dt)
{
    double loss = getAppConfig().animal_base_energy_consumption + speed_ * getEnergyLossFactor() * dt.asSeconds();
    OrganicEntity::decreaseEnergyLevel(loss);
}

Vec2d Animal::computeForceFeeding() const
{
    if(isEqual(speed_, 0.0, 0.5))
        return Vec2d(0,0);
    return computeForce(convertToGlobalCoord(Vec2d(-1,0)));
}
