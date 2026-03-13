#include <cmath>
#include "Vec2.hpp"

Vec2::Vec2(float x, float y)
  : x(x)
  , y(y)
{}

Vec2 Vec2::operator + (const Vec2 & rhs) const
{
  return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator - (const Vec2 & rhs) const
{
  return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator * (const Vec2 & rhs) const
{
  return Vec2(x * rhs.x, y * rhs.y);
}

Vec2 Vec2::operator / (const Vec2 & rhs) const
{
  return Vec2(x / rhs.x, y / rhs.y);
}

bool Vec2::operator == (const Vec2 & rhs) const
{
  return (x == rhs.x && y == rhs.y);
}

Vec2 & Vec2::operator += (float rhs)
{
  x += rhs;
  y += rhs;

  return *this;
}

Vec2 & Vec2::operator -= (float rhs)
{
  x -= rhs;
  y -= rhs;

  return *this;
}

Vec2 & Vec2::operator *= (float rhs)
{
  x *= rhs;
  y *= rhs;

  return *this;
}

Vec2 & Vec2::operator /= (float rhs)
{
  x /= rhs;
  y /= rhs;

  return *this;
}

Vec2 & Vec2::scale(float sX, float sY)
{
  x *= sX;
  y *= sY;

  return *this;
}

float Vec2::magnitude(void)
{
  return std::sqrtf((x * x) + (y * y));
}

Vec2 & Vec2::normalize(void)
{
  float m { std::sqrtf((x * x) + (y * y)) };
  *this /= m;

  return *this;
}
