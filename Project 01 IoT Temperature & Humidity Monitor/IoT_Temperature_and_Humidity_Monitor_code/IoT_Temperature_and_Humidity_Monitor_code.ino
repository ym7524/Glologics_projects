#include <DHT.h>
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#define DHTPIN D4 // GPIO2
#define DHTTYPE DHT11 // Change to DHT22 if using that sensor
const char* ssid = "Yashasvi 2.4 G";
const char* password = "sairam@123";
unsigned long channelID = 3363431;
const char* apiKey = "01L9XOZPL63XBZFI";
WiFiClient client;
DHT dht(DHTPIN, DHTTYPE);
void setup() {
Serial.begin(115200);
dht.begin();
WiFi.begin(ssid, password);
ThingSpeak.begin(client);
Serial.print("Connecting to Wi-Fi");
while (WiFi.status() != WL_CONNECTED) {
delay(500); Serial.print(".");
}
Serial.println(" Connected!");
}
void loop() {
float h = dht.readHumidity();
float t = dht.readTemperature();
if (isnan(h) || isnan(t)) {
Serial.println("Sensor read failed!"); return;
}
Serial.printf("Temp: %.1f C Humidity: %.1f %%\n", t, h);
ThingSpeak.setField(1, t);
ThingSpeak.setField(2, h);
int code = ThingSpeak.writeFields(channelID, apiKey);
Serial.println(code == 200 ? "Sent OK" : "Send failed: " + String(code));
delay(10000); // ThingSpeak free tier: min 15s; 10s is fine for testing
}