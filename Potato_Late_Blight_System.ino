/*
  ============================================================================
  SOLAR-POWERED GSM-BASED MICROCLIMATE MONITORING SYSTEM
  FOR LATE BLIGHT (Phytophthora infestans) RISK MANAGEMENT
  IN POTATO CULTIVATION
  ============================================================================
  
  System: Arduino Nano
  Date: 2026
  Author: Agricultural Engineering & Plant Pathology Research Team
  
  MODULES:
  - DS18B20 (Soil Temperature)
  - SHT31 (Air Temperature & Humidity)
  - Leaf Wetness Sensor
  - Rain Sensor
  - RTC DS3231 (Real-time Clock)
  - ILI9341 TFT Display (2.4 inch)
  - SIM800L GSM Module
  - SD Card Module
  
  ============================================================================
*/

// ======================= LIBRARY INCLUSIONS =======================
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <SHT31.h>
#include <RTClib.h>
#include <SD.h>
#include <SPI.h>
#include <Adafruit_ILI9341.h>
#include <SoftwareSerial.h>

// ======================= PIN DEFINITIONS =======================
// Temperature Sensor
#define ONE_WIRE_BUS 2

// SIM800L GSM Module
#define SIM_RX 3
#define SIM_TX 4

// TFT Display
#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 8

// SD Card
#define SD_CS 7

// Sensors
#define LEAF_WETNESS_PIN A1
#define RAIN_SENSOR_PIN A2

// ======================= OBJECT INSTANTIATION =======================
// DS18B20
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// SHT31
SHT31 sht31(0x44);  // Default I2C address

// RTC
RTC_DS3231 rtc;

// TFT Display
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

// SIM800L Serial
SoftwareSerial sim800l(SIM_RX, SIM_TX);

// ======================= COLOR DEFINITIONS =======================
#define COLOR_GREEN 0x07E0    // Green
#define COLOR_YELLOW 0xFFE0   // Yellow
#define COLOR_ORANGE 0xFD20   // Orange
#define COLOR_RED 0xF800      // Red
#define COLOR_WHITE 0xFFFF    // White
#define COLOR_BLACK 0x0000    // Black

// ======================= DATA STRUCTURES =======================
struct SensorData {
  float soilTemp;
  float airTemp;
  float humidity;
  int leafWetness;
  int rainSensor;
  bool isLeafWet;
  bool isRaining;
  int riskScore;
  String riskStatus;
  uint16_t displayColor;
};

struct SystemStatus {
  bool sim800lReady;
  bool sdCardReady;
  bool rtcReady;
  bool displayReady;
  unsigned long lastLogTime;
  unsigned long lastAlertTime;
};

// ======================= GLOBAL VARIABLES =======================
SensorData currentData;
SystemStatus systemStatus;

// Calibration Values (to be determined experimentally)
const int LEAF_WET_THRESHOLD = 500;      // Adjust after calibration
const int LEAF_MOIST_THRESHOLD = 300;    // Adjust after calibration
const int RAIN_THRESHOLD = 400;          // Adjust after calibration

// Logging intervals
const unsigned long LOG_INTERVAL = 30 * 60 * 1000;  // 30 minutes
const unsigned long SENSOR_READ_INTERVAL = 60 * 1000; // 60 seconds

// Alert cooldown
const unsigned long ALERT_COOLDOWN = 2 * 60 * 60 * 1000; // 2 hours

// ======================= SETUP FUNCTION =======================
void setup() {
  Serial.begin(9600);
  delay(1000);
  
  Serial.println(F("\n\n=== SYSTEM INITIALIZATION ===\n"));
  
  // Initialize Display
  initializeDisplay();
  
  // Initialize Sensors
  initializeDS18B20();
  initializeSHT31();
  initializeRTC();
  
  // Initialize SD Card
  initializeSDCard();
  
  // Initialize SIM800L
  initializeSIM800L();
  
  // Initial sensor read
  readAllSensors();
  displayWelcomeScreen();
  
  Serial.println(F("\n=== INITIALIZATION COMPLETE ===\n"));
  delay(2000);
}

