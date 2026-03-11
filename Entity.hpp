#include <cstddef>
#include <memory>
#include "Components.hpp"

enum class Tag {
  Default,
};

class Entity
{
  friend class EntityManager;

  size_t  m_id      =  0;
  bool    m_alive   =  true;
  Tag     m_tag     =  Tag::Default;

  Entity(size_t id, Tag tag);

public:
  // components
  std::shared_ptr<CTransform> cTransform;
  std::shared_ptr<CShape>     cShape;
  std::shared_ptr<CCollision> cCollision;
  std::shared_ptr<CInput>     cInput;
  std::shared_ptr<CScore>     cScore;
  std::shared_ptr<CLifespan>  cLifespan;

  const  size_t  id()       const;
  const  bool    isAlive()  const;
  const  Tag     tag()      const;

  void destroy();
};
