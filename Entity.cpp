#include "Entity.hpp"

Entity::Entity(size_t id, Tag tag)
  : m_id(id)
  , m_tag(tag)
{}

const size_t Entity::id() const
{
  return m_id;
};

const bool Entity::isAlive() const
{
  return m_alive;
}

const Tag Entity::tag() const
{
  return m_tag;
};

void Entity::destroy()
{
  m_alive = false;
}
