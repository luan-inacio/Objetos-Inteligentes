#include <WiFi.h>
#include <PubSubClient.h>

#define SENSOR_PIN 36  // VP
#define BUZZER_PIN 21

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "mqtt.eclipseprojects.io";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(100);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
  }
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP32Client")) {
      // Conectado
    } else {
      delay(500);
    }
  }
}

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int sensorValue = analogRead(SENSOR_PIN);
  String status = (sensorValue > 1000) ? "Vazamento detectado" : "Sem vazamento";

  // Monitor Serial
  Serial.print("Valor do sensor: ");
  Serial.print(sensorValue);
  Serial.print(" - Status: ");
  Serial.println(status);

  // Acionamento do buzzer
  if (sensorValue > 1000) {
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }

  // Publicação MQTT
  client.publish("sensor/vazamento", status.c_str());

  delay(2000);
}
