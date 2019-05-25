/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#include <Environment/Environment.hpp>
#include <Environment/OrganicEntity.hpp>
#include <Environment/Wave.hpp>
#include <Animal/Animal.hpp>
#include <Animal/Scorpion.hpp>
#include <Obstacle/Obstacle.hpp>
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
    //std::cerr << nbScorpions_ << std::endl;
    for(auto& entity : entities_) {
        entity->update(dt);
        if(!entity->isAlive()) {
            delete entity;
            entity = nullptr;
        }
    }
    entities_.erase(std::remove(entities_.begin(), entities_.end(), nullptr), entities_.end());

    for(auto generator : generators_)
        generator->update(dt);

    for(auto& wave:waves_) {
        wave->update(dt);
        if(wave->getIntensity() < getAppConfig().wave_intensity_threshold) {
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

    for(auto obstacle : obstacles_)
        obstacle->draw(targetWindow);
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

    for(auto& obstacle:obstacles_)
        delete obstacle;

    obstacles_.clear();
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

void Environment::addObstacle(Obstacle* obstacle)
{
    obstacles_.push_back(obstacle);
}

std::list<Obstacle *> Environment::getObstacleColliding(Wave* wave)
{
    std::list<Obstacle*> obstaclesColliding;
    for(auto& obstacle:obstacles_) {
        if(obstacle->isColliding(*wave)) {
            obstaclesColliding.push_back(obstacle);
        }
    }

    return obstaclesColliding;
}

double Environment::getWaveIntensity(Vec2d position) const
{
    double intensity(0.0);
    for(auto& wave : waves_) {
        intensity += wave->getIntensityAt(position);
    }

    return intensity;
}

std::unordered_map<std::string, double> Environment::fetchData(std::string title)
{
    std::unordered_map<std::string, double> newData;

    if(title == s::GENERAL) {
        newData[s::SCORPIONS] = nbScorpions_;//Scorpion::getNumberOfInstances();//Scorpion::getNumberScorpions();
        newData[s::GERBILS] = nbGerbils_;
        newData[s::FOOD] = nbFood_;
    } else if(title == s::WAVES) {
        newData[s::WAVES] =  waves_.size();
    }

    return newData;
}

void Environment::increaseCounter(Scorpion *)
{
    ++nbScorpions_;
}
void Environment::increaseCounter(Gerbil *)
{
    ++nbGerbils_;
}

void Environment::increaseCounter(Food *)
{
    ++nbFood_;
}

void Environment::decreaseCounter(Scorpion *)
{
    --nbScorpions_;
}

void Environment::decreaseCounter(Gerbil *)
{
    --nbGerbils_;
}

void Environment::decreaseCounter(Food *)
{
    --nbFood_;
}
