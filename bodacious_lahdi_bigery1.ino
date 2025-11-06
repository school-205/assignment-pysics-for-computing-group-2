// Motion Activated Security Light

int pirPin = 2;       // PIR sensor output
int ledPin = 13;      // LED pin
int pirState = LOW;
int val = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
  Serial.begin(9600);
  Serial.println("PIR sensor warming up...");
  delay(2000); // Allow sensor to stabilize
}

void loop() {
  val = digitalRead(pirPin);

  if (val == HIGH) {
    digitalWrite(ledPin, HIGH);
    if (pirState == LOW) {
      Serial.println("Motion detected!");
      pirState = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW);
    if (pirState == HIGH) {
      Serial.println("Motion ended!");
      pirState = LOW;
    }
  }
}