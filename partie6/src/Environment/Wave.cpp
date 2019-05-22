/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#include <Environment/Wave.hpp>
#include <Obstacle/Obstacle.hpp>
#include <Utility/Vec2d.hpp>
#include <Utility/Constants.hpp>
#include <Utility/Utility.hpp>
#include <Application.hpp>

#include <math.h>
#include <list>
#include <utility>
#include <SFML/Graphics.hpp>

Wave::Wave(Vec2d const& origin, double energyLevel, double initialRadius, double mu, double propagationSpeed)
    :CircularCollider (origin,initialRadius)
    ,initialEnergyLevel_(energyLevel)
    ,initialRadius_(initialRadius)
    ,mu_(mu)
    ,propagationSpeed_(propagationSpeed)
    ,timer_(sf::Time::Zero)
{
    arcs_.push_back(Arc(0, 2 * PI));
}

Wave::~Wave()
{

}

void Wave::draw(sf::RenderTarget& target) const
{
    for(auto& arc:arcs_){
        target.draw(buildArc(arc.first/DEG_TO_RAD, arc.second/DEG_TO_RAD,  getRadius(), getPosition(), sf::Color::Black, 0, getAppConfig().wave_intensity_thickness_ratio * getIntensity()));
    }
}

void Wave::update(sf::Time dt)
{
    timer_ += dt;
    setRadius(propagationSpeed_ * timer_.asSeconds() + initialRadius_);
    std::list<Obstacle const*> obstacles = getAppEnv().getObstacleColliding(this);

    for(auto& obstacle:obstacles){
        double obstacleAngle(computeRelativeAngle(obstacle->getPosition()));
        Arc arcColliding = findArcColliding(obstacleAngle) ;
        if(arcColliding != Arc(0,0)){
            double separationAngle(std::atan2(obstacle->getRadius(), getRadius() + obstacle->getRadius()));
            arcs_.remove(arcColliding);
            arcs_.push_back(Arc(arcColliding.first,obstacleAngle - separationAngle));
            arcs_.push_back(Arc(obstacleAngle + separationAngle, arcColliding.second));
        }
    }
}

double Wave::getEnergy() const
{
    return initialEnergyLevel_ * exp(-getRadius()/mu_);
}

double Wave::getIntensity() const
{
    return getEnergy()/(2 * PI * getRadius());
}

double Wave::getIntensityAt(Vec2d const& position) const
{
    double margin(getAppConfig().wave_on_wave_marging);
    double distance((position-getPosition()).length());
    if(distance > getRadius() - margin
            && distance < getRadius() + margin
            && findArcColliding(computeRelativeAngle(position)) != Arc(0,0)){
        return getIntensity();
    }

    return 0.0;
}

Wave::Arc Wave::findArcColliding(double obstacleAngle) const
{
    for(auto& arc:arcs_){
        if(obstacleAngle >= arc.first && obstacleAngle <= arc.second){
            return arc;
        }
    }
    return Arc(0,0);
}

double Wave::computeRelativeAngle(Vec2d const& position) const
{
    double angle((position - getPosition()).angle());
    if(angle < 0)
        angle += 2*PI;

    return angle;
}
