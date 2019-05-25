/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#include <Animal/NeuronalScorpion/Sensor.hpp>
#include <Animal/NeuronalScorpion/NeuronalScorpion.hpp>
#include <Utility/Utility.hpp>
#include <Application.hpp>

#include <list>
#include <math.h>
#include <SFML/Graphics.hpp>

Sensor::Sensor(NeuronalScorpion* scorpion)
    :active_(false)
    ,score_(0.0)
    ,inhibitor_(0.0)
    ,scorpion_(scorpion)
{

}

Sensor::~Sensor()
{

}

void Sensor::update(sf::Time dt)
{
    if(active_) {
        score_ +=  2.0 * (1.0 - inhibitor_);
        for(auto& sensor:connectedSensors_) {
            sensor->increaseInhibitor(getAppConfig().sensor_inhibition_factor * score_);
        }
    } else {
        active_ = (getAppEnv().getWaveIntensity(scorpion_->getPositionOfSensor(this)) > getAppConfig().sensor_intensity_threshold);
    }
}

void Sensor::draw(sf::RenderTarget& target) const
{
    sf::Color color(sf::Color::Green);
    if(inhibitor_ > 0.2) {
        if(active_)
            color = sf::Color::Magenta;
        else
            color = sf::Color::Blue;
    } else {
        if(active_)
            color = sf::Color::Red;
    }

    target.draw(buildCircle(scorpion_->getPositionOfSensor(this), 0.25 * scorpion_->getRadius(), color));
}

void Sensor::connect(Sensor* sensor)
{
    connectedSensors_.push_back(sensor);
}


void Sensor::reset()
{
    active_ = false;
    score_ = 0.0;
    inhibitor_ = 0.0;
}

bool Sensor::isActive() const
{
    return active_;
}

double Sensor::getScore() const
{
    return score_;
}

void Sensor::setInhibitor(double inhibitor)
{
    inhibitor_ = std::max(0.0, std::min(inhibitor, getAppConfig().sensor_inhibition_max));
}

void Sensor::increaseInhibitor(double increase)
{
    setInhibitor(inhibitor_ + increase);
}
