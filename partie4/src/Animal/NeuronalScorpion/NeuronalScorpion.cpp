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
{
    initSensors();
}

NeuronalScorpion::NeuronalScorpion(Vec2d position)
    :Scorpion (position)
    ,targetDirection_(0,0)
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
    for(auto& sensor:sensors_){
        sensor.first->update(dt);
    }
    Scorpion::update(dt);
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
}
