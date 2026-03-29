class Vec2
{
public:
  float x { 0.0f };
  float y { 0.0f };

  Vec2();

  Vec2(float x, float y);

  Vec2 operator + (const Vec2 & rhs) const;

  Vec2 operator - (const Vec2 & rhs) const;

  Vec2 operator * (const Vec2 & rhs) const;

  Vec2 operator / (const Vec2 & rhs) const;

  bool operator == (const Vec2 & rhs) const;


  Vec2 & operator += (float rhs);

  Vec2 & operator -= (float rhs);

  Vec2 & operator *= (float rhs);

  Vec2 & operator /= (float rhs);


  Vec2 & scale(float sX, float sY);

  float magnitude();

  Vec2 & normalize();

  Vec2 & rotate(float angle);
};
