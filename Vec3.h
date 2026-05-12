#pragma once
#include <math.h>

struct Vector3{
  float x, y, z;

  constexpr Vector3(float x, float y, float z) : x(x), y(y), z(z) {};
  constexpr Vector3() : x(0), y(0), z(0) {};
  
  Vector3 operator+(const Vector3& v) const {
    return Vector3(x + v.x, y + v.y, z + v.z);
  }

  Vector3 operator-(const Vector3& v) const {
    return Vector3(x - v.x, y - v.y, z - v.z);
  }

  Vector3 operator*(float e) const {
    return Vector3(x * e, y * e, z * e);
  }

  float static dot(const Vector3& v1, const Vector3& v2){
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
  }

  float static length(const Vector3& vector){

    // Dot product de um Vetor com ele mesmo vira basicamente pitagoras
    // aplicando raíz temos nossa magnitude real.
    return sqrt(dot(vector, vector));
  }

  float static lengthSquared(const Vector3& vector){

    //Isso aqui é basicamente a magnitude porém sem a raíz
    //é o mesmo que:  ||V||^2
    return dot(vector, vector);
  }

  Vector3 static normalized(const Vector3& vector){
    float mag = length(vector);
    
    if (mag > 0.0f) {
        return Vector3(vector.x / mag, vector.y / mag, vector.z / mag);
    }

    return Vector3(0, 0, 0);
  }
};

inline Vector3 operator*(float e, const Vector3& v){
  return v * e;
}
