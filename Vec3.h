#pragma once

struct Vector3{
  float x, y, z;

  constexpr Vector3(float x, float y, float z) : x(x), y(y), z(z) {};

  Vector3 operator+(const Vector3 v){
    return Vector3(x + v.x, y + v.y, z + v.z);
  }

  Vector3 operator-(const Vector3 v){
    return Vector3(x - v.x, y - v.y, z - v.z);
  }

};