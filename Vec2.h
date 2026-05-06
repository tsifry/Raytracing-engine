#pragma once

struct Vec2{
  int x, y;

  constexpr Vec2(int x, int y) : x(x), y(y) {};

  constexpr Vec2(unsigned x, unsigned y) : 
    x(static_cast<int>(x)), y(static_cast<int>(y)) {}
};