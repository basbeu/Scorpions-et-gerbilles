/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <Utility/Vec2d.hpp>

#include <list>
#include <SFML/Graphics.hpp>

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
     * @brief Add an animal in the environment
     * @param Pointer to the Animal that is added to the environment
     */
    void addAnimal(Animal* animal);

    /*!
     * @brief Add a target to the environment
     * @param target is represented by its position (Vec2d)
     */
    void addTarget(const Vec2d& target);

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
     * @brief Get all target that is in sight for a given animal
     * @param animal Pointer to the animal for which the potential targets are requested
     * @return a list (std::list) of Vec2d representing the targets seens by the given animal
     */
    std::list<Vec2d> getTargetsInSightForAnimal(Animal* animal);
private:
    /*!
     * @brief animals_ list of all animals living in the environment
     */
    std::list<Animal*> animals_;

    /*!
     * @brief targets_ list of all targets living in the environment
     */
    std::list<Vec2d> targets_;
};

#endif //ENVIRONMENT_HPP
