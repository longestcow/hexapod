/*
 * FluxGarage RoboEyes for ST7789 TFT Displays V 1.0.1 (Modified)
 * Draws smoothly animated robot eyes on ST7789 TFT displays, based on the Adafruit GFX 
 * library's graphics primitives, such as rounded rectangles and triangles.
 *   
 * Copyright (C) 2024 Dennis Hoelscher
 * www.fluxgarage.com
 * www.youtube.com/@FluxGarage
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

 #ifndef _FLUXGARAGE_ROBOEYES_H
 #define _FLUXGARAGE_ROBOEYES_H
 #include <Adafruit_ST7789.h>

 // Usage of display colors adapted for ST7789 TFT (using Adafruit_ST77XX color constants)
 #define BGCOLOR ST77XX_BLACK  // background and overlays
 #define MAINCOLOR ST77XX_WHITE  // drawings
 
 // For mood type switch
 #define DEFAULT 0
 #define TIRED 1
 #define ANGRY 2
 #define HAPPY 3
 
 // For turning things on or off
 #define ON 1
 #define OFF 0
 
 // For switch "predefined positions"
 #define N 1    // north, top center
 #define NE 2   // north-east, top right
 #define E 3    // east, middle right
 #define SE 4   // south-east, bottom right
 #define S 5    // south, bottom center
 #define SW 6   // south-west, bottom left
 #define W 7    // west, middle left
 #define NW 8   // north-west, top left 
 // for middle center set "DEFAULT"
 extern Adafruit_ST7789 display;
 class roboEyes
 {
   private:
     // (All variables are public in this version for simplicity.)
     
   public:
 
     // For general setup - screen size and max. frame rate
     int screenWidth = 128; // Display width, in pixels
     int screenHeight = 64; // Display height, in pixels
     int frameInterval = 20; // default value for 50 frames per second (1000/50 = 20 milliseconds)
     unsigned long fpsTimer = 0; // for timing the frames per second
 
     // For controlling mood types and expressions
     bool tired = 0;
     bool angry = 0;
     bool happy = 0;
     bool curious = 0; // if true, draw the outer eye larger when looking left or right
     bool cyclops = 0; // if true, draw only one eye
     bool eyeL_open = 0; // left eye opened or closed?
     bool eyeR_open = 0; // right eye opened or closed?
 
     //*********************************************************************************************
     //  Eyes Geometry
     //*********************************************************************************************
 
     // EYE LEFT - size and border radius
     int eyeLwidthDefault = 36;
     int eyeLheightDefault = 36;
     int eyeLwidthCurrent = eyeLwidthDefault;
     int eyeLheightCurrent = 1; // start with closed eye, otherwise set to eyeLheightDefault
     int eyeLwidthNext = eyeLwidthDefault;
     int eyeLheightNext = eyeLheightDefault;
     int eyeLheightOffset = 0;
     // Border Radius
     byte eyeLborderRadiusDefault = 8;
     byte eyeLborderRadiusCurrent = eyeLborderRadiusDefault;
     byte eyeLborderRadiusNext = eyeLborderRadiusDefault;
 
     // EYE RIGHT - size and border radius
     int eyeRwidthDefault = eyeLwidthDefault;
     int eyeRheightDefault = eyeLheightDefault;
     int eyeRwidthCurrent = eyeRwidthDefault;
     int eyeRheightCurrent = 1; // start with closed eye, otherwise set to eyeRheightDefault
     int eyeRwidthNext = eyeRwidthDefault;
     int eyeRheightNext = eyeRheightDefault;
     int eyeRheightOffset = 0;
     // Border Radius
     byte eyeRborderRadiusDefault = 8;
     byte eyeRborderRadiusCurrent = eyeRborderRadiusDefault;
     byte eyeRborderRadiusNext = eyeRborderRadiusDefault;
 
     // EYE LEFT - Coordinates
     int spaceBetweenDefault = 10;
     int eyeLxDefault = ((screenWidth) - (eyeLwidthDefault + spaceBetweenDefault + eyeRwidthDefault)) / 2;
     int eyeLyDefault = ((screenHeight - eyeLheightDefault) / 2);
     int eyeLx = eyeLxDefault;
     int eyeLy = eyeLyDefault;
     int eyeLxNext = eyeLx;
     int eyeLyNext = eyeLy;
 
     // EYE RIGHT - Coordinates
     int eyeRxDefault = eyeLx + eyeLwidthCurrent + spaceBetweenDefault;
     int eyeRyDefault = eyeLy;
     int eyeRx = eyeRxDefault;
     int eyeRy = eyeRyDefault;
     int eyeRxNext = eyeRx;
     int eyeRyNext = eyeRy;
 
     // BOTH EYES 
     // Eyelid top size
     byte eyelidsHeightMax = eyeLheightDefault / 2; // top eyelids max height
     byte eyelidsTiredHeight = 0;
     byte eyelidsTiredHeightNext = eyelidsTiredHeight;
     byte eyelidsAngryHeight = 0;
     byte eyelidsAngryHeightNext = eyelidsAngryHeight;
     // Bottom happy eyelids offset
     byte eyelidsHappyBottomOffsetMax = (eyeLheightDefault / 2) + 3;
     byte eyelidsHappyBottomOffset = 0;
     byte eyelidsHappyBottomOffsetNext = 0;
     // Space between eyes
     int spaceBetweenCurrent = spaceBetweenDefault;
     int spaceBetweenNext = 10;
 
     //*********************************************************************************************
     //  Macro Animations
     //*********************************************************************************************
 
     // Animation - horizontal flicker/shiver
     bool hFlicker = 0;
     bool hFlickerAlternate = 0;
     byte hFlickerAmplitude = 2;
 
     // Animation - vertical flicker/shiver
     bool vFlicker = 0;
     bool vFlickerAlternate = 0;
     byte vFlickerAmplitude = 10;
 
     // Animation - auto blinking
     bool autoblinker = 0; // activate auto blink animation
     int blinkInterval = 1; // basic interval between each blink in full seconds
     int blinkIntervalVariation = 4; // interval variation range in full seconds
     unsigned long blinktimer = 0; // for organizing eyeblink timing
 
     // Animation - idle mode: eyes looking in random directions
     bool idle = 0;
     int idleInterval = 1; // basic interval between each eye repositioning in full seconds
     int idleIntervalVariation = 3; // interval variation range in full seconds
     unsigned long idleAnimationTimer = 0; // for organizing eye repositioning timing
 
     // Animation - eyes confused: eyes shaking left and right
     bool confused = 0;
     unsigned long confusedAnimationTimer = 0;
     int confusedAnimationDuration = 500;
     bool confusedToggle = 1;
 
     // Animation - eyes laughing: eyes shaking up and down
     bool laugh = 0;
     unsigned long laughAnimationTimer = 0;
     int laughAnimationDuration = 500;
     bool laughToggle = 1;
 
     //*********************************************************************************************
     //  GENERAL METHODS
     //*********************************************************************************************
 
     // Startup RoboEyes with defined screen-width, screen-height and max. frames per second
     void begin(int width, int height, byte frameRate) {
       screenWidth = width; // TFT display width, in pixels
       screenHeight = height; // TFT display height, in pixels
       // Clear the display by filling it with the background color
       display.fillScreen(BGCOLOR);
       eyeLheightCurrent = 1; // start with closed eyes
       eyeRheightCurrent = 1; // start with closed eyes
       setFramerate(frameRate); // calculate frame interval based on defined frameRate
     }
 
     void update() {
       // Limit drawing updates to defined max framerate
       if (millis() - fpsTimer >= frameInterval) {
         drawEyes();
         fpsTimer = millis();
       }
     }
 
     //*********************************************************************************************
     //  SETTERS METHODS
     //*********************************************************************************************
 
     // Calculate frame interval based on defined frameRate
     void setFramerate(byte fps) {
       frameInterval = 1000 / fps;
     }
 
     void setWidth(byte leftEye, byte rightEye) {
       eyeLwidthNext = leftEye;
       eyeRwidthNext = rightEye;
       eyeLwidthDefault = leftEye;
       eyeRwidthDefault = rightEye;
     }
 
     void setHeight(byte leftEye, byte rightEye) {
       eyeLheightNext = leftEye;
       eyeRheightNext = rightEye;
       eyeLheightDefault = leftEye;
       eyeRheightDefault = rightEye;
     }
 
     // Set border radius for left and right eye
     void setBorderradius(byte leftEye, byte rightEye) {
       eyeLborderRadiusNext = leftEye;
       eyeRborderRadiusNext = rightEye;
       eyeLborderRadiusDefault = leftEye;
       eyeRborderRadiusDefault = rightEye;
     }
 
     // Set space between the eyes, can also be negative
     void setSpacebetween(int space) {
       spaceBetweenNext = space;
       spaceBetweenDefault = space;
     }
 
     // Set mood expression
     void setMood(unsigned char mood) {
       switch (mood) {
         case TIRED:
           tired = 1;
           angry = 0;
           happy = 0;
           break;
         case ANGRY:
           tired = 0;
           angry = 1;
           happy = 0;
           break;
         case HAPPY:
           tired = 0;
           angry = 0;
           happy = 1;
           break;
         default:
           tired = 0;
           angry = 0;
           happy = 0;
           break;
       }
     }
 
     // Set predefined position
     void setPosition(unsigned char position) {
       switch (position) {
         case N:
           // North, top center
           eyeLxNext = getScreenConstraint_X() / 2;
           eyeLyNext = 0;
           break;
         case NE:
           // North-east, top right
           eyeLxNext = getScreenConstraint_X();
           eyeLyNext = 0;
           break;
         case E:
           // East, middle right
           eyeLxNext = getScreenConstraint_X();
           eyeLyNext = getScreenConstraint_Y() / 2;
           break;
         case SE:
           // South-east, bottom right
           eyeLxNext = getScreenConstraint_X();
           eyeLyNext = getScreenConstraint_Y();
           break;
         case S:
           // South, bottom center
           eyeLxNext = getScreenConstraint_X() / 2;
           eyeLyNext = getScreenConstraint_Y();
           break;
         case SW:
           // South-west, bottom left
           eyeLxNext = 0;
           eyeLyNext = getScreenConstraint_Y();
           break;
         case W:
           // West, middle left
           eyeLxNext = 0;
           eyeLyNext = getScreenConstraint_Y() / 2;
           break;
         case NW:
           // North-west, top left
           eyeLxNext = 0;
           eyeLyNext = 0;
           break;
         default:
           // Middle center
           eyeLxNext = getScreenConstraint_X() / 2;
           eyeLyNext = getScreenConstraint_Y() / 2;
           break;
       }
     }
 
     // Set automated eye blinking, minimal blink interval in full seconds and blink interval variation range in full seconds
     void setAutoblinker(bool active, int interval, int variation) {
       autoblinker = active;
       blinkInterval = interval;
       blinkIntervalVariation = variation;
     }
     void setAutoblinker(bool active) {
       autoblinker = active;
     }
 
     // Set idle mode - automated eye repositioning, minimal time interval in full seconds and time interval variation range in full seconds
     void setIdleMode(bool active, int interval, int variation) {
       idle = active;
       idleInterval = interval;
       idleIntervalVariation = variation;
     }
     void setIdleMode(bool active) {
       idle = active;
     }
 
     // Set curious mode - the respectively outer eye gets larger when looking left or right
     void setCuriosity(bool curiousBit) {
       curious = curiousBit;
     }
 
     // Set cyclops mode - show only one eye 
     void setCyclops(bool cyclopsBit) {
       cyclops = cyclopsBit;
     }
 
     // Set horizontal flickering (displacing eyes left/right)
     void setHFlicker(bool flickerBit, byte Amplitude) {
       hFlicker = flickerBit;
       hFlickerAmplitude = Amplitude;
     }
     void setHFlicker(bool flickerBit) {
       hFlicker = flickerBit;
     }
 
     // Set vertical flickering (displacing eyes up/down)
     void setVFlicker(bool flickerBit, byte Amplitude) {
       vFlicker = flickerBit;
       vFlickerAmplitude = Amplitude;
     }
     void setVFlicker(bool flickerBit) {
       vFlicker = flickerBit;
     }
 
     //*********************************************************************************************
     //  GETTERS METHODS
     //*********************************************************************************************
 
     // Returns the max x position for left eye
     int getScreenConstraint_X() {
       return screenWidth - eyeLwidthCurrent - spaceBetweenCurrent - eyeRwidthCurrent;
     }
 
     // Returns the max y position for left eye
     int getScreenConstraint_Y() {
       return screenHeight - eyeLheightDefault; // using default height here
     }
 
     //*********************************************************************************************
     //  BASIC ANIMATION METHODS
     //*********************************************************************************************
 
     // BLINKING FOR BOTH EYES AT ONCE
     // Close both eyes
     void close() {
       eyeLheightNext = 1; // closing left eye
       eyeRheightNext = 1; // closing right eye
       eyeL_open = 0;
       eyeR_open = 0;
     }
 
     // Open both eyes
     void open() {
       eyeL_open = 1;
       eyeR_open = 1;
     }
 
     // Trigger eyeblink animation
     void blink() {
       close();
       open();
     }
 
     // BLINKING FOR SINGLE EYES, CONTROL EACH EYE SEPARATELY
     // Close eye(s)
     void close(bool left, bool right) {
       if (left) {
         eyeLheightNext = 1;
         eyeL_open = 0;
       }
       if (right) {
         eyeRheightNext = 1;
         eyeR_open = 0;
       }
     }
 
     // Open eye(s)
     void open(bool left, bool right) {
       if (left) {
         eyeL_open = 1;
       }
       if (right) {
         eyeR_open = 1;
       }
     }
 
     // Trigger eyeblink(s) animation
     void blink(bool left, bool right) {
       close(left, right);
       open(left, right);
     }
 
     //*********************************************************************************************
     //  MACRO ANIMATION METHODS
     //*********************************************************************************************
 
     // Play confused animation - one shot animation of eyes shaking left and right
     void anim_confused() {
       confused = 1;
     }
 
     // Play laugh animation - one shot animation of eyes shaking up and down
     void anim_laugh() {
       laugh = 1;
     }
 
     //*********************************************************************************************
     //  PRE-CALCULATIONS AND ACTUAL DRAWINGS
     //*********************************************************************************************
 
     void drawEyes() {
 
       // PRE-CALCULATIONS - EYE SIZES AND VALUES FOR ANIMATION TWEENINGS
 
       // Vertical size offset for larger eyes when looking left or right (curious gaze)
       if (curious) {
         if (eyeLxNext <= 10) { eyeLheightOffset = 8; }
         else if (eyeLxNext >= (getScreenConstraint_X() - 10) && cyclops) { eyeLheightOffset = 8; }
         else { eyeLheightOffset = 0; }
         if (eyeRxNext >= screenWidth - eyeRwidthCurrent - 10) { eyeRheightOffset = 8; }
         else { eyeRheightOffset = 0; }
       } else {
         eyeLheightOffset = 0;
         eyeRheightOffset = 0;
       }
 
       // Left eye height
       eyeLheightCurrent = (eyeLheightCurrent + eyeLheightNext + eyeLheightOffset) / 2;
       eyeLy += ((eyeLheightDefault - eyeLheightCurrent) / 2);
       eyeLy -= eyeLheightOffset / 2;
       // Right eye height
       eyeRheightCurrent = (eyeRheightCurrent + eyeRheightNext + eyeRheightOffset) / 2;
       eyeRy += (eyeRheightDefault - eyeRheightCurrent) / 2;
       eyeRy -= eyeRheightOffset / 2;
 
       // Open eyes again after closing them
       if (eyeL_open) {
         if (eyeLheightCurrent <= 1 + eyeLheightOffset) { eyeLheightNext = eyeLheightDefault; }
       }
       if (eyeR_open) {
         if (eyeRheightCurrent <= 1 + eyeRheightOffset) { eyeRheightNext = eyeRheightDefault; }
       }
 
       // Left eye width
       eyeLwidthCurrent = (eyeLwidthCurrent + eyeLwidthNext) / 2;
       // Right eye width
       eyeRwidthCurrent = (eyeRwidthCurrent + eyeRwidthNext) / 2;
 
       // Space between eyes
       spaceBetweenCurrent = (spaceBetweenCurrent + spaceBetweenNext) / 2;
 
       // Left eye coordinates
       eyeLx = (eyeLx + eyeLxNext) / 2;
       eyeLy = (eyeLy + eyeLyNext) / 2;
       // Right eye coordinates
       eyeRxNext = eyeLxNext + eyeLwidthCurrent + spaceBetweenCurrent;
       eyeRyNext = eyeLyNext;
       eyeRx = (eyeRx + eyeRxNext) / 2;
       eyeRy = (eyeRy + eyeRyNext) / 2;
 
       // Left eye border radius
       eyeLborderRadiusCurrent = (eyeLborderRadiusCurrent + eyeLborderRadiusNext) / 2;
       // Right eye border radius
       eyeRborderRadiusCurrent = (eyeRborderRadiusCurrent + eyeRborderRadiusNext) / 2;
 
       // APPLYING MACRO ANIMATIONS
 
       if (autoblinker) {
         if (millis() >= blinktimer) {
           blink();
           blinktimer = millis() + (blinkInterval * 1000) + (random(blinkIntervalVariation) * 1000);
         }
       }
 
       // Laughing - eyes shaking up and down
       if (laugh) {
         if (laughToggle) {
           setVFlicker(1, 5);
           laughAnimationTimer = millis();
           laughToggle = 0;
         } else if (millis() >= laughAnimationTimer + laughAnimationDuration) {
           setVFlicker(0, 0);
           laughToggle = 1;
           laugh = 0;
         }
       }
 
       // Confused - eyes shaking left and right
       if (confused) {
         if (confusedToggle) {
           setHFlicker(1, 20);
           confusedAnimationTimer = millis();
           confusedToggle = 0;
         } else if (millis() >= confusedAnimationTimer + confusedAnimationDuration) {
           setHFlicker(0, 0);
           confusedToggle = 1;
           confused = 0;
         }
       }
 
       // Idle - eyes moving to random positions on screen
       if (idle) {
         if (millis() >= idleAnimationTimer) {
           eyeLxNext = random(getScreenConstraint_X());
           eyeLyNext = random(getScreenConstraint_Y());
           idleAnimationTimer = millis() + (idleInterval * 1000) + (random(idleIntervalVariation) * 1000);
         }
       }
 
       // Horizontal flickering/shivering
       if (hFlicker) {
         if (hFlickerAlternate) {
           eyeLx += hFlickerAmplitude;
           eyeRx += hFlickerAmplitude;
         } else {
           eyeLx -= hFlickerAmplitude;
           eyeRx -= hFlickerAmplitude;
         }
         hFlickerAlternate = !hFlickerAlternate;
       }
 
       // Vertical flickering/shivering
       if (vFlicker) {
         if (vFlickerAlternate) {
           eyeLy += vFlickerAmplitude;
           eyeRy += vFlickerAmplitude;
         } else {
           eyeLy -= vFlickerAmplitude;
           eyeRy -= vFlickerAmplitude;
         }
         vFlickerAlternate = !vFlickerAlternate;
       }
 
       // Cyclops mode: hide right eye
       if (cyclops) {
         eyeRwidthCurrent = 0;
         eyeRheightCurrent = 0;
         spaceBetweenCurrent = 0;
       }
 
       // ACTUAL DRAWINGS
 
       // Clear the display by filling with background color (ST7789)
       display.fillScreen(BGCOLOR);
 
       // Draw basic eye rectangles
       display.fillRoundRect(eyeLx, eyeLy, eyeLwidthCurrent, eyeLheightCurrent, eyeLborderRadiusCurrent, MAINCOLOR); // left eye
       if (!cyclops) {
         display.fillRoundRect(eyeRx, eyeRy, eyeRwidthCurrent, eyeRheightCurrent, eyeRborderRadiusCurrent, MAINCOLOR); // right eye
       }
 
       // Prepare mood type transitions
       if (tired) { eyelidsTiredHeightNext = eyeLheightCurrent / 2; eyelidsAngryHeightNext = 0; }
       else { eyelidsTiredHeightNext = 0; }
       if (angry) { eyelidsAngryHeightNext = eyeLheightCurrent / 2; eyelidsTiredHeightNext = 0; }
       else { eyelidsAngryHeightNext = 0; }
       if (happy) { eyelidsHappyBottomOffsetNext = eyeLheightCurrent / 2; }
       else { eyelidsHappyBottomOffsetNext = 0; }
 
       // Draw tired top eyelids 
       eyelidsTiredHeight = (eyelidsTiredHeight + eyelidsTiredHeightNext) / 2;
       if (!cyclops) {
         display.fillTriangle(eyeLx, eyeLy - 1, eyeLx + eyeLwidthCurrent, eyeLy - 1, eyeLx, eyeLy + eyelidsTiredHeight - 1, BGCOLOR); // left eye 
         display.fillTriangle(eyeRx, eyeRy - 1, eyeRx + eyeRwidthCurrent, eyeRy - 1, eyeRx + eyeRwidthCurrent, eyeRy + eyelidsTiredHeight - 1, BGCOLOR); // right eye
       } else {
         // Cyclops tired eyelids
         display.fillTriangle(eyeLx, eyeLy - 1, eyeLx + (eyeLwidthCurrent / 2), eyeLy - 1, eyeLx, eyeLy + eyelidsTiredHeight - 1, BGCOLOR);
         display.fillTriangle(eyeLx + (eyeLwidthCurrent / 2), eyeLy - 1, eyeLx + eyeLwidthCurrent, eyeLy - 1, eyeLx + eyeLwidthCurrent, eyeLy + eyelidsTiredHeight - 1, BGCOLOR);
       }
 
       // Draw angry top eyelids 
       eyelidsAngryHeight = (eyelidsAngryHeight + eyelidsAngryHeightNext) / 2;
       if (!cyclops) {
         display.fillTriangle(eyeLx, eyeLy - 1, eyeLx + eyeLwidthCurrent, eyeLy - 1, eyeLx + eyeLwidthCurrent, eyeLy + eyelidsAngryHeight - 1, BGCOLOR);
         display.fillTriangle(eyeRx, eyeRy - 1, eyeRx + eyeRwidthCurrent, eyeRy - 1, eyeRx, eyeRy + eyelidsAngryHeight - 1, BGCOLOR);
       } else {
         // Cyclops angry eyelids
         display.fillTriangle(eyeLx, eyeLy - 1, eyeLx + (eyeLwidthCurrent / 2), eyeLy - 1, eyeLx + (eyeLwidthCurrent / 2), eyeLy + eyelidsAngryHeight - 1, BGCOLOR);
         display.fillTriangle(eyeLx + (eyeLwidthCurrent / 2), eyeLy - 1, eyeLx + eyeLwidthCurrent, eyeLy - 1, eyeLx + (eyeLwidthCurrent / 2), eyeLy + eyelidsAngryHeight - 1, BGCOLOR);
       }
 
       // Draw happy bottom eyelids
       eyelidsHappyBottomOffset = (eyelidsHappyBottomOffset + eyelidsHappyBottomOffsetNext) / 2;
       display.fillRoundRect(eyeLx - 1, (eyeLy + eyeLheightCurrent) - eyelidsHappyBottomOffset + 1, eyeLwidthCurrent + 2, eyeLheightDefault, eyeLborderRadiusCurrent, BGCOLOR);
       if (!cyclops) {
         display.fillRoundRect(eyeRx - 1, (eyeRy + eyeRheightCurrent) - eyelidsHappyBottomOffset + 1, eyeRwidthCurrent + 2, eyeRheightDefault, eyeRborderRadiusCurrent, BGCOLOR);
       }
 
       // For ST7789, drawing functions update the display immediately so no display.display() call is needed.
     } // end of drawEyes method
 
 }; // end of class roboEyes
 
 #endif
 
