#pragma once


class Time
{
public:
  static Time *instance;
  static Time* Instance();

public:
  float DeltaTime;
};