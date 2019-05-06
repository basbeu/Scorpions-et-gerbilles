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

class Sensor:public Updatable, public Drawable
{
public:
    Sensor(NeuronalScorpion* scorpion);

    virtual ~Sensor() override;

    virtual void update(sf::Time dt) override;
    void draw(sf::RenderTarget& target) const override;

    void connect(Sensor* sensor);
private:
    bool active_;
    double score_;
    double inhibitor_;

    NeuronalScorpion* scorpion_;
    std::list<Sensor*> connectedSensors_;
    void setInhibitor(double inhibitor);
    void increaseInhibitor(double increase);
};

#endif // SENSOR_HPP
