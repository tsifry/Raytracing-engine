#pragma once
#include "Sphere.h"

class Scene{
  public:
    int totalQty;
    int current;

    //Scene guarda os objetos na memória
    Scene(int qty) : totalQty(qty), current(0), spheres(new Sphere[totalQty]()) {};
    ~Scene() { delete[] spheres; };

    Scene(const Scene &) = delete;
    Scene &operator=(const Scene &) = delete;

    Sphere *spheres;

    Sphere* begin() { return spheres; }
    Sphere* end()   { return spheres + current; }

    void AddSphere(const Sphere &sphere){
      if(current == totalQty){
        return;
      }

      spheres[current] = sphere;
      current++;

      return;
    }
};