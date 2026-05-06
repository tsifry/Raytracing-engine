#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Color {
  public:
    std::uint8_t r, g, b, a;

    constexpr Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) : 
      r(r), g(g), b(b), a(a) {}
};
