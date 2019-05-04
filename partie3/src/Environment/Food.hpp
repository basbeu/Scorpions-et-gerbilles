/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#ifndef FOOD_HPP
#define FOOD_HPP

#include <Environment/OrganicEntity.hpp>
#include <Utility/Vec2d.hpp>

/*!
 * @brief The Food class is an OrganicEntity that represents food
 */
class Food:public OrganicEntity
{
public:
    /*!
     * @brief build an instance of Food
     * @param position of the food (Vec2d)
     */
    Food(Vec2d position);

    /*!
     * @brief destroy a food instance
     */
    virtual ~Food() override;

private:
    /*
     * Virtual methods that are inherited from OrganicEntity
     * see OrganiEntity.hpp for the corresponding documentation
     */
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
