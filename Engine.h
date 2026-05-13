#pragma once
#include "Scene.h"
#include "Camera.h"
#include "HitInfo.h"
#include "Vec2.h"
#include "Vec3.h"

class Engine{
  private:
    Scene &scene;
    Camera cam;

  public:
    Engine(Scene &sce, Camera &cam) : scene(sce), cam(cam) {
    };
  

    //Traça um ray dado origem e direção, e determina intersecções
    Color TraceRay(Vector3 O, Vector3 D, float t_min, float t_max, int limit){

      HitInfo hitInfo = closestIntersection(O, D, t_min, t_max);
      
      //Sem hit outra cor
      if(!hitInfo.hit) {
        return Color(0.3f, 0.3f, 0.3f);
      }

      //Ponto P aonde vamos calcular luz
      Vector3 P = O + D * hitInfo.closest_t;
      //Normal do ponto P
      Vector3 N = P - hitInfo.closest_sphere.center;
      N = Vector3::normalized(N);

      //Vetor que aponta do ponto P até a origem, View direction
      D = Vector3::normalized(D);

      //Com hit retorna cor da esféra * intesidade da luz naquele ponto
      float intensity = ComputeLighting(N, P, D * -1, hitInfo.closest_sphere.specular);
      Color localColor = hitInfo.closest_sphere.color * intensity;

      //Recursividade pra calcular reflexo
      float r = hitInfo.closest_sphere.reflective;
      if(limit <= 0){
        return localColor;
      }

      Vector3 R = reflectRay(N, D * -1);
      Color reflectedColor = TraceRay(P, R, 0.001f, t_max, limit - 1);

      //Nao entendi direito isso aqui ainda
      Color finalcolor = localColor * (1 - r) + reflectedColor * r;

      return finalcolor;
      
    }

    //Computa a interseção mais próxima dado um ray
    HitInfo closestIntersection(Vector3 O, Vector3 D, float t_min, float t_max){

      //Começa com o closest_t no infinito
      float closest_t = std::numeric_limits<float>::infinity();
      Sphere closest_sphere;
      bool hit = false;

      for(int i = 0; i < scene.currentSpheres; i++){
        
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

      HitInfo intersection;
      intersection.closest_t = closest_t;
      intersection.closest_sphere = closest_sphere;
      intersection.hit = hit;

      return intersection;
    }

    //Dado Origem, Direção e uma esfera, checa se essa esfera foi intersectada
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
    
    //Computa a intensidade da luz com base na Normal de P e o ponto P.
    float ComputeLighting(Vector3 N, Vector3 P, Vector3 V, int specular){

      float intensity;
      float t_max;
      Vector3 L;

      for(int i = 0; i < scene.currentLights; i++)
      {
        
        //Pega a luz atual da cena.
        Lights currentLight = scene.lights[i];

        //Se for ambient, só soma valor fixo
        if(currentLight.type == "ambient")
        {
          intensity += currentLight.intensity;
        }
        else
        { 
          //Se for point, retorna vetor de direção.
          if(currentLight.type == "point"){
            L = currentLight.position - P;
            t_max = 1;
          }
          else if (currentLight.type == "directional"){
            L = currentLight.direction;
            t_max = std::numeric_limits<float>::infinity();
          }

          //Normaliza o vetor da luz
          L = Vector3::normalized(L);
          
          //Calcula sombras
          HitInfo shadow = closestIntersection(P, L, 0.001, t_max);
          if(shadow.hit){
            continue;
          }

          //Dot product entre a Luz e a Normal nos retorna um valor equivalente a Intensidade/Area
          //normalizando entao esse valor, multiplicamos pela nossa cor no final após o return
          //Diffuse
          float n_dot_l = Vector3::dot(N, L);

          if(n_dot_l > 0){
            intensity += n_dot_l * currentLight.intensity;
          }

          
          //Specular diffusion
          //Se for -1 significa que é uma esféra matte
          if(specular != -1){

            Vector3 R = reflectRay(N, L);

            //O quanto a View Direction esta de acordo com R para ver o brilho
            float r_dot_v = Vector3::dot(R, V);
  
            if(r_dot_v > 0){
              intensity += currentLight.intensity * std::pow(r_dot_v, specular);
            }
          }
  
        }
      };

      return intensity;
    }

    //Reflete um vetor com base em outro
    Vector3 reflectRay(Vector3 N, Vector3 R){
      return ((2.0 * N) * Vector3::dot(N, R)) - R;
    }
};