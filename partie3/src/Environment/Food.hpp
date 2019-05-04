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

    virtual ~Food() override;

    virtual void update(sf::Time dt) override;
    virtual void draw(sf::RenderTarget& targetWindow) const override;

    virtual bool eatable(OrganicEntity const* entity) override;
    virtual bool eatableBy(Scorpion  const* scorpion) const override;
    virtual bool eatableBy(Gerbil const* gerbil) const override;
    virtual bool eatableBy(Food const* food) const override;

    virtual bool matable(OrganicEntity const* other) const override;
    virtual bool canMate(Scorpion const* scorpion) const override;
    virtual bool canMate(Gerbil const* gerbil) const override;
    virtual bool canMate(Food const* food) const override;
};

#endif // FOOD_HPP
