#define BLYNK_TEMPLATE_ID "TMPL3D0QlNjP_"
#define BLYNK_TEMPLATE_NAME "Insomnia Prediction Using IoT Integrated Smart Pil"
#define BLYNK_AUTH_TOKEN "evrJ8ZNPK28GfhNvR7iTsGiuh365hXiO"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <HTTPClient.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "PILLOW";
char pass[] = "12345678";

Adafruit_MPU6050 mpu;

// Sensor pins connected
int TEMP_PIN = 36; 
int RESP_PIN = 39;
int PULSE_PIN = 34;
int FORCE_PIN = 35;
int LDR_PIN = 32;

// Buzzer and switch
int buzzer = 13;  
int sw = 2;

void alert();

void setup() {
  Blynk.begin(auth, ssid, pass);
  
  Serial.begin(9600);
  while (!Serial)
    delay(10);

  Serial.println("Adafruit MPU6050 test!");
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
  delay(100);

  pinMode(buzzer, OUTPUT);
  pinMode(TEMP_PIN, INPUT);
  pinMode(RESP_PIN, INPUT);
  pinMode(PULSE_PIN, INPUT);
  pinMode(FORCE_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(sw, INPUT);
}

void loop() {
  Blynk.run();
  
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp); 

  int S = digitalRead(sw);
  int L = analogRead(LDR_PIN) * 0.025;
  int F = analogRead(FORCE_PIN);
  int P = analogRead(PULSE_PIN) * 0.02;
  int R = analogRead(RESP_PIN) * 0.0056;
  int T = analogRead(TEMP_PIN) * 0.032;

  // Sensor data display
  Serial.print("LDR Status = "); Serial.print(L);
  Serial.print(" || Force Applied = "); Serial.print(F);
  Serial.print(" || Pulse Level = "); Serial.print(P);
  Serial.print(" || Respiration Level = "); Serial.print(R);
  Serial.print(" || Sleep Angle = "); Serial.print(a.acceleration.z);
  Serial.print(" || Body Temp = "); Serial.println(T);

  // Send data to Blynk dashboard
  Blynk.virtualWrite(V0, L);
  Blynk.virtualWrite(V1, F);
  Blynk.virtualWrite(V2, P);
  Blynk.virtualWrite(V3, R);
  Blynk.virtualWrite(V4, a.acceleration.z);
  Blynk.virtualWrite(V5, T); 

  // Check for conditions and send alerts
  if ((P < 30) && (R < 15) && (F > 20) && (F < 70) && (T > 115)) {
    Serial.println("Patient had Affected A PISD Disease...");
    Blynk.logEvent("alert", "Patient had Affected A PISD Disease...!");
    alert();
  }
  
  if (S == 1) {
    Blynk.logEvent("alert", "I need an Emergency..!");
  } 
  else if ((F > 90) && (a.acceleration.z > 2) && (a.acceleration.z < 7) && (L > 80)) {
    Serial.println("Insomnia Affected ...The Patient Did not Sleep Properly..!");
    Blynk.logEvent("alert", "Insomnia Affected ...The Patient Did not Sleep Properly..!");
  }

  // Send data to MongoDB via Flask
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("192.168.26.200/upload");  // Replace with your laptop's IP
    http.addHeader("Content-Type", "application/json");

    // Create JSON payload
    String jsonData = "{";
    jsonData += "\"pulse\":" + String(P) + ",";
    jsonData += "\"respiration\":" + String(R) + ",";
    jsonData += "\"temperature\":" + String(T) + ",";
    jsonData += "\"force\":" + String(F) + ",";
    jsonData += "\"light\":" + String(L) + ",";
    jsonData += "\"sleep_angle\":" + String(a.acceleration.z);
    jsonData += "}";

    int httpResponseCode = http.POST(jsonData);
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }

  delay(500);
}

// Alert function to trigger buzzer
void alert() {
  digitalWrite(buzzer, 1);
  delay(2000);
  digitalWrite(buzzer, 0);
  delay(100);
  digitalWrite(buzzer, 1);
  delay(2000);
  digitalWrite(buzzer, 0);
  delay(100);
}
