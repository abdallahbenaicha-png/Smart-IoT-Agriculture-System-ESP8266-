#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASS";

String server = "http://192.168.1.10:5000/data";

int soilPin = A0;
int relayPin = D1;

WiFiClient client;

void setup() {
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void loop() {

  int soil = analogRead(soilPin);

  Serial.println(soil);

  HTTPClient http;

  String url = server + "?soil=" + String(soil);

  http.begin(client, url);

  int code = http.GET();
  String response = http.getString();

  http.end();

  if (soil > 700) {   // dry soil (adjust value)
    digitalWrite(relayPin, HIGH); // pump ON
  } else {
    digitalWrite(relayPin, LOW);  // pump OFF
  }

  delay(5000);
}
