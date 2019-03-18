/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <Animal/Animal.hpp>
#include <Utility/Vec2d.hpp>

#include <list>
#include <SFML/Graphics.hpp>

class Environment
{
public:
    Environment() = default;
    /*!
     * @brief Environment
     */
    Environment(Environment const& other) = delete;

    /*!
     * @brief
     */
    ~Environment();

    /*!
     * @brief addAnimal
     * @param animal
     */
    void addAnimal(Animal* animal);

    /*!
     * @brief addTarget
     * @param target
     */
    void addTarget(const Vec2d& target);

    /*!
     * @brief update
     * @param dt
     */
    void update(sf::Time dt) const;

    /*!
     * @brief draw
     * @param targetWindow
     */
    void draw(sf::RenderTarget& targetWindow) const;

    /*!
     * @brief clean
     */
    void clean();

private:
    std::list<Animal*> animals_;
    std::list<Vec2d> targets_;
};

#endif
