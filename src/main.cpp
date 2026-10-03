#include <Arduino.h>
#include <DHT.h>

const uint8_t SENSOR_PIN = 2;
const uint8_t WARNING_LED = 8;
const float TEMP_LIMIT = 30.0;  // Degrees Celsius

DHT sensor(SENSOR_PIN, DHT22);

void setup() {
    Serial.begin(9600);
    pinMode(WARNING_LED, OUTPUT);
    sensor.begin();

    Serial.println("Temperature monitor started");
}

void loop() {
    // Allow two seconds between sensor readings.
    delay(2000);

    float temperature = sensor.readTemperature();
    float humidity = sensor.readHumidity();

    if (isnan(temperature) || isnan(humidity)) {
        digitalWrite(WARNING_LED, LOW);
        Serial.println("Sensor read failed");
        return;
    }

    bool tooHot = temperature >= TEMP_LIMIT;
    digitalWrite(WARNING_LED, tooHot ? HIGH : LOW);

    Serial.print("Temperature: ");
    Serial.print(temperature, 1);
    Serial.print(" C | Humidity: ");
    Serial.print(humidity, 1);
    Serial.print("% | ");

    Serial.println(tooHot ? "HIGH TEMPERATURE" : "Normal");
}