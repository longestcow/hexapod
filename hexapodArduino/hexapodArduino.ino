#include <Servo.h>
#include "vector3.h"

struct Leg {
  int startMs, endMs;
  Servo coxaJoint, femurJoint, tibiaJoint;
  Vector3 targetPos; 
  bool forward;
};

Vector3 currentPos = Vector3();
const float length1 = 70, length2 = 148.7;
Leg legs[1];

int potX, potY, potZ;


void setup() {
  int i = 9;
  for(int i = 0; i<3; i++){
    
  }
  
  Serial.begin(9600);

}

void loop() {
//  delay(50);
//  potX = map(analogRead(A0), 0, 1023, -150, 150); potY = map(analogRead(A4), 0, 1023, 0, 200); potZ = map(analogRead(A2), 0, 1023, -200, 200);
////  Serial.println(potX); Serial.println(potY); Serial.println(potZ); Serial.println("--------------");
////  legs[0].coxaJoint.writeMicroseconds(potX);
////  legs[0].femurJoint.writeMicroseconds(potY);
////  legs[0].tibiaJoint.writeMicroseconds(potZ);
//  currentPos.x=potX;currentPos.y=potY;currentPos.z=potZ;
//  moveToPos(currentPos);
  

}

void moveToPos(Vector3 movePos){
    float x = movePos.x, y = movePos.y, z = movePos.z;
    float dis = Vector3(0,0,0).distance(movePos);
    if(dis>length1+length2) return;
    if(dis<length1/2) return;
    float theta1 = atan2(y,x) * (180 / PI); // base angle
    float l = sqrt(x*x + y*y); // x and y extension 
    float h = sqrt(l*l + z*z);
  
    float phi1 = acos(constrain((pow(h,2) + pow(length1,2) - pow(length2,2)) / (2*h*length2),-1,1));
    float phi2 = atan2(z, l);
    float theta2 = (phi1 + phi2) * 180 / PI;
    float phi3 = acos(constrain((pow(length1,2) + pow(length2,2) - pow(h,2)) / (2*length1*length2),-1,1));
    float theta3 = 180 - (phi3 * 180 / PI);
    
    Serial.println(x);
    Serial.println(y);
    Serial.println(z);
    Serial.println("------------");


  legs[0].coxaJoint.writeMicroseconds(map(theta1,0,180,500,2500));
  legs[0].femurJoint.writeMicroseconds(map(theta2,0,180,500,2500));
  legs[0].tibiaJoint.writeMicroseconds(map(theta3,0,180,500,2500));

    
    
}
