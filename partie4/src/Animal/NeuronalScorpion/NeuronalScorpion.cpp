/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#include <Animal/NeuronalScorpion/NeuronalScorpion.hpp>
#include <Animal/NeuronalScorpion/Sensor.hpp>
#include <Utility/Utility.hpp>
#include <Application.hpp>

#include <math.h>
#include <vector>
#include <unordered_map>
#include <utility>

NeuronalScorpion::NeuronalScorpion(Vec2d position, double energyLevel, bool female)
    :Scorpion (position, energyLevel,female)
    ,targetDirection_(0,0)
    ,state_(WANDERING)
    ,stateTimer_(sf::Time::Zero)
    ,receptionTimer_(sf::Time::Zero)
{
    initSensors();
}

NeuronalScorpion::NeuronalScorpion(Vec2d position)
    :Scorpion (position)
    ,targetDirection_(0,0)
    ,state_(WANDERING)
    ,stateTimer_(sf::Time::Zero)
    ,receptionTimer_(sf::Time::Zero)
{
    initSensors();
}

NeuronalScorpion::~NeuronalScorpion()
{
    for(auto& sensor:sensors_){
        delete sensor.first;
    }

    sensors_.clear();
}

void NeuronalScorpion::initSensors()
{
    std::vector<std::pair<Sensor*, double >> sensors = {
        std::pair<Sensor*,double>(new Sensor(this), 18.0),
        std::pair<Sensor*,double>(new Sensor(this), 54.0),
        std::pair<Sensor*,double>(new Sensor(this), 90.0),
        std::pair<Sensor*,double>(new Sensor(this), 140.0),
        std::pair<Sensor*,double>(new Sensor(this), -140.0),
        std::pair<Sensor*,double>(new Sensor(this), -90.0),
        std::pair<Sensor*,double>(new Sensor(this), -54.0),
        std::pair<Sensor*,double>(new Sensor(this), -18.0)
    };

    for(size_t i = 0; i < sensors.size(); ++i){
        for(size_t j = 3 ; j <=5; ++j){
            sensors[i].first->connect(sensors[(j+i) % sensors.size()].first);
        }
    }

    sensors_ = std::unordered_map<Sensor *,double>(sensors.begin(),sensors.end());
    /*sensors_ = {
        {new Sensor(), 18.0},
        {new Sensor(), 54.0},
        {new Sensor(), 90.0},
        {new Sensor(), 140.0},
        {new Sensor(), -140.0},
        {new Sensor(), -90.0},
        {new Sensor(), -54.0},
        {new Sensor(), -18.0}
    };*/
}

/*Vec2d NeuronalScorpion::getPositionOfSensor(size_t i) const
{
    if (i > sensors_.size()-1)
        throw "Out of bound exception";
    double angle(sensors_[i].second*DEG_TO_RAD);
    return convertToGlobalCoord(getAppConfig().scorpion_sensor_radius * Vec2d(cos(angle),sin(angle)));
}*/


void NeuronalScorpion::update(sf::Time dt)
{
    OrganicEntity::update(dt);
    stateTimer_ += dt;
    bool receptive = false;
    for(auto& sensor:sensors_){
        sensor.first->update(dt);
        receptive |= sensor.first->isActive();
    }

    if(receptive){
        receptionTimer_ += dt;
        if(receptionTimer_.asSeconds() > getAppConfig().sensor_activation_duration){
            targetDirection_ = computeTargetDirection();
            receptionTimer_ = sf::Time::Zero;
            resetSensors();
        }
    }

    //Scorpion::update(dt);

    updateState(dt);

    Vec2d force(0,0);
    switch (state_) {
    case IDLE:
        break;
    case MOVING:
        force = move();
        break;
    case WANDERING:
        force = randomWalk();
        break;
    case TARGET_IN_SIGHT:
        force = computeAttractionForce();
        break;
    }
    Scorpion::update(force, dt);
    Animal::decreaseEnergyLevel(dt);
}