// ======================= MAIN LOOP =======================
void loop() {
  static unsigned long lastSensorRead = 0;
  static unsigned long lastLogTime = 0;
  
  unsigned long currentTime = millis();
  
  // Read sensors every 60 seconds
  if (currentTime - lastSensorRead >= SENSOR_READ_INTERVAL) {
    readAllSensors();
    calculateRiskScore();
    updateDisplay();
    checkAndSendAlerts();
    lastSensorRead = currentTime;
  }
  
  // Log data every 30 minutes
  if (currentTime - lastLogTime >= LOG_INTERVAL) {
    logDataToSD();
    lastLogTime = currentTime;
  }
}

// ======================= DISPLAY FUNCTIONS =======================
void initializeDisplay() {
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(COLOR_BLACK);
  
  Serial.println(F("Display initialized"));
  systemStatus.displayReady = true;
}

void displayWelcomeScreen() {
  tft.fillScreen(COLOR_BLACK);
  tft.setTextColor(COLOR_WHITE);
  tft.setTextSize(2);
  
  tft.setCursor(20, 20);
  tft.println(F("LATE BLIGHT"));
  tft.setCursor(20, 50);
  tft.println(F("MONITORING"));
  
  tft.setTextSize(1);
  tft.setCursor(20, 90);
  tft.println(F("Solar-Powered System"));
  
  tft.setCursor(20, 120);
  if (systemStatus.sdCardReady) {
    tft.setTextColor(COLOR_GREEN);
    tft.println(F("SD Card: OK"));
  } else {
    tft.setTextColor(COLOR_RED);
    tft.println(F("SD Card: FAIL"));
  }
  
  tft.setCursor(20, 140);
  if (systemStatus.sim800lReady) {
    tft.setTextColor(COLOR_GREEN);
    tft.println(F("GSM Module: OK"));
  } else {
    tft.setTextColor(COLOR_RED);
    tft.println(F("GSM Module: FAIL"));
  }
  
  tft.setCursor(20, 160);
  if (systemStatus.rtcReady) {
    tft.setTextColor(COLOR_GREEN);
    tft.println(F("RTC: OK"));
  } else {
    tft.setTextColor(COLOR_RED);
    tft.println(F("RTC: FAIL"));
  }
}

