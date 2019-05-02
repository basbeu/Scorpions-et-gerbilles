/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#ifndef FOOD_HPP
#define FOOD_HPP

#include <Environment/OrganicEntity.hpp>
#include <Utility/Vec2d.hpp>

class Food:public OrganicEntity
{
public:
    Food(Vec2d position);

    virtual ~Food();

    void update(sf::Time dt);
    void draw(sf::RenderTarget& targetWindow) const;
};

#endif // FOOD_HPP
