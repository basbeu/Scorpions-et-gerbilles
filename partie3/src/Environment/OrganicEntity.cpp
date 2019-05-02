/*
 * Project : infoSV 2019
 * Author  : Bastien Beuchat
 */

#include "OrganicEntity.hpp"

OrganicEntity::OrganicEntity(Vec2d position, double size, double energyLevel)
    :CircularCollider (position, size/2)
    ,energyLevel_(energyLevel)
{

}

OrganicEntity::~OrganicEntity()
{

}
