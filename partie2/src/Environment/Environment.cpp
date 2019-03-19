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

Environment::~Environment()
{
    clean();
}

void Environment::addAnimal(Animal* animal)
{
    animals_.push_back(animal);
}

void Environment::addTarget(const Vec2d& target)
{
    targets_.push_back(target);
}

void Environment::update(sf::Time dt) const
{
    for(auto animal : animals_)
        animal->update(dt);
}

void Environment::draw(sf::RenderTarget& targetWindow) const
{
    for(auto animal: animals_)
        animal->draw(targetWindow);
    for(auto& target:targets_)
        targetWindow.draw(buildCircle(target, 5, sf::Color(255,0,0)));
}

void Environment::clean()
{
    for(auto& animal:animals_)
        delete animal;
    animals_.clear();
    targets_.clear();
}
