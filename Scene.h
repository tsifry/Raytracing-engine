#pragma once
#include "Sphere.h"
#include "Ligth.h"

class Scene{
  public:
    int totalQty;
    int currentSpheres;
    int currentLights;

    //Scene guarda os objetos na memória
    Scene(int qty) : totalQty(qty), currentSpheres(0), currentLights(0), 
      spheres(new Sphere[totalQty]()), 
      lights(new Lights[3]) {}; 

    ~Scene() { delete[] spheres; delete[] lights; };

    Scene(const Scene &) = delete;
    Scene &operator=(const Scene &) = delete;

    Sphere *spheres;
    Lights *lights;

    Sphere* begin() { return spheres; }
    Sphere* end()   { return spheres + currentSpheres; }

    void AddSphere(const Sphere &sphere){
      if(currentSpheres == totalQty){
        return;
      }

      spheres[currentSpheres] = sphere;
      currentSpheres++;

      return;
    }

    void AddLight(const Lights &light){
      if(currentLights == 3){
        return;
      }

      lights[currentLights] = light;
      currentLights++;

      return;
    }

    void instantiateObjects(){
      
      Sphere s2;
      s2.center = Vector3(0, -1, 2.5);
      s2.color = Color(0, 0, 1);
      s2.radius = 1;
      s2.specular = -1;
      s2.reflective = 0.1;

      Sphere s1;
      s1.center = Vector3(-2, 0, 3);
      s1.color = Color(1, 0, 0);
      s1.radius = 1;
      s1.specular = 1000;
      s1.reflective = 0.2;
      
      Sphere s3;
      s3.center = Vector3(2, 0, 3);
      s3.color = Color(0, 1, 0);
      s3.radius = 1;
      s3.specular = 100;
      s3.reflective = 0.4;

      Sphere s4; 
      s4.center = Vector3(0, -5001, 0);;
      s4.color = Color(0.5, 0.5, 0);
      s4.radius = 5000;
      s4.specular = -1;

      AddSphere(s1);
      AddSphere(s2);
      AddSphere(s3);
      AddSphere(s4);

      //Criação de luzes
      Lights l1;
      l1.type = "ambient";
      l1.intensity = 0.2;

      Lights l2;
      l2.type = "point";
      l2.intensity = 0.6;
      l2.position = Vector3(2, 1, 0);

      Lights l3;
      l3.type = "directional";
      l3.intensity = 0.2;
      l3.direction = Vector3(1, 4, 0);

      AddLight(l1);
      AddLight(l2);
      AddLight(l3);
      
    }

};