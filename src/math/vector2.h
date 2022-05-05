#pragma once
#define _USE_MATH_DEFINES
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
    float mag = magnitude();
    return Vector2(this->X / mag, this->Y / mag);
  }

  float distanceTo(const Vector2 &b)
  {
    return Distance(*this, b);
  }

  float getAngleRad()
  {
    return atan2(Y, X);
  }

  float getAngleDeg()
  {
    return getAngleRad() * 180 / M_PI;
  }

  void print(std::string message = "")
  {
    std::cout << message << "(x: " << X << ", y: " << Y << ")" << std::endl;
  }

  Vector2 operator-()
  {
    return Vector2(-this->X, -this->Y);
  }

  Vector2 operator-(const Vector2 &b)
  {
    return Vector2(this->X - b.X, this->Y - b.Y);
  }

  Vector2 operator+(const Vector2 &b)
  {
    return Vector2(this->X + b.X, this->Y + -b.Y);
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

  static Vector2 AngleToVector(float angle)
  {
    return Vector2(cos(angle), sin(angle));
  }

  static Vector2 RandomUnitVector()
  {
    float randomAngle = ((rand() % 1000) / 1000.0f) * M_PI * 2.0f;
    return AngleToVector(randomAngle);
  }
};