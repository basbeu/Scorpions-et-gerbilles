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

    virtual ~Rock() override;

    virtual std::string getTexture() const override;
};

#endif // ROCK_HPP
