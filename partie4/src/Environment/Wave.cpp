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

Wave::Wave(Vec2d origin, double energyLevel, double initialRadius, double mu, double propagationSpeed)
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
    std::list<Obstacle*> obstacles = getAppEnv().getObstacleColliding(this);

    for(auto& obstacle:obstacles){
        double obstacleAngle((obstacle->getPosition() - getPosition()).angle());
        if(obstacleAngle < 0)
            obstacleAngle += 2*PI;
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

Wave::Arc Wave::findArcColliding(double obstacleAngle) const
{
    for(auto& arc:arcs_){
        if(obstacleAngle >= arc.first && obstacleAngle <= arc.second){
            return arc;
        }
    }
    return Arc(0,0);
}
