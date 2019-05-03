/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#include "Scorpion.hpp"
#include <Utility/Vec2d.hpp>
#include <Application.hpp>
#include <Random/Uniform.hpp>

Scorpion::Scorpion(Vec2d position, double energyLevel, bool female)
    :Animal(position, getAppConfig().scorpion_size, energyLevel, female)
{

}

Scorpion::Scorpion(Vec2d position)
    :Animal (position, getAppConfig().scorpion_size, getAppConfig().scorpion_energy_initial, uniform(0, 1) == 0)
{

}

Scorpion::~Scorpion()
{

}

double Scorpion::getStandardMaxSpeed() const
{
    return getAppConfig().scorpion_max_speed;
}

double Scorpion::getMass() const
{
    return getAppConfig().scorpion_mass;
}

double Scorpion::getRandomWalkRadius() const
{
    return getAppConfig().scorpion_random_walk_radius;
}

double Scorpion::getRandomWalkDistance() const
{
    return getAppConfig().scorpion_random_walk_distance;
}

double Scorpion::getRandomWalkJitter() const
{
    return getAppConfig().scorpion_random_walk_jitter;
}

double Scorpion::getViewRange() const
{
    return getAppConfig().scorpion_view_range;
}

double Scorpion::getViewDistance() const
{
    return getAppConfig().scorpion_view_distance;
}

std::string Scorpion::getTexture() const
{
    return getAppConfig().scorpion_texture;
}

bool Scorpion::eatable(OrganicEntity const* entity)
{
    return entity->eatableBy(this);
}

bool Scorpion::eatableBy(Scorpion  const* scorpion) const
{
    return false;
}

bool Scorpion::eatableBy(Gerbil const* gerbil) const
{
    return false;
}

bool Scorpion::eatableBy(Food const* food) const
{
    return false;
}

sf::Time Scorpion::getLongevity() const
{
    return getAppConfig().scorpion_longevity;
}

double Scorpion::getEnergyLossFactor() const
{
    return getAppConfig().scorpion_energy_loss_factor;
}

double Scorpion::getTiredMaxSpeed() const
{
    return getAppConfig().scorpion_tired_max_speed;
}
