/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#ifndef FOODGENERATOR_HPP
#define FOODGENERATOR_HPP

#include <SFML/Graphics.hpp>

/*!
 * @brief The FoodGenerator class generates food
 */
class FoodGenerator
{
public:
    /*!
     * @brief build a FoodGenerator instance
     */
    FoodGenerator();

    /*!
     * @brief destroy a FoodGenerator instance
     */
    virtual ~FoodGenerator();

    /*!
     * @brief generate food if the elapsed time since last generation is updated
     * @param dt elapsed time since the last update
     */
    void update(sf::Time dt);
private:
    /*!
     * @brief counts elapsed time since last food generation
     */
    sf::Time counter_;
};

#endif // FOODGENERATOR_HPP
