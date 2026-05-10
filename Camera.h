#pragma once
#include "Vec3.h"

class Camera{
  public:
    Vector3 pos;
    float Vw;
    float Vh;
    float d;

    Camera(Vector3 pos, const float &Vw, const float &Vh, float const &d) :
      pos(pos), Vw(Vw), Vh(Vh), d(d) {
    };
    
    Vector3 generateRayDirection(int x, int y, int Cw, int Ch){
      //Transforma Cx e Cy em Vx e Vy
      float Vx = x * (Vw / (float)Cw);
      float Vy = y * (Vh / (float)Ch);

      // 2. Define o ponto na Viewport (considerando a distância d)
      Vector3 pointInViewport = Vector3(Vx, Vy, d);
      
      // 3. Retorna a direção (pointInViewport - cameraPos) = (V - O)
      // Como CameraPos é (0,0,0) por enquanto, retornamos o ponto.
      return pointInViewport;
    }
};