/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#ifndef WAVE_HPP
#define WAVE_HPP

#include <Utility/Vec2d.hpp>

class Wave
{
public:
    Wave(Vec2d origin, double energyLevel, double initialRadius, double mu, double propagationSpeed);
};

#endif // WAVE_HPP
