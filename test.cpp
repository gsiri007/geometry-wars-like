#include "Vec2.hpp"
#include <cassert>
#include <cmath>
#include <iostream>

int main()
{
  Vec2 v1(100, 50);
  Vec2 v2(50, 25);

  assert(v1 + v2 == Vec2(150, 75));
  assert(v1 - v2 == Vec2(50, 25));
  assert(v1 * v2 == Vec2(5000, 1250));
  assert(v1 / v2 == Vec2(2, 2));

  assert((v1 += 10) == Vec2(110, 60));
  assert((v1 -= 10) == Vec2(100, 50));
  assert((v1 *= 10) == Vec2(1000, 500));
  assert((v1 /= 10) == Vec2(100, 50));

  assert(v1.scale(0.5, -2) == Vec2(50, -100));
  assert(v2.magnitude() == sqrtf((50 * 50) + (25 * 25)));
  //TODO: assertion for normalize

  std::cout << "Vec2: PASSED" << '\n';

  return 0;
}
