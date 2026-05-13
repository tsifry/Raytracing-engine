#pragma once
#include "Sphere.h"

struct HitInfo{
  float closest_t;
  Sphere closest_sphere;
  bool hit;
};