# CIRCUIT SCHEMATIC & WIRING DIAGRAM
## Solar-Powered Late Blight Monitoring System

---

## 1. COMPLETE SYSTEM BLOCK DIAGRAM

```
┌──────────────────────────────────────────────────────────────────────┐
│                       POWER SYSTEM                                    │
├──────────────────────────────────────────────────────────────────────┤
│                                                                        │
│  ┌─────────────┐     ┌──────────┐     ┌──────────┐    ┌──────────┐ │
│  │  20W Solar  │────▶│ CN3791   │────▶│ 3×18650  │───▶│ LM2596   │ │
│  │   Panel     │     │ Charger  │     │ Battery  │    │ Regulator│ │
│  │  (~20V)     │     │          │     │ (11.1V)  │    │ (5.0V)   │ │
│  └─────────────┘     └──────────┘     └──────────┘    └──────────┘ │
│                                             │              │         │
│                                             │    ┌─────────┼─────┐   │
│                                             │    │ 2200µF  │     │   │
│                                             │    │Capacitor│     │   │
│                                             │    └─────────┘     │   │
│                                             │                    │   │
│                                    ┌────────┴────────┐    ┌─────┴───┤
│                                    │  SIM800L (+11V) │    │  5V Rail│
│                                    └─────────────────┘    └──────────┘
│
└──────────────────────────────────────────────────────────────────────┘

┌──────────────────────────────────────────────────────────────────────┐
│                    ARDUINO NANO & SENSORS                             │
├──────────────────────────────────────────────────────────────────────┤
│                                                                        │
│  ┌──────────────────────────────────┐                                │
│  │      ARDUINO NANO (ATmega328P)   │                                │
│  │                                  │                                │
│  │  ┌──────────────────────────────┤                                │
│  │  │ POWER:                       │                                │
│  │  │  VCC (5V) ◄──┐               │                                │
│  │  │  GND      ◄──┼───────┐       │                                │
│  │  │            │       │       │                                │
│  │  ├──────────────────────────────┤                                │
│  │  │ DIGITAL I/O:                │                                │
│  │  │  D2   ◄── DS18B20 (Temp)    │                                │
│  │  │  D3   ◄── SIM800L RX        │                                │
│  │  │  D4   ◄── SIM800L TX        │                                │
│  │  │  D7   ◄── SD Card CS        │                                │
│  │  │  D8   ◄── TFT RST           │                                │
│  │  │  D9   ◄── TFT DC            │                                │
│  │  │  D10  ◄── TFT CS            │                                │
│  │  │  D11  ◄── SPI MOSI (SD+TFT) │                                │
│  │  │  D12  ◄── SPI MISO (SD+TFT) │                                │
│  │  │  D13  ◄── SPI SCK (SD+TFT)  │                                │
│  │  │                             │                                │
│  │  ├──────────────────────────────┤                                │
│  │  │ ANALOG INPUT:                │                                │
│  │  │  A0   (unused)              │                                │
│  │  │  A1   ◄── Leaf Wetness      │                                │
│  │  │  A2   ◄── Rain Sensor       │                                │
│  │  │  A4   ◄── I2C SDA (SHT31+RTC)                               │
│  │  │  A5   ◄── I2C SCL (SHT31+RTC)                               │
│  │  │                             │                                │
│  │  └──────────────────────────────┘                                │
│  │                                                                   │
│  └───────────────────────────────────────────────────────────────────┘
│
└──────────────────────────────────────────────────────────────────────┘
```

---

## 2. DETAILED PIN-BY-PIN CONNECTIONS

### Arduino Nano Header Pinout

