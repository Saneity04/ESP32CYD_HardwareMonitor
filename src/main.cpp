#include <Arduino.h>
#include <TFT_eSPI.h>
#include <ESP32CYD_defines.h>

TFT_eSPI tft = TFT_eSPI();
uint16_t calData[5];
int lastX = -1;
int lastY = -1;

void setup(void) {
  // Initialise the TFT screen
  tft.init();
  tft.fillScreen(TFT_BLACK);
  pinMode(LDR_PIN, INPUT);
  // Set the rotation to the orientation you wish to use in your project before calibration
  // (the touch coordinates returned then correspond to that rotation only)
  tft.setRotation(1);
  tft.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);
  
  tft.setTouch(calData);

  // Clear the screen
  tft.fillScreen(TFT_BLACK);
  tft.drawCentreString("Touch screen to test!",tft.width()/2, tft.height()/2, 2);
}

void loop() {
  uint16_t x = 0, y = 0; // To store the touch coordinates

  bool pressed = tft.getTouch(&x, &y);

  tft.drawString("LDR: " + String(ldrValue), 10, 10, 2);

   if (pressed) {

    if (lastX >= 0 && lastY >= 0) {
      tft.drawLine(lastX, lastY, x, y, TFT_GREEN);
    }else {
      tft.drawPixel(x, y, TFT_GREEN); 
    }

  
  lastX = x;
  lastY = y;

  }else {
    lastX = -1;
    lastY = -1;
  }

  delay(10);
}

