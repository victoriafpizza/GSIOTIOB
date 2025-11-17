#include <DHT.h>
#include <ArduinoJson.h>

#define dhtpin 2
#define dhttype DHT22
#define trigger 7
#define echo 8
#define ldrpin A0
#define ledG 13
#define ledY 12
#define ledR 11

int dist = 0;
int ldrvalor = 0;

DHT dht(dhtpin, dhttype);

void setup() {
  Serial.begin(115200);     // Comunicação para gateway MQTT/HTTP
  dht.begin();

  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(ldrpin, INPUT);

  pinMode(ledG, OUTPUT);
  pinMode(ledY, OUTPUT);
  pinMode(ledR, OUTPUT);

  digitalWrite(ledG, LOW);
  digitalWrite(ledY, LOW);
  digitalWrite(ledR, LOW);
}

void loop() {
  // --- MEDIÇÃO DE DISTÂNCIA (HC-SR04) ---
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  dist = pulseIn(echo, HIGH);
  dist = dist / 58;  // cm aproximado

  // --- LEITURA DOS SENSORES AMBIENTAIS ---
  int temp = dht.readTemperature();
  int umi  = dht.readHumidity();
  ldrvalor = analogRead(ldrpin);

  // --- LÓGICA DO SEMÁFORO DE FALA ---
  // Ajuste esses limites conforme a posição física do candidato
  String estado_conversacao;

  if (dist > 0 && dist < 50) {
    // Candidato próximo do ponto de fala → candidato fala
    digitalWrite(ledG, HIGH);
    digitalWrite(ledY, LOW);
    digitalWrite(ledR, LOW);
    estado_conversacao = "candidato_fala";
  } else if (dist >= 50 && dist < 100) {
    // Região intermediária → pausa / troca de turno
    digitalWrite(ledG, LOW);
    digitalWrite(ledY, HIGH);
    digitalWrite(ledR, LOW);
    estado_conversacao = "pausa_troca_turno";
  } else {
    // Candidato longe → recrutador fala / candidato escuta
    digitalWrite(ledG, LOW);
    digitalWrite(ledY, LOW);
    digitalWrite(ledR, HIGH);
    estado_conversacao = "recrutador_fala";
  }

  // Flags lógicas para uso no backend (MQTT/HTTP)
  bool pode_falar  = (estado_conversacao == "candidato_fala");
  bool pode_ouvir  = (estado_conversacao == "recrutador_fala" || estado_conversacao == "pausa_troca_turno");

  // --- MONTA PAYLOAD JSON PARA ENVIAR AO GATEWAY (MQTT/HTTP) ---
  StaticJsonDocument<256> json;

  json["distancia_cm"]      = dist;
  json["temperatura_c"]     = temp;
  json["umidade_pct"]       = umi;
  json["luminosidade_raw"]  = ldrvalor;

  json["estado_conversacao"] = estado_conversacao;  // "candidato_fala", "recrutador_fala", "pausa_troca_turno"
  json["pode_falar"]         = pode_falar;
  json["pode_ouvir"]         = pode_ouvir;

  // Campos extras para monitoramento de ambiente da sala de entrevista
  json["alerta_conforto"] = (temp > 28 || temp < 18 || umi < 30 || umi > 70);
  json["alerta_iluminacao"] = (ldrvalor < 200);  // exemplo: ambiente escuro

  // Envio para o PC/gateway (que publica em MQTT/HTTP)
  serializeJson(json, Serial);
  Serial.println();

  delay(2000); // taxa de atualização ~2s
}
