#include "Vec2.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstddef>


class CTransform
{
public:
  Vec2  position  { 0.0f, 0.0f };
  Vec2  velocity  { 0.0f, 0.0f };
  float angle     { 0.0f };

  CTransform(const Vec2 & p, const Vec2 & v, float a)
    : position(p)
    , velocity(v)
    , angle(a)
  {};
};

class CShape
{
public:
  sf::CircleShape circle;

  CShape( float radius
        , size_t vertices
        , const sf::Color & fillColor
        , const sf::Color & outlineColor
        , float outlineThickness)
    : circle(radius, vertices)
  {
    circle.setFillColor(fillColor);
    circle.setOutlineColor(outlineColor);
    circle.setOutlineThickness(outlineThickness);
    circle.setOrigin(sf::Vector2f(radius, radius));
  }
};

class CCollision
{
public:
  float radius { 0.0f };

  CCollision(float r) : radius(r) {};
};

class CScore
{
public:
  size_t score { 0 };

  CScore(size_t s) : score(s) {};
};

class CLifespan
{
public:
  // FTL - Frames To Live
  size_t initialFTL   { 0 };
  size_t remainingFTL { 0 };

  CLifespan(size_t framesToLive)
    : initialFTL(framesToLive)
    , remainingFTL(framesToLive)
  {}
};

class CInput
{
public:
  bool  up     { false };
  bool  down   { false };
  bool  left   { false };
  bool  right  { false };
  bool  shoot  { false };

  CInput() {};
};
