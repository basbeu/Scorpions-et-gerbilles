/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#ifndef STATS_HPP
#define STATS_HPP

#include <Interface/Updatable.hpp>
#include <Interface/Drawable.hpp>
#include <Utility/Vec2d.hpp>

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class Stats:public Updatable, public Drawable
{
public:
    Stats();

    virtual void update(sf::Time dt);
    virtual void draw(sf::RenderTarget& target) const;

    void focusOn(std::string graph_title);
    void reset();
    void addGraph(int graphId, std::string const& title, std::vector<std::string> const& series, double min, double max, Vec2d statsSize);
};

#endif // STATS_HPP
