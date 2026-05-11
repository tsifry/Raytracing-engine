#pragma once
#include <iostream>
#include "Vec3.h"


struct Lights {
  std::string type;
  float intensity;
  Vector3 position;
  Vector3 direction;
};