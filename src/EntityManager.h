#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include <memory>
#include <map>

#include "Entity.h"

typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map   <std::string, EntityVec>  EntityMap;

class EntityManager
{
private:
    EntityVec   m_entities;
    EntityMap   m_entityMap;
    size_t      m_totalEntities = 0;
public:
    EntityManager();
    std::shared_ptr<Entity> addEntity(const std::string& tag);
    EntityVec& getEntities();                                       // Get all entities
    EntityVec& getEntities(const std::string& tag);                 // Get all entities with a tag
};

#endif