#pragma once
#include "Vec3.h"
#include "Sphere.h"
#include "Scene.h"
#include <math.h>
#include <limits>

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

    Vector2 IntersectRaySphere(Vector3 O, Vector3 D, Sphere sph){

      //Caso não retorne nada, retorna indef
      float indef = -100;

      //Vetor do centro até origem, C - O
      Vector3 CO =  O - sph.center;
      
      //Quadratica que descobrer qual componente escalar faz o ponto P acerta a superfície da esfera
      //Se tiver duas raízes significa que atravessou por completo
      float a = Vector3::lengthSquared(D);
      float b = 2 * Vector3::dot(CO, D);
      float c = Vector3::lengthSquared(CO) - (sph.radius * sph.radius);

      float discriminante = (b * b) - 4 * a * c;
      float numerador = 2 * a;

      //Discriminante = 0 quando não acertou nada
      if( discriminante < 0){
        return Vector2(indef, indef);
      }

      float sqrtDisc = std::sqrt(discriminante);
      float t1 = (-b + sqrtDisc) / numerador;
      float t2 = (-b - sqrtDisc) / numerador;

      //Retorna raízes
      return Vector2(t1, t2);
    }

    Color TraceRay(Vector3 O, Vector3 D, float t_min, float t_max, const Scene &scene){

      //Começa com o closest_t no infinito
      float closest_t = std::numeric_limits<float>::infinity();
      Sphere closest_sphere;
      bool hit = false;

      for(int i = 0; i < scene.totalQty; i++){
        
        //Pra cada esfera, checa se o ray vai ter alguma raiz
        Sphere sph = scene.spheres[i];
        Vector2 t = IntersectRaySphere(O, D, sph);

        //Se tiver uma raiz e ela for a que esta mais perto do viewport, hit = true;
        if(t.x >= t_min && t.x <= t_max && t.x < closest_t){
          closest_t = t.x;
          closest_sphere = sph;
          hit = true;
        }

        if(t.y >= t_min && t.y <= t_max && t.y < closest_t){
          closest_t = t.y;
          closest_sphere = sph;
          hit = true;
        }
      }
      
      //Sem hit retorna branco
      if(!hit) {
        return Color(1, 1, 1, 1);
      }

      //Com hit retorna cor da esféra
      return closest_sphere.color;
    }
};