/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#include <Animal/ChasingAutomaton.hpp>
#include <Obstacle/CircularCollider.hpp>
#include <Utility/Constants.hpp>
#include <Utility/Utility.hpp>
#include <Utility/Vec2d.hpp>
#include <Application.hpp>

#include <SFML/Graphics.hpp>

ChasingAutomaton::ChasingAutomaton(Vec2d position)
:CircularCollider (position, CHASING_AUTOMATON_RADIUS)
,direction_(1,0)
,speed_(0)
,targetPosition_(0,0)
{

}

ChasingAutomaton::~ChasingAutomaton()
{

}

double ChasingAutomaton::getStandardMaxSpeed() const
{
    return CHASING_AUTOMATON_MAX_SPEED;
}

double ChasingAutomaton::getMass() const
{
    return CHASING_AUTOMATON_MASS;
}

void ChasingAutomaton::setTargetPosition(Vec2d targetPosition)
{
    targetPosition_ = targetPosition;
}

Vec2d ChasingAutomaton::getSpeedVector() const
{
    return direction_*speed_;
}

void ChasingAutomaton::update(sf::Time dt)
{

}

void ChasingAutomaton::draw(sf::RenderTarget& targetWindow) const
{
    targetWindow.draw(buildCircle(targetPosition_, 5, sf::Color(255,0,0)));
    sf::Texture& texture = getAppTexture(GHOST_TEXTURE);
    auto image_to_draw(buildSprite(getPosition(), 2*getRadius(),texture));
    targetWindow.draw(image_to_draw);
}
