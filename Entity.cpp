#include "Entity.hpp"

Entity::Entity(size_t id, Tag tag)
  : m_id(id)
  , m_tag(tag)
{}

inline size_t Entity::id() const
{
  return m_id;
}

inline bool Entity::isAlive() const
{
  return m_alive;
}

inline Tag Entity::tag() const
{
  return m_tag;
}

inline void Entity::destroy()
{
  m_alive = false;
}
