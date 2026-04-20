#include <WiFi.h>

int ledPin = 23;
int buttonPin = 0;

int pressCount = 0;
unsigned long firstPressTime = 0;
bool trojanActive = false;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(115200);
  Serial.println("STARTED");
}

void loop() {
  static int lastState = HIGH;
  int currentState = digitalRead(buttonPin);

  if (lastState == HIGH && currentState == LOW) {

    if (pressCount == 0) {
      firstPressTime = millis();
    }

    pressCount++;

    if (pressCount >= 5 && (millis() - firstPressTime <= 3000)) {
      trojanActive = true;
    }

    if (millis() - firstPressTime > 3000) {
      pressCount = 1;
      firstPressTime = millis();
    }
  }

  lastState = currentState;

  if (currentState == LOW) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  if (trojanActive) {
    activateTrojan();
    trojanActive = false;
  }
}

void activateTrojan() {
  Serial.println("Trojan Activated!");

  WiFi.begin("FloridaPoly_Open", "");
  Serial.println("\nWifi Not Connected");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");
  Serial.println("Sending: Trojan activated");

  // Keep LED on permanently
  digitalWrite(ledPin, HIGH);

  // Halt program so nothing turns it off
  while (true) {
    delay(1000);
  
}
}
