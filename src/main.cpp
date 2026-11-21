#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <PubSubClient.h>

// Network credentials & MQTT Settings
const char* WIFI_SSID = "YOUR_WIFI_SSID";
const char* WIFI_PASS = "YOUR_WIFI_PASSWORD";
const char* MQTT_SERVER = "192.168.1.100";
const int MQTT_PORT = 1883;

WiFiClient espClient;
PubSubClient client(espClient);
Adafruit_BME280 bme; 

void setupWiFi() {
    delay(10);
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi Connected. IP: " + WiFi.localIP().toString());
}

void setup() {
    Serial.begin(115200);
    pinMode(2, OUTPUT);
    
    setupWiFi();
    client.setServer(MQTT_SERVER, MQTT_PORT);

    if (!bme.begin(0x76)) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
    }
}

void loop() {
    if (!client.connected()) {
        while (!client.connected()) {
            if (client.connect("ESP32_Env_Node")) {
                Serial.println("MQTT Connected");
            } else {
                delay(2000);
            }
        }
    }
    client.loop();

    float temp = bme.readTemperature();
    float hum = bme.readHumidity();
    float press = bme.readPressure() / 100.0F;

    char msg[100];
    snprintf(msg, sizeof(msg), "{\"temp\":%.2f,\"hum\":%.2f,\"press\":%.2f}", temp, hum, press);
    client.publish("telemetry/environment", msg);

    digitalWrite(2, HIGH);
    delay(100);
    digitalWrite(2, LOW);

    delay(10000); // Send data every 10 seconds
}
