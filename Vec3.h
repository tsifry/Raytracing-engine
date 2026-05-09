#pragma once
#include <math.h>

struct Vector3{
  float x, y, z;

  constexpr Vector3(float x, float y, float z) : x(x), y(y), z(z) {};

  Vector3 operator+(const Vector3 v){
    return Vector3(x + v.x, y + v.y, z + v.z);
  }

  Vector3 operator-(const Vector3 v){
    return Vector3(x - v.x, y - v.y, z - v.z);
  }

  float static dotProduct(const Vector3 v1, const Vector3 v2){
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
  }

  float static magnitude(const Vector3 vector){
    return sqrt(dotProduct(vector, vector));
  }

  Vector3 static normalized(const Vector3 vector){
    float mag = magnitude(vector);
    
    if (mag > 0.0f) {
        return Vector3(vector.x / mag, vector.y / mag, vector.z / mag);
    }

    return Vector3(0, 0, 0);
  }
};