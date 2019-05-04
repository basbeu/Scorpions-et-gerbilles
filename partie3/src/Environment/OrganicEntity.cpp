/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#include <Environment/OrganicEntity.hpp>
#include <Application.hpp>

#include <SFML/Graphics.hpp>

OrganicEntity::OrganicEntity(Vec2d position, double size, double energyLevel)
    :CircularCollider (position, size/2)
    ,energyLevel_(energyLevel)
    ,age_(sf::Time::Zero)
{

}

OrganicEntity::~OrganicEntity()
{

}

void OrganicEntity::update(sf::Time dt)
{
    age_ += dt;
}

sf::Time OrganicEntity::getLongevity() const
{
    return sf::seconds(1E9);
}

bool OrganicEntity::isAlive() const
{
    return age_ < getLongevity() && energyLevel_ > getAppConfig().animal_min_energy;
}

double OrganicEntity::getEnergyLevel() const
{
    return energyLevel_;
}

double OrganicEntity::getAge() const
{
    return age_.asSeconds();
}

void OrganicEntity::eaten()
{
    decreaseEnergyLevel(getEnergyLevel());
}

void OrganicEntity::decreaseEnergyLevel(double loss)
{
    energyLevel_ -= loss;
}


void OrganicEntity::increaseEnergyLevel(double increase)
{
   energyLevel_ += increase;
}

