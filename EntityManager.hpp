#include "Entity.hpp"
#include <cstddef>
#include <map>
#include <memory>
#include <vector>

typedef  std::vector<std::shared_ptr<Entity>>   EntityVec;
typedef  std::map<Tag, EntityVec>               EntityMap;

class EntityManager
{
  EntityVec   m_entities;
  EntityVec   m_buffer;
  EntityMap   m_entityMap;
  size_t      m_nextID        { 0 };
  size_t      m_totalEntities { 0 };

public:
  EntityManager();

  std::shared_ptr<Entity> addEntity(Tag tag);
  EntityVec &   getEntities();
  EntityVec &   getEntities(Tag tag);
  const size_t  getTotalEntities() const;

  void update();
};
