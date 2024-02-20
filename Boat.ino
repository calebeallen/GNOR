
#include <Wire.h>
#include "Vector.h"

#define ACC_SENS 16384.0 //accelerometer sensitivity
#define MPU6050 0x68
#define POND_A 8; //length from pong origin to side (meters)
#define POND_B 10; //length from pond origin to edge nearest to library (meters)

Vector currentPos, pos, ideal;

float t1 = 0, t2 = 0, dt = 0;

float adjustAngle, theta, lenDifference; //phi is angle between set xAxis and accelerometer x axis

int state = 0;

void setup() {

  //begin communication with accelerometer
  Wire.begin();                      
  Wire.beginTransmission(MPU);      

  //Reset accelerometer
  Wire.write(0x6B);                  // Talk to the register 6B
  Wire.write(0x00);                  // Make reset - place a 0 into the 6B register
  Wire.endTransmission(true);  
 
}

void loop() {

  /* Set position of boat relative to where it was turned on */

  Wire.beginTransmission(MPU);
  Wire.write(0x3B); // Start with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission( false );
  Wire.requestFrom( MPU, 6, true ); // Read 6 registers total, each axis value is stored in 2 registers

  t2 = millis(); // get current time in milliseconds    
  dt = ( t2 - t1 ) / 1000; //calculate change in time in second

  //read 16 bit acceleration data for each axis. each Wire.read() increments read by 8 bits
  currentPos.x += deltaPos( ( Wire.read() << 8 | Wire.read() ) / 2G_SENS );
  currentPos.y += deltaPos( ( Wire.read() << 8 | Wire.read() ) / 2G_SENS );

  //set this time to previous time
  t1 = t2;

  switch(state){

    //await calibration
    case 0:

      //on calibration button clicked

      //define x axis using angle of current position
      adjustAngle = -currentPos.angle();

      state = 1;

      break;

    //awaiting start
    case 1;

      //if start button clicked
      state = 2;

      break;

    //go
    case 2:

      /* Read accelerometer data to update position */

      pos.copy( currentPos );
      pos.rotate( adjustAngle ); //adjust with calibration axis

      ideal.setFromAngle( pos.angle() ); //set ideal vector from angle of position

      ideal.x *= POND_A;
      ideal.y *= POND_B;

      lenDifference = pos.magnitude() - ideal.magnitude();

      if(lenDifference < 0){

        //turn right

      }else if(lenDifference > 0){

        //turn left

      }

      break;

  }
 
}

float deltaPos( float a ){
 
  return a * (dt * dt) / 2;
 
}



