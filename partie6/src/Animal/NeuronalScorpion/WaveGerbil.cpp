/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#include <Animal/NeuronalScorpion/WaveGerbil.hpp>
#include <Utility/Vec2d.hpp>
#include <Application.hpp>

#include <SFML/Graphics.hpp>

WaveGerbil::WaveGerbil(Vec2d const& position, double energyLevel, bool female)
    :Gerbil(position, energyLevel, female)
    ,waveGenElapsedTime_(sf::Time::Zero)
{

}

WaveGerbil::WaveGerbil(Vec2d const& position)
    :Gerbil(position)
    ,waveGenElapsedTime_(sf::Time::Zero)
{

}

WaveGerbil::~WaveGerbil()
{

}

void WaveGerbil::update(sf::Time dt)
{
    Gerbil::update(dt);
    waveGenElapsedTime_ += dt;

    if(waveGenElapsedTime_.asSeconds() >= 1.0/getAppConfig().wave_gerbil_frequency){
        getAppEnv().addWave(new Wave(getPosition(),
                                     getAppConfig().wave_default_energy,
                                     getAppConfig().wave_default_radius,
                                     getAppConfig().wave_default_mu,
                                     getAppConfig().wave_default_speed));

        waveGenElapsedTime_ = sf::Time::Zero;
    }

}
