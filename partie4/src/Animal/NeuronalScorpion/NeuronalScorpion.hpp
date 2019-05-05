/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#ifndef NEURONALSCORPION_H
#define NEURONALSCORPION_H

#include <Animal/Scorpion.hpp>
#include <Utility/Vec2d.hpp>

class NeuronalScorpion:public Scorpion
{
public:
    NeuronalScorpion(Vec2d position);
};

#endif // NEURONALSCORPION_H
