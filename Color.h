#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <algorithm>

class Color {
  public:
    std::uint8_t r, g, b, a;

    //Clamp de color pra constructor
    std::uint8_t static constexpr clamp_color(int value){
      if(value < 0) return 0;
      if(value > 255) return 255;
      return static_cast<std::uint8_t>(value);
    }

    //Constructor padrao
    constexpr Color(int r, int g, int b, int a = 255) : 
      r(clamp_color(r)), 
      g(clamp_color(g)), 
      b(clamp_color(b)), 
      a(clamp_color(a)) {}

    //Overload +
    Color operator+(const Color &color) const{
      return Color(r + color.r, g + color.g, b + color.b, a + color.a);
    };

    //Overload -
    Color operator-(const Color &color) const{
      return Color(r - color.r, g - color.g, b - color.b, a - color.a);
    };

    //Overload * by a int
    Color operator*(float scalar) const{
      return Color( r * scalar, g * scalar, b * scalar, a * scalar);
    }

    //Overload * by another color, blending
    Color operator*(const Color &color) const{
      return Color(
        (r * color.r) / 255, 
        (g * color.g) / 255,
        (b * color.b) / 255,
        (a * color.a) / 255);
    };

};
