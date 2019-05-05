/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#include <Environment/Wave.hpp>
#include <Utility/Vec2d.hpp>
#include <Utility/Constants.hpp>
#include <Utility/Utility.hpp>
#include <Application.hpp>

#include <math.h>
#include <list>
#include <utility>
#include <SFML/Graphics.hpp>

Wave::Wave(Vec2d origin, double energyLevel, double initialRadius, double mu, double propagationSpeed)
    :CircularCollider (origin,initialRadius)
    ,initialEnergyLevel_(energyLevel)
    ,initialRadius_(initialRadius)
    ,mu_(mu)
    ,propagationSpeed_(propagationSpeed)
    ,timer_(sf::Time::Zero)
{
    arcs_.push_back(std::pair<double, double>(0, 2 * PI));
}

Wave::~Wave()
{

}

void Wave::draw(sf::RenderTarget& target) const
{
    for(auto& arc:arcs_){
        target.draw(buildArc(arc.first/DEG_TO_RAD, arc.second/DEG_TO_RAD,  getRadius(), getPosition(), sf::Color::Black, 0.f, getAppConfig().wave_intensity_thickness_ratio * getIntensity()));
    }
}

void Wave::update(sf::Time dt)
{
    timer_ += dt;
    setRadius(propagationSpeed_ * timer_.asSeconds() + initialRadius_);
}

double Wave::getEnergy() const
{
    return initialEnergyLevel_ * exp(-getRadius()/mu_);
}

double Wave::getIntensity() const
{
    return getEnergy()/(2 * PI * getRadius());
}
