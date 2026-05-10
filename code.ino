#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const char* ssid = "Yashasvi 2.4 G";
const char* password = "sairam@123";

const char* host = "api.telegram.org";
const int httpsPort = 443;

String botToken = "8509684317:AAGStAfpnzWFBIctgjwQQDF5IHgrDINa_yA";
String chatID = "6809234238";

#define SENSOR_PIN D2
#define LED_PIN D1

WiFiClientSecure client;

unsigned long lastAlert = 0;
const unsigned long cooldown = 30000;

void sendTelegramMessage() {

  client.setInsecure();

  Serial.println("Connecting to Telegram...");

  if (!client.connect(host, httpsPort)) {

    Serial.println("Telegram Connection Failed");
    return;
  }

  String url =
    "/bot" + botToken +
    "/sendMessage?chat_id=" +
    chatID +
    "&text=🚨 Object Detected!";

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println("Telegram Message Sent!");
}

void setup() {

  Serial.begin(115200);

  pinMode(SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  WiFi.begin(ssid, password);

  Serial.print("Connecting WiFi");

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
}

void loop() {

  int sensorValue = digitalRead(SENSOR_PIN);

  if (sensorValue == LOW) {

    digitalWrite(LED_PIN, HIGH);

    if (millis() - lastAlert > cooldown) {

      Serial.println("Object Detected!");

      sendTelegramMessage();

      lastAlert = millis();
    }

  } else {

    digitalWrite(LED_PIN, LOW);
  }

  delay(200);
}