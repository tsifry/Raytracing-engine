#pragma once
#include <math.h>
#include <limits>
#include "Vec3.h"
#include "Sphere.h"
#include "Scene.h"
#include "Ligth.h"

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
      
      //Quadratica que descobrer qual componente escalar faz o ponto P acertar a superfície da esfera
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
      
      //Sem hit outra cor
      if(!hit) {
        return Color(0.5f, 0.5f, 0.5f);
      }

      //Ponto P aonde vamos calcular luz
      Vector3 P = O + D * closest_t;
      //Normal do ponto P
      Vector3 N = P - closest_sphere.center;
      N = Vector3::normalized(N);

      //Vetor que aponta do ponto P até a origem, View direction
      D = Vector3::normalized(D);

      //Com hit retorna cor da esféra * intesidade da luz naquele ponto
      return closest_sphere.color * ComputeLighting(N, P, D * -1, closest_sphere.specular, scene);
    }

    //Computa a intensidade da luz com base na Normal de P e o ponto P.
    float ComputeLighting(Vector3 N, Vector3 P, Vector3 V, int specular, const Scene &scene){

      float intesinty = 0;
      Vector3 L;

      for(int i = 0; i < scene.currentLights; i++)
      {
        
        //Pega a luz atual da cena.
        Lights currentLight = scene.lights[i];

        //Se for ambient, só soma valor fixo
        if(currentLight.type == "ambient")
        {
          intesinty += currentLight.intensity;
        }
        else
        { 
          //Se for point, retorna vetor de direção.
          if(currentLight.type == "point"){
            L = currentLight.position - P;
          }
          else if (currentLight.type == "directional"){
            L = currentLight.direction;
          }

          //Normaliza o vetor da luz
          L = Vector3::normalized(L);

          //Dot product entre a Luz e a Normal nos retorna um valor equivalente a Intensidade/Area
          //normalizando entao esse valor, multiplicamos pela nossa cor no final após o return
          float n_dot_l = Vector3::dot(N, L);

          if(n_dot_l > 0){
            intesinty += n_dot_l;
          }
          
          //Se for -1 significa que é uma esféra matte
          if(specular != -1){
            //Specular diffusion, calculamos primeiro o Vetor R
            //Sendo R a luz refletida
            Vector3 R;
            R = ((2.0 * N) * n_dot_l) - L;
  
            //O quanto a View Direction esta de acordo com R para ver o brilho
            float r_dot_v = Vector3::dot(R, V);
  
            if(r_dot_v > 0){
              intesinty += std::pow(r_dot_v, specular);
            }
          }
  
        }
      };

      return intesinty;
    }
};