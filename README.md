# assignment-pysics-for-computing
physics for computing 

---------------------------------------------------------------------------
--------------------------------------------------------------------------
------
GROUP MEMBERS.
1. ARISTOTE ALPHONSE   BSCCS/2025/
2. AMY SIMIYU   BSCCS/2025/
3. BRILLIAN ANDALO   BSCCS/2025/
4. DAVIS MANORE   BSCCS/2025/
5. EDWIN LUKE   BSCCS/2025/
6. EMMANUEL SIGEI   BSCCS/2025/
7. ERICSON KARANJA   BSCCS/2025/39563
8. LATETIA   BSCCS/2025/
9. LYN   BSCCS/2025/
10. TINAELIS MUMBI   BSCCS/2025/
11.    BSCCS/2025/
   

   PROJECT: MOTION-ACTIVATED SECURITY LIGHT.

   Motion Activated Security Light - Technical Explanation

Motion Activated Security Light
This Arduino sketch creates a simple yet effective motion-activated security light using a PIR (Passive Infrared) sensor to detect movement and an LED to simulate the light output. When motion is detected, the LED turns on, and a message is sent to the Serial Monitor. Once motion stops, the LED turns off, and another message confirms the end of the detection. This setup is ideal for learning about sensor integration, digital I/O, and state management in Arduino programming.
The code is efficient, non-blocking, except for the initial warmup delay, and avoids flooding the Serial Monitor with repeated messages by using a state-tracking variable.

Hardware Requirements

-Arduino Board 
-PIR Sensor connected to digital pin 2
-LED (with a 220Ω resistor) connected to digital pin 13
-Breadboard and Jumper Wires
-USB Cable for power and Serial communication

Wiring Diagram: (Schematics available in images folder)

textPIR Sensor:
- VCC → 5V
- GND → GND
- OUT → Pin 2

LED:
- Anode (+) → Pin 13 (via 220Ω resistor)
- Cathode (-) → GND
- 
Code Overview
The sketch initializes the hardware in setup(), then continuously monitors the PIR sensor in loop(). It uses a state variable (pirState) to track whether motion is currently active, ensuring the LED only toggles on rising/falling edges of the sensor signal. Serial output provides debugging feedback.

Key concepts demonstrated:

1.Digital Input/Output: Reading sensor state and controlling the LED.
2.State Management: Preventing redundant Serial prints during sustained motion.
3.Debouncing/Warmup: A delay allows the PIR sensor to stabilize after power-on.
4.Serial Communication: For logging events (viewable in the Arduino IDE's Serial Monitor at 9600 baud).

Detailed Code Breakdown

Global Variables
These are declared at the top for easy access across functions. They define pins and track system state.
cppint pirPin = 2;       // PIR sensor output pin (digital input)
int ledPin = 13;      // LED pin (digital output, built-in on most Arduinos)
int pirState = LOW;   // Tracks previous PIR state (LOW = no motion, HIGH = motion detected)
int val = 0;          // Temporary variable to store current PIR reading

-pirPin: Connects to the PIR's output signal. PIR sensors output HIGH (5V) when motion is detected and LOW (0V) otherwise.
-ledPin: Controls the LED. Pin 13 is chosen for convenience (often has a built-in LED on Arduino boards).
-pirState: A "memory" variable that remembers the last known motion state. This prevents spamming the Serial Monitor with messages while motion persists (e.g., someone standing still after triggering).
-val: Holds the instantaneous reading from the PIR sensor. It's reset each loop iteration.

Setup Function

This runs once at startup to configure hardware and prepare the sensor.
cppvoid setup() {
  pinMode(ledPin, OUTPUT);  // Set LED pin as output (can send HIGH/LOW signals)
  pinMode(pirPin, INPUT);   // Set PIR pin as input (reads HIGH/LOW from sensor)
  Serial.begin(9600);       // Initialize Serial communication at 9600 baud rate
  Serial.println("PIR sensor warming up...");  // Print startup message
  delay(2000);  // Pause for 2 seconds to let PIR stabilize
}

-pinMode(): Configures pins for their roles. INPUT mode enables pull-up/pull-down if needed, but here it's a simple digital read.
-Serial.begin(9600): Starts the Serial interface for debugging. Open the Serial Monitor in Arduino IDE to see outputs.
-Serial.println(): Sends a human-readable message to confirm initialization.
-delay(2000): Critical for PIR sensors—they need 30-60 seconds to "warm up" after power-on to calibrate to the environment. This 2-second delay is a minimal safe period; in production, extend it if needed.

Loop Function
-This is the heart of the program, running repeatedly (thousands of times per second) to poll the sensor.
cppvoid loop() {
  val = digitalRead(pirPin);  // Read the current state of the PIR pin (HIGH or LOW)

  if (val == HIGH) {  // Motion detected
    digitalWrite(ledPin, HIGH);  // Turn LED ON
    if (pirState == LOW) {  // Only print if this is a new detection (rising edge)
      Serial.println("Motion detected!");
      pirState = HIGH;  // Update state to remember motion is active
    }
  } else {  // No motion
    digitalWrite(ledPin, LOW);  // Turn LED OFF
    if (pirState == HIGH) {  // Only print if motion just ended (falling edge)
      Serial.println("Motion ended!");
      pirState = LOW;  // Update state to remember no motion
    }
  }
}

digitalRead(pirPin): Samples the sensor pin. Returns HIGH (1) or LOW (0). Assigned to val for readability.
If Branch (Motion Active):

digitalWrite(ledPin, HIGH): Sets the LED pin to 5V, lighting the LED.
Nested if (pirState == LOW): Checks for a transition from no-motion to motion. This edge-detection logic ensures "Motion detected!" prints only once per event, not continuously.
pirState = HIGH: Updates the state to avoid repeated prints.


Else Branch (No Motion):

digitalWrite(ledPin, LOW): Sets the LED pin to 0V, turning off the light.
Nested if (pirState == HIGH): Detects the end of motion and prints "Motion ended!" only once.
pirState = LOW: Resets the state.


Why State Tracking? Without pirState, you'd get flooded with prints (e.g., 1000+ "Motion detected!" per second while moving). This makes the system responsive yet clean.

How It Works in Practice

Power On: Arduino boots, warms up the PIR (you'll see the warmup message in Serial Monitor).
Idle State: LED off, pirState = LOW. Loop polls quietly.
Motion Trigger: PIR detects heat/movement (e.g., a person walking by). val goes HIGH → LED on → Single "Motion detected!" print → pirState = HIGH.
Sustained Motion: LED stays on, but no extra prints (state prevents it).
Motion End: val goes LOW → LED off → Single "Motion ended!" print → pirState = LOW.
Repeat: System resets to idle, ready for next detection.

PIR Sensor Notes:

Sensitivity: Adjustable via onboard potentiometers (time delay and trigger distance).
Range: Typically 3-7 meters, 100-120° field of view.
False Triggers: Avoid direct sunlight/heat sources; the warmup helps calibrate.

Enhancements & Extensions

Add a Buzzer: Connect to another pin and trigger on motion for audible alerts.
Relay for Real Light: Replace LED with a relay module to control a high-power bulb.
Timeout: Use millis() for auto-off after inactivity (e.g., 5 minutes).
WiFi Integration: With ESP32, send notifications via Blynk or MQTT.
Debugging Tip: If no output, check wiring and baud rate in Serial Monitor.

Usage Instructions

1.Check the sketch via Arduino IDE.
2.Open Serial Monitor (Tools > Serial Monitor, set to 9600 baud).
3.Wave your hand near the PIR—watch the LED and messages!
4.Tinker: Adjust delay or add features as needed.




