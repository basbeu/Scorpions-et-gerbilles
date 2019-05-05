/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#ifndef WAVEGERBIL_HPP
#define WAVEGERBIL_HPP

#include <Animal/Gerbil.hpp>
#include <Utility/Vec2d.hpp>

#include <SFML/Graphics.hpp>

class WaveGerbil:public Gerbil
{
public:
    WaveGerbil(Vec2d position, double energyLevel, bool female);

    WaveGerbil(Vec2d position);

    virtual ~WaveGerbil() override;

    virtual void update(sf::Time dt) override;

private:
    sf::Time waveGenElapsedTime_;
};

#endif // WAVEGERBIL_HPP
