#define BLYNK_TEMPLATE_ID "TMPL3u0A1_Oqg"
#define BLYNK_TEMPLATE_NAME "IoT Light Control via Mobile App"
#define BLYNK_AUTH_TOKEN "qFkLnoZtKClyBp7aCrO7Gm-AtTjLHmQD"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "Yashasvi 2.4 G";
char pass[] = "sairam@123";

#define RELAY_PIN D1

BLYNK_WRITE(V0)
{
  int value = param.asInt();

  digitalWrite(RELAY_PIN, value);

  Serial.println(value ? "Relay ON" : "Relay OFF");
}

void setup()
{
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, LOW);

  Serial.println("Connecting to Blynk...");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{
  Blynk.run();
}