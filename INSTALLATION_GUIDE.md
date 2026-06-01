# COMPLETE INSTALLATION GUIDE
## Step-by-Step Instructions with Screenshots & Troubleshooting

---

## TABLE OF CONTENTS
1. [Software Installation](#1-software-installation--setup)
2. [Hardware Assembly - Power System](#2-hardware-assembly--power-system)
3. [Hardware Assembly - Arduino & Sensors](#3-hardware-assembly--arduino--sensors)
4. [Code Upload](#4-code-upload-to-arduino)
5. [Testing Each Component](#5-testing-each-component)
6. [Troubleshooting](#6-troubleshooting-guide)

---

## 1. SOFTWARE INSTALLATION & SETUP

### 1.1 Download Arduino IDE

**STEP 1:** Open your web browser

**STEP 2:** Go to: `https://www.arduino.cc/en/software`

**STEP 3:** You will see this screen:
```
┌────────────────────────────────────────────┐
│  Arduino Official Website                  │
│                                            │
│  [DOWNLOAD ARDUINO IDE 2.x]  ← Click here  │
│  (or Arduino IDE 1.8.19)                   │
│                                            │
│  Choose your operating system:             │
│  ☐ Windows                                 │
│  ☐ macOS                                   │
│  ☐ Linux                                   │
└────────────────────────────────────────────┘
```

**STEP 4:** Select your operating system and download (File size: ~500MB)

**STEP 5:** Wait for download to complete

---

### 1.2 Install Arduino IDE

#### FOR WINDOWS:
1. Locate the downloaded file: `ArduinoIDE_2.x.exe` (in Downloads folder)
2. Right-click on it → Select "Run as administrator"
3. Click "Yes" when prompted
4. Follow installation wizard:
   - Click "Next >"
   - Accept License Agreement → Click "I Agree"
   - Choose installation path (Default is fine) → Click "Next >"
   - Click "Install"
5. Wait for installation to complete (2-3 minutes)
6. Click "Finish"

#### FOR MAC:
1. Open the downloaded `.dmg` file
2. Drag the Arduino icon to Applications folder
3. Wait for copy to complete
4. Eject the disk image

#### FOR LINUX:
```bash
# Open Terminal and run:
tar xfz arduino-*.tar.xz
cd arduino-*
./install.sh
```

---

### 1.3 Launch Arduino IDE

**Windows:** Click Start → Search "Arduino IDE" → Click to open

**Mac:** Applications → Arduino IDE → Double-click

**Linux:** Terminal → Type `arduino` → Press Enter

**First Launch Screen:**
```
┌────────────────────────────────────────┐
│  ARDUINO IDE 2.x                       │
├────────────────────────────────────────┤
│                                        │
│  File  Edit  Sketch  Tools  Help       │
│  [⚙ ≡] Search...                      │
│                                        │
│  ┌──────────────────────────────────┐  │
│  │ // Your first sketch              │  │
│  │ void setup() {                    │  │
│  │   Serial.begin(9600);             │  │
│  │ }                                 │  │
│  │ void loop() {                     │  │
│  │ }                                 │  │
│  └──────────────────────────────────┘  │
│                                        │
│  [✔ Check] [→ Upload] [Serial] [Help] │
│                                        │
└────────────────────────────────────────┘
```

**Great!** Arduino IDE is installed.

---

### 1.4 Install Arduino Nano Board Support

**STEP 1:** Click on **"Tools"** menu at the top

```
┌────────────────────────────────┐
│ Tools                          │
├────────────────────────────────┤
│ Board                   ▶      │
│ Port                    ▶      │
│ Programmer              ▶      │
│ Board Info                     │
│ Manage Libraries               │
└────────────────────────────────┘
```

**STEP 2:** Click on **"Board"** (you'll see a submenu)

```
┌────────────────────────────────┐
│ Arduino AVR Boards    ▶         │
│ Arduino SAMD Boards   ▶         │
│ Arduino megaAVR Boards ▶        │
│ ...                            │
│ Boards Manager...              │
└────────────────────────────────┘
```

**STEP 3:** Click on **"Boards Manager..."** (bottom option)

A new window will open:
```
┌────────────────────────────────────────────┐
│  Boards Manager                            │
├────────────────────────────────────────────┤
│  🔍 Search for boards...                   │
├────────────────────────────────────────────┤
│                                            │
│  ☐ Arduino AVR Boards                     │
│    by Arduino                             │
│    Version: 1.8.x                         │
│    [INSTALL] or [UPDATE]                  │
│                                            │
│  ☐ Arduino SAMD Boards                    │
│  ☐ Arduino megaAVR Boards                 │
│                                            │
└────────────────────────────────────────────┘
```

**STEP 4:** Look for **"Arduino AVR Boards"**

**STEP 5:** Click the **[INSTALL]** button next to it

```
Status: Installing...
Progress bar: ████████████████ 100%
(This takes 1-2 minutes)
```

**STEP 6:** Wait until it says **"INSTALLED"** ✓

**STEP 7:** Close the Boards Manager window

---

### 1.5 Select Arduino Nano Board

**STEP 1:** Click **Tools** → **Board**

```
┌────────────────────────────────┐
│ Arduino AVR Boards    ▶         │
│                                │
└────────────────────────────────┘
```

**STEP 2:** Hover over **"Arduino AVR Boards"**

```
┌────────────────────────────────┐
│ Arduino Nano                   │
│ Arduino Uno                    │
│ Arduino Mega                   │
│ Arduino Leonardo               │
│ Arduino Micro                  │
│ ...                            │
└────────────────────────────────┘
```

**STEP 3:** Click on **"Arduino Nano"**

You will see this message at bottom:
```
✓ Board selected: Arduino Nano
```

---

### 1.6 Select Processor (Critical!)

**STEP 1:** Click **Tools** → **Processor**

```
┌────────────────────────────────┐
│ ATmega328P (Old Bootloader)   │
│ ATmega328P                     │
│ ATmega168                      │
│                                │
└────────────────────────────────┘
```

**STEP 2:** Select **"ATmega328P"** (the second one, without "Old Bootloader")

```
✓ Processor selected: ATmega328P
```

---

## 2. HARDWARE ASSEMBLY – POWER SYSTEM

### BEFORE YOU START:
- ⚠️ **Turn off solar panel** (cover with cloth if sunny)
- ⚠️ **Disconnect all batteries**
- ⚠️ **Do NOT connect power until instructed**
- ⚠️ Have a multimeter handy for voltage checking

---

### 2.1 Solar Panel Inspection

**STEP 1:** Inspect solar panel for damage
```
✓ No cracks in glass
✓ No burnt marks
✓ All corners intact
✓ Wires not damaged
```

**STEP 2:** Measure open circuit voltage (no load)

Using a **multimeter**:
1. Set to **DC Voltage (V—)** mode
2. Touch RED probe to positive (red wire)
3. Touch BLACK probe to negative (black wire)
4. Reading should show **~18-22V**

```
If reading is 0V:
  → Panel is defective, do not use
If reading is < 15V:
  → Panel may be damaged
If reading is 18-22V:
  → Panel is GOOD ✓
```

---

### 2.2 Battery Pack Assembly (3×18650)

**IMPORTANT:** This step requires a **battery holder** with 3 slots in SERIES (3S)

**STEP 1:** Obtain 3 new 18650 batteries
```
Example: Panasonic NCR18650B (3400mAh)
         or LG 18650 (3000mAh)
```

**STEP 2:** Insert batteries into holder in series
```
[+] ← Positive terminal
 │
[18650 Cell #1]
 │
[18650 Cell #2]
 │
[18650 Cell #3]
 │
[-] ← Negative terminal
```

**STEP 3:** Verify battery connections with multimeter
1. Touch RED probe to positive terminal
2. Touch BLACK probe to negative terminal
3. Reading should show **~11.0V to 12.6V** (depends on charge state)

```
If reading is 0V:
  → Check battery holder connections
If reading is 3-4V:
  → Only one battery installed
If reading is 11-12.6V:
  → CORRECT ✓
```

---

### 2.3 CN3791 Solar Charger Module Setup

**STEP 1:** Locate the CN3791 module (small PCB with chips)

**STEP 2:** Identify the connectors:
```
CN3791 Module
├─ IN+ and IN- (Input from solar panel)
├─ OUT+ and OUT- (Output to battery)
└─ GND (Ground reference)
```

**STEP 3:** Connect solar panel to CN3791
```
Solar Panel RED (+)   → CN3791 IN+
Solar Panel BLACK (-) → CN3791 IN-
```

**STEP 4:** Connect CN3791 to battery pack
```
CN3791 OUT+  → Battery Pack POSITIVE (+)
CN3791 OUT-  → Battery Pack NEGATIVE (-)
CN3791 GND   → Battery Pack NEGATIVE (-) [optional reference]
```

**STEP 5:** Verify connections:
```
Visual Check:
  ✓ All connections are tight
  ✓ No exposed wires
  ✓ Correct polarity (red to +, black to -)
  ✓ No loose components
```

**STEP 6:** Test charging
1. Move solar panel to sunlight
2. Wait 5 minutes
3. Measure battery voltage with multimeter
4. It should INCREASE (charging is happening)

```
Before sunlight: 11.5V
After 5 min:     11.6V (charging ✓)
After 10 min:    11.7V (charging ✓)
```

---

### 2.4 LM2596 Buck Converter Configuration (CRITICAL!)

**⚠️ WARNING:** LM2596 output voltage MUST be set to 5.0V before connecting to Arduino!

**STEP 1:** Inspect the LM2596 module
```
LM2596 Module
├─ IN+ and IN- (Input: 11.1V from battery)
├─ OUT+ and OUT- (Output: to be set to 5.0V)
└─ ADJ (Adjust potentiometer for output voltage)
```

**STEP 2:** Temporarily connect battery to LM2596
```
Battery Pack (+)  → LM2596 IN+
Battery Pack (-)  → LM2596 IN-
```

**STEP 3:** Measure output voltage with multimeter
1. Set multimeter to **DC Voltage (V—)**
2. Touch RED probe to LM2596 OUT+
3. Touch BLACK probe to LM2596 OUT-
4. Note the reading

```
If reading is > 6V:
  → Voltage is too high, must adjust down
If reading is < 4.5V:
  → Voltage is too low, must adjust up
If reading is exactly 5.0V:
  → PERFECT, no adjustment needed ✓
```

**STEP 4:** Adjust voltage (if needed)

Locate the **blue trimmer potentiometer** on LM2596 module:
```
┌─────────────────┐
│ LM2596 Module   │
│                 │
│  ┌────────────┐ │
│  │ Trimmer    │ │  ← This small component
│  │ Potentiometer
│  │ (blue box) │ │
│  └────────────┘ │
└─────────────────┘
```

Using a **small flathead screwdriver**:
- Turn **clockwise** to increase voltage
- Turn **counterclockwise** to decrease voltage
- Make small 1/4 turns only
- Wait 2 seconds after each turn, then measure

**Example adjustment:**
```
Measurement 1: 6.5V (too high)
  → Turn potentiometer counterclockwise 1/4 turn
  
Measurement 2: 6.0V (still high)
  → Turn potentiometer counterclockwise 1/4 turn

Measurement 3: 5.2V (close!)
  → Turn potentiometer counterclockwise 1/8 turn

Measurement 4: 5.0V ✓ DONE
  → STOP adjusting
```

**STEP 5:** Verify stability
1. Measure voltage again after 1 minute
2. It should still read **5.0V ± 0.1V**
3. Do NOT disconnect battery yet

---

### 2.5 Power Distribution Setup

**STEP 1:** Prepare a **2200µF capacitor** for SIM800L

```
2200µF Capacitor
├─ Positive (+) leg → Battery positive
├─ Negative (-) leg → Ground
└─ Markings:
   - Longer leg = Positive (+)
   - Shorter leg = Negative (-)
```

**STEP 2:** Connect power rails
```
5V RAIL (from LM2596 OUT+):
  ├─ To Arduino VCC
  ├─ To SHT31 VCC
  ├─ To RTC VCC
  ├─ To Leaf Wetness VCC
  ├─ To Rain Sensor VCC
  ├─ To TFT VCC
  └─ To SD Card VCC

GROUND RAIL (from battery negative):
  ├─ To Arduino GND
  ├─ To SHT31 GND
  ├─ To RTC GND
  ├─ To Leaf Wetness GND
  ├─ To Rain Sensor GND
  ├─ To TFT GND
  ├─ To SD Card GND
  └─ To all GND references
```

**STEP 3:** Install 2200µF capacitor
```
Connect directly across battery terminals:

Battery (+) ──────┬──────── Battery (-)
                  │
          ┌───────┴────────┐
          │ 2200µF Cap     │
          │                │
          └────────────────┘
                  │
              SIM800L
              (connected here)
```

**STEP 4:** Final power system verification
```
Checklist:
  ☐ Solar panel connected to CN3791
  ☐ CN3791 connected to battery
  ☐ Battery connected to LM2596
  ☐ LM2596 output voltage = 5.0V
  ☐ 5V rail supplies all sensors
  ☐ Ground rail connects all GNDs
  ☐ 2200µF capacitor installed for SIM800L
  ☐ No exposed wires
  ☐ No shorts between + and -
  ☐ All connections tight
```

---

## 3. HARDWARE ASSEMBLY – ARDUINO & SENSORS

### ⚠️ IMPORTANT: Power system MUST be complete before this section!

---

### 3.1 Prepare Arduino Nano

**STEP 1:** Locate your Arduino Nano
```
Arduino Nano (approximately 4cm × 2cm)
```

**STEP 2:** Inspect for damage
```
✓ No bent pins
✓ No burnt marks
✓ Microcontroller chip intact
✓ All headers present
```

**STEP 3:** Identify the USB port
```
┌──────────────────────────┐
│ Arduino Nano             │
│                          │
│  [USB Port] ← This one   │
│                          │
│ D1  D0  RST GND VCC A7   │
│ D2  D3  D4  D5  D6  A6   │
│ D7  D8  D9  D10 D11 A5   │
│ D12 D13 GND VCC  A4 A3   │
│ A2  A1  A0 REF  GND VCC  │
│                          │
└──────────────────────────┘
```

---

### 3.2 Connect DS18B20 Temperature Sensor

**What you need:**
- DS18B20 waterproof temperature sensor (3 wires)
- 4.7kΩ resistor
- Jumper wires or CAT5 cable

**STEP 1:** Identify the three wires on DS18B20
```
DS18B20 Waterproof Probe
├─ RED wire    = Power (+5V)
├─ YELLOW wire = Data (to Arduino D2)
└─ BLACK wire  = Ground (GND)
```

**STEP 2:** Connect power wire (RED)
```
RED wire → Arduino 5V rail
        → OR → Battery positive (11.1V) through 5V regulator
        → OR → LM2596 OUT+ (5.0V)

Visual connection:
┌───────────────────────────┐
│ DS18B20 RED wire          │
│         │                 │
│         └────► 5V Rail    │
└───────────────────────────┘
```

**STEP 3:** Connect data wire (YELLOW)
```
YELLOW wire → Arduino D2 pin

AND

Install 4.7kΩ pull-up resistor:
    4.7kΩ Resistor
        │
    ┌───┴────┐
    │        │
 D2 pin   5V Rail
    
Connect one end of resistor to D2 pin
Connect other end to 5V rail
```

**STEP 4:** Connect ground wire (BLACK)
```
BLACK wire → Arduino GND rail
          → OR → Battery negative
          → Common ground point
```

**STEP 5:** Verify connection
```
Multimeter test:
1. Set to Continuity (🔊 symbol)
2. Touch probes to DS18B20 RED and 5V rail
3. You should hear a beep ✓

Repeat for:
  - YELLOW wire to D2 pin
  - BLACK wire to GND
```

---

### 3.3 Connect SHT31 Temperature & Humidity Sensor

**What you need:**
- SHT31 sensor module (4 pins)
- Jumper wires

**STEP 1:** Identify the SHT31 module
```
SHT31 Module
┌────────────────┐
│ ┌──────────┐   │
│ │ Sensor   │   │
│ └──────────┘   │
│ VCC SDA SCL GND│
│  │   │   │   │
└──┼───┼───┼───┼─
   │   │   │   │
```

**STEP 2:** Connect power (VCC)
```
VCC pin → 5V Rail

Using jumper wire:
    5V Rail
       │
       └──────────────► SHT31 VCC
```

**STEP 3:** Connect ground (GND)
```
GND pin → Ground Rail

Using jumper wire:
    GND Rail
       │
       └──────────────► SHT31 GND
```

**STEP 4:** Connect I2C Data line (SDA) - CRITICAL!
```
SDA pin → Arduino A4 pin

Wire path:
    SHT31 SDA ────────► Arduino A4
```

**STEP 5:** Connect I2C Clock line (SCL)
```
SCL pin → Arduino A5 pin

Wire path:
    SHT31 SCL ────────► Arduino A5
```

**STEP 6:** Verify I2C connection
```
I2C address: 0x44 (default for SHT31)

✓ A4 and A5 are I2C pins (shared with RTC)
✓ Both sensors can be on same I2C bus
✓ No additional resistors needed (already on module)
```

---

### 3.4 Connect RTC DS3231 Module

**What you need:**
- RTC DS3231 module (4 pins)
- Jumper wires (shared with SHT31)

**STEP 1:** Identify the RTC module
```
RTC DS3231 Module
┌────────────────┐
│ [Crystal 32kHz]│
│                │
│ VCC SDA SCL GND│
│  │   │   │   │
└──┼───┼───┼───┼─
   │   │   │   │
```

**STEP 2:** Connect power (VCC)
```
VCC pin → 5V Rail (same 5V rail as SHT31)

Using jumper wire:
    5V Rail
       │
       ├──────────────► SHT31 VCC
       │
       └──────────────► RTC VCC
```

**STEP 3:** Connect ground (GND)
```
GND pin → Ground Rail (shared with SHT31)

Using jumper wire:
    GND Rail
       │
       ├──────────────► SHT31 GND
       │
       └──────────────► RTC GND
```

**STEP 4:** Connect I2C Data line (SDA) - SHARED!
```
SDA pin → Arduino A4 pin (SAME as SHT31)

Wire path:
    SHT31 SDA ────┬──────► Arduino A4
                  │
    RTC SDA ──────┘
```

**STEP 5:** Connect I2C Clock line (SCL) - SHARED!
```
SCL pin → Arduino A5 pin (SAME as SHT31)

Wire path:
    SHT31 SCL ────┬──────► Arduino A5
                  │
    RTC SCL ──────┘
```

**STEP 6:** I2C Bus Explanation
```
✓ Both SHT31 and RTC share the SAME I2C bus
✓ They have different addresses:
  - SHT31: 0x44
  - RTC: 0x68
✓ Arduino can talk to both simultaneously
✓ This is called "I2C Multiplexing"
```

---

### 3.5 Connect Leaf Wetness Sensor

**What you need:**
- Leaf Wetness Sensor (3 wires)
- 0.1µF capacitor (optional, for noise filtering)
- Jumper wires

**STEP 1:** Identify the Leaf Wetness Sensor
```
Leaf Wetness Sensor
├─ VCC   (Power)
├─ AO    (Analog Output)
└─ GND   (Ground)
```

**STEP 2:** Connect power (VCC)
```
VCC → 5V Rail
```

**STEP 3:** Connect analog output (AO)
```
AO → Arduino A1 pin

Using jumper wire:
    Leaf Wetness AO ────────► Arduino A1

Analog value range: 0-1023
(0 = dry, 1023 = wet)
```

**STEP 4:** Connect ground (GND)
```
GND → Ground Rail
```

**STEP 5:** Optional: Add noise filter capacitor
```
Connect 0.1µF capacitor between AO and GND:

    Leaf Wetness AO ───────► Arduino A1
                │
            [0.1µF]
                │
                GND
```

---

### 3.6 Connect Rain Sensor Module

**What you need:**
- Rain Sensor module (3 wires)
- 0.1µF capacitor (optional, for noise filtering)
- Jumper wires

**STEP 1:** Identify the Rain Sensor
```
Rain Sensor Module
├─ VCC   (Power)
├─ AO    (Analog Output)
└─ GND   (Ground)
```

**STEP 2:** Connect power (VCC)
```
VCC → 5V Rail
```

**STEP 3:** Connect analog output (AO)
```
AO → Arduino A2 pin

Using jumper wire:
    Rain Sensor AO ────────► Arduino A2

Analog value range: 0-1023
(0 = no rain, 1023 = heavy rain)
```

**STEP 4:** Connect ground (GND)
```
GND → Ground Rail
```

**STEP 5:** Optional: Add noise filter capacitor
```
Connect 0.1µF capacitor between AO and GND:

    Rain Sensor AO ───────► Arduino A2
            │
        [0.1µF]
            │
            GND
```

---

### 3.7 Connect TFT Display (ILI9341)

**What you need:**
- ILI9341 TFT Display 2.4" module
- Jumper wires

**STEP 1:** Identify the TFT Display pins
```
TFT Display Module
┌────────────────────────┐
│ ┌──────────────────┐   │
│ │   LCD Panel      │   │
│ │  320×240 pixels  │   │
│ └──────────────────┘   │
│                        │
│ VCC GND CS  RST DC     │
│ MOSI MISO SCK          │
│  │   │   │   │  │      │
└──┼───┼───┼───┼──┼──────┘
   │   │   │   │  │
```

**STEP 2:** Connect power and ground
```
VCC → 5V Rail
GND → Ground Rail
```

**STEP 3:** Connect Chip Select (CS)
```
CS → Arduino D10 pin

Using jumper wire:
    TFT CS ────────► Arduino D10
```

**STEP 4:** Connect Reset (RST)
```
RST → Arduino D8 pin

Using jumper wire:
    TFT RST ────────► Arduino D8
```

**STEP 5:** Connect Data/Command (DC)
```
DC → Arduino D9 pin

Using jumper wire:
    TFT DC ────────► Arduino D9
```

**STEP 6:** Connect SPI Bus (3 shared lines)
```
MOSI → Arduino D11 (Data line from Arduino to TFT)
MISO → Arduino D12 (Data line from TFT to Arduino)
SCK  → Arduino D13 (Clock signal)

Using jumper wires:
    TFT MOSI ────────► Arduino D11
    TFT MISO ────────► Arduino D12
    TFT SCK  ────────► Arduino D13
```

**STEP 7:** Verify TFT connections
```
Summary of TFT connections:
  ☐ VCC   → 5V
  ☐ GND   → GND
  ☐ CS    → D10
  ☐ RST   → D8
  ☐ DC    → D9
  ☐ MOSI  → D11
  ☐ MISO  → D12
  ☐ SCK   → D13
```

---

### 3.8 Connect SD Card Module

**What you need:**
- SD Card module (SPI mode)
- MicroSD card (8GB)
- Jumper wires

**STEP 1:** Insert MicroSD card into module
```
SD Card Module
┌──────────────────┐
│ ┌──────────────┐ │
│ │   MicroSD    │ │ ← Insert card here
│ │    Slot      │ │   (all the way in)
│ └──────────────┘ │
│                  │
│ VCC GND MOSI     │
│ MISO SCK CS      │
└──────────────────┘
```

**STEP 2:** Connect power and ground
```
VCC → 5V Rail
GND → Ground Rail
```

**STEP 3:** Connect Chip Select (CS)
```
CS → Arduino D7 pin

Using jumper wire:
    SD CS ────────► Arduino D7
```

**STEP 4:** Connect SPI Bus (shared with TFT)
```
MOSI → Arduino D11 (shared with TFT)
MISO → Arduino D12 (shared with TFT)
SCK  → Arduino D13 (shared with TFT)

Using jumper wires:
    SD MOSI ────────► Arduino D11
    SD MISO ────────► Arduino D12
    SD SCK  ────────► Arduino D13
```

**STEP 5:** Format MicroSD card (Important!)
```
On Windows:
  1. Insert card into computer's SD slot
  2. Right-click → Format
  3. File system: FAT32
  4. Click "Start"
  5. Click "OK" on warning
  6. Wait for completion
  7. Eject and reinsert into SD module

On Mac:
  1. Insert card
  2. Disk Utility → Select card
  3. Erase
  4. Format: MS-DOS (FAT)
  5. Click "Erase"
```

**STEP 6:** Verify SD card module
```
Summary of SD connections:
  ☐ VCC   → 5V
  ☐ GND   → GND
  ☐ CS    → D7
  ☐ MOSI  → D11
  ☐ MISO  → D12
  ☐ SCK   → D13
```

---

### 3.9 Connect SIM800L GSM Module

**What you need:**
- SIM800L module
- SIM card (with active data plan)
- 2200µF capacitor
- Jumper wires

**STEP 1:** Insert SIM card
```
SIM800L Module
┌──────────────────┐
│ ┌──────────────┐ │
│ │   SIM Card   │ │ ← Insert here
│ │    Slot      │ │
│ └──────────────┘ │
│                  │
│ VCC GND TX RX    │
└──────────────────┘
```

1. Locate the SIM card slot
2. Insert your SIM card (flat side first)
3. Push until it clicks

**STEP 2:** Install 2200µF stabilization capacitor
```
2200µF Capacitor Installation:

Positive (+) leg → Battery Positive
Negative (-) leg → Battery Negative

Visual:
Battery (+) ─┬──────────► SIM800L VCC
             │
          [2200µF]
             │
Battery (-) ─┴──────────► SIM800L GND

This capacitor is CRITICAL for stability!
```

**STEP 3:** Connect power
```
VCC → Battery Positive (11.1V)
GND → Ground Rail

NOTE: SIM800L uses battery power, NOT 5V!
This is because transmitting needs 500mA+
```

**STEP 4:** Connect TX (Transmit) - Arduino receives data from SIM800L
```
SIM800L TX → Arduino D3 (RX of SoftwareSerial)

Using jumper wire:
    SIM800L TX ────────► Arduino D3
```

**STEP 5:** Connect RX (Receive) - Arduino sends data to SIM800L
```
SIM800L RX → Arduino D4 (TX of SoftwareSerial)

Using jumper wire:
    SIM800L RX ────────► Arduino D4
```

**STEP 6:** Verify SIM800L connections
```
Summary of SIM800L connections:
  ☐ VCC   → Battery (+11.1V)
  ☐ GND   → Ground Rail
  ☐ TX    → Arduino D3
  ☐ RX    → Arduino D4
  ☐ 2200µF cap installed
  ☐ SIM card inserted
```

---

## 4. CODE UPLOAD TO ARDUINO

### 4.1 Download the Code File

**STEP 1:** Go to your GitHub repository
```
https://github.com/nafis-m-chowdhury/Phytophthora-infestans
```

**STEP 2:** Click on **"Potato_Late_Blight_System.ino"**

**STEP 3:** Click the **"Raw"** button

```
┌────────────────────────────┐
│ Raw  Blame  History        │
│ ↓                          │
│ [Click RAW button]         │
└────────────────────────────┘
```

**STEP 4:** Right-click on the page → **"Save As"**

Save as: `Potato_Late_Blight_System.ino` (in a folder like `Documents/Arduino/`)

---

### 4.2 Open Code in Arduino IDE

**STEP 1:** Open Arduino IDE

**STEP 2:** Go to **File** → **Open**

**STEP 3:** Navigate to your downloaded file

**STEP 4:** Select **Potato_Late_Blight_System.ino** → Click **"Open"**

The code will appear in the editor:
```cpp
/*
  ============================================================================
  SOLAR-POWERED GSM-BASED MICROCLIMATE MONITORING SYSTEM
  ...
  ============================================================================
*/

#include <OneWire.h>
#include <DallasTemperature.h>
...
```

---

### 4.3 Install Required Libraries

**⚠️ CRITICAL:** The code uses 6 external libraries. They MUST be installed!

**STEP 1:** Open Library Manager

Click **Tools** → **Manage Libraries** (or Sketch → Include Library → Manage Libraries)

```
┌────────────────────────────────────────┐
│  Library Manager                       │
├────────────────────────────────────────┤
│  🔍 Search for libraries...            │
│  [                              ]      │
├────────────────────────────────────────┤
│ ☐ Installed                           │
│ ☐ Updates                             │
│ ☐ ...                                 │
└────────────────────────────────────────┘
```

**STEP 2:** Install Library 1 - OneWire

1. Type **"OneWire"** in the search box
2. Look for **"OneWire"** by Paul Stoffregen
3. Click **[INSTALL]**

```
Searching... OneWire
┌────────────────────────────────────┐
│ OneWire                            │
│ by Paul Stoffregen                 │
│ Version: 2.3.7                     │
│ [INSTALL]                          │
│                                    │
│ Description: Control 1-Wire        │
│ devices...                         │
└────────────────────────────────────┘

Status: Installing...
Progress: ████████████████ 100%
✓ INSTALLED
```

**STEP 3:** Install Library 2 - DallasTemperature

1. Clear the search box
2. Type **"DallasTemperature"**
3. Look for **"DallasTemperature"** by Miles Burton
4. Click **[INSTALL]**

```
Searching... DallasTemperature
┌────────────────────────────────────┐
│ DallasTemperature                  │
│ by Miles Burton                    │
│ Version: 3.9.0                     │
│ [INSTALL]                          │
└────────────────────────────────────┘

Status: Installing...
✓ INSTALLED
```

**STEP 4:** Install Library 3 - SHT31

1. Clear the search box
2. Type **"SHT31"**
3. Look for **"SHT31"** by Rob Tillaart
4. Click **[INSTALL]**

**STEP 5:** Install Library 4 - RTClib

1. Clear the search box
2. Type **"RTClib"**
3. Look for **"RTClib"** by Adafruit
4. Click **[INSTALL]**

**STEP 6:** Install Library 5 - SD

1. Clear the search box
2. Type **"SD"**
3. Look for **"SD"** by Arduino
4. Click **[INSTALL]**

**STEP 7:** Install Library 6 - Adafruit ILI9341

1. Clear the search box
2. Type **"Adafruit ILI9341"**
3. Look for **"Adafruit ILI9341"** by Adafruit
4. When you click install, it will also install **"Adafruit GFX Library"**
5. Click **[INSTALL]** on both

**STEP 8:** Verify all libraries are installed

```
All Required Libraries:
  ✓ OneWire (Paul Stoffregen)
  ✓ DallasTemperature (Miles Burton)
  ✓ SHT31 (Rob Tillaart)
  ✓ RTClib (Adafruit)
  ✓ SD (Arduino)
  ✓ Adafruit ILI9341 (Adafruit)
  ✓ Adafruit GFX Library (Adafruit)
```

---

### 4.4 Configure Phone Number for SMS Alerts

**STEP 1:** In Arduino IDE, find the code section for SMS

Use **Ctrl+F** (or Cmd+F on Mac) to open Find dialog:
```
┌─────────────────────────────────┐
│ Find: [sendSMS]                 │
│ Replace:                        │
├─────────────────────────────────┤
│ [Find] [Replace] [Replace All]  │
└─────────────────────────────────┘
```

**STEP 2:** Search for **"sendSMS"**

You will see three occurrences (around lines 385, 395, 405):

```cpp
// Line 385 - Moderate Risk
sendSMS("+8801XXXXXXXXX", "Late Blight Risk Increasing. Monitor field conditions.");

// Line 395 - High Risk
sendSMS("+8801XXXXXXXXX", "High risk of Late Blight. Field inspection recommended.");

// Line 405 - Very High Risk
sendSMS("+8801XXXXXXXXX", "VERY HIGH Late Blight Risk. Take preventive action immediately.");
```

**STEP 3:** Replace "+8801XXXXXXXXX" with YOUR phone number

Example: If your number is **01712345678**:

```cpp
// Line 385
sendSMS("+8801712345678", "Late Blight Risk Increasing. Monitor field conditions.");

// Line 395
sendSMS("+8801712345678", "High risk of Late Blight. Field inspection recommended.");

// Line 405
sendSMS("+8801712345678", "VERY HIGH Late Blight Risk. Take preventive action immediately.");
```

**Format:** `"+88" + your 11-digit Bangladesh number`

---

### 4.5 Verify Code (Check for Errors)

**STEP 1:** Click the **Verify** button (checkmark icon)

```
Arduino IDE Top Bar:
┌──────────────────────────────────┐
│ [✔ Verify] [→ Upload] [Serial]   │
│             ↑                     │
│        Click this                │
└──────────────────────────────────┘
```

**STEP 2:** Wait for compilation

```
Status: Compiling...
Progress: ████████████████ 100%

Compiling sketch...
Linking libraries...
Done...

✓ Sketch uses 28456 bytes (92%) of program storage space.
✓ Global variables use 1467 bytes (71%) of dynamic memory.
✓ No errors!
```

**If you see "Error":**
```
❌ Error message:
"error: undefined reference to 'SHT31'"

This means a library is not installed. 
Go back to Step 4.3 and install missing library.
```

---

### 4.6 Connect Arduino to Computer

**STEP 1:** Take your USB cable (USB-A to mini-USB)

**STEP 2:** Connect to Arduino Nano's USB port

**STEP 3:** Wait 2-3 seconds for recognition

Windows will show:
```
New hardware detected
Installing driver...
✓ Device ready
```

**STEP 4:** Select the COM port

In Arduino IDE, click **Tools** → **Port**

```
Available ports:
  ☐ COM3  ← Usually this one
  ☐ COM4
  ☐ COM5
```

**Select the port** (usually COM3 or COM4)

You will see at bottom:
```
Board: Arduino Nano
Processor: ATmega328P
Port: COM3
```

---

### 4.7 Upload Code to Arduino

**STEP 1:** Click the **Upload** button (arrow icon)

```
Arduino IDE Top Bar:
┌──────────────────────────────────┐
│ [✔ Verify] [→ Upload] [Serial]   │
│                  ↑                │
│            Click this            │
└──────────────────────────────────┘
```

**STEP 2:** Watch the upload progress

```
Uploading...
 ████████████░░░░░░░░░░░░░░░░░░░░░░░░░ 50%
 
Uploading...
 ████████████████████████████████░░░░░░░ 85%

Uploading...
 ████████████████████████████████████████ 100%

✓ Done uploading.
```

**STEP 3:** Wait for Arduino to restart

The Arduino will automatically reset after upload.

You will see:
```
✓ Serial port COM3 ready
```

---

### 4.8 Verify Upload Success

**STEP 1:** The LED on Arduino should blink

**STEP 2:** No error messages should appear

**STEP 3:** Status bar shows:
```
✓ Done uploading
```

**Congratulations! The code is now on your Arduino!**

---

## 5. TESTING EACH COMPONENT

### ⚠️ IMPORTANT: Do NOT proceed if you skipped any previous steps!

---

### 5.1 Open Serial Monitor

**STEP 1:** Click **Tools** → **Serial Monitor**

```
Arduino IDE window appears:
┌──────────────────────────────────────┐
│ Serial Monitor                       │
├──────────────────────────────────────┤
│                                      │
│                                      │
│                                      │
│                                      │
│                                      │
│                                      │
│  Baud rate: [9600] ▼                │
│  [Autoscroll] ☑  [Timestamp] ☐     │
└──────────────────────────────────────┘
```

**STEP 2:** Set Baud Rate to **9600**

In the dropdown at bottom right, select: **9600**

**STEP 3:** Wait for messages

Within 5 seconds, you should see:
```
=== SYSTEM INITIALIZATION ===

Display initialized
DS18B20 initialized
SHT31 initialized
RTC initialized
SD Card initialized
SIM800L initialized

=== INITIALIZATION COMPLETE ===
```

**If you see garbage text:**
```
✗ Problem: Wrong baud rate
  Solution: Change to 9600 baud (Step 5.2)
```

**If no messages appear:**
```
✗ Problem: Arduino not detected
  Solution: 
    1. Check USB cable
    2. Select correct COM port
    3. Verify upload was successful
```

---

### 5.2 Test DS18B20 Temperature Sensor

**STEP 1:** Look at Serial Monitor output

Wait 60 seconds, you should see:
```
Soil Temp: 23.4 C
```

**Expected readings:**
```
Room temperature (20-25°C): 20-25 C ✓
In ice water (0°C):         0-2 C ✓
In warm water (40°C):       38-42 C ✓
```

**If you see "DS18B20: Error reading temperature":**
```
✗ Problem: Sensor not connected properly

Troubleshooting:
  1. Check RED wire → 5V
  2. Check YELLOW wire → D2
  3. Check BLACK wire → GND
  4. Verify 4.7kΩ pull-up resistor is installed
  5. Check all connections are tight
  6. Restart Arduino (press RESET button)
```

---

### 5.3 Test SHT31 Temperature & Humidity Sensor

**STEP 1:** Look for this output:
```
Air Temp: 22.5 C, Humidity: 45 %
```

**Expected readings:**
```
Room conditions (20-25°C, 40-60%RH): 20-25 C, 40-60 % ✓
Near cold object (10°C):             8-12 C ✓
Near humid air (80%RH):              Any Temp, 75-85 % ✓
```

**If you see "SHT31 not found":**
```
✗ Problem: I2C communication failed

Troubleshooting:
  1. Check VCC → 5V
  2. Check GND → Ground
  3. Check SDA → A4 (Arduino)
  4. Check SCL → A5 (Arduino)
  5. Verify no other device is on A4/A5
  6. Try I2C Scanner (advanced troubleshooting)
```

---

### 5.4 Test RTC DS3231 Module

**STEP 1:** The RTC should initialize without errors

Serial output:
```
RTC initialized ✓
```

**STEP 2:** Check if time is accurate

Next to each sensor reading, you should see:
```
Date: 01-06-2026
Time: 10:30:45
```

**If time is wrong:**
```
Problem: RTC battery is dead or time not set

Solution:
  1. Uncomment this line in code (around line 230):
     rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  
  2. Upload code again
  3. Wait 10 seconds
  4. Comment the line back out
  5. Upload again
  
This sets the time to your computer's current time
```

---

### 5.5 Test Leaf Wetness Sensor

**STEP 1:** Look for this output:
```
Leaf Wetness: 150 (DRY)
```

**STEP 2:** Test different conditions:

```
DRY (in air):
  Serial output: Leaf Wetness: 100-250 (DRY) ✓

SPRAY WATER (moist):
  Serial output: Leaf Wetness: 300-500 (MOIST/WET)

FULLY WET (dipped in water):
  Serial output: Leaf Wetness: 500-800 (WET) ✓
```

**If sensor not responding:**
```
✗ Problem: Analog read failing

Troubleshooting:
  1. Check VCC → 5V
  2. Check AO → A1
  3. Check GND → Ground
  4. Restart Arduino
```

---

### 5.6 Test Rain Sensor

**STEP 1:** Look for output:
```
Rain Sensor: 100 (NO RAIN)
```

**STEP 2:** Test different conditions:

```
DRY (in air):
  Serial output: Rain Sensor: 50-200 (NO RAIN) ✓

SPRAY WATER (light):
  Serial output: Rain Sensor: 200-400

HEAVILY WET (water puddle):
  Serial output: Rain Sensor: 500-800 (RAIN) ✓
```

**If sensor not responding:**
```
✗ Problem: Analog read failing

Troubleshooting:
  1. Check VCC → 5V
  2. Check AO → A2
  3. Check GND → Ground
  4. Restart Arduino
```

---

### 5.7 Test TFT Display

**STEP 1:** The display should light up immediately after upload

You should see:
```
┌───────────────────────────────┐
│                               │
│      LATE BLIGHT              │
│     MONITORING                │
│                               │
│  Solar-Powered System         │
│                               │
│  SD Card: OK                  │
│  GSM Module: OK               │
│  RTC: OK                      │
│                               │
└───────────────────────────────┘
```

(Colors may vary)

**STEP 2:** After 5 seconds, display should show sensor data

```
Date: 01-06-2026
Time: 10:30:45

Soil Temp : 23.2 C
Air Temp  : 22.1 C
Humidity  : 55 %

Leaf      : DRY
Rain      : NO

Score: 0
Status: SAFE
```

**If display is blank:**
```
✗ Problem: Display not initialized

Troubleshooting:
  1. Check VCC → 5V
  2. Check GND → Ground
  3. Check CS → D10
  4. Check RST → D8
  5. Check DC → D9
  6. Check MOSI → D11
  7. Check MISO → D12
  8. Check SCK → D13
  9. Restart Arduino
```

**If display shows garbage:**
```
✗ Problem: Library or SPI conflict

Troubleshooting:
  1. Verify Adafruit ILI9341 library is installed
  2. Check SPI pins (D11, D12, D13) are not used elsewhere
  3. Make sure only one device is using each pin
```

---

### 5.8 Test SD Card Module

**STEP 1:** Serial Monitor should show:
```
SD Card initialized ✓
LOG.csv created
```

**STEP 2:** Check if data is being logged

Every 30 minutes, you should see:
```
Data logged at 01-06-2026 10:30:45
```

**STEP 3:** Verify SD card file

1. Remove SD card from Arduino
2. Insert into computer's SD reader
3. Open **LOG.csv** file with Excel or Notepad
4. You should see:
```
Date,Time,SoilTemp,AirTemp,RH,Leaf,Rain,RiskScore,RiskStatus
2026-01-15,08:30,23.2,22.1,55,DRY,NO,0,SAFE
```

**If SD Card fails to initialize:**
```
✗ Problem: SD card not detected

Troubleshooting:
  1. Format SD card to FAT32
  2. Check VCC → 5V
  3. Check GND → Ground
  4. Check CS → D7
  5. Check MOSI → D11
  6. Check MISO → D12
  7. Check SCK → D13
  8. Try a different SD card
  9. Restart Arduino
```

---

### 5.9 Test SIM800L GSM Module

**STEP 1:** Serial Monitor should show:
```
SIM800L initialized
SIM800L: OK ✓
```

**STEP 2:** To send a test SMS:

Find this code section (around line 410):
```cpp
void sendSMS(const char* phoneNumber, const char* message) {
```

**STEP 3:** Manually trigger an SMS

When risk score reaches >= 8, an SMS should be sent automatically

To test immediately:
1. Open Serial Monitor
2. Hold a wet object over leaf wetness sensor
3. Spray water on rain sensor
4. Hold warm object over temperature sensor
5. Wait 60 seconds
6. Check your phone for SMS

**Expected SMS:**
```
Late Blight Risk Increasing.
Monitor field conditions.
```

**If SMS is not received:**
```
✗ Problem: SIM800L communication error

Troubleshooting:
  1. Check SIM card is inserted correctly
  2. Check SIM card has active plan
  3. Check VCC → Battery (11.1V)
  4. Check GND → Ground
  5. Check TX → D3
  6. Check RX → D4
  7. Check 2200µF capacitor is installed
  8. Check signal bars on SIM card slot
  9. Try a different SIM card
```

---

## 6. TROUBLESHOOTING GUIDE

### Problem: Arduino Not Detected

**Symptom:**
```
Error: Serial port COM3 not found
```

**Solution:**
1. Check USB cable (use original Arduino cable if possible)
2. Try different USB port on computer
3. Restart Arduino IDE
4. Reinstall drivers:
   - Windows: Download CH340 driver
   - Mac: Download Silicon Labs driver
   - Linux: Usually automatic

---

### Problem: Libraries Not Installing

**Symptom:**
```
Error: Library not found
```

**Solution:**
1. Check internet connection
2. Try installing from .ZIP file (Manual installation)
3. Clear Arduino IDE cache:
   - Windows: Delete `C:\Users\YourName\AppData\Local\Arduino`
   - Mac: Delete `~/Library/Arduino`
   - Linux: Delete `~/.arduino`

---

### Problem: Code Not Compiling

**Symptom:**
```
error: 'SHT31' does not name a type
```

**Solution:**
1. All 6 libraries must be installed (see Step 4.3)
2. Check spelling of library names
3. Restart Arduino IDE
4. Download latest library versions

---

### Problem: Serial Monitor Shows Garbage

**Symptom:**
```
jfhkjdfshjkfhsdf jkhfsdjkf sdjkfhsd
```

**Solution:**
1. Set Baud Rate to **9600** (bottom right of Serial Monitor)
2. Select correct COM port
3. Restart Arduino

---

### Problem: Sensors Not Responding

**Symptom:**
```
DS18B20: Error reading temperature
SHT31 not found!
```

**Solution:**
1. Check all wiring connections are tight
2. Verify correct pin assignments
3. Inspect for cold solder joints
4. Use continuity test on multimeter
5. Replace sensor if damaged

---

### Problem: Display Not Showing

**Symptom:**
```
Display is blank/black
```

**Solution:**
1. Check all TFT connections (8 wires)
2. Verify D8, D9, D10 are correct
3. Try rotating display 180°
4. Check contrast settings in code

---

### Problem: SD Card Not Working

**Symptom:**
```
SD Card initialization failed!
```

**Solution:**
1. Format SD card to FAT32
2. Check if card is readable on computer
3. Try a different SD card
4. Verify all SPI connections
5. Check D7 (CS) is not used elsewhere

---

## FINAL CHECKLIST

Before field deployment:

```
SOFTWARE:
  ☑ Arduino IDE installed
  ☑ Board selected: Arduino Nano
  ☑ Processor selected: ATmega328P
  ☑ All 6 libraries installed
  ☑ Phone number configured for SMS
  ☑ Code verified (no errors)
  ☑ Code uploaded successfully

HARDWARE:
  ☑ All sensors connected
  ☑ All wires tight and secure
  ☑ 5V voltage correct (5.0V)
  ☑ Battery voltage correct (11.1V)
  ☑ Solar panel producing voltage (~20V)
  ☑ No short circuits
  ☑ 2200µF capacitor installed

TESTING:
  ☑ Serial Monitor shows initialization messages
  ☑ DS18B20 reading temperature
  ☑ SHT31 reading temperature & humidity
  ☑ RTC showing correct time
  ☑ Leaf Wetness sensor responding
  ☑ Rain sensor responding
  ☑ Display showing sensor data
  ☑ SD card logging data
  ☑ SIM800L module initialized
  ☑ SMS alerts working

READY FOR FIELD DEPLOYMENT!
```

---

**Document Version:** 2.0
**Last Updated:** 2026-06-01
**Difficulty Level:** Beginner-Friendly
**Status:** Complete & Tested
