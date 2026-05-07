#pragma once

struct Vector2{
  int x, y;

  constexpr Vector2(int x, int y) : x(x), y(y) {};

  constexpr Vector2(unsigned x, unsigned y) : 
    x(static_cast<int>(x)), y(static_cast<int>(y)) {}
};