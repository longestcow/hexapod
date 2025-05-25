#include <SoftwareSerial.h>
SoftwareSerial BTserial(2, 3); // RX | TX
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

bool clear = true;
 
char c = ' ';
 
void setup() 
{
    Serial.begin(9600);
    BTserial.begin(9600);  
    
    tft.init(height,width); 
    tft.invertDisplay(true);
    tft.setRotation(1); 
    tft.setTextWrap(true);
    tft.fillScreen(ST77XX_BLACK); 
    
    tft.setTextColor(ST77XX_GREEN); 
    tft.setTextSize(textSize);
}
 
void loop()
{
 
    // Keep reading from HC-05 and send to Arduino Serial Monitor
    while(BTserial.available())
    {  
      if(!clear){
        tft.setCursor(width/2-20,height/2);
        tft.fillScreen(ST77XX_BLACK); 
        clear=true;
      }
        c = BTserial.read();
        Serial.write(c);
        tft.print(c);
    }
    clear=false;
 
    // Keep reading from Arduino Serial Monitor and send to HC-05
    if (Serial.available())
    {
        c =  Serial.read();
        BTserial.write(c); 
         
    }
 
}
