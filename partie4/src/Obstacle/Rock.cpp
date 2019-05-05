/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#include <Obstacle/Rock.hpp>
#include <Random/Uniform.hpp>
#include <Utility/Constants.hpp>
#include <Application.hpp>

#include <algorithm>

Rock::Rock(Vec2d position)
    :Obstacle (position, std::max(1, uniform(getAppConfig().simulation_world_size/50, 2*getAppConfig().simulation_world_size/50)), uniform(-PI,PI))
{

}

Rock::~Rock()
{

}

std::string Rock::getTexture() const
{
    return getAppConfig().rock_texture;
}
