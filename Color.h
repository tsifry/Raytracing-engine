#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <algorithm>

class Color {
  public:
    float r, g, b, a;

    //Constructor padrao
    constexpr Color() : 
      r(0), g(0), b(0), a(0) {};

    constexpr Color(float r, float g, float b, float a = 1) : 
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
      return Color(r * scalar, g * scalar, b * scalar, a * scalar);
    }

    //Overload * by another color, blending
    Color operator*(const Color &color) const{
      return Color(r * color.r, g * color.g, b * color.b, a * color.a);
    };

    static Color clamp(Color &color){
      color.r = std::clamp(color.r, 0.0f, 1.0f);
      color.g = std::clamp(color.g, 0.0f, 1.0f);
      color.b = std::clamp(color.b, 0.0f, 1.0f);
      color.a = std::clamp(color.a, 0.0f, 1.0f);

      return color;
    };

};
