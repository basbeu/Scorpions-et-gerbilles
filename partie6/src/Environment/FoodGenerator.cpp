/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#include <Environment/FoodGenerator.hpp>
#include <Environment/Food.hpp>
#include <Random/Normal.hpp>
#include <Application.hpp>

#include <SFML/Graphics.hpp>

FoodGenerator::FoodGenerator()
    :counter_(sf::Time::Zero)
{

}

FoodGenerator::~FoodGenerator()
{

}

void FoodGenerator::update(sf::Time dt)
{
    counter_ += dt;
    if(counter_ > sf::seconds(getAppConfig().food_generator_delta)) {
        counter_ = sf::Time::Zero;
        int envSize = getAppConfig().simulation_world_size;
        getAppEnv().addEntity(new Food(Vec2d(normal(envSize/2, envSize*envSize/16),normal(envSize/2, envSize*envSize/16))));
    }

}
