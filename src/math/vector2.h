#pragma once
#include <cmath>

class Vector2
{
public:
  Vector2() : X(0.0f), Y(0.0f) {}
  Vector2(float x, float y) : X(x), Y(y) {}
  float X, Y;

  void add(const Vector2 &b)
  {
    X += b.X;
    Y += b.Y;
  }

  void add(float x, float y)
  {
    X += x;
    Y += y;
  }

  float magnitude()
  {
    return sqrt(X * X + Y * Y);
  }

  Vector2 normalized()
  {
    return Vector2(this->X / magnitude(), this->Y / magnitude());
  }

  float distanceTo(const Vector2 &b) {
    return Distance(*this, b);
  }

  Vector2 operator-(const Vector2 &b)
  {
    // Vector2 a;
    // a.X = this->X - b.X;
    // a.Y = this->Y - b.Y;
    // return a;
    return Vector2(this->X - b.X, this->Y - b.Y);
  }

  Vector2 operator*(float v)
  {
    Vector2 a;
    a.X = this->X * v;
    a.Y = this->Y * v;
    return a;
  }

  static float Distance(const Vector2 &a, const Vector2 &b)
  {
    return sqrt(DistanceSquared(a, b));
  }

  static float DistanceSquared(const Vector2 &a, const Vector2 &b)
  {
    return (a.X - b.X) * (a.X - b.X) + (a.Y - b.Y) * (a.Y - b.Y);
  }
};