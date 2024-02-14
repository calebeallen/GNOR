
#include "Vector.h"

Vector::Vector(){}

void Vector:copy( Vector v ){

  x = v.x;
  y = v.y;
  z = v.z;

}

void Vector::rotate( float t ){

  float sinT = Math.sin(t), cosT = Math.cos(t);

  //apply rotation matrix to current 
  x = x * cosT - y * sinT;
  y = x * sinT + y * cosT;

}

void Vector::setFromAngle( float t ){

  x = Math.cos(t);
  y = Maht.sin(t);

}

void Vector::normalize(){

  float len = magnitude();

  x /= len;
  y /= len;
  z /= len;

}

float Vector::angle(){

  return Math.atan( y / x );

}

float Vector::magnitude(){

  return Math.sqrt( x * x + y * y + z * z );

}


