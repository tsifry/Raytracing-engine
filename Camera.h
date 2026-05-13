#pragma once
#include <math.h>
#include <limits>
#include "Vec3.h"
#include "Sphere.h"
#include "Scene.h"
#include "Ligth.h"
#include "HitInfo.h"

class Camera{
  public:
    //Camera and viewport stuff
    Vector3 posO;
    float Vw;
    float Vh;
    float d;

    //Canvas
    int Cw;
    int Ch;
    
    Camera(Vector3 posO, const float &Vw, const float &Vh, const int &Cw, const int &Ch, float const &d) :
      posO(posO), Vw(Vw), Vh(Vh), Cw(Cw), Ch(Ch), d(d) {
    };
    
    Vector3 CanvasToViewportDir(int x, int y){

      //Transforma Cx e Cy em Vx e Vy
      float Vx = x * (Vw / (float)Cw);
      float Vy = y * (Vh / (float)Ch);

      // 2. Define o ponto na Viewport (considerando a distância d)
      Vector3 pointInViewport = Vector3(Vx, Vy, d);

      // 3. Retorna a direção (pointInViewport - camerapos) = (V - O)
      return pointInViewport - posO;

    }
};