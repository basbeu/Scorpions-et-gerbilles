/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#include <Environment/Environment.hpp>
#include <Environment/OrganicEntity.hpp>
#include <Environment/Wave.hpp>
#include <Animal/Animal.hpp>
#include <Utility/Vec2d.hpp>
#include <Utility/Utility.hpp>
#include <Application.hpp>

#include <list>
#include <algorithm>
#include <SFML/Graphics.hpp>

Environment::~Environment()
{
    clean();
}

void Environment::addEntity(OrganicEntity* entity)
{
    entities_.push_back(entity);
}

void Environment::update(sf::Time dt)
{
    for(auto& entity : entities_){
        entity->update(dt);
        if(!entity->isAlive()){
            delete entity;
            entity = nullptr;
        }
    }
    entities_.erase(std::remove(entities_.begin(), entities_.end(), nullptr), entities_.end());

    for(auto generator : generators_)
        generator->update(dt);

    for(auto& wave:waves_){
        wave->update(dt);
        if(wave->getIntensity() < getAppConfig().wave_intensity_threshold){
            delete wave;
            wave = nullptr;
        }
    }
    waves_.erase(std::remove(waves_.begin(), waves_.end(), nullptr), waves_.end());
}

void Environment::draw(sf::RenderTarget& targetWindow) const
{
    for(auto entity : entities_)
        entity->draw(targetWindow);

    for(auto wave : waves_)
        wave->draw(targetWindow);
}

void Environment::clean()
{
    for(auto& entity:entities_)
        delete entity;
    entities_.clear();

    for(auto& generator:generators_)
        delete generator;

    generators_.clear();

    for(auto& wave:waves_)
        delete wave;

    waves_.clear();
}

std::list<OrganicEntity *> Environment::getEntitiesInSightForAnimal(Animal* animal)
{
    std::list<OrganicEntity*> entitiesInSight;
    for(auto& entity:entities_) {
        if(entity != nullptr && animal->isTargetInSight(entity->getPosition()))
            entitiesInSight.push_back(entity);
    }

    return entitiesInSight;
}

void Environment::addGenerator(FoodGenerator* gen)
{
    generators_.push_back(gen);
}

void Environment::addWave(Wave* wave)
{
    waves_.push_back(wave);
}
