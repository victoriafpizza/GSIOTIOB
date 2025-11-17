#include <DHT.h>
#include <ArduinoJson.h>

// ------------------------
// DEFINIÇÃO DE PINOS
// ------------------------
#define DHTPIN 2
#define DHTTYPE DHT22

#define TRIGGER_PIN 7
#define ECHO_PIN 8

#define LDR_PIN A0

#define LED_VERDE 13
#define LED_AMARELO 12
#define LED_VERMELHO 11

// ------------------------
// OBJETOS
// ------------------------
DHT dht(DHTPIN, DHTTYPE);

// ------------------------
// VARIÁVEIS DE SENSORES
// ------------------------
int dist = 0;
int ldrValor = 0;

// ------------------------
// TURNOS DE FALA (CONFIGURÁVEIS)
// ------------------------
unsigned long tempoCandidato = 15000; // 15s
unsigned long tempoTransicao = 5000;  // 5s
unsigned long tempoRecrutador = 15000; // 15s

// ------------------------
// CONTROLE DO CICLO
// ------------------------
unsigned long inicioTurno = 0;
int turnoAtual = 0; 
/*
0 = candidato fala (verde)
1 = transição (amarelo)
2 = recrutador fala (vermelho)
*/

// ------------------------
// CONFIGURAÇÃO INICIAL
// ------------------------
void setup() {
  Serial.begin(115200);

  dht.begin();

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  inicioTurno = millis();
}

// ------------------------
// LÊ DISTÂNCIA (AUXILIAR)
// ------------------------
int lerDistancia() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  long duracao = pulseIn(ECHO_PIN, HIGH);
  int cm = duracao / 58;

  return cm;
}

// ------------------------
// ATUALIZA O TURNO COM BASE NO CRONÔMETRO
// ------------------------
String atualizarTurno() {
  unsigned long agora = millis();
  unsigned long decorrido = agora - inicioTurno;

  if (turnoAtual == 0 && decorrido >= tempoCandidato) {
    turnoAtual = 1;
    inicioTurno = agora;
  }
  else if (turnoAtual == 1 && decorrido >= tempoTransicao) {
    turnoAtual = 2;
    inicioTurno = agora;
  }
  else if (turnoAtual == 2 && decorrido >= tempoRecrutador) {
    turnoAtual = 0;
    inicioTurno = agora;
  }

  // Atualiza LEDs conforme turno
  if (turnoAtual == 0) {
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERMELHO, LOW);
    return "candidato_fala";
  }

  if (turnoAtual == 1) {
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARELO, HIGH);
    digitalWrite(LED_VERMELHO, LOW);
    return "transicao";
  }

  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_VERMELHO, HIGH);
  return "recrutador_fala";
}

// ------------------------
// LOOP PRINCIPAL
// ------------------------
void loop() {

  // ----- Lê sensores -----
  dist = lerDistancia();
  int temperatura = dht.readTemperature();
  int umidade = dht.readHumidity();
  ldrValor = analogRead(LDR_PIN);

  // ----- Atualiza turno -----
  String turno = atualizarTurno();

  // Flags úteis para dashboards / decisões
  bool podeFalar = (turno == "candidato_fala");
  bool podeOuvir = (turno == "recrutador_fala" || turno == "transicao");

  // ----- Monta JSON -----
  StaticJsonDocument<256> json;

  json["distancia_cm"]     = dist;
  json["temperatura_c"]    = temperatura;
  json["umidade_pct"]      = umidade;
  json["luminosidade_raw"] = ldrValor;

  json["turno"] = turno;
  json["pode_falar"] = podeFalar;
  json["pode_ouvir"] = podeOuvir;

  json["alerta_conforto"] = (temperatura > 28 || temperatura < 18 || umidade < 30 || umidade > 70);
  json["alerta_luz_baixa"] = (ldrValor < 200);

  // ----- Envia pela Serial -----
  serializeJson(json, Serial);
  Serial.println();

  delay(1000); // Taxa de envio
}
