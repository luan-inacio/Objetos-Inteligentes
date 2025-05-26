#include <WiFi.h>
#include <PubSubClient.h>

#define SENSOR_PIN 36  // VP
#define BUZZER_PIN 21

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(100);
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Conectado ao WiFi!");
}

void reconnect() {
  // Loop até reconectar
  while (!client.connected()) {
    Serial.print("Tentando conexão MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println(" Conectado ao broker MQTT!");
    } else {
      Serial.print(" Falha na conexão, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos...");
      delay(5000);
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
    Serial.println("MQTT desconectado! Tentando reconectar...");
    reconnect();
  } else {
    Serial.println("MQTT ainda conectado.");
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

  // Publicação MQTT com verificação de sucesso
  bool sucesso = client.publish("SensorMack/vazamento", status.c_str());

  if (sucesso) {
    Serial.println("Mensagem MQTT enviada com sucesso!");
  } else {
    Serial.println("Falha ao enviar mensagem MQTT.");
  }

  delay(2000);  
}
