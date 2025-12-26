#include <Arduino.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void setup() {
  // Start the tft display and set it to black
  tft.init();
  tft.setRotation(0); //This is the display in landscape
  // Clear the screen before writing to it
  tft.fillScreen(TFT_BLACK);

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  int x = 5;
  int y = 10;
  int fontNum = 2; 
  tft.drawString("Hello", x, y, fontNum); // Left Aligned
  x = 320 /2;
  y += 16;
  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.drawCentreString("World", x, y, fontNum);

}

void loop() {
  // put your main code here, to run repeatedly:

}