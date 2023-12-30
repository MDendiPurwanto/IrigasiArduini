#include <ESP8266WiFi.h> //library
//#define DHTTYPE DHT11 // Tipe sensor DHT yang digunakan
#include "DHT.h"
const char* ssid = "Simosachi"; //ssid
const char* password = "Simosachi2023"; //password
const int analogPin = A0; // Pin analog untuk sensor kelembaban tanah
const int relayPin = D1; // Pin untuk mengontrol relay
#define DHTPIN D2
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);

  // Menghubungkan ke WiFi
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  }

void loop() {
  int soilMoisture = analogRead(analogPin);
 // Membaca nilai suhu dan kelembaban dari sensor DHT11
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Sesuaikan nilai batas kelembaban tanah sesuai kebutuhan
  if (soilMoisture < 500) {
    // Aktifkan relay untuk menyiram tanaman
    digitalWrite(relayPin, HIGH);
    Serial.println(soilMoisture);
    Serial.println("Menyiram Tanaman");
  } else {
    // Matikan relay karena tanah sudah cukup lembab
    digitalWrite(relayPin, LOW);
    Serial.println(soilMoisture);
    Serial.println("Tanah Cukup Lembab");
  }

  //Tampilkan suhu dan kelembaban
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("°C, Humidity: ");
  Serial.print(humidity);
  Serial.println("%");
  delay(1000); // Interval pembacaan sensor (dalam milidetik), sesuaikan sesuai kebutuhan
}
