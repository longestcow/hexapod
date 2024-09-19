#include <Arduino.h>
#include <Servo.h>
#include <math.h>
#include "vector_type.h"

Servo coxa, femur, tibia;
const float length1 = 2.2, length2 = 3.4;
float cx = 0, cy = 0, cz = 0;

void setup() {
  coxa.attach(3);
  femur.attach(6);
  tibia.attach(7);
  Serial.begin(9600);

}

void loop() {
  moveToPos(++cx,++cy,++cz);
  delay(3000);

}

void moveToPos(float x, float y, float z){
    float j1 = atan2(-z,x) * (180 / PI);

    float l = sqrt(x*x + z*z);
    float h = sqrt(l*l + y*y);

    float phi = atan(y/l) * (180/PI);
        
    float theta1 = acos(constrain(((length1*length1)+(h*h)-(length2*length2))/(2*length1*h), -1, 1)) * (180/PI);
    float theta2 = acos(constrain(((length1*length1)+(length2*length2)-(h*h))/(2*length1*length2), -1, 1)) * (180/PI);

    float j2 = phi + theta1;
    float j3 = theta2 + 180;
    
    Serial.println(j1);
    Serial.println(j2);
    Serial.println(j3);
    Serial.println("------------");
    
}
