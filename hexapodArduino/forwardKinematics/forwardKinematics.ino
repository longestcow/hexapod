#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver();
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41);

struct Leg {
  Adafruit_PWMServoDriver pwm;
  int j[3]; 
  int b_d[3], b_md[3], b_m[3], b_mu[3], m_u[3], f_mu[3], f_m[3], f_md[3], 
      f_d[3], b_b1[3], b_b2[3], b_b3[3], b_mb[3], b_b4[3], b_b5[3], b_b6[3];
      
  int* states[16] = {b_d, b_md, b_m, b_mu, m_u, f_mu, f_m, f_md, f_d, b_b1, b_b2, b_b3, b_mb, b_b4, b_b5, b_b6};

};
void moveLeg(int i, bool lLeg = false);

Leg legs[6];
int stateCount = 9, state=0;
int timeMs = 30;
unsigned long timer;

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
  fillLegValues();
  timer=millis()+timeMs;



}


void loop() {
//  moveLeg(0);
//  moveLeg(2);
//  moveLeg(4);
//  moveLeg(1);
//  moveLeg(3);
//  moveLeg(5, true);


  for(int j = 0; j<stateCount+7; j++){
    for(int i = 0; i<6; i++){
      moveLeg(i);
    }
    delay(timeMs);
  }

}

void fillLegValues(){  
  int a[] = {0,2,3,5};
  int b[] = {1,4};
  int c[] = {1,3,5};

  int diffA = -100, diffB = 100, diffC = 50;
  int currA = 2000, currB = 1900, currC = 1600;
  
  for(int i = 0; i<sizeof(a)/sizeof(int); i++){ 
    for(int j = 0; j<stateCount; j++){
      legs[a[i]].states[j][2] = currA;
      legs[a[i]].states[j][1] = currB;
      legs[a[i]].states[j][0] = currC;

      if(j==(stateCount/2)){
        diffB*=-1; diffC*=-1;
      }
      currA+=diffA; currB+=diffB; currC+=diffC;

    }
    currA-=diffA;
    for(int j = 0; j<7; j++){
      legs[a[i]].states[stateCount+j][2] = currA-diffA;
      legs[a[i]].states[stateCount+j][1] = currB;
      legs[a[i]].states[stateCount+j][0] = currC;

      currA-=diffA;
      
    }
    diffA=-100;diffB=100;diffC=50;
    currA=2000;currB=1900;currC=1600;

  }
  
  currA=1200;currB=1900;currC=1600;
  diffA=100;diffB=100;diffC=50;
  for(int i = 0; i<sizeof(b)/sizeof(int); i++){
    for(int j = 0; j<stateCount; j++){
      legs[b[i]].states[j][2] = currA;
      legs[b[i]].states[j][1] = currB;
      legs[b[i]].states[j][0] = currC;

      
      if(j==(stateCount/2)){
        diffB*=-1; diffC*=-1;
      }
      currA+=diffA; currB+=diffB; currC+=diffC;

    }
    currA-=diffA;
    for(int j = 0; j<7; j++){
      legs[b[i]].states[stateCount+j][2] = currA-diffA;
      legs[b[i]].states[stateCount+j][1] = currB;
      legs[b[i]].states[stateCount+j][0] = currC;

      currA-=diffA;
    }
    currA=1200;currB=1900;currC=1600;
    diffA=100;diffB=100;diffC=50;
    
  }

  for(int i = 0; i<sizeof(c)/sizeof(int); i++){
    for(int j = 0; j<stateCount+7; j++){
      if(i==0) {
        Serial.print(legs[c[i]].states[j][2]);
        Serial.print(" - ");
        Serial.println(switchVal(legs[c[i]].states[j][2], 1600));
      }
      legs[c[i]].states[j][2] = switchVal(legs[c[i]].states[j][2], 1600);
    }
  }

  

}

int switchVal(int angle, int midpoint){
  int diff = abs(midpoint-angle);
  if(angle>midpoint) 
    return (midpoint - diff);
  
  else 
    return (midpoint + diff);
}

void moveLeg(int i, bool lLeg){
//  if(timer>millis())return;

  if(i%2==0){
    legs[i].pwm.writeMicroseconds(legs[i].j[2], legs[i].states[state][2]);
    legs[i].pwm.writeMicroseconds(legs[i].j[1], legs[i].states[state][1]);
    legs[i].pwm.writeMicroseconds(legs[i].j[0], legs[i].states[state][0]);
  }
  else {
    legs[i].pwm.writeMicroseconds(legs[i].j[2], legs[i].states[(state+9)%16][2]);
    legs[i].pwm.writeMicroseconds(legs[i].j[1], legs[i].states[(state+9)%16][1]);
    legs[i].pwm.writeMicroseconds(legs[i].j[0], legs[i].states[(state+9)%16][0]);
  }

  if(i==5) {
    state++;
//    if(state==16)timer=millis()+timeMs*3;
//    else timer = millis()+timeMs;
  }
  
  if(state==16) 
    state=0;



  
}
