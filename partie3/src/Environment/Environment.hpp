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
    void update(sf::Time dt) const;

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
private:

    /*!
     * @brief entities_ list of all the organic entities living in the environment
     */
    std::list<OrganicEntity*> entities_;
};

#endif //ENVIRONMENT_HPP
