/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#ifndef FOODGENERATOR_HPP
#define FOODGENERATOR_HPP

#include <SFML/Graphics.hpp>


class FoodGenerator
{
public:
    FoodGenerator();

    virtual ~FoodGenerator();

    void update(sf::Time dt);
private:
    sf::Time counter_;
};

#endif // FOODGENERATOR_HPP
