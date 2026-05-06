#include <iostream>
#include <SFML/Graphics.hpp>
#include "Color.h"
#include "Vec2.h"

class Canvas{
  public:
    Canvas(const int &WIDTH, const int &HEIGHT) : 
      WIDTH(WIDTH), HEIGHT(HEIGHT), pixels( new std::uint8_t[ WIDTH * HEIGHT * 4]() ) {};
    ~Canvas() { delete[] pixels; }
    int WIDTH;
    int HEIGHT;
    std::uint8_t *pixels;
    void PutPixel(const unsigned int x, unsigned int y, const Color &color){
      if(x >= WIDTH || y >= HEIGHT) return;

      int i = (y * WIDTH + x) * 4;

      pixels[i + 0] = color.r; 
      pixels[i + 1] = color.g; 
      pixels[i + 2] = color.b;   
      pixels[i + 3] = color.a; 
    }

    void PutPixel(Vec2 v, const Color &color){
      PutPixel(static_cast<unsigned>(v.x), static_cast<unsigned>(v.y), color);
    }
};