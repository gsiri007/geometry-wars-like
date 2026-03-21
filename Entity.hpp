#include <cstddef>
#include <memory>
#include "Components.hpp"

enum class Tag {
  Default,
  Player,
  Enemy,
  Bullet,
  Special,
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
  std::unique_ptr<CTransform> cTransform;
  std::unique_ptr<CShape>     cShape;
  std::unique_ptr<CCollision> cCollision;
  std::unique_ptr<CInput>     cInput;
  std::unique_ptr<CScore>     cScore;
  std::unique_ptr<CLifespan>  cLifespan;

  size_t  id()       const;
  bool    isAlive()  const;
  Tag     tag()      const;

  void destroy();
};
