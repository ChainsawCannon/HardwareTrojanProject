#include <WiFi.h>

const int ledPin = 23;
const int buttonPin = 0;

int pressCount = 0;
unsigned long firstPressTime = 0;
bool trojanTriggered = false;
bool wifiActive = false;

unsigned long eventCount = 0;

void connectWiFi();
void activateTrojan();
void reportMetrics(unsigned long responseTimeUs);

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
    unsigned long pressDetectedUs = micros();
    unsigned long now = micros();
    eventCount++;

    if (pressCount == 0 || (now - firstPressTime > 3000000)) {
      pressCount = 0;
      firstPressTime = now;
    }

    pressCount++;

    if (pressCount == 5 && (now - firstPressTime <= 3000000)) {
      trojanTriggered = true;
      pressCount = 0;
      Serial.println("Trigger condition met: 5 presses within 3 seconds");
    }

    if (trojanTriggered) {
      activateTrojan();
      trojanTriggered = false;
    }

    digitalWrite(ledPin, HIGH);

    unsigned long responseTimeUs = micros() - pressDetectedUs;
    reportMetrics(responseTimeUs);
  }

  if (lastState == LOW && currentState == HIGH) {
    if (!wifiActive) {
      digitalWrite(ledPin, LOW);
    }
  }

  lastState = currentState;
}

void activateTrojan() {
  Serial.println("Trojan Activated!");
  if (!wifiActive) {
    connectWiFi();
  }
}

void connectWiFi() {
  Serial.println("Connecting to WiFi...");
  WiFi.begin("FloridaPoly_Open");

  unsigned long startAttemptTime = micros();

  while (WiFi.status() != WL_CONNECTED && micros() - startAttemptTime < 50000000) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    wifiActive = true;
    digitalWrite(ledPin, HIGH);
    Serial.println("\nWiFi Connected");
  } else {
    Serial.println("\nWiFi Failed");
  }
}

void reportMetrics(unsigned long responseTimeUs) {
  int wifiStatus = (WiFi.status() == WL_CONNECTED) ? 1 : 0;

  Serial.print("WiFi Status = ");
  Serial.print(wifiStatus);
  Serial.print(", Response Time = ");
  Serial.print(responseTimeUs);
  Serial.print(", Event Count = ");
  Serial.println(eventCount);
}