```
                    ╔═══════════════╗
                    ║  ARDUINO NANO ║
    D1  [USB]  D0  ║               ║
    D2         RST  ║               ║
    D3         GND  ║               ║  
    D4         VCC  ║               ║  
    D5         A7   ║               ║  
    D6         A6   ║               ║  
    D7         A5(SCL)──┐          ║
    D8         A4(SDA)──┼──┐       ║
    D9         A3    │  │       ║
    D10        A2    │  │       ║
    D11        A1    │  │       ║
    D12        A0    │  │       ║
    D13        REF   │  │       ║
    GND────┐   GND   │  │       ║
    VCC────┼─► VCC   │  │       ║
           │         │  │       ║
                    ╚═══════════════╝
                          │  │
                ┌─────────┘  └───────┬──────┐
                │                    │      │
            SHT31 I2C           RTC I2C    │
           (SDA/SCL)         (SDA/SCL)    │
                │                   │      │
```

---

## 3. POWER SUPPLY SCHEMATIC

### 3.1 Solar Panel to Battery Charging

```
┌─────────────────────────────────────────────────────┐
│                 SOLAR CHARGING CIRCUIT              │
└─────────────────────────────────────────────────────┘

      20W Solar Panel
         (20V open circuit)
             │
          ┌──┴──┐
          │  +  │  (Red)
          └──┬──┘
             │
        ┌────▼────┐
        │ CN3791  │  Solar Charging IC
        │ Charger │
        └────┬────┘
             │
          ┌──┴──────────────────────────────────┐
          │                                     │
       ┌──▼──┐                              ┌──▼──┐
       │OUT+ │────────────┐                 │OUT- │
       └─────┘            │                 └─────┘
                      ┌───┴────┐
                      │ Battery │  3S1P Configuration
                      │ Pack    │
                      │ 11.1V   │  Cell 1: 18650 │
                      │         │  Cell 2: 18650 │
                      │         │  Cell 3: 18650 │
                      └───┬────┘
                          │
                      ┌───▼─────────────────┐
                      │   Common Ground     │
                      └─────────────────────┘
```

### 3.2 Battery to Arduino Power Distribution

```
┌──────────────────────────────────────────────────────┐
│            POWER DISTRIBUTION CIRCUIT               │
└──────────────────────────────────────────────────────┘

3×18650 Battery Pack (11.1V Nominal)
│
├─────────────────────┬──────────────────────┐
│                     │                      │
│              [2200µF Cap]            [LM2596]
│              ├─ VCC                  Buck Converter
│              │                       (11.1V → 5.0V)
│              │                       │
│              │                  ┌────▼────┐
│              │                  │ OUT (+) │
│              │                  └────┬────┘
│              │                       │
│    ┌─────────┴──────────────────────┴─────────┐
│    │                                          │
│    │          5V POWER RAIL                  │
│    │  ┌─ Arduino VCC                         │
│    │  ├─ SHT31 VCC                           │
│    │  ├─ RTC DS3231 VCC                      │
│    │  ├─ Leaf Wetness VCC                    │
│    │  ├─ Rain Sensor VCC                     │
│    │  ├─ TFT VCC                             │
│    │  ├─ DS18B20 VCC (with pull-up)         │
│    │  └─ SD Card VCC                         │
│    │                                          │
│    └──────────┬───────────────────────────────┘
│               │
│          ┌────▼─────┐
│          │  GND Bus │
│          │ (Common) │
│          └─────┬────┘
│                │
│    ┌───────────┴──────────────────┬─────────┐
│    │          │          │                  │
│    │    Arduino GND   SHT31 GND        RTC GND
│    │    
│    │
│ SIM800L GND (to battery pack GND)
│
└──────────────────────────────────────────────────────┘
```

---

## 4. SENSOR WIRING DETAILS

### 4.1 DS18B20 Temperature Sensor

