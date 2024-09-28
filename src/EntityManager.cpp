#include "EntityManager.h"

void EntityManager::update()
{
    for (auto entity : m_entitiesToAdd)
    {
        m_entities.push_back(entity);
        m_entityMap[entity->tag()].push_back(entity);
    }
    m_entitiesToAdd.clear();

    removeDeadEntities(m_entities);

    for (auto& [tag, entityVec] : m_entityMap)
    {
        removeDeadEntities(entityVec);
    }
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
    auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));

    m_entitiesToAdd.push_back(entity);

    return entity;
}

void EntityManager::removeDeadEntities(EntityVec& vec)
{
    // shifts elements to be deleted to the end, and returns iterator to the start of that
    auto new_end = std::remove_if(vec.begin(), vec.end(), [](const std::shared_ptr<Entity>& e) {return !e->isActive();});

    // remove elements shifted to the end to be deleted
    vec.erase(new_end, vec.end());
}

EntityVec& EntityManager::getEntities()
{
    return m_entities;
}

EntityVec& EntityManager::getEntities(const std::string& tag) 
{
    return m_entityMap[tag];
}

