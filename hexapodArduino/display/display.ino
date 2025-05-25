#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <Fonts/FreeSerif18pt7b.h>

#define TFT_CS 10 
#define TFT_DC 9   
#define TFT_RST -1 
int width = 320;
int height = 240;
int textSize = 3;

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
void setup() {
    Serial.begin(9600);
    
    tft.init(height,width); 
    tft.invertDisplay(true);
    tft.setRotation(1); 
    tft.setTextWrap(false);
    tft.fillScreen(ST77XX_BLACK); 
    
    tft.setTextColor(ST77XX_GREEN); 
    tft.setTextSize(textSize); 
//    tft.setFont(&FreeSerif18pt7b);  // Set a custom font

//    int x = 80;
//    int y = 210;
//    tft.setCursor(x-20, y);  
//    tft.print(":");
//    tft.setTextSize(textSize-1); 
//    tft.setCursor(x+20,y-10);
//    tft.print(")");

  tft.setCursor(width/2,height/2);
  tft.fillScreen(ST77XX_BLACK); 
  tft.print("h");
  tft.setCursor(width/2,height/2);
  tft.fillScreen(ST77XX_BLACK); 
  tft.print("he");
  tft.setCursor(width/2,height/2);
  tft.fillScreen(ST77XX_BLACK); 
  tft.print("hel");
  tft.setCursor(width/2,height/2);
  tft.fillScreen(ST77XX_BLACK); 
  tft.print("hell");
  tft.setCursor(width/2,height/2);
  tft.fillScreen(ST77XX_BLACK); 
  tft.print("hello");
  tft.setCursor(width/2,height/2);


}

void loop() {
}
