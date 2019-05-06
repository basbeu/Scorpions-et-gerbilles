/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <Utility/Vec2d.hpp>

#include <list>
#include <SFML/Graphics.hpp>
#include <Environment/OrganicEntity.hpp>
#include <Environment/Wave.hpp>
#include <Environment/FoodGenerator.hpp>
#include <Obstacle/Obstacle.hpp>

class Animal;

/*!
 * @brief The Environment class represents a natural environment that have a set of animals in it and some ressources.
 */
class Environment
{
public:
    /*!
     * @brief Only the default constructor is provided
     */
    Environment() = default;

    /*!
     * @brief Copy constructor is not provided for an Environment
     */
    Environment(Environment const& other) = delete;

    /*!
     * @brief The destructor that destroy the environment and its animals and ressources
     */
    ~Environment();

    /*!
     * @brief Add an organic entity in the environment
     * @param Pointer to the organic entity that is added to the environment
     */
    void addEntity(OrganicEntity* entity);

    /*!
     * @brief Update the environment for the tic of time dt
     * @param dt elapsed time from the last update
     */
    void update(sf::Time dt);

    /*!
     * @brief Draw the environment to a window
     * @param targetWindow the window in which the environment have to be rendered
     */
    void draw(sf::RenderTarget& targetWindow) const;

    /*!
     * @brief Clean the environment, destroy all animals and ressources
     */
    void clean();

    /*!
     * @brief Get all organic entities that is in sight for a given animal
     * @param animal Pointer to the animal for which the potential targets are requested
     * @return a list (std::list) of OrganicEntity representing the different entitys seen by the given animal
     */
    std::list<OrganicEntity*> getEntitiesInSightForAnimal(Animal* animal);

    /*!
     * @brief add a food generator to the environment
     * \param Pointer to the FoodGenerator added to the environment
     */
    void addGenerator(FoodGenerator* gen);

    /**
     * @brief add a wave to the environment
     * @param pointer to the wave added to the environment
     */
    void addWave(Wave* wave);

    /**
     * @brief add an obstacle to the environment
     * @param pointer to the obstacle added to the environment
     */
    void addObstacle(Obstacle* obstacle);

    /**
     * @brief get the obstacles that are colliding with a given wave
     * @param pointer to the wave
     * @return a list of obstacles that are colliding with a wave
     */
    std::list<Obstacle *> getObstacleColliding(Wave* wave);

    /**
     * @brief get the total wave intensity for a given point of the simulation world
     * @param position in the simulation world
     * @return the total wave intensity for the given position
     */
    double getWaveIntensity(Vec2d position) const;
private:

    /*!
     * @brief entities_ list of all the organic entities living in the environment
     */
    std::list<OrganicEntity*> entities_;

    /*!
     * @brief generators_ list of all food generators that are in the environment
     */
    std::list<FoodGenerator*> generators_;

    /**
     * @brief stores the waves that are propagating in the environment
     */
    std::list<Wave *> waves_;

    /**
     * @brief stores the obstacles of the environment
     */
    std::list<Obstacle*> obstacles_;
};

#endif //ENVIRONMENT_HPP
