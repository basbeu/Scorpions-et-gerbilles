/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#ifndef ROCK_HPP
#define ROCK_HPP

#include <Obstacle/Obstacle.hpp>

/**
 * @brief The Rock class represents a rock in the simulation
 */
class Rock:public Obstacle
{
public:
    /**
     * @brief build a Rock instance
     * @param position of the rock
     */
    Rock(Vec2d const& position);

    /**
     * @brief destroy a Rock
     */
    virtual ~Rock() override;

    /*
     * Overriden method
     */
    virtual std::string getTexture() const override;
};

#endif // ROCK_HPP