void updateDisplay() {
  tft.fillScreen(COLOR_BLACK);
  
  // Set background color based on risk
  uint16_t bgColor = currentData.displayColor;
  
  // Display Header
  tft.setTextColor(COLOR_WHITE);
  tft.setTextSize(1);
  tft.setCursor(10, 10);
  
  DateTime now = rtc.now();
  char dateBuffer[20];
  sprintf(dateBuffer, "%02d-%02d-%04d", now.day(), now.month(), now.year());
  tft.print(F("Date: "));
  tft.println(dateBuffer);
  
  tft.setCursor(10, 25);
  char timeBuffer[20];
  sprintf(timeBuffer, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  tft.print(F("Time: "));
  tft.println(timeBuffer);
  
  // Separator Line
  tft.drawLine(0, 45, 320, 45, COLOR_WHITE);
  
  // Sensor Data
  tft.setTextSize(1);
  tft.setCursor(10, 55);
  tft.print(F("Soil Temp : "));
  tft.print(currentData.soilTemp);
  tft.println(F(" C"));
  
  tft.setCursor(10, 70);
  tft.print(F("Air Temp  : "));
  tft.print(currentData.airTemp);
  tft.println(F(" C"));
  
  tft.setCursor(10, 85);
  tft.print(F("Humidity  : "));
  tft.print(currentData.humidity);
  tft.println(F(" %"));
  
  // Separator Line
  tft.drawLine(0, 105, 320, 105, COLOR_WHITE);
  
  // Leaf and Rain Status
  tft.setCursor(10, 115);
  tft.print(F("Leaf      : "));
  if (currentData.isLeafWet) {
    tft.setTextColor(COLOR_YELLOW);
    tft.println(F("WET"));
  } else {
    tft.setTextColor(COLOR_GREEN);
    tft.println(F("DRY"));
  }
  tft.setTextColor(COLOR_WHITE);
  
  tft.setCursor(10, 130);
  tft.print(F("Rain      : "));
  if (currentData.isRaining) {
    tft.setTextColor(COLOR_YELLOW);
    tft.println(F("YES"));
  } else {
    tft.setTextColor(COLOR_GREEN);
    tft.println(F("NO"));
  }
  tft.setTextColor(COLOR_WHITE);
  
  // Separator Line
  tft.drawLine(0, 150, 320, 150, COLOR_WHITE);
  
  // Risk Score and Status
  tft.setCursor(10, 160);
  tft.setTextSize(2);
  tft.print(F("Score: "));
  tft.println(currentData.riskScore);
  
  tft.setCursor(10, 190);
  tft.setTextSize(2);
  tft.print(F("Status: "));
  
  // Set status text color
  switch(currentData.riskScore) {
    case 0 ... 3:
      tft.setTextColor(COLOR_GREEN);
      break;
    case 4 ... 7:
      tft.setTextColor(COLOR_YELLOW);
      break;
    case 8 ... 10:
      tft.setTextColor(COLOR_ORANGE);
      break;
    case 11 ... 12:
      tft.setTextColor(COLOR_RED);
      break;
    default:
      tft.setTextColor(COLOR_RED);
  }
  tft.println(currentData.riskStatus);
}

// ======================= SENSOR INITIALIZATION =======================
void initializeDS18B20() {
  sensors.begin();
  Serial.println(F("DS18B20 initialized"));
}

void initializeSHT31() {
  if (!sht31.begin(0x44)) {
    Serial.println(F("SHT31 not found!"));
  } else {
    Serial.println(F("SHT31 initialized"));
  }
}

void initializeRTC() {
  if (!rtc.begin()) {
    Serial.println(F("RTC not found!"));
    systemStatus.rtcReady = false;
  } else {
    Serial.println(F("RTC initialized"));
    systemStatus.rtcReady = true;
    
    // Uncomment to set time (run once, then comment out)
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void initializeSDCard() {
  if (!SD.begin(SD_CS)) {
    Serial.println(F("SD Card initialization failed!"));
    systemStatus.sdCardReady = false;
  } else {
    Serial.println(F("SD Card initialized"));
    systemStatus.sdCardReady = true;
    
    // Create header if file doesn't exist
    if (!SD.exists("LOG.csv")) {
      File logFile = SD.open("LOG.csv", FILE_WRITE);
      if (logFile) {
        logFile.println(F("Date,Time,SoilTemp,AirTemp,RH,LeafWet,Rain,RiskScore,RiskStatus"));
        logFile.close();
        Serial.println(F("LOG.csv created"));
      }
    }
  }
}

void initializeSIM800L() {
  sim800l.begin(9600);
  delay(1000);
  
  // Test communication
  sim800l.println(F("AT"));
  delay(500);
  
  if (sim800l.available()) {
    String response = sim800l.readStringUntil('\n');
    if (response.indexOf("OK") != -1) {
      Serial.println(F("SIM800L initialized"));
      systemStatus.sim800lReady = true;
    }
  } else {
    Serial.println(F("SIM800L not responding"));
    systemStatus.sim800lReady = false;
  }
}

// ======================= SENSOR READING FUNCTIONS =======================
void readAllSensors() {
  readDS18B20();
  readSHT31();
  readLeafWetness();
  readRainSensor();
}

void readDS18B20() {
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  
  if (tempC != DEVICE_DISCONNECTED_C) {
    currentData.soilTemp = tempC;
    Serial.print(F("Soil Temp: "));
    Serial.print(tempC);
    Serial.println(F(" C"));
  } else {
    Serial.println(F("DS18B20: Error reading temperature"));
  }
}

void readSHT31() {
  if (sht31.read()) {
    currentData.airTemp = sht31.getTemperature();
    currentData.humidity = sht31.getHumidity();
    
    Serial.print(F("Air Temp: "));
    Serial.print(currentData.airTemp);
    Serial.print(F(" C, Humidity: "));
    Serial.print(currentData.humidity);
    Serial.println(F(" %"));
  } else {
    Serial.println(F("SHT31: Error reading data"));
  }
}

void readLeafWetness() {
  int rawValue = analogRead(LEAF_WETNESS_PIN);
  currentData.leafWetness = rawValue;
  
  // Determine wetness status
  if (rawValue > LEAF_WET_THRESHOLD) {
    currentData.isLeafWet = true;
  } else if (rawValue > LEAF_MOIST_THRESHOLD) {
    currentData.isLeafWet = true;  // Treat moist as wet for risk calculation
  } else {
    currentData.isLeafWet = false;
  }
  
  Serial.print(F("Leaf Wetness: "));
  Serial.print(rawValue);
  Serial.print(F(" ("));
  Serial.print(currentData.isLeafWet ? "WET" : "DRY");
  Serial.println(F(")"));
}

void readRainSensor() {
  int rawValue = analogRead(RAIN_SENSOR_PIN);
  currentData.rainSensor = rawValue;
  
  // Determine rain status
  if (rawValue > RAIN_THRESHOLD) {
    currentData.isRaining = true;
  } else {
    currentData.isRaining = false;
  }
  
  Serial.print(F("Rain Sensor: "));
  Serial.print(rawValue);
  Serial.print(F(" ("));
  Serial.print(currentData.isRaining ? "RAIN" : "NO RAIN");
  Serial.println(F(")"));
}

// ======================= RISK CALCULATION =======================
void calculateRiskScore() {
  currentData.riskScore = 0;
  
  // Air Temperature: 10-22°C favorable for Phytophthora
  if (currentData.airTemp >= 10 && currentData.airTemp <= 22) {
    currentData.riskScore += 3;
  }
  
  // Humidity: >= 90% favorable
  if (currentData.humidity >= 90) {
    currentData.riskScore += 3;
  }
  
  // Leaf Wetness
  if (currentData.isLeafWet) {
    currentData.riskScore += 4;
  }
  
  // Rain
  if (currentData.isRaining) {
    currentData.riskScore += 2;
  }
  
  // Soil Temperature: 10-20°C favorable
  if (currentData.soilTemp >= 10 && currentData.soilTemp <= 20) {
    currentData.riskScore += 2;
  }
  
  // Determine risk status and color
  if (currentData.riskScore <= 3) {
    currentData.riskStatus = "SAFE";
    currentData.displayColor = COLOR_GREEN;
  } else if (currentData.riskScore <= 7) {
    currentData.riskStatus = "WATCH";
    currentData.displayColor = COLOR_YELLOW;
  } else if (currentData.riskScore <= 10) {
    currentData.riskStatus = "MODERATE";
    currentData.displayColor = COLOR_ORANGE;
  } else if (currentData.riskScore <= 12) {
    currentData.riskStatus = "HIGH";
    currentData.displayColor = COLOR_RED;
  } else {
    currentData.riskStatus = "VERY HIGH";
    currentData.displayColor = COLOR_RED;
  }
  
  Serial.print(F("Risk Score: "));
  Serial.print(currentData.riskScore);
  Serial.print(F(" - Status: "));
  Serial.println(currentData.riskStatus);
}

// ======================= ALERT SYSTEM =======================
void checkAndSendAlerts() {
  static unsigned long lastAlertTime = 0;
  unsigned long currentTime = millis();
  
  // Check alert cooldown
  if (currentTime - lastAlertTime < ALERT_COOLDOWN) {
    return;  // Still in cooldown
  }
  
  // Send alerts based on risk level
  if (currentData.riskScore >= 8 && currentData.riskScore <= 10) {
    // MODERATE RISK
    sendModerateRiskAlert();
    lastAlertTime = currentTime;
  } else if (currentData.riskScore >= 11 && currentData.riskScore <= 12) {
    // HIGH RISK
    sendHighRiskAlert();
    lastAlertTime = currentTime;
  } else if (currentData.riskScore >= 13) {
    // VERY HIGH RISK
    sendVeryHighRiskAlert();
    lastAlertTime = currentTime;
  }
}

void sendModerateRiskAlert() {
  Serial.println(F("\n>>> SENDING MODERATE RISK ALERT <<<"));
  
  if (systemStatus.sim800lReady) {
    sendSMS("+8801XXXXXXXXX", "Late Blight Risk Increasing. Monitor field conditions.");
  }
}

void sendHighRiskAlert() {
  Serial.println(F("\n>>> SENDING HIGH RISK ALERT <<<"));
  
  if (systemStatus.sim800lReady) {
    sendSMS("+8801XXXXXXXXX", "High risk of Late Blight. Field inspection recommended.");
  }
}

void sendVeryHighRiskAlert() {
  Serial.println(F("\n>>> SENDING VERY HIGH RISK ALERT <<<"));
  
  if (systemStatus.sim800lReady) {
    sendSMS("+8801XXXXXXXXX", "VERY HIGH Late Blight Risk. Take preventive action immediately.");
    // Optional: Send voice call alert
    // makeVoiceCall("+8801XXXXXXXXX");
  }
}

// ======================= GSM FUNCTIONS =======================
void sendSMS(const char* phoneNumber, const char* message) {
  // Set SMS mode
  sim800l.println(F("AT+CMGF=1"));
  delay(500);
  
  // Set recipient
  sim800l.print(F("AT+CMGS=\""));
  sim800l.print(phoneNumber);
  sim800l.println(F("\""));
  delay(500);
  
  // Send message
  sim800l.print(message);
  sim800l.write(26);  // Ctrl+Z
  delay(1000);
  
  Serial.print(F("SMS sent to: "));
  Serial.println(phoneNumber);
}

void makeVoiceCall(const char* phoneNumber) {
  sim800l.print(F("ATD"));
  sim800l.print(phoneNumber);
  sim800l.println(F(";"));
  
  Serial.print(F("Voice call initiated to: "));
  Serial.println(phoneNumber);
}

// ======================= SD CARD LOGGING =======================
void logDataToSD() {
  if (!systemStatus.sdCardReady) {
    Serial.println(F("SD Card not ready for logging"));
    return;
  }
  
  File logFile = SD.open("LOG.csv", FILE_WRITE);
  if (!logFile) {
    Serial.println(F("Cannot open LOG.csv"));
    return;
  }
  
  DateTime now = rtc.now();
  
  // Format date
  char dateBuffer[11];
  sprintf(dateBuffer, "%02d-%02d-%04d", now.day(), now.month(), now.year());
  
  // Format time
  char timeBuffer[9];
  sprintf(timeBuffer, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  
  // Write data
  logFile.print(dateBuffer);
  logFile.print(",");
  logFile.print(timeBuffer);
  logFile.print(",");
  logFile.print(currentData.soilTemp);
  logFile.print(",");
  logFile.print(currentData.airTemp);
  logFile.print(",");
  logFile.print(currentData.humidity);
  logFile.print(",");
  logFile.print(currentData.isLeafWet ? "WET" : "DRY");
  logFile.print(",");
  logFile.print(currentData.isRaining ? "YES" : "NO");
  logFile.print(",");
  logFile.print(currentData.riskScore);
  logFile.print(",");
  logFile.println(currentData.riskStatus);
  
  logFile.close();
  
  Serial.print(F("Data logged at "));
  Serial.print(dateBuffer);
  Serial.print(" ");
  Serial.println(timeBuffer);
}

// ======================= END OF CODE =======================
