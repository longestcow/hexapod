#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeSerif18pt7b.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver();
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41);

struct Leg {
  Adafruit_PWMServoDriver pwm;
  int j[3]; 
};

Leg legs[6];
int stateCount = 9, state=0;
int timeMs = 50;
char c = 'a';
String text = "";
int id,x,y,z;
bool newText = false;
bool mode = true;

#define TFT_CS 10 
#define TFT_DC 9   
#define TFT_RST -1 
int width = 320;
int height = 240;
int textSize = 7;
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

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
//    delay(100);
    jointC++;
  }
  jointC=0;
  legC++;
  for(int i = 0; i<11; i++){
    if(i==3 || i==7){i++;legC++;jointC=0;}
    pwm2.writeMicroseconds(i,1600);
    legs[legC].pwm=pwm2;
    legs[legC].j[jointC]=i;
//    delay(100);
    jointC++;
  }

//  delay(100);
    Serial.println("current format: [leg] [joint] [angleMS]");

    //display stuff

    tft.init(height,width); 
    tft.invertDisplay(true);
    tft.setRotation(2); 
    tft.setTextWrap(false);
    tft.fillScreen(ST77XX_BLACK); 
    
    tft.setTextColor(ST77XX_GREEN); 
    tft.setTextSize(textSize); 
    tft.setFont(&FreeSerif18pt7b);  // Set a custom font

    int x = 80;
    int y = 210;
    tft.setCursor(x-20, y);  
    tft.print(":");
    tft.setTextSize(textSize-1); 
    tft.setCursor(x+20,y-10);
    tft.print(")");

}


void loop() {
  while(Serial.available()){
    c = (char) Serial.read();
    if(c=='\n'){
      newText=true;
      break;
    }
    text+=c;
  }

  if(newText){
    newText=false;
    if(text.equals("mode")){
      mode=!mode;
      if(mode)
        Serial.println("current format: [leg] [joint] [angleMS]");
      else
        Serial.println("current format: [leg] [j1] [j2] [j3]");
    }
    else
      moveLeg(text);
    
    text="";
  }
  
}

void moveLeg(String text) {
  if(mode){// [leg] [joint] [angleMS]
    
    id = text.substring(0,text.indexOf(" ")).toInt();
    text=text.substring(text.indexOf(" ")+1);
    x = text.substring(0,text.indexOf(" ")).toInt();
    text=text.substring(text.indexOf(" ")+1);
    y = text.substring(0,text.indexOf(" ")).toInt();
    
    legs[id-1].pwm.writeMicroseconds(legs[id-1].j[x-1], y);
    
    Serial.print("changed leg ");
    Serial.print(id);
    Serial.print(" (joint ");
    Serial.print(x);
    Serial.print(") to ");
    Serial.println(y);
    
  }
  else {// [leg] [j1] [j2] [j3]
    id = text.substring(0,text.indexOf(" ")).toInt();
    text=text.substring(text.indexOf(" ")+1);
    x = text.substring(0,text.indexOf(" ")).toInt();
    text=text.substring(text.indexOf(" ")+1);
    y = text.substring(0,text.indexOf(" ")).toInt();
    text=text.substring(text.indexOf(" ")+1);
    z = text.substring(0,text.indexOf(" ")).toInt();
    
    legs[id-1].pwm.writeMicroseconds(legs[id-1].j[0], x);
    legs[id-1].pwm.writeMicroseconds(legs[id-1].j[1], y);
    legs[id-1].pwm.writeMicroseconds(legs[id-1].j[2], z);

    Serial.print("changed leg ");
    Serial.print(id);
    Serial.print(" to ");
    Serial.print(x); Serial.print(", ");
    Serial.print(y); Serial.print(", ");
    Serial.println(z);
  }

}