void NeuronalScorpion::updateState(sf::Time dt)
{
    analyzeEnvironment();
    OrganicEntity* target = getNearestEatable();

    if(target != nullptr){
        switchToState(TARGET_IN_SIGHT);
        setTargetPosition(target->getPosition());
        if(isColliding(*target)){
            target->eaten();
        }
    }else{
        switch (state_) {
        case IDLE:
            if(targetDirection_.length() > getAppConfig().scorpion_minimal_score_for_action)
                switchToState(MOVING);
            else if (stateTimer_.asSeconds() > 5)
                switchToState(WANDERING);
            break;
        case MOVING:
            if(stateTimer_.asSeconds() > 3){
                switchToState(IDLE);
                targetDirection_ = Vec2d(0,0);
            }
            break;
        case WANDERING:
            if(receptionTimer_ > sf::Time::Zero)
                switchToState(IDLE);
            break;
        case TARGET_IN_SIGHT:
            switchToState(IDLE);
            break;
        }
    }
}

Vec2d NeuronalScorpion::getPositionOfSensor(Sensor const * sensor) const
{
    double angle(sensors_.at((Sensor *)sensor)*DEG_TO_RAD);
    return convertToGlobalCoord(getAppConfig().scorpion_sensor_radius * Vec2d(cos(angle),sin(angle)));
}

void NeuronalScorpion::drawDebugState(sf::RenderTarget& targetWindow) const
{
    //for(size_t i = 0; i < sensors_.size(); ++i){
        //targetWindow.draw(buildCircle(getPositionOfSensor(i), 0.25 * getRadius(), sf::Color::Green));
    for(auto& sensor:sensors_){
        sensor.first->draw(targetWindow);
        //targetWindow.draw(buildCircle(getPositionOfSensor(sensor.first), 0.25 * getRadius(), sf::Color::Green));
        /*targetWindow.draw(buildText(std::to_string((int)sensor.second),getPositionOfSensor(sensor.first),getAppFont(),
                                    getAppConfig().default_debug_text_size,
                                    getAppConfig().debug_text_color));*/
    }
    std::string state("");
    switch (state_) {
    case IDLE:
        state = "IDLE";
        break;
    case MOVING:
        state = "MOVING";
        break;
    case WANDERING:
        state = "WANDERING";
        break;
    case TARGET_IN_SIGHT:
        state = "TARGET_IN_SIGHT";
        break;
    }
    targetWindow.draw(buildText(state,
                                convertToGlobalCoord(Vec2d(getRandomWalkDistance(), 0)),
                                getAppFont(),
                                getAppConfig().default_debug_text_size,
                                getAppConfig().debug_text_color,
                                getRotation() / DEG_TO_RAD + 90
                               ));

}

void NeuronalScorpion::switchToState(State state)
{
    state_ = state;
    stateTimer_ = sf::Time::Zero;
}

Vec2d NeuronalScorpion::computeTargetDirection() const
{
    Vec2d direction(0,0);

    for(auto& sensor:sensors_){
        direction += (getPositionOfSensor(sensor.first)-getPosition()) * sensor.first->getScore();
    }
    return direction;
}

void NeuronalScorpion::resetSensors()
{
    for(auto& sensor:sensors_){
        sensor.first->reset();
    }
}

Vec2d NeuronalScorpion::move()
{
    Vec2d force(0,0);
    double p = getAppConfig().simulation_world_size/25;
    if(abs(targetDirection_.angle() - getRotation()) > getAppConfig().scorpion_rotation_angle_precision){
        setRotation(targetDirection_.angle());
        force = computeForceDecelerate();
    }else{
        setTargetPosition(convertToGlobalCoord(Vec2d(p,0)));
        force = computeAttractionForce();
    }

    return force;
}

double NeuronalScorpion::getMaxSpeed() const
{
    double maxSpeed(getStandardMaxSpeed());

    if(state_ == TARGET_IN_SIGHT)
        maxSpeed = 3 * maxSpeed;

    return std::max(maxSpeed, Animal::getMaxSpeed());
}
