/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#include <Environment/Food.hpp>
#include <Environment/OrganicEntity.hpp>
#include <Utility/Utility.hpp>
#include <Application.hpp>
#include <SFML/Graphics.hpp>

Food::Food(Vec2d position)
:OrganicEntity (position, getAppConfig().food_size, getAppConfig().food_energy)
{

}

Food::~Food()
{

}

void Food::update(sf::Time dt)
{
    // TODO : Evolution de la source de nourriture à programmer
}

void Food::draw(sf::RenderTarget& targetWindow) const
{
    sf::Texture& texture = getAppTexture(getAppConfig().food_texture);
    auto image_to_draw(buildSprite(getPosition(), 2*getRadius(),texture));
    targetWindow.draw(image_to_draw);
}
