/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#ifndef STATS_HPP
#define STATS_HPP

#include <Interface/Updatable.hpp>
#include <Interface/Drawable.hpp>
#include <Utility/Vec2d.hpp>
#include <Stats/Graph.hpp>

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <SFML/Graphics.hpp>

/**
 * @brief The Stats class manage the statistics of the simulations
 */
class Stats:public Updatable, public Drawable
{
public:
    /**
     * @brief Build a Stats instance
     */
    Stats();

    /**
     * @brief destroy a Stats instance
     */
    virtual ~Stats();

    /*
     * overriden methods, see Updatable.hpp and drawable.hpp
     */
    virtual void update(sf::Time dt);
    virtual void draw(sf::RenderTarget& target) const;

    /**
     * @brief set the graph that is currently focus (drawn)
     * @param title of the graph currently shown
     */
    void focusOn(std::string const& graph_title);
    /**
     * @brief reset the stats
     */
    void reset();

    /**
     * @brief add a graph in the statistics of the simulation
     * @param graphId internal Application id of the graph
     * @param title of the graph
     * @param collection of series belonging to the graph
     * @param min value
     * @param max value
     * @param statsSize size of the graph
     */
    void addGraph(int graphId, std::string const& title, std::vector<std::string> const& series, double min, double max, Vec2d statsSize);
private:
    /**
     * @brief store the different graph
     */
    std::unordered_map<int,std::unique_ptr<Graph>> graphs_;

    /**
     * @brief store the labels of the graph
     */
    std::unordered_map<int, std::string> labels_;

    /**
     * @brief id of the current active graph
     */
    int active_;

    /**
     * @brief elapsed time from last stats update
     */
    sf::Time timer_;
};

#endif // STATS_HPP
