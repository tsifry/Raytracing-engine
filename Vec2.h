#pragma once

struct Vector2{
  float x, y;

  constexpr Vector2(float x, float y) : x(x), y(y) {};

  constexpr Vector2(unsigned x, unsigned y) : 
    x(static_cast<int>(x)), y(static_cast<int>(y)) {}
};