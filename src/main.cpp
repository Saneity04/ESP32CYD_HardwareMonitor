#include <Arduino.h>
#include <TFT_eSPI.h>
#include <Preferences.h>
#include <ESP32CYD_defines.h>
TFT_eSPI tft = TFT_eSPI();
Preferences preferences;
uint16_t calData[5];
int lastX = -1;
int lastY = -1;

bool loadCalibration();

void setup(void) {
  // Initialise the TFT screen
  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.setRotation(1);
  // Save Data
  if (!loadCalibration()) {
    preferences.begin("Calibration", false);
    tft.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);

    for (int i = 0; i < 5; i++) {
      char key[6];
      sprintf(key, "cal%d", i);
      preferences.putUShort(key, calData[i]);
    }
    preferences.end();

  }

  tft.setTouch(calData);

    // Clear the screen
  tft.fillScreen(TFT_BLACK);
  tft.drawCentreString("Touch screen to test!",tft.width()/2, tft.height()/2, 2);
}

void loop() {
  uint16_t x = 0, y = 0; // To store the touch coordinates
  
  bool pressed = tft.getTouch(&x, &y);
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

bool loadCalibration() {
  preferences.begin("Calibration", true);

  for (int i = 0; i < 5; i++) {
    char key[6];
    sprintf(key, "cal%d", i);

    if (!preferences.isKey(key)) {
      preferences.end();
      return false;   // calibration missing
    }

    calData[i] = preferences.getUShort(key);
  }

  preferences.end();
  return true;        // calibration exists
}