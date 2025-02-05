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
    ,break_(sf::Time::Zero)
    ,nearestFood_(nullptr)
    ,nearestMate_(nullptr)
    ,enemies_()
    ,childrenPending_(0)
    ,gestation_(sf::Time::Zero)
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
    double maxSpeed(getStandardMaxSpeed());
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

bool Animal::isPregnant() const
{
    return gestation_ > sf::Time::Zero && childrenPending_ > 0;
}

bool Animal::isGivingBirth() const
{
    return state_ == GIVING_BIRTH;
}

void Animal::update(sf::Time dt)
{
    OrganicEntity::update(dt);
    analyzeEnvironment();
    updateState(dt);
    Vec2d force(0,0);
    switch (state_) {
    case RUNNING_AWAY:
        force = computeForceRunningAway();
        break;
    case MATING:
    case GIVING_BIRTH:
    case FEEDING:
        force = computeForceDecelerate();
        break;
    case FOOD_IN_SIGHT:
    case MATE_IN_SIGHT:
        force = computeAttractionForce();
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

void Animal::setRotation(double angle)
{
    direction_.x = cos(angle);
    direction_.y = sin(angle);
}

Vec2d Animal::convertToGlobalCoord(Vec2d local) const
{
    sf::Transform matTransform;
    matTransform.translate(getPosition());
    matTransform.rotate(getRotation()/DEG_TO_RAD);
    return matTransform.transformPoint(local);
}

sf::Time Animal::getMatingTime() const
{
    return sf::seconds(getAppConfig().animal_mating_time);
}

void Animal::updateState(sf::Time dt)
{
    if(break_ < sf::Time::Zero) {
        state_ = WANDERING;
        break_ = sf::Time::Zero;
    }

    if(state_ == FEEDING || state_ == MATING || isGivingBirth()) {
        break_ -= dt;
    } else if(!enemies_.empty()) {
        state_ = RUNNING_AWAY;
    } else if(nearestMate_ != nullptr) {
        state_ = MATE_IN_SIGHT;
        targetPosition_ = nearestMate_->getPosition();
        if(isColliding(*nearestMate_)) {
            state_ = MATING;
            break_ = getMatingTime();
            meet(nearestMate_);
            ((Animal*)nearestMate_)->state_ = MATING;
            ((Animal*)nearestMate_)->break_ = getMatingTime();
            ((Animal*)nearestMate_)->meet(this);
        }
    } else if(nearestFood_ != nullptr) {
        state_ = FOOD_IN_SIGHT;
        targetPosition_ = nearestFood_->getPosition();
        if(isColliding(*nearestFood_)) {
            state_= FEEDING;
            break_ = getFeedingBreak();
            OrganicEntity::increaseEnergyLevel(getFeedingEfficiency() * nearestFood_->getEnergyLevel());
            nearestFood_->eaten();
        }
    } else {
        state_ = WANDERING;
        targetPosition_ = Vec2d(0,0);
    }

    if(isPregnant()) {
        gestation_ -= dt;

        if(gestation_ <= sf::Time::Zero) {
            state_ = GIVING_BIRTH;
            break_ = getGivingBirthBreak();
            makeChildren();
            childrenPending_ = 0;
            gestation_ = sf::Time::Zero;
        }
    }
}

void Animal::analyzeEnvironment()
{
    std::list<OrganicEntity*> entitiesInSight(getAppEnv().getEntitiesInSightForAnimal(this));
    Vec2d maxVector(std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
    Vec2d targetFood(maxVector);
    Vec2d targetMate(maxVector);
    nearestFood_ = nullptr;
    nearestMate_ = nullptr;
    enemies_.clear();
    for(auto& entity:entitiesInSight) {
        if(eatable(entity) && entity->distanceTo(getPosition()) < distanceTo(targetFood)) {
            targetFood = entity->getPosition();
            nearestFood_ = entity;
        } else if(matable(entity) && entity->matable(this) && entity->distanceTo(getPosition()) < distanceTo(targetMate)) {
            targetMate = entity->getPosition();
            nearestMate_ = entity;
        }
        if(entity->eatable(this))
            enemies_.push_back(entity);
    }
}


OrganicEntity* Animal::getNearestEatable() const
{
    return nearestFood_;
}

void Animal::update(Vec2d force, sf::Time dt)
{
    Vec2d acceleration = force / getMass();
    Vec2d newSpeed = getSpeedVector() + acceleration * dt.asSeconds();
    direction_ = newSpeed.normalised();
    speed_ = std::min(newSpeed.length(), getMaxSpeed());
    move(newSpeed * dt.asSeconds());
}


Vec2d Animal::computeAttractionForce() const
{
    Vec2d toTarget(targetPosition_ - getPosition());
    double speed(std::min(toTarget.length() / deceleration_, getMaxSpeed()));

    return toTarget.normalised() * speed - getSpeedVector();
}

Vec2d Animal::computeForceDecelerate() //const
{
    if(isEqual(speed_, 0.0, 0.5))
        return Vec2d(0,0);
    //return computeForce(convertToGlobalCoord(Vec2d(-1,0)));
    targetPosition_ = convertToGlobalCoord(Vec2d(-1,0));
    return computeAttractionForce();
}

Vec2d Animal::computeForceRunningAway() const
{
    Vec2d force(0,0);
    double delta1(500.0);
    double delta2(1.2);
    for(auto& enemy:enemies_) {
        if(enemy != nullptr) {
            Vec2d dir(enemy->getPosition()-getPosition());
            force += delta1*dir/pow(dir.length(),delta2);
        }
    }
    return -force;
}

Vec2d Animal::randomWalk()
{
    Vec2d random_vec(uniform(-1.0, 1.0), uniform(-1.0, 1.0));
    currentTarget_ += random_vec * getRandomWalkJitter();
    currentTarget_  = currentTarget_.normalised() * getRandomWalkRadius();
    return convertToGlobalCoord(currentTarget_ + Vec2d(getRandomWalkDistance(), 0)) - getPosition();
}

void Animal::meet(OrganicEntity * entity)
{
    if(matable(entity) && entity->matable(this)) {
        Animal* female = (Animal*)entity;
        Animal* male = this;
        if(isFemale()) {
            female = this;
            male = (Animal*)entity;
        }
        female->childrenPending_ = uniform(female->getMinChildren(), female->getMaxChildren());
        female->OrganicEntity::decreaseEnergyLevel(childrenPending_*female->getEnergyLossFemalePerChild());
        male->OrganicEntity::decreaseEnergyLevel(male->getEnergyLossMatingMale());
        female->gestation_ = sf::seconds(female->getGestationTime());
    }
}

void Animal::makeChildren() const
{
    for(int i = 0; i < childrenPending_; ++i) {
        getAppEnv().addEntity(giveBirth());
    }
}

void Animal::drawRandomWalkTarget(sf::RenderTarget& targetWindow) const
{
    targetWindow.draw(buildAnnulus(getPosition()+getRandomWalkDistance()*direction_, getRandomWalkRadius(),sf::Color(255, 150, 0),2));
    targetWindow.draw(buildCircle(convertToGlobalCoord(currentTarget_ + Vec2d(getRandomWalkDistance(), 0)), 5, sf::Color(0,0,255)));
}


void Animal::drawVision(sf::RenderTarget& targetWindow) const
{
    sf::Color color = sf::Color::Black;
    color.a = 16; // light, transparent grey
    Arc arc(buildArc(-getViewRange()/(DEG_TO_RAD*2), getViewRange()/(DEG_TO_RAD * 2), getViewDistance(), getPosition(), color, getRotation()/DEG_TO_RAD));
    targetWindow.draw(arc);
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

    debugText += "\n age : "+std::to_string(getAge());
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
    if(isPregnant())
        targetWindow.draw(buildAnnulus(getPosition(), getRadius(),sf::Color::Magenta,2));

}

void Animal::decreaseEnergyLevel(sf::Time dt)
{
    double loss = getAppConfig().animal_base_energy_consumption + speed_ * getEnergyLossFactor() * dt.asSeconds();
    OrganicEntity::decreaseEnergyLevel(loss);
}

