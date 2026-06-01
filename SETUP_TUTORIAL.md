# SETUP TUTORIAL: Late Blight Monitoring System
## Complete Step-by-Step Installation Guide for Arduino Nano

---

## TABLE OF CONTENTS
1. [Software Setup](#software-setup)
2. [Hardware Assembly](#hardware-assembly)
3. [Library Installation](#library-installation)
4. [Pin Configuration](#pin-configuration)
5. [Calibration Procedure](#calibration-procedure)
6. [Testing & Debugging](#testing--debugging)
7. [Field Deployment](#field-deployment)

---

## 1. SOFTWARE SETUP

### 1.1 Arduino IDE Installation
- Download Arduino IDE from: https://www.arduino.cc/en/software
- Install the latest version (1.8.19 or newer)
- Launch Arduino IDE

### 1.2 Board Manager Setup
1. Go to **Tools → Board → Boards Manager**
2. Search for "Arduino AVR"
3. Install "Arduino AVR Boards"
4. Select **Tools → Board → Arduino Nano**
5. Select **Tools → Processor → ATmega328P**

### 1.3 Port Configuration
1. Connect Arduino Nano via USB cable to your computer
2. Go to **Tools → Port**
3. Select the appropriate COM port (usually COM3-COM9 on Windows, /dev/ttyUSB0 on Linux)

---

## 2. HARDWARE ASSEMBLY

### 2.1 Power System Assembly

#### Step 1: Solar Panel to CN3791 Charger
```
20W Solar Panel
    ├─ (+) Red   → CN3791 "IN+"
    └─ (-) Black → CN3791 "IN-"
```

#### Step 2: CN3791 to Battery Pack
```
CN3791 Charger
    ├─ OUT+ (Red)   → Battery Pack Positive (+)
    ├─ OUT- (Black) → Battery Pack Negative (-)
    └─ GND          → Common Ground
```

**Battery Pack Configuration (3×18650):**
```
[18650] [18650] [18650]  (3S1P = 3 cells in series)
   │       │       │
   └───┬───┴───┬───┘
       │       │
      (+)     (-)
    11.1V nominal
```

#### Step 3: LM2596 Buck Converter Setup
```
Battery Pack (+11.1V)
    ├─ (+) → LM2596 "IN+"
    └─ (-) → LM2596 "IN-"

LM2596 "OUT+" → 5V Rail (to Arduino & Sensors)
LM2596 "OUT-" → GND Rail

Adjustment:
- Use multimeter to set LM2596 output to 5.0V
- Trim potentiometer carefully
```

#### Step 4: SIM800L Power Path
```
Battery Pack (11.1V) → 2200µF Capacitor
                       ├─ VCC (+) → SIM800L VCC
                       ├─ GND (-) → SIM800L GND
                       └─ GND     → Common Ground
```

---

### 2.2 Arduino Nano Pinout Reference

```
Arduino Nano (Top View)

D1  [USB] D0
D2  [    ] RST
D3  [    ] GND
D4  [    ] VCC
D5  [    ] A7
D6  [    ] A6
D7  [    ] A5 (SCL)
D8  [    ] A4 (SDA)
D9  [    ] A3
D10 [    ] A2
D11 [    ] A1
D12 [    ] A0
D13 [    ] REF
GND [    ] GND
VCC [    ] VCC
```

---

### 2.3 Complete Wiring Diagram

#### **TEMPERATURE SENSOR (DS18B20)**
```
DS18B20 Waterproof Sensor
    ├─ Red    (VCC) → 5V
    ├─ Black  (GND) → GND
    └─ Yellow (DQ)  → D2

Pull-up Resistor:
    4.7kΩ resistor between D2 and 5V
```

#### **AIR TEMPERATURE & HUMIDITY (SHT31)**
```
SHT31 Module
    ├─ VCC → 5V
    ├─ GND → GND
    ├─ SDA → A4 (I2C Data)
    └─ SCL → A5 (I2C Clock)

I2C Default Address: 0x44
```

#### **RTC MODULE (DS3231)**
```
DS3231 RTC Module
    ├─ VCC → 5V
    ├─ GND → GND
    ├─ SDA → A4 (I2C Data - shared with SHT31)
    └─ SCL → A5 (I2C Clock - shared with SHT31)

I2C Default Address: 0x68
```

#### **LEAF WETNESS SENSOR**
```
Leaf Wetness Sensor
    ├─ VCC → 5V
    ├─ GND → GND
    └─ AO  → A1 (Analog Input)

Calibration Range: 0-1023 (10-bit ADC)
Typical Values:
    - Dry:  200-300
    - Moist: 300-500
    - Wet:  500-1023
```

#### **RAIN SENSOR MODULE**
```
Rain Sensor Module
    ├─ VCC → 5V
    ├─ GND → GND
    └─ AO  → A2 (Analog Input)

Calibration Range: 0-1023 (10-bit ADC)
Typical Values:
    - No Rain: 100-200
    - Light Rain: 200-400
    - Rain: 400-1023
```

#### **SD CARD MODULE**
```
SD Card Module (SPI Mode)
    ├─ VCC  → 5V
    ├─ GND  → GND
    ├─ MOSI → D11
    ├─ MISO → D12
    ├─ SCK  → D13
    └─ CS   → D7
```

#### **TFT DISPLAY (ILI9341 - 2.4")**
```
TFT Display Module
    ├─ VCC  → 5V
    ├─ GND  → GND
    ├─ CS   → D10
    ├─ RST  → D8
    ├─ DC   → D9
    ├─ MOSI → D11
    ├─ MISO → D12
    └─ SCK  → D13

Note: MOSI, MISO, SCK shared with SD card (SPI Bus)
```

#### **SIM800L GSM MODULE**
```
SIM800L Module (via SoftwareSerial)
    ├─ VCC  → Battery Pack (+11.1V)
    ├─ GND  → Common Ground
    ├─ TX   → D4 (Arduino RX)
    ├─ RX   → D3 (Arduino TX)
    ├─ GND  → GND (reference)
    
Power Stability:
    - Connect 2200µF capacitor across VCC and GND (near module)
    - Use short, thick wires
    - Separate power supply from Arduino 5V if possible
```

---

## 3. LIBRARY INSTALLATION

### 3.1 Install Required Libraries

Open Arduino IDE and go to **Sketch → Include Library → Manage Libraries**

Search for and install each library:

| Library Name | Author | Version | Purpose |
|---|---|---|---|
| OneWire | Paul Stoffregen | Latest | DS18B20 communication |
| DallasTemperature | Miles Burton | Latest | DS18B20 temperature reading |
| SHT31 | Rob Tillaart | Latest | SHT31 sensor |
| RTClib | Adafruit | Latest | DS3231 Real-time clock |
| SD | Arduino | Latest | SD card file operations |
| Adafruit ILI9341 | Adafruit | Latest | TFT display control |

### 3.2 Installation Steps

1. **OneWire & DallasTemperature:**
   - Search: "OneWire" → Install
   - Search: "DallasTemperature" → Install

2. **SHT31:**
   - Search: "SHT31" → Install (Rob Tillaart version)

3. **RTClib:**
   - Search: "RTClib" → Install

4. **SD Card:**
   - Search: "SD" → Install (Arduino version)

5. **Adafruit ILI9341:**
   - Search: "Adafruit ILI9341" → Install

### 3.3 Verify Installation
```cpp
// Test in Arduino IDE - Sketch → Verify
// Should compile without errors
```

---

## 4. PIN CONFIGURATION

### 4.1 Update Phone Number for SMS Alerts

Open **Potato_Late_Blight_System.ino** and find these lines:

```cpp
// Line ~385 - sendModerateRiskAlert()
sendSMS("+8801XXXXXXXXX", "Late Blight Risk Increasing...");

// Line ~395 - sendHighRiskAlert()
sendSMS("+8801XXXXXXXXX", "High risk of Late Blight...");

// Line ~405 - sendVeryHighRiskAlert()
sendSMS("+8801XXXXXXXXX", "VERY HIGH Late Blight Risk...");
```

**Replace "+8801XXXXXXXXX" with your actual phone number:**
```cpp
sendSMS("+8801712345678", "Late Blight Risk Increasing...");
```

### 4.2 Verify Pin Assignments

Before uploading, verify all pins match your wiring:

```cpp
#define ONE_WIRE_BUS 2          // DS18B20
#define SIM_RX 3                // GSM RX
#define SIM_TX 4                // GSM TX
#define TFT_CS 10               // Display Chip Select
#define TFT_DC 9                // Display Data/Command
#define TFT_RST 8               // Display Reset
#define SD_CS 7                 // SD Card Chip Select
#define LEAF_WETNESS_PIN A1     // Analog Input 1
#define RAIN_SENSOR_PIN A2      // Analog Input 2
```

---

## 5. CALIBRATION PROCEDURE

### 5.1 DS18B20 Temperature Calibration

**Procedure:**
1. Place sensor in ice water (0°C)
2. Wait 2 minutes for stabilization
3. Note reading (should be close to 0°C)
4. Adjust in code if necessary

**Verification:**
```
Ice Water:    Expected 0°C,    Actual: ___°C
Room Temp:    Expected ~22°C,  Actual: ___°C
Hot Water:    Expected ~80°C,  Actual: ___°C
```

### 5.2 SHT31 Calibration

**Humidity Calibration:**
1. Use salt solution method (75% RH)
2. Place sensor in sealed container with salt solution
3. Wait 30 minutes
4. Note reading (should be ~75% RH)

**Temperature Verification:**
- Compare with laboratory thermometer
- Accuracy should be within ±0.5°C

### 5.3 Leaf Wetness Sensor Calibration

**Critical for accurate disease prediction!**

```cpp
// Find these lines in the code:
const int LEAF_WET_THRESHOLD = 500;      
const int LEAF_MOIST_THRESHOLD = 300;    
```

**Calibration Steps:**

1. **Dry Condition:**
   - Keep sensor dry in air
   - Read analog value → Record as DRY_VALUE
   - Typical: 100-200

2. **Moist Condition:**
   - Spray light mist of water
   - Wait 5 minutes
   - Read analog value → Record as MOIST_VALUE
   - Typical: 300-500

3. **Wet Condition:**
   - Wet sensor thoroughly (simulate rain/dew)
   - Read analog value → Record as WET_VALUE
   - Typical: 500-900

**Update Code:**
```cpp
const int LEAF_WET_THRESHOLD = <WET_VALUE>;      
const int LEAF_MOIST_THRESHOLD = <MOIST_VALUE>;  
```

### 5.4 Rain Sensor Calibration

```cpp
const int RAIN_THRESHOLD = 400;
```

**Calibration Steps:**

1. **No Rain:**
   - Keep sensor dry
   - Read value → DRY_VALUE (typically 50-150)

2. **Light Rain:**
   - Spray light mist
   - Read value → LIGHT_RAIN (typically 200-400)

3. **Heavy Rain:**
   - Pour water on sensor
   - Read value → HEAVY_RAIN (typically 400-800)

**Update Code:**
```cpp
const int RAIN_THRESHOLD = 400;  // Adjust based on calibration
```

### 5.5 Create Calibration Sketch

```cpp
// CALIBRATION_TEST.ino - Use this for sensor testing
void setup() {
  Serial.begin(9600);
  pinMode(A1, INPUT);  // Leaf Wetness
  pinMode(A2, INPUT);  // Rain Sensor
}

void loop() {
  int leafWet = analogRead(A1);
  int rainSensor = analogRead(A2);
  
  Serial.print("Leaf Wetness: ");
  Serial.print(leafWet);
  Serial.print("  Rain Sensor: ");
  Serial.println(rainSensor);
  
  delay(500);
}
```

---

## 6. TESTING & DEBUGGING

### 6.1 Serial Monitor Output

1. Upload code to Arduino Nano
2. Open **Tools → Serial Monitor**
3. Set Baud Rate to **9600**
4. You should see:

```
=== SYSTEM INITIALIZATION ===

Display initialized
DS18B20 initialized
SHT31 initialized
RTC initialized
SD Card initialized
SIM800L initialized
SIM800L: OK
RTC: OK
SD Card: OK
GSM Module: OK

=== INITIALIZATION COMPLETE ===

Reading sensors...
Soil Temp: 15.2 C
Air Temp: 18.5 C, Humidity: 92 %
Leaf Wetness: 620 (WET)
Rain Sensor: 450 (RAIN)
Risk Score: 14 - Status: VERY HIGH

Data logged at 15-01-2027 08:30:45
```

### 6.2 Troubleshooting Guide

| Problem | Cause | Solution |
|---|---|---|
| "DS18B20 not found" | Sensor not connected | Check D2 wiring + pull-up resistor |
| "SHT31 not found" | I2C address issue | Verify I2C address (0x44) with I2C scanner |
| "RTC not found" | RTC not connected | Check A4/A5 (SDA/SCL) wiring |
| "SD Card failed" | SPI not working | Check D7, D11, D12, D13 wiring |
| "SIM800L not responding" | Serial communication issue | Check D3/D4 TX/RX wiring |
| Display shows garbage | Wrong initialization | Verify TFT library version |

### 6.3 I2C Scanner (for debugging I2C devices)

```cpp
#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println("I2C Scanner");
}

void loop() {
  byte error, address;
  int nDevices = 0;

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    
    if (error == 0) {
      Serial.print("Device found at address 0x");
      Serial.println(address, HEX);
      nDevices++;
    }
  }
  
  if (nDevices == 0) Serial.println("No I2C devices found");
  delay(5000);
}
```

---

## 7. FIELD DEPLOYMENT

### 7.1 Pre-Deployment Checklist

- [ ] All sensors tested individually
- [ ] Calibration values finalized
- [ ] Phone number configured for SMS
- [ ] RTC time set correctly
- [ ] SD card formatted and inserted
- [ ] SIM card installed in SIM800L with active credit
- [ ] Battery fully charged (check voltage)
- [ ] Solar panel tested (measures ~20V open circuit)
- [ ] Weatherproof enclosure assembled
- [ ] All connectors properly sealed

### 7.2 Sensor Installation in Field

**Soil Temperature Sensor (DS18B20):**
```
Depth: 5-10 cm below soil surface
Location: Near potato root zone
Tip: Use waterproof extension tube if needed
```

**Air Temperature & Humidity (SHT31):**
```
Height: 10-20 cm above potato canopy
Protection: Inside radiation shield
Mount: Vertical orientation
Purpose: Measure canopy microclimate
```

**Leaf Wetness Sensor:**
```
Height: At leaf height
Placement: Inside canopy
Angle: Tilted 30-45° (mimics leaf angle)
Purpose: Detect dew and rainfall persistence
```

**Rain Sensor:**
```
Height: Above plant canopy
Position: Fully exposed to sky
Angle: Slight tilt (45°) for drainage
Purpose: Detect rainfall events
```

### 7.3 Weatherproof Enclosure Setup

```
Waterproof Box Layout:

┌─────────────────────────┐
│   [TFT Display]         │ ← Face outward
├─────────────────────────┤
│ Arduino Nano            │
│ SIM800L Module          │
│ SD Card                 │
│ 2200µF Capacitor        │
├─────────────────────────┤
│ LM2596 Regulator        │
│ 3×18650 Battery Pack    │
│ CN3791 Charger          │
├─────────────────────────┤
│ Cable Glands (sealed)   │
│ - Solar Panel wire      │
│ - Sensor wires (CAT5)   │
└─────────────────────────┘
```

**Sealing:**
- Use silicone sealant on all cable entries
- Apply waterproof tape on junction points
- Use cable glands with rubber seals

### 7.4 Expected Performance in Field

**Data Logging:**
- New entry every 30 minutes
- CSV file format: `DATE,TIME,SoilTemp,AirTemp,RH,Leaf,Rain,RiskScore,Status`
- Approximately 48 entries per day = 1,440 entries per 30 days

**Battery Life (3×3000mAh without solar):**
- With sensors: ~35-40 hours
- With GSM alerts: ~30 hours (SMS consumes more power)

**Power Consumption Breakdown:**
| Component | Current (mA) | Duration |
|---|---|---|
| Arduino + Sensors | 50 | Continuous |
| TFT Display | 100 | Periodic updates |
| SIM800L (Idle) | 20 | Continuous |
| SIM800L (Sending SMS) | 500 | 5-10 seconds |

---

## 8. EXAMPLE DATA OUTPUT

### Serial Monitor Output:
```
=== SENSOR READINGS ===
Date: 15-01-2027
Time: 08:30:45

Soil Temp: 14.8 C
Air Temp: 18.5 C
Humidity: 95 %

Leaf Wetness: 620 (WET)
Rain Sensor: 450 (RAIN)

=== RISK CALCULATION ===
Air Temp (10-22°C): +3
Humidity (≥90%): +3
Leaf Wetness: +4
Rain: +2
Soil Temp (10-20°C): +2
─────────────────────
TOTAL SCORE: 14

STATUS: VERY HIGH RISK
DISPLAY COLOR: RED

>>> SENDING VERY HIGH RISK ALERT <<<
SMS sent to: +8801712345678
Message: "VERY HIGH Late Blight Risk. Take preventive action immediately."
```

### SD Card Output (LOG.csv):
```
Date,Time,SoilTemp,AirTemp,RH,Leaf,Rain,RiskScore,RiskStatus
2027-01-15,08:30,14.8,18.5,95,WET,YES,14,VERY HIGH
2027-01-15,09:00,15.2,18.4,93,WET,YES,14,VERY HIGH
2027-01-15,09:30,15.5,19.2,90,WET,NO,13,VERY HIGH
2027-01-15,10:00,16.1,20.5,85,DRY,NO,3,SAFE
2027-01-15,10:30,17.2,22.1,78,DRY,NO,0,SAFE
```

---

## 9. RESEARCH DATA ANALYSIS

After 30-60 days of field operation, you can:

1. **Generate disease risk graphs** (Score vs. Time)
2. **Analyze temperature trends** (Soil vs. Air)
3. **Study humidity patterns** (Peak periods)
4. **Calculate leaf wetness duration** (Hours with wet leaves)
5. **Correlate with field observations** (Actual disease occurrence)
6. **Statistical validation** (Compare predictions vs. actual disease)

---

## FINAL VERIFICATION

Before field deployment, verify:

```cpp
// Code should have NO errors
✓ Compiles without warnings
✓ All sensors respond on Serial Monitor
✓ Display shows data correctly
✓ SD card logs entries every 30 minutes
✓ SMS alerts work (send test SMS)
✓ RTC keeps time accurately
✓ Battery voltage stable at 5V
✓ Solar panel charges battery (measure voltage increase over 2 hours)
```

---

## CONTACT & SUPPORT

For debugging assistance:
- Check Serial Monitor output for specific error messages
- Use I2C scanner to verify device addresses
- Test each sensor module individually before integration
- Review wiring against diagrams multiple times

**Happy Monitoring!** 🌾🥔

---

**Last Updated:** 2026-06-01
**Version:** 1.0
**Status:** Production Ready
