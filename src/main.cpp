#include <Arduino.h>
#include <TFT_eSPI.h>
#include <Preferences.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP32CYD_defines.h>
// ================= WIFI =================
const char* ssid = "WiFi Saya";
const char* password = "YewonKim123!";
String serverName = "http://10.10.10.198:8085/data.json";

// ================= TIMING =================
unsigned long lastTime = 0;
const unsigned long timerDelay = 1000; // 5 seconds

// ================= DATA =================
String cpuTemp = "--";
String gpuTemp = "--";
String hotspotTemp = "--";
String cpuUtil = "--";
String gpuUtil = "--";
String disk1 = "--";
String disk2 = "--";
String disk3 = "--";
String disk4 = "--";
String disk1Read = "--";
String disk2Read = "--";
String disk3Read = "--";
String disk4Read = "--";
String disk1Write = "--";
String disk2Write = "--";
String disk3Write = "--";
String disk4Write = "--";
String fps = "--";

// ================= TFT & PREFS =================
TFT_eSPI tft = TFT_eSPI();
Preferences preferences;
uint16_t calData[5];

// ================= FUNCTION DECLARATIONS =================
bool loadCalibration();
void fetch(JsonArray children, String parent = "");
void showTemps();
void showUtils();

// ================= SETUP =================
void setup() {
  Serial.begin(115200);

  // TFT
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  // WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  // Touch calibration
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

  tft.fillScreen(TFT_BLACK);
  tft.drawCentreString("System Monitor", tft.width() / 2, 10, 2);
}

// ================= LOOP =================
void loop() {
  if (millis() - lastTime > timerDelay) {

    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      String serverPath = serverName;

      http.begin(serverPath.c_str());
      int httpResponseCode = http.GET();

      if (httpResponseCode > 0) {
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, http.getStream(), DeserializationOption::NestingLimit(14));

        if (!error) {
          JsonArray root = doc["Children"];
          fetch(root);
          showTemps();   // display after fetch
        } else {
          Serial.println("JSON parse error");
          Serial.println(error.c_str());
        }
      } else {
        Serial.print("HTTP error: ");
        Serial.println(httpResponseCode);
      }

      http.end();
    }

    lastTime = millis();
  }
}

// ================= LOAD CALIBRATION =================
bool loadCalibration() {
  preferences.begin("Calibration", true);

  for (int i = 0; i < 5; i++) {
    char key[6];
    sprintf(key, "cal%d", i);

    if (!preferences.isKey(key)) {
      preferences.end();
      return false;
    }
    calData[i] = preferences.getUShort(key);
  }

  preferences.end();
  return true;
}

// ================= JSON FETCH =================
void fetch(JsonArray children, String parent)
{
  for (JsonObject node : children)
  {
    const char* text  = node["Text"];
    const char* value = node["Value"];

    String current = parent;
    if (text) {
      if (current.length() > 0) current += "/";
      current += text;
    }

    if (text && value)
    {
      String label = text;
      String val   = value;

      // CPU temp
      if (label == "Core (Tctl/Tdie)" && val.indexOf("°C") != -1)
        cpuTemp = val;

      // GPU temp
      else if (label == "GPU Core" && val.indexOf("°C") != -1)
        gpuTemp = val;

      // ✅ Ethernet download speed ONLY
      else if (current == "SAH/Ethernet 2/Throughput/Download Speed")
        hotspotTemp = val;

      else if (current == "SAH/ST2000DM001-1ER164/Load/Used Space")
        disk1 = val;

      else if (current == "SAH/KINGSTON SNV2S1000G/Load/Used Space")
        disk2 = val;

      else if (current == "SAH/MTFDHBA256TCK-1AS1AABHA/Load/Used Space")
        disk3 = val;

      else if (current == "SAH/WD Green 2.5 480GB/Load/Used Space")
        disk4 = val;
      
        else if (current == "SAH/ST2000DM001-1ER164/Throughput/Read Rate")
        disk1Read = val;

        else if (current == "SAH/KINGSTON SNV2S1000G/Throughput/Read Rate")
        disk2Read = val;

        else if (current == "SAH/MTFDHBA256TCK-1AS1AABHA/Throughput/Read Rate")
        disk3Read = val;

        else if (current == "SAH/WD Green 2.5 480GB/Throughput/Read Rate")
        disk4Read = val;

      else if (current == "SAH/ST2000DM001-1ER164/Throughput/Write Rate")
      disk1Write = val;
      else if (current == "SAH/KINGSTON SNV2S1000G/Throughput/Write Rate")
      disk2Write = val;
      else if (current == "SAH/MTFDHBA256TCK-1AS1AABHA/Throughput/Write Rate")
      disk3Write = val;
      else if (current == "SAH/WD Green 2.5 480GB/Throughput/Write Rate")
      disk4Write = val;
      

      // CPU usage
      else if (label == "CPU Total" && val.indexOf("%") != -1)
        cpuUtil = val;

      else if (label == "Fullscreen FPS")
      fps = val;

      // GPU usage
      else if (label == "GPU Core" && val.indexOf("%") != -1)
        gpuUtil = val;
    }

    if (node.containsKey("Children")) {
      fetch(node["Children"].as<JsonArray>(), current);
    }
  }
}


// ================= DISPLAY TEMPS =================
void showTemps() {
  tft.fillScreen(TFT_BLACK);
  tft.drawString("CPU Temp:", 10, 20, 2);
  tft.drawString(cpuTemp, 150, 20, 2);

  tft.drawString("GPU Temp:", 10, 50, 2);
  tft.drawString(gpuTemp, 150, 50, 2);
  

  tft.drawString("Download Speed:", 10, 80, 2);
  tft.fillRect(120, 80, 120, 20, TFT_BLACK);  // erase old text
  tft.drawString(hotspotTemp, 150, 80, 2);

  tft.drawString("CPU Util:", 10, 120, 2);
  tft.drawString(cpuUtil, 150, 120, 2);

  tft.drawString("GPU Util:", 10, 150, 2);
  tft.drawString(gpuUtil, 150, 150, 2);
  tft.drawString("FPS:", 250, 150, 2);
  tft.drawString(fps, 350, 150, 2);


  tft.drawString("Disk 0 T/R/W:", 10, 180, 2);
  tft.drawString(disk1, 150, 180, 2);
  tft.drawString(disk1Read, 200, 180, 2);
  tft.drawString(disk1Write, 280, 180, 2);

  tft.drawString("Disk 1 T/R/W:", 10, 210, 2);
  tft.drawString(disk2, 150, 210, 2);
  tft.drawString(disk2Read, 200, 210, 2);
  tft.drawString(disk2Write, 280, 210, 2);

  tft.drawString("Disk 2 T/R/W:", 10, 240, 2);
  tft.drawString(disk3, 150, 240, 2);
  tft.drawString(disk3Read, 200, 240, 2);
  tft.drawString(disk3Write, 280, 240, 2);

  tft.drawString("Disk 3 T/R/W:", 10, 270, 2);
  tft.drawString(disk4, 150, 270, 2);
  tft.drawString(disk4Read, 200, 270, 2);
  tft.drawString(disk4Write, 280, 270, 2);
  
  
}

// ================= OPTIONAL UTIL SCREEN =================
void showUtils() {

  tft.drawString("CPU Util:", 10, 40, 2);
  tft.drawString(cpuUtil, 150, 40, 2);

  tft.drawString("GPU Util:", 10, 80, 2);
  tft.drawString(gpuUtil, 150, 80, 2);

}
