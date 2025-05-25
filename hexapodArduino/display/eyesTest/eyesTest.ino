#include <Arduino_ST7789_Fast.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include "roboEyes.h"

// Define your TFT pins
#define TFT_CS   10
#define TFT_DC   9
#define TFT_RST  8

// Create your ST7789 display instance (named "display" so that roboEyes uses it)
Adafruit_ST7789 display = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// Create a roboEyes instance
roboEyes eyes;

void setup() {
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  // Initialize the display (adjust resolution as needed)
  display.init(240, 320);  // or tft.initR(...) for certain modules
  display.setRotation(3);  // adjust rotation if needed

  // Start up roboEyes
  eyes.begin(240, 240, 10);  // width, height, and desired frame rate
  eyes.setIdleMode(true, 2, 2); 
  eyes.setAutoblinker(true, 2,2);
}

void loop() {
  eyes.drawEyes();  // update animations according to frameInterval
}
