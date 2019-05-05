/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#include <Obstacle/Obstacle.hpp>
#include <Utility/Utility.hpp>
#include <Application.hpp>

Obstacle::Obstacle(Vec2d position, double radius, double orientation)
    :CircularCollider (position, radius)
    ,orientation_(orientation)
{

}

Obstacle::~Obstacle()
{

}


void Obstacle::draw(sf::RenderTarget& target) const
{
    sf::Texture& texture = getAppTexture(getTexture());
    target.draw(buildSprite(getPosition(), 2 * getRadius(), texture, orientation_/DEG_TO_RAD));
}

