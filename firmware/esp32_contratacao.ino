#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ---------------------- DEFINIÇÕES ----------------------

#define DHTPIN 15
#define DHTTYPE DHT22

#define BUTTON_PIN 4
#define MIC_PIN 32

#define LED_R 25
#define LED_G 26
#define LED_B 27

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
DHT dht(DHTPIN, DHTTYPE);

// ---------------------- WIFI E MQTT ----------------------

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* mqtt_server = "broker.hivemq.com";
WiFiClient espClient;
PubSubClient client(espClient);

String deviceId = "esp32-contratacao-01";

String topicPub = "iot/contratacao/" + deviceId + "/status";
String topicCmd = "iot/contratacao/" + deviceId + "/cmd";

enum StatusVaga {
  ABERTA,
  AVALIANDO,
  FECHADA
};

StatusVaga statusVaga = FECHADA;

// ---------------------- HELPER DE LED ----------------------

void setLED(StatusVaga s) {
  switch (s) {
    case ABERTA:    // Verde
      digitalWrite(LED_R, LOW);
      digitalWrite(LED_G, HIGH);
      digitalWrite(LED_B, LOW);
      break;

    case AVALIANDO: // Amarelo
      digitalWrite(LED_R, HIGH);
      digitalWrite(LED_G, HIGH);
      digitalWrite(LED_B, LOW);
      break;

    case FECHADA:   // Vermelho
      digitalWrite(LED_R, HIGH);
      digitalWrite(LED_G, LOW);
      digitalWrite(LED_B, LOW);
      break;
  }
}

// ---------------------- OLED ----------------------

void showStatus(String texto) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.println("Sistema de Contratacao");
  display.println("-----------------------");
  display.print("Status: ");
  display.println(texto);

  display.display();
}

// ---------------------- MQTT CALLBACK ----------------------

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  String msg = "";
  for (int i = 0; i < length; i++) msg += (char)payload[i];

  if (msg.indexOf("abrir_vaga") >= 0) {
    statusVaga = ABERTA;
    setLED(statusVaga);
    showStatus("Vaga aberta");
  }

  if (msg.indexOf("fechar_vaga") >= 0) {
    statusVaga = FECHADA;
    setLED(statusVaga);
    showStatus("Vaga fechada");
  }

  if (msg.indexOf("reanalisar") >= 0) {
    statusVaga = AVALIANDO;
    setLED(statusVaga);
    showStatus("Reavaliando");
  }
}

// ---------------------- MQTT RECONNECT ----------------------

void reconnect() {
  while (!client.connected()) {
    String clientId = "contratacao-" + String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      client.subscribe(topicCmd.c_str());
    } else {
      delay(1000);
    }
  }
}

// ---------------------- SETUP ----------------------

void setup() {
  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(MIC_PIN, INPUT);

  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  setLED(FECHADA);

  dht.begin();
  Wire.begin(21, 22);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  showStatus("Iniciando...");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(200);

  client.setServer(mqtt_server, 1883);
  client.setCallback(mqttCallback);

  showStatus("Conectado");
}

// ---------------------- LOOP ----------------------

unsigned long lastPub = 0;

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  int buttonState = digitalRead(BUTTON_PIN);
  int micRaw = analogRead(MIC_PIN);
  int fala = map(micRaw, 0, 4095, 0, 100);

  float temp = dht.readTemperature();
  float umid = dht.readHumidity();

  if (isnan(temp) || isnan(umid)) {
    temp = 25;
    umid = 55;
  }

  // Quando o candidato chega
  if (buttonState == LOW && statusVaga == ABERTA) {
    statusVaga = AVALIANDO;
    setLED(AVALIANDO);
    showStatus("Avaliando candidato...");
  }

  // Publicação MQTT a cada 3 segundos
  if (millis() - lastPub >= 3000) {
    String json = "{";
    json += "\"vaga\":\"Desenvolvedor IoT\",";
    json += "\"presenca\":" + String(buttonState == LOW ? 1 : 0) + ",";
    json += "\"fala\":" + String(fala) + ",";
    json += "\"temp\":" + String(temp) + ",";
    json += "\"umid\":" + String(umid) + ",";
    json += "\"status\":\"";

    if (statusVaga == ABERTA) json += "aberta";
    if (statusVaga == AVALIANDO) json += "avaliando";
    if (statusVaga == FECHADA) json += "fechada";

    json += "\"}";

    client.publish(topicPub.c_str(), json.c_str());

    lastPub = millis();
  }

  // Atualização do display
  if (statusVaga == ABERTA) showStatus("Vaga aberta");
  if (statusVaga == AVALIANDO) showStatus("Avaliando candidato");
  if (statusVaga == FECHADA) showStatus("Vaga fechada");

  delay(50);
}