```
                    DS18B20 (Waterproof Probe)
                    
    ┌─────────────────────────┐
    │  │ │ │                  │
    │  │ │ │   Probe Tip      │
    │  │ │ │                  │
    │  └─┬─┴─────────────────┬┘
    │    │                   │
   RED  YELLOW              BLACK
    │    │                   │
    │    │               ┌───▼────┐
    │    │               │ GND    │
    │    │               │ Bus    │
    │    │               └────────┘
    │    │
    │    └─────────┐
    │              │
    │          [4.7kΩ]  Pull-up Resistor
    │              │
    │              │
    │    ┌─────────┴────────┐
    │    │   Arduino Pin D2 │  (One-Wire Data)
    │    └──────────────────┘
    │
    └─────────────────────────┐
                              │
                         ┌────▼────┐
                         │ 5V Rail │
                         └─────────┘

Note: Pull-up resistor CRITICAL for reliable communication
      Use 4.7kΩ (or 10kΩ maximum)
      Keep wires short (< 1 meter)
```

### 4.2 SHT31 Temperature & Humidity Sensor

```
                    SHT31 Sensor Module
                    
    ┌──────────────────────────┐
    │  ┌────┐                  │
    │  │    │  (Sensor Die)    │
    │  └────┘                  │
    │                          │
    │  VCC  SDA  SCL  GND      │
    │   │    │    │    │       │
    └───┼────┼────┼────┼───────┘
        │    │    │    │
        │    │    │    └────────────────────┐
        │    │    │                         │
        │    │    └──────────────────┐      │
        │    │                       │      │
        │    └─────────┐             │      │
        │              │             │      │
    ┌───▼──┐       ┌───▼──┐     ┌───▼──┐ ┌─▼──┐
    │ 5V   │       │ A4   │     │ A5   │ │GND │
    │ Rail │       │(SDA) │     │(SCL) │ │Bus │
    └──────┘       └──────┘     └──────┘ └────┘
    
    I2C Address: 0x44 (Default)
    
    NOTE: SDA and SCL use 4.7kΩ pull-ups to 5V
          (Already on SHT31 module)
```

### 4.3 RTC DS3231 Module

```
                    RTC DS3231 Module
                    
    ┌──────────────────────────┐
    │  Crystal (32.768 kHz)    │
    │  Battery Backup          │
    │                          │
    │  VCC  SDA  SCL  GND      │
    │   │    │    │    │       │
    └───┼────┼────┼────┼───────┘
        │    │    │    │
        │    │    │    └──────────────────┐
        │    │    │                       │
        │    │    └──────────────────┐    │
        │    │                       │    │
    ┌───▼──┐│    ┌───┐          ┌───┐   ┌─▼──┐
    │ 5V   ││    │ A4│          │ A5│   │GND │
    │ Rail ││    │SDA│          │SCL│   │Bus │
    └──────┘└────└───┘          └───┘   └────┘
    
    I2C Address: 0x68
    
    WIRING: Share same I2C bus as SHT31
            SDA to Arduino A4
            SCL to Arduino A5
```

### 4.4 Leaf Wetness Sensor

```
                    Leaf Wetness Sensor
                    
    ┌──────────────────────────┐
    │  ┌──────────────────┐    │
    │  │ Two Metal Prongs │    │
    │  │ (Capacitive Type)│    │
    │  └──────────────────┘    │
    │                          │
    │  VCC   AO   GND          │
    │   │    │    │            │
    └───┼────┼────┼────────────┘
        │    │    │
        │    │    └───────────────────┐
        │    │                        │
    ┌───▼──┐ │    ┌────┐       ┌─────▼──┐
    │ 5V   │ │    │ A1 │       │ GND    │
    │ Rail │ │    │AIN │       │ Bus    │
    └──────┘ │    └────┘       └────────┘
             │
             └── 0.1µF Capacitor (Optional: for noise filtering)
                      │
                 ┌────┴────┐
                 │ Between  │
                 │ AO & GND │
                 └──────────┘

CALIBRATION VALUES (to be determined):
    Dry:   100-250 ADC counts
    Moist: 300-500 ADC counts
    Wet:   500-1023 ADC counts
```

### 4.5 Rain Sensor Module

