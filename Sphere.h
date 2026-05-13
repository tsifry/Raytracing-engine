#pragma once
#include "Vec3.h"
#include "Color.h"

//Struct simples pras propriedaeds de uma esféra
struct Sphere {
  Vector3 center;
  float reflective;
  int radius;
  int specular;
  Color color;

};

