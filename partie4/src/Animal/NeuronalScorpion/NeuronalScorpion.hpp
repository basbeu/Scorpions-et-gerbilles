/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#ifndef NEURONALSCORPION_H
#define NEURONALSCORPION_H

#include <Animal/Scorpion.hpp>
#include <Animal/NeuronalScorpion/Sensor.hpp>
#include <Utility/Vec2d.hpp>

//#include <vector>
#include <unordered_map>
#include <utility>

class NeuronalScorpion:public Scorpion
{
public:
    NeuronalScorpion(Vec2d position, double energyLevel, bool female);

    NeuronalScorpion(Vec2d position);

    virtual ~NeuronalScorpion() override;

    virtual void update(sf::Time dt) override;

    Vec2d getPositionOfSensor(Sensor const * sensor) const;
private:
    //std::vector<std::pair<Sensor,double>> sensors_;
    std::unordered_map<Sensor *, double> sensors_;
    Vec2d targetDirection_;

    void initSensors();

    //Vec2d getPositionOfSensor(size_t i) const;
    virtual void drawDebugState(sf::RenderTarget& targetWindow) const override;

};

#endif // NEURONALSCORPION_H
