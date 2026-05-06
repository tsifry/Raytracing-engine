#include <SFML/Graphics.hpp>
#include "Color.h"
#include "Vec2.h"
#include "algorithm"

class Canvas{
  public:
    Canvas(const int &WIDTH, const int &HEIGHT) : 
      WIDTH(WIDTH), HEIGHT(HEIGHT), pixels( new std::uint8_t[ WIDTH * HEIGHT * 4]() ) {};
    ~Canvas() { delete[] pixels; }
    int WIDTH;
    int HEIGHT;
    std::uint8_t *pixels;

    void PutPixel(int x, int y, const Color &color){

      //Conversion from Canvas space to Screen space
      int Sx = (WIDTH / 2) + x;
      int Sy = (HEIGHT / 2) - y;

      //Bound box
      if (Sx < 0 || Sx >= WIDTH || Sy < 0 || Sy >= HEIGHT) return;

      int i = (Sy * WIDTH + Sx) * 4;

      //Transform o float de Color pra uint8_t, enquanto faz o clamp
      pixels[i + 0] = static_cast<std::uint8_t>(std::clamp(color.r * 255.0f, 0.0f, 255.0f)); 
      pixels[i + 1] = static_cast<std::uint8_t>(std::clamp(color.g * 255.0f, 0.0f, 255.0f)); 
      pixels[i + 2] = static_cast<std::uint8_t>(std::clamp(color.b * 255.0f, 0.0f, 255.0f));   
      pixels[i + 3] = static_cast<std::uint8_t>(std::clamp(color.a * 255.0f, 0.0f, 255.0f));
      
    }

    void PutPixel(Vec2 v, const Color &color){
      PutPixel(v.x, v.y, color);
    }
};