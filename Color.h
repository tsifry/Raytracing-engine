#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <algorithm>

class Color {
  public:
    float r, g, b, a;

    //Constructor padrao
    constexpr Color(int r, int g, int b, int a = 255) : 
      r(r), g(g), b(b), a(a) {};

    //Overload +
    Color operator+(const Color &color) const{
      return Color(r + color.r, g + color.g, b + color.b, a + color.a);
    };

    //Overload -
    Color operator-(const Color &color) const{
      return Color(r - color.r, g - color.g, b - color.b, a - color.a);
    };

    //Overload * by a float
    Color operator*(float scalar) const{
      return Color( r * scalar, g * scalar, b * scalar, a * scalar);
    }

    //Overload * by another color, blending
    Color operator*(const Color &color) const{
      return Color(r * color.r, g * color.g, b * color.b, a * color.a);
    };

};
