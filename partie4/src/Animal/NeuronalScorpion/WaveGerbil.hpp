/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#ifndef WAVEGERBIL_HPP
#define WAVEGERBIL_HPP

#include <Animal/Gerbil.hpp>
#include <Utility/Vec2d.hpp>

#include <SFML/Graphics.hpp>

/**
 * @brief The WaveGerbil class is a specialized Gerbil used during Neuronal Simulation. This kind of Gerbim emit waves.
 */
class WaveGerbil:public Gerbil
{
public:
    /*!
     * @brief build an instance of WaveGerbil
     * @param position Vec2d representing the initial position
     * @param energyLevel initial level of the gerbil
     * @param female gender of the Gerbil instance : true => female, false => male
     */
    WaveGerbil(Vec2d position, double energyLevel, bool female);


    /*!
     * @brief build an instance of WaveGerbil
     * @param initial position of the gerbil (Vec2d)
     */
    WaveGerbil(Vec2d position);

    /**
     * @brief destroy a WaveGerbil instance
     */
    virtual ~WaveGerbil() override;

    /*
     * Overriden method
     */
    virtual void update(sf::Time dt) override;

private:
    /**
     * @brief count the time between two wave emissions
     */
    sf::Time waveGenElapsedTime_;
};

#endif // WAVEGERBIL_HPP
