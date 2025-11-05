// Heartbeat Monitor

int reading = 0;
int reading_final;
int Heart_rate;
void setup()
{
    Serial.begin(9600); // Initializing Serial connections.
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
}
// Taking readings and plotting.
void loop()
{
    for (int i = 0; i < 5; i++) // For debugging.
    {
        reading = reading + analogRead(A0);
        // calculating sum of ambient junk readings 5 times so that we can eliminate them afterwards.
    }
    reading_final = (reading) / 5; // Average junk reading calulated.
    delay(100);
    Heart_rate = analogRead(A0) - reading_final; // Final reading value.
    Serial.println(Heart_rate);                  // Printing and plotting.
}