```
                    Rain Sensor Module
                    
    ┌──────────────────────────┐
    │  ┌──────────────────┐    │
    │  │   PCB with Water │    │
    │  │   Detection      │    │
    │  │   Traces         │    │
    │  └──────────────────┘    │
    │                          │
    │  VCC   AO   GND          │
    │   │    │    │            │
    └───┼────┼────┼────────────┘
        │    │    │
        │    │    └───────────────────┐
        │    │                        │
    ┌───▼──┐ │    ┌────┐       ┌─────▼──┐
    │ 5V   │ │    │ A2 │       │ GND    │
    │ Rail │ │    │AIN │       │ Bus    │
    └──────┘ │    └────┘       └────────┘
             │
             └── 0.1µF Capacitor (Optional: for noise filtering)
                      │
                 ┌────┴────┐
                 │ Between  │
                 │ AO & GND │
                 └──────────┘

CALIBRATION VALUES (to be determined):
    No Rain:    100-200 ADC counts
    Light Rain: 200-400 ADC counts
    Heavy Rain: 400-800 ADC counts
```

---

## 5. DISPLAY & DATA LOGGING

### 5.1 TFT ILI9341 Display Wiring

```
                    ILI9341 TFT Display (2.4")
                    
    ┌─────────────────────────────┐
    │  ┌───────────────────────┐  │
    │  │                       │  │
    │  │     LCD Panel         │  │
    │  │    320×240 Pixels     │  │
    │  │                       │  │
    │  └───────────────────────┘  │
    │                             │
    │ VCC  GND  CS  RST  DC MOSI  │
    │ MISO SCK                    │
    │  │    │   │   │   │  │      │
    └──┼────┼───┼───┼───┼──┼──────┘
       │    │   │   │   │  │
       │    │   │   │   │  │
   ┌───▼──┐│  │┌──┘ │┌─┐ ┌──────┐
   │ 5V   ││  ││    ││ │ │Arduino│
   │ Rail ││  ││    ││ │ │ D11  │
   └──────┘│  ││    ││ │ │MOSI  │
           │  ││    ││ │ │      │
       ┌───▼──┘│    ││ │ └──────┘
       │      │    ││ │
    ┌──▼──┐  │┌───▘│ │┌──────┐
    │ GND │  ││ D10│ ││Arduino│
    │ Bus │  │└─CS─ │ │ D12  │
    └─────┘  │      │ │MISO  │
             │      │ │      │
             │      │ └──────┘
             │      │
             │   ┌──▼──────┐
             │   │Arduino  │
             │   │ D9  DC  │
             │   └────┬────┘
             │        │
             │   ┌────▼────┐
             │   │Arduino  │
             │   │ D8  RST │
             │   └─────────┘
             │
             └────Arduino D13 (SCK)

PIN MAPPING:
    TFT VCC   → 5V
    TFT GND   → GND
    TFT CS    → Arduino D10
    TFT RST   → Arduino D8
    TFT DC    → Arduino D9
    TFT MOSI  → Arduino D11 (SPI)
    TFT MISO  → Arduino D12 (SPI)
    TFT SCK   → Arduino D13 (SPI)
```

### 5.2 SD Card Module Wiring

