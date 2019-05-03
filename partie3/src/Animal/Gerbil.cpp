/*
* Project : infoSV 2019
* Author  : Bastien Beuchat
*/

#include <Animal/Gerbil.hpp>
#include <Utility/Vec2d.hpp>
#include <Application.hpp>
#include <Random/Uniform.hpp>

Gerbil::Gerbil(Vec2d position, double energyLevel, bool female)
    :Animal(position, getAppConfig().gerbil_size, energyLevel, female)
{

}

Gerbil::Gerbil(Vec2d position)
    :Animal(position, getAppConfig().gerbil_size, getAppConfig().gerbil_energy_initial, uniform(0,1) == 0)
{

}

Gerbil::~Gerbil()
{

}

double Gerbil::getStandardMaxSpeed() const
{
    return getAppConfig().gerbil_max_speed;
}

double Gerbil::getMass() const
{
    return getAppConfig().gerbil_mass;
}

double Gerbil::getRandomWalkRadius() const
{
    return getAppConfig().gerbil_random_walk_radius;
}

double Gerbil::getRandomWalkDistance() const
{
    return getAppConfig().gerbil_random_walk_distance;
}

double Gerbil::getRandomWalkJitter() const
{
    return getAppConfig().gerbil_random_walk_jitter;
}

double Gerbil::getViewRange() const
{
    return getAppConfig().gerbil_view_range;
}

double Gerbil::getViewDistance() const
{
    return getAppConfig().gerbil_view_distance;
}

std::string Gerbil::getTexture() const
{
    return isFemale() ? getAppConfig().gerbil_texture_female : getAppConfig().gerbil_texture_male;
}

bool Gerbil::eatable(OrganicEntity const* entity)
{
    return entity->eatableBy(this);
}

bool Gerbil::eatableBy(Scorpion  const* scorpion) const
{
    return true;
}

bool Gerbil::eatableBy(Gerbil const* gerbil) const
{
    return false;
}

bool Gerbil::eatableBy(Food const* food) const
{
    return false;
}

sf::Time Gerbil::getLongevity() const
{
    return getAppConfig().gerbil_longevity;
}

double Gerbil::getEnergyLossFactor() const
{
    return getAppConfig().gerbil_energy_loss_factor;
}

double Gerbil::getTiredMaxSpeed() const
{
    return getAppConfig().gerbil_tired_max_speed;
}
