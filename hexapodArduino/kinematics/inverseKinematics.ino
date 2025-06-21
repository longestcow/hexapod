#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "vector3.h"

Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver();
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41);

struct Leg {
  Adafruit_PWMServoDriver pwm;
  int j[3]; 
  Vector3 targetPos;
};
Leg legs[6];
const float length1 = 70, length2 = 176;
char tPos[] = "20,20,20";

void setup() {
  Serial.begin(9600);
  pwm1.begin();
  pwm2.begin();   
  pwm1.setPWMFreq(50);  
  pwm2.setPWMFreq(50);  

  delay(10);
  
  int legC = 0, jointC = 0;
  
  for(int i = 0; i<11; i++){
    if(i==3 || i==7){i++;legC++;jointC=0;}
    pwm1.writeMicroseconds(i,1600);
    legs[legC].pwm=pwm1;
    legs[legC].j[jointC]=i;
    delay(100);
    jointC++;
  }
  jointC=0;
  legC++;
  for(int i = 0; i<11; i++){
    if(i==3 || i==7){i++;legC++;jointC=0;}
    pwm2.writeMicroseconds(i,1600);
    legs[legC].pwm=pwm2;
    legs[legC].j[jointC]=i;
    delay(100);
    jointC++;
  }
  delay(1000);
}

void loop(){
  if(Serial.available() > 0){
    String input = Serial.readStringUntil('\n');  
    int num1 = 0, num2 = 0, num3 = 0;
    int commaIndex1 = input.indexOf(','); 
    int commaIndex2 = input.indexOf(',', commaIndex1 + 1); 
    
    num1 = input.substring(0, commaIndex1).toInt(); 
    num2 = input.substring(commaIndex1 + 1, commaIndex2).toInt(); 
    num3 = input.substring(commaIndex2 + 1).toInt(); 

    legs[0].targetPos = Vector3(num1,num2,num3);
    moveToPos(legs[0]);

  }
}

void moveToPos(Leg leg){ // tPos has been changed by this point
  Vector3 movePos = leg.targetPos;
  float x = movePos.x, y = movePos.y, z = movePos.z;
  float dis = Vector3(0,0,0).distance(movePos);
//  if(dis>length1+length2 || dis<length1/2) {
//    Serial.println(dis);
//    return;
//  }
  
  float theta1 = atan2(y,x) * (180 / PI); // base angle
  float l = sqrt(x*x + y*y); // x and y extension 
  float h = sqrt(l*l + z*z);

  float phi1 = acos(constrain((pow(h,2) + pow(length1,2) - pow(length2,2)) / (2*h*length2),-1,1));
  float phi2 = atan2(z, l);
  float theta2 = (phi1 + phi2) * 180 / PI;
  float phi3 = acos(constrain((pow(length1,2) + pow(length2,2) - pow(h,2)) / (2*length1*length2),-1,1));
  float theta3 = 180 - (phi3 * 180 / PI);
  Serial.print(theta1);
  Serial.print(",");
  Serial.print(theta2);
  Serial.print(",");
  Serial.println(theta3);
  
  leg.pwm.writeMicroseconds(leg.j[2],map(theta1,0,180,600,2600));
  leg.pwm.writeMicroseconds(leg.j[1],map(theta2,0,180,600,2600));
  leg.pwm.writeMicroseconds(leg.j[0],map(theta3,0,180,600,2600));

}
