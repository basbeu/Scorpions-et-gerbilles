/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#ifndef ROCK_HPP
#define ROCK_HPP

#include <Obstacle/Obstacle.hpp>

class Rock:public Obstacle
{
public:
    Rock(Vec2d position);

    virtual ~Rock();

    virtual std::string getTexture() const;
};

#endif // ROCK_HPP
