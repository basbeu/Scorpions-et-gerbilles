/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#include <Environment/Environment.hpp>
#include <Animal/Animal.hpp>
#include <Utility/Vec2d.hpp>
#include <Utility/Utility.hpp>

#include <list>
#include <SFML/Graphics.hpp>
#include <Environment/OrganicEntity.hpp>

Environment::~Environment()
{
    clean();
}

void Environment::addEntity(OrganicEntity* entity)
{
    entities_.push_back(entity);
}

void Environment::update(sf::Time dt) const
{
    for(auto entity : entities_)
        entity->update(dt);
}

void Environment::draw(sf::RenderTarget& targetWindow) const
{
    for(auto entity: entities_)
        entity->draw(targetWindow);
}

void Environment::clean()
{
    for(auto& entity:entities_)
        delete entity;
    entities_.clear();
}

std::list<OrganicEntity *> Environment::getEntitiesInSightForAnimal(Animal* animal)
{
    std::list<OrganicEntity*> entitiesInSight;
    for(auto& entity:entities_) {
        if(animal->isTargetInSight(entity->getPosition()))
            entitiesInSight.push_back(entity);
    }

    return entitiesInSight;
}
