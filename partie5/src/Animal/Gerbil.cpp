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
    getAppEnv().increaseCounter(this);
}

Gerbil::Gerbil(Vec2d position)
    :Animal(position, getAppConfig().gerbil_size, getAppConfig().gerbil_energy_initial, uniform(0,1) == 0)
{
    getAppEnv().increaseCounter(this);
}

Gerbil::~Gerbil()
{
    getAppEnv().decreaseCounter(this);
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

bool Gerbil::matable(OrganicEntity const* other) const
{
    return other->canMate(this);
}

bool Gerbil::canMate(Scorpion const* scorpion) const
{
    return false;
}

bool Gerbil::canMate(Gerbil const* gerbil) const
{
    return gerbil->isFemale() != isFemale()
            && !gerbil->isPregnant()
            && !gerbil->isGivingBirth()
            && gerbil->getEnergyLevel() >= gerbil->getMinimumMatingEnergy()
            && gerbil->getAge() >= getMinAgeMating();
}

bool Gerbil::canMate(Food const* Gerbil) const
{
    return false;
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

sf::Time Gerbil::getFeedingBreak() const
{
    return getAppConfig().gerbil_feeding_break;
}

double Gerbil::getFeedingEfficiency() const
{
    return getAppConfig().gerbil_feeding_efficiency;
}

double Gerbil::getMinimumMatingEnergy() const
{
    return isFemale()?getAppConfig().gerbil_energy_min_mating_female:getAppConfig().gerbil_energy_min_mating_male;
}

double Gerbil::getMinAgeMating()const
{
    return getAppConfig().gerbil_min_age_mating;
}

int Gerbil::getMinChildren() const
{
    return getAppConfig().gerbil_min_children;
}

int Gerbil::getMaxChildren() const
{
    return getAppConfig().gerbil_max_children;
}

double Gerbil::getEnergyLossFemalePerChild() const
{
    return getAppConfig().gerbil_energy_loss_female_per_child;
}

double Gerbil::getEnergyLossMatingMale() const
{
    return getAppConfig().gerbil_energy_loss_mating_male;
}

double Gerbil::getGestationTime() const
{
    return getAppConfig().gerbil_gestation_time;
}

sf::Time Gerbil::getGivingBirthBreak() const
{
    return getAppConfig().gerbil_giving_birth_break;
}

Animal* Gerbil::giveBirth() const
{
    return new Gerbil(getPosition());
}
