#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <memory>

#include "Components.h"

class Entity
{
private:
    friend class EntityManager;

    bool        m_active    = true;
    bool        m_id        = 0;
    std::string m_tag       = "default";

    Entity(const size_t id, const std::string& tag);

public:
    std::shared_ptr<CTransform> cTransform;
    std::shared_ptr<CShape>     CShape;
    std::shared_ptr<CCollision> CCollision;
    std::shared_ptr<CInput>     CInput;
    std::shared_ptr<CScore>     CScore;
    std::shared_ptr<CLifespan>  CLifespan;

    bool isActive() const;
    const std::string& tag() const;
    const size_t id() const;
    void destroy();
}; 

#endif