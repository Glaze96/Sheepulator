#pragma once
#include <cmath>
#include <iostream>

class Vector2
{
public:
  Vector2() : X(0.0f), Y(0.0f) {}
  Vector2(float x, float y) : X(x), Y(y) {}
  float X, Y;

  float magnitude()
  {
    return sqrt(X * X + Y * Y);
  }

  Vector2 normalized()
  {
    return Vector2(this->X / magnitude(), this->Y / magnitude());
  }

  float distanceTo(const Vector2 &b)
  {
    return Distance(*this, b);
  }

  void print()
  {
    std::cout << "VECTOR - X: " << X << ", Y: " << Y << std::endl;
  }

  Vector2 operator-(const Vector2 &b)
  {
    return Vector2(this->X - b.X, this->Y - b.Y);
  }

  Vector2 operator+(const Vector2 &b)
  {
    return Vector2(this->X + b.X, this->Y +- b.Y);
  }

  Vector2 operator*(float v)
  {
    Vector2 a;
    a.X = this->X * v;
    a.Y = this->Y * v;
    return a;
  }

  void operator+=(const Vector2 &b)
  {
    this->X += b.X;
    this->Y += b.Y;
  }

  void operator-=(const Vector2 &b)
  {
    this->X -= b.X;
    this->Y -= b.Y;
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