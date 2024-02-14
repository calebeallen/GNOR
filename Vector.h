
#ifndef VECTOR
#define VECTOR

  #include <Math.h>

  class Vector{

    float x = 0, y = 0, z = 0;

    Vector( float, float, float );

    void copy( Vector );

    void rotate( float );

    void setFromAngle();

    void normalize();

    float angle();

    float magnitude();

  }

#endif