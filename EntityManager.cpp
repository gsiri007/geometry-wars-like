#include "EntityManager.hpp"
#include <memory>

EntityManager::EntityManager() {}

std::shared_ptr<Entity> EntityManager::addEntity(Tag tag)
{
  auto id { m_nextID++ };
  auto e { std::shared_ptr<Entity>(new Entity(id, tag)) };

  m_buffer.push_back(e);
  return e;
}

EntityVec & EntityManager::getEntities()
{
  return m_entities;
}

EntityVec & EntityManager::getEntities(Tag tag)
{
  return m_entityMap.at(tag);
}

const size_t EntityManager::getTotalEntities() const
{
  return m_totalEntities;
}

const size_t EntityManager::getTotalEntities(Tag tag) const
{
  auto entities = m_entityMap.find(tag);

  if (entities != m_entityMap.end())
  {
    return m_entityMap.at(tag).size();
  }

  return 0;
}

void EntityManager::update()
{

  for (const auto & e : m_buffer)
  {
    m_entities.push_back(e);
    m_entityMap[e->m_tag].push_back(e);
    m_totalEntities++;
  }

  m_buffer.clear();

  std::erase_if( m_entities
               , [] (const std::shared_ptr<Entity> & e) { return !(e->m_alive); });

  for (auto & pair : m_entityMap)
  {
    std::erase_if( pair.second
                 , [] (const std::shared_ptr<Entity> & e) { return !(e->m_alive); });
  }
}
