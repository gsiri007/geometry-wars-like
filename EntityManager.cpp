#include "EntityManager.hpp"
#include <memory>

const size_t EntityManager::addEntity(Tag tag)
{
  auto id { m_nextID++ };
  auto e { std::make_shared<Entity>(Entity(id, tag)) };

  m_buffer.push_back(e);
  return id;
};

const EntityVec & EntityManager::getEntities() const
{
  return m_entities;
};

const EntityVec & EntityManager::getEntities(Tag tag) const
{
  return m_entityMap.at(tag);
};

const size_t EntityManager::getTotalEntities() const
{
  return m_totalEntities;
};

void EntityManager::toggleEntityAlive(size_t id)
{
  for (auto & e : m_entities)
  {
    if (e->m_id == id)
    {
      e->m_alive = !(e->m_alive);
    }
  }
};

void EntityManager::update()
{

  for (auto & e : m_buffer)
  {
    m_entities.push_back(e);
    m_entityMap[e->m_tag].push_back(e);
    m_totalEntities++;
  }

};