```
                    SD Card Module (SPI)
                    
    ┌─────────────────────────┐
    │  ┌──────────────────┐   │
    │  │   MicroSD Card   │   │
    │  │   (8GB)          │   │
    │  └──────────────────┘   │
    │                         │
    │ VCC  GND  MOSI MISO    │
    │ CS   SCK               │
    │  │    │   │    │       │
    └──┼────┼───┼────┼───────┘
       │    │   │    │
       │    │   │    └──────────┐
       │    │   │               │
   ┌───▼──┐│  │ ┌───────────────┘
   │ 5V   ││  │ │
   │ Rail ││  │ └────┐
   └──────┘│  │      │
           │  │  ┌───▼────┐
       ┌───▼──┐ │ │Arduino │
       │ GND  │ │ │ D12   │
       │ Bus  │ │ │MISO   │
       └─────┘ │ │       │
               │ └───────┘
               │
           ┌───▼────┐
           │Arduino │
           │ D7     │
           │CS      │
           │(SD)    │
           └────────┘

PIN MAPPING:
    SD VCC   → 5V
    SD GND   → GND
    SD MOSI  → Arduino D11 (SPI)
    SD MISO  → Arduino D12 (SPI)
    SD SCK   → Arduino D13 (SPI)
    SD CS    → Arduino D7

SHARED SPI BUS:
    MOSI (D11) shared with TFT
    MISO (D12) shared with TFT
    SCK (D13)  shared with TFT
    Separate CS pins: D7 (SD) and D10 (TFT)
```

---

## 6. GSM MODULE WIRING

### 6.1 SIM800L Connection Diagram

```
                    SIM800L GSM Module
                    
    ┌─────────────────────────┐
    │  ┌──────────────────┐   │
    │  │   GSM Chipset    │   │
    │  │   (SIM800L)      │   │
    │  └──────────────────┘   │
    │                         │
    │ VCC GND TX RX           │
    │  │   │   │  │           │
    └──┼───┼───┼──┼───────────┘
       │   │   │  │
       │   │   │  └─────────┐
       │   │   │            │
       │   │   │     ┌──────▼──┐
       │   │   │     │Arduino  │
       │   │   │     │ D3  RX  │
       │   │   │     │(SoftSerial)
       │   │   │     └─────────┘
       │   │   │
       │   │   └──────┐
       │   │          │
       │   │     ┌────▼──┐
       │   │     │Arduino│
       │   │     │ D4 TX │
       │   │     │(SoftSerial)
       │   │     └──────┘
       │   │
   ┌───┴───▼────┐
   │Common GND   │
   │Bus          │
   └─────────────┘
   
   │
   └── Battery Pack (11.1V)
       WITH 2200µF Capacitor

CRITICAL: SIM800L draws up to 500mA during SMS
          Use battery power, not Arduino 5V regulator
          2200µF capacitor essential for stability
```

### 6.2 Power Stabilization for SIM800L

```
┌────────────────────────────────────────────┐
│  SIM800L POWER SUPPLY (Critical)           │
└────────────────────────────────────────────┘

Battery Pack (11.1V)
      │
      │  Short, thick wires (< 30cm)
      │  (Use AWG 18 or thicker)
      │
   ┌──┴──┐
   │     │  2200µF Electrolytic Capacitor
   │     │  (Voltage rating: 25V minimum)
   │     │
   │     ├──────────────────► SIM800L VCC
   │     │
   │     └──────────────────► SIM800L GND (reference)
   │
   └──────────────────────────► Common GND Bus

WHY 2200µF?
  - SIM800L draws 500mA+ during transmission
  - Voltage drop would occur without capacitor
  - Capacitor smooths transients
  - Prevents module reset during SMS send

INSTALLATION:
  1. Connect capacitor as close to module as possible
  2. Use short wires (< 5 cm)
  3. Use thick wires for power lines
  4. Verify polarity (+/-)
```

---

## 7. COMPLETE SYSTEM INTERCONNECT

