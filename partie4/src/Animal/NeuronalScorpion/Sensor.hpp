/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <Interface/Updatable.hpp>
#include <Interface/Drawable.hpp>

#include <list>
#include <SFML/Graphics.hpp>

class NeuronalScorpion;

/**
 * @brief The Sensor class represents a neuronal sensor of a NeuronalScorpion
 */
class Sensor:public Updatable, public Drawable
{
public:
    /**
     * @brief buil an instance of Sensor
     * @param NeuronalScorpion that "owns" the sensor
     */
    Sensor(NeuronalScorpion* scorpion);

    /**
     * @brief destroy the Sensor instance
     */
    virtual ~Sensor() override;

    /*
     * Overriden methods
     */
    virtual void update(sf::Time dt) override;
    virtual void draw(sf::RenderTarget& target) const override;

    /**
     * @brief connect to an another sensor
     * @param sensor connected, this sensor will be inhibitted by this
     */
    void connect(Sensor* sensor);

    /**
     * @brief reset the sensor to initial values
     */
    void reset();

    /**
     * @return true if the Sensor is active, false otherwise
     */
    bool isActive() const;

    /**
     * @return the score of the activation
     */
    double getScore() const;
private:
    /**
     * @brief state of the sensor
     */
    bool active_;

    /**
     * @brief score of the current activation if any
     */
    double score_;

    /**
     * @brief inhibitor score, that decrease the score
     */
    double inhibitor_;

    /**
     * @brief owner of the sensor
     */
    NeuronalScorpion* scorpion_;

    /**
     * @brief list of connected sensor, these sensors will be inhibitted by the current sensor
     */
    std::list<Sensor*> connectedSensors_;

    /**
     * @brief set the inhibitor score value
     * @param new inhibitor score value
     */
    void setInhibitor(double inhibitor);

    /**
     * @brief increase the inhibitor score value
     * @param value added to the current inhibitor value
     */
    void increaseInhibitor(double increase);
};

#endif // SENSOR_HPP
