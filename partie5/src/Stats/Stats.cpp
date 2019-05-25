/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#include <Stats/Stats.hpp>
#include <Interface/Updatable.hpp>
#include <Interface/Drawable.hpp>
#include <Utility/Vec2d.hpp>
#include <Stats/Graph.hpp>
#include <Application.hpp>

#include <string>
#include <vector>
#include <unordered_map>

#include <utility>
#include <list>
#include <memory>
#include <SFML/Graphics.hpp>

Stats::Stats()
    :active_(-1)
{

}

Stats::~Stats()
{

}

void Stats::update(sf::Time dt)
{
    timer_ += dt;
    if(timer_.asSeconds() > getAppConfig().stats_refresh_rate) {
        for(auto& graph:graphs_) {

            /*for(auto stat:getAppEnv().fetchData(labels_.at(graph.first))){
                std::cerr << stat.first << " " << stat.second << std::endl;
            }*/
            //std::cerr << std::endl << labels_.at(graph.first) <<std::endl;
            if(graph.first == active_)
                graph.second->updateData(dt, getAppEnv().fetchData(labels_.at(graph.first)));
        }
    }
}

void Stats::draw(sf::RenderTarget& target) const
{
    graphs_.at(active_)->draw(target);
}

void Stats::focusOn(std::string graph_title)
{
    for(auto& label:labels_) {
        if(label.second == graph_title) {
            active_ = label.first;
        }
    }
}

void Stats::reset()
{
    for(auto& graph:graphs_) {
        graph.second->reset();
    }
}

void Stats::addGraph(int graphId, std::string const& title, std::vector<std::string> const& titles, double min, double max, Vec2d statsSize)
{
    std::unordered_map<int,std::unique_ptr<Graph>>::const_iterator graph = graphs_.find (graphId);

    if(graph == graphs_.end()) {
        graphs_.insert(std::pair<int, std::unique_ptr<Graph>>(graphId, std::unique_ptr<Graph>(new Graph(titles, statsSize, min, max))));
    } else {
        graphs_[graphId].reset(new Graph(titles, statsSize, min, max));
    }
    labels_.insert(std::pair<int, std::string>(graphId, title));
    active_ = graphId;
}