```
┌─────────────────────────────────────────────────────────────────────────┐
│                                                                         │
│                 COMPLETE SYSTEM BLOCK DIAGRAM                         │
│                                                                         │
└─────────────────────────────────────────────────────────────────────────┘

                           ┌──────────────┐
                           │ 20W Solar    │
                           │ Panel        │
                           └───────┬──────┘
                                   │
                           ┌───────▼──────┐
                           │ CN3791       │
                           │ Charger IC   │
                           └───────┬──────┘
                                   │
                    ┌──────────────▼──────────────┐
                    │   3×18650 Battery Pack      │
                    │   (11.1V, 9000mAh)         │
                    └──┬─────────────────────┬───┘
                       │                     │
         ┌─────────────┘  ┌──────────────────┤
         │                │                  │
    ┌────▼────┐  ┌────────▼────┐      ┌──────▼──┐
    │ 2200µF  │  │  LM2596     │      │SIM800L  │
    │ Cap     │  │  Buck Conv  │      │(+11.1V) │
    │         │  │  (→5.0V)    │      │         │
    └────┬────┘  └─────┬──────┘      └──┬──────┘
         │             │                 │
         │             │            ┌────▼──────┐
         │        ┌────▼────┐      │ SIM Card   │
         │        │ 5V Rail │      │ (Data Plan)│
         │        └─────────┘      └────────────┘
         │             │
         └─────┬───────┴───────────────────┐
               │                           │
         ┌─────▼────────────────────┐  ┌──▼────┐
         │                          │  │ GND   │
         │      ARDUINO NANO        │  │ Bus   │
         │                          │  │       │
         │  D2: DS18B20            │  │       │
         │  D3/D4: SIM800L Serial  │  │       │
         │  D7: SD Card CS         │  │       │
         │  D8/D9/D10: TFT         │  │       │
         │  D11/D12/D13: SPI       │  │       │
         │  A1: Leaf Wetness       │  │       │
         │  A2: Rain Sensor        │  │       │
         │  A4/A5: I2C (SHT31/RTC) │  │       │
         │                          │  │       │
         └──────┬──────────┬────────┴──┴───────┘
                │          │
        ┌───────┘          └────────────┬──────┐
        │                               │      │
    ┌───▼──┐  ┌──────┐  ┌──────┐  ┌────▼──┐ ┌─▼──┐
    │DS18B20   │SHT31│  │RTC   │  │TFT    │ │SD  │
    │Soil Temp │Temp/│  │3231  │  │ILI9341│ │Card│
    │          │Humid│  │Clock │  │Disp   │ │Module
    └──────┘  └──────┘  └──────┘  └────────┘ └────┘
        │         │         │          │        │
        │         │         │          │        │
    ┌───▼────┬────▼────┬────▼───┬─────▼───┬───▼──┐
    │ Sensor │  I2C    │ I2C    │ SPI Bus │ SPI  │
    │ Cable  │  Bus    │ Bus    │         │ Bus  │
    │ CAT5   │ (4.7k)  │ (4.7k) │ Shared  │      │
    └────────┴────────┴────────┴────────┴──────┘

            ┌─────────────────────────┐
            │ FIELD SENSORS           │
            │                         │
            │ • Soil Temperature      │
            │ • Air Temperature       │
            │ • Humidity              │
            │ • Leaf Wetness          │
            │ • Rain Detection        │
            └─────────────────────────┘
```

---

## 8. CABLE SPECIFICATIONS

### 8.1 Power Cables

| Connection | Gauge | Length | Type | Color |
|---|---|---|---|---|
| Solar Panel to Charger | 12 AWG | 5m | Stranded | Red/Black |
| Charger to Battery | 10 AWG | 0.5m | Stranded | Red/Black |
| Battery to LM2596 | 10 AWG | 0.2m | Stranded | Red/Black |
| Battery to SIM800L | 8 AWG | 0.3m | Stranded | Red/Black |
| 5V Rail to Components | 18 AWG | Varies | Stranded | Red |
| GND Bus | 18 AWG | Varies | Stranded | Black |

### 8.2 Signal Cables

| Connection | Type | Shielding | Length | Notes |
|---|---|---|---|---|
| DS18B20 to Arduino | CAT5 | Yes | < 5m | Use twisted pair |
| Leaf/Rain to Arduino | CAT5 | Yes | < 5m | Group with GND |
| I2C Bus | CAT5 | Yes | < 3m | 120Ω termination |
| SPI Bus (TFT/SD) | Ribbon | Optional | < 0.5m | 8-10 conductor |
| SIM800L RX/TX | CAT5 | Yes | < 3m | Twisted pair |

