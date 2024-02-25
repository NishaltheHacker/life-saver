#include <TinyGPS++.h>
#include <SoftwareSerial.h>

const int forceSensorPin = A0;  // Connect the force sensor to analog pin A0
const int threshold =800;    // You may need to adjust the threshold based on your sensor and requirements
const int RXPin = 2;
const int TXPin = 3;
const int GPSBaud = 9600;

// Create a TinyGPS++ object
TinyGPSPlus gps;

// Create a software serial port called "gpsSerial"
SoftwareSerial gpsSerial(RXPin, TXPin);

void setup() {
  pinMode(forceSensorPin, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  gpsSerial.begin(GPSBaud);
}

void loop() {
  // Read the analog value from the force sensor
  int forceValue = analogRead(forceSensorPin);

  // If force is above the threshold, turn on the LED and display GPS information
  if (forceValue > threshold) {
    digitalWrite(13, HIGH);
    displayInfo();
  } else {
    digitalWrite(13, LOW);
  }

  // GPS code
  while (gpsSerial.available() > 0)
    if (gps.encode(gpsSerial.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10) {
    Serial.println("No GPS detected");
    while (true);
  }
}

void displayInfo() {
  if (gps.location.isValid()) {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
    Serial.print("Altitude: ");
    Serial.println(gps.altitude.meters());
  } else {
    Serial.println("Location: Not Available");
  }

  Serial.print("Date: ");
  if (gps.date.isValid()) {
    Serial.print(gps.date.month());
    Serial.print("/");
    Serial.print(gps.date.day());
    Serial.print("/");
    Serial.println(gps.date.year());
  } else {
    Serial.println("Not Available");
  }



  Serial.println();
  Serial.println();
  delay(1000);
}