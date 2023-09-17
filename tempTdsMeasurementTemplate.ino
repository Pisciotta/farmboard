#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Information about the WiFi network
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Information about Firebase
#define FIREBASE_HOST "your_FIREBASE_HOST"
#define FIREBASE_AUTH "your_FIREBASE_AUTH"

// Pin of the sensors
#define SENSOR_PIN_1 D1
#define SENSOR_PIN_2 D2
#define SENSOR_PIN_3 D3
#define SENSOR_PIN_4 D4

#define TdsSensorPin1 A0
#define TdsSensorPin2 A1
#define TdsSensorPin3 A2
#define TdsSensorPin4 A3

// Setup OneWire instances
OneWire oneWire1(SENSOR_PIN_1);
OneWire oneWire2(SENSOR_PIN_2);
OneWire oneWire3(SENSOR_PIN_3);
OneWire oneWire4(SENSOR_PIN_4);

// Pass OneWire instance to DallasTemperature library
DallasTemperature sensor1(&oneWire1);
DallasTemperature sensor2(&oneWire2);
DallasTemperature sensor3(&oneWire3);
DallasTemperature sensor4(&oneWire4);

void setup(void)
{
  Serial.begin(9600);
  
  // Connect to the WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Connect to Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  // Start the sensors
  sensor1.begin();
  sensor2.begin();
  sensor3.begin();
  sensor4.begin();
}

void loop(void)
{ 
  // Request temperatures from the sensors
  sensor1.requestTemperatures(); 
  sensor2.requestTemperatures();
  sensor3.requestTemperatures();
  sensor4.requestTemperatures();

  // Read TDS values from the sensors
  float tdsValue1 = analogRead(TdsSensorPin1);
  float tdsValue2 = analogRead(TdsSensorPin2);
  float tdsValue3 = analogRead(TdsSensorPin3);
  float tdsValue4 = analogRead(TdsSensorPin4);

  // Send the data to Firebase
  Firebase.setFloat("temperature1", sensor1.getTempCByIndex(0));
  Firebase.setFloat("temperature2", sensor2.getTempCByIndex(0));
  Firebase.setFloat("temperature3", sensor3.getTempCByIndex(0));
  Firebase.setFloat("temperature4", sensor4.getTempCByIndex(0));
  
  Firebase.setFloat("tdsValue1", tdsValue1);
  Firebase.setFloat("tdsValue2", tdsValue2);
  Firebase.setFloat("tdsValue3", tdsValue3);
  Firebase.setFloat("tdsValue4", tdsValue4);

  delay(1000);
}