### 8.3 CAT5 Cable Pairing Strategy

```
CAT5 Cable Pinout (8 wires, 4 twisted pairs)

Pair 1: White/Orange + Orange
        ├─ Signal
        └─ Signal Ground

Pair 2: White/Green + Green
        ├─ Signal
        └─ Signal Ground

Pair 3: White/Blue + Blue
        ├─ Power (+5V or Data)
        └─ Ground

Pair 4: White/Brown + Brown
        ├─ Power (+5V or Data)
        └─ Ground

EXAMPLE WIRING:
  DS18B20 (3 wires):
    Pair 1: Orange/White Orange → VCC
    Pair 2: Green/White Green   → Data (D2)
    Pair 3: Blue/White Blue     → GND

  Leaf Wetness (3 wires):
    Pair 1: Orange/White Orange → VCC
    Pair 2: Green/White Green   → AO (A1)
    Pair 3: Blue/White Blue     → GND
```

---

## 9. PCB LAYOUT (Recommended)

```
┌─────────────────────────────────────────────────┐
│         50mm × 80mm PCB Layout                   │
├─────────────────────────────────────────────────┤
│                                                 │
│  ┌────────────────────────────────────┐        │
│  │    Arduino Nano (socket)           │        │
│  │                                    │        │
│  └────────────────────────────────────┘        │
│         │         │         │                   │
│   ┌─────▼─────┬───▼─────┬───▼─────┐           │
│   │           │         │         │           │
│   │ Screw     │ I2C     │ SPI     │           │
│   │ Terminals │ Pullup  │ Pullup │           │
│   │           │ 4.7kΩ   │         │           │
│   └───┬───────┴─────────┴─────────┘           │
│       │                                       │
│   ┌───▼──────────────────┐                    │
│   │  Decoupling Cap      │                    │
│   │  (0.1µF × 4)         │                    │
│   └──────────────────────┘                    │
│                                                 │
│  Power Distribution:                           │
│  ├─ 5V Rail (Copper pour)                     │
│  └─ GND Rail (Ground plane)                   │
│                                                 │
└─────────────────────────────────────────────────┘
```

---

## 10. CONNECTOR TYPES RECOMMENDED

| Connection | Connector Type | Rating | Notes |
|---|---|---|---|
| Power Input (Solar) | MC4 | 50A | Industry standard |
| Battery to System | Anderson PowerPole | 45A | Weatherproof |
| Sensor Field Connectors | M12 or IP67 | 5A | Waterproof |
| Internal Signal | IDC Headers | 2A | Standard Arduino |
| External Power | XT60 | 60A | Backup connection |

---

## 11. TESTING CHECKPOINTS

Before field deployment, verify:

```
┌─────────────────────────────────────────────┐
│ VOLTAGE MEASUREMENTS                        │
├─────────────────────────────────────────────┤
│ Solar Panel (Open Circuit)    : ~20V        │
│ CN3791 Output                 : ~13.5V      │
│ Battery Pack (Full)           : ~11.8V      │
│ Battery Pack (Depleted)       : ~10.0V      │
│ LM2596 Output                 : 5.0V ±0.1V  │
│ Arduino VCC                   : 5.0V ±0.1V  │
│ 5V Rail (No Load)            : 5.0V        │
│ 5V Rail (Full Load)          : 4.95V+      │
│ SIM800L Capacitor Voltage    : 11.1V       │
└─────────────────────────────────────────────┘

Current Measurements:
├─ Arduino at rest: ~50mA
├─ All sensors active: ~60mA
├─ Display on: +100mA
├─ SIM800L at rest: +20mA
└─ SIM800L sending SMS: +500mA peak
```

---

**Document Version:** 1.0  
**Last Updated:** 2026-06-01  
**Status:** Ready for Implementation
