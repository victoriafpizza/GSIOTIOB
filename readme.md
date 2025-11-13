# Sistema Inteligente de Contratação IoT (ESP32)
  
![Status](https://img.shields.io/badge/Status-Em%20Desenvolvimento-yellow)
![License](https://img.shields.io/badge/License-MIT-green)

---

## 👥 Desenvolvedores
- **Victoria Franceschini Pizza** – RM 550609  
- **Eric de Carvalho Rodrigues** – RM 550249  

---

<p align="center">
<img src="https://img.shields.io/badge/-Feito%20com%20cafe-6f4e37?logo=buymeacoffee&logoColor=white" />
</p>

---

## 🧠 Sobre o Projeto
O processo de contratação tradicional é lento, subjetivo e exige muitos recursos humanos. Em um contexto de trabalho cada vez mais digital, híbrido e automatizado, surgem desafios como:

- falhas de comunicação entre candidato e RH
- dificuldade de acompanhar entrevistas em tempo real
- pouca utilização de dados objetivos
- processos repetitivos que poderiam ser automatizados
<p align="center">
**Para o futuro do trabalho, é essencial criar soluções que tornem a contratação mais eficiente, justa e baseada em dados.**

---
## Solução Proposta 

Este projeto apresenta um Sistema Inteligente de Contratação IoT, desenvolvido com ESP32 e comunicação MQTT, capaz de:

- Detectar presença do candidato via botão.
- Simular resposta verbal usando um microfone analógico.
- Monitorar temperatura e umidade do ambiente da entrevista (DHT22).
- Exibir o status da vaga e do processo no display OLED.
- Indicar o estado da contratação através de um LED RGB:
- Verde → Vaga Aberta
- Amarelo → Avaliando Candidato
- Vermelho → Vaga Fechada
- Enviar todos os dados em tempo real para um servidor MQTT, permitindo dashboards e automação externa.
- Receber comandos via MQTT para abrir vaga, fechar vaga ou reavaliar.

---

## 🚀 Tecnologias Utilizadas

- Hardware
- ESP32 DevKit V1
- DHT22
- Microfone Analógico
- Botão (presença)
- OLED 128x64 SSD1306
- LED RGB
- WiFi integrado
- Software / Protocolo
- C++ (Arduino)
- MQTT (HiveMQ Broker)
- Wokwi IoT Simulator
- WiFi.h, PubSubClient, Adafruit SSD1306

---

## 🔍 Como Funciona

✔ Comunicação MQTT (publicação + comandos)
✔ Simulação prática no Wokwi
✔ Sensores funcionando juntos: botão, microfone, DHT22
✔ Display OLED com status da contratação
✔ LED RGB para estados do processo
✔ Código organizado e extensível
✔ Automação compatível com Node-RED, ThingsBoard, HiveMQ, etc.

✅ O sistema funciona em tempo real ou com vídeos gravados.  
✅ Encerramento com a tecla `q`.  

---

## 🎯 Funcionalidades

- Registrar presença do candidato
- Simular resposta verbal (intensidade sonora)
- Coletar dados ambientais
- Atualizar estado da vaga em tempo real
- Exibir dados em MQTT
- Reagir a comandos enviados pelo RH

---

## Componentes Utilizados

- ESP32 DevKit V1
- DHT22 – Temperatura e Umidade
- Microfone Analógico – Simula fala do candidato
- Botão – Chegada / presença
- OLED 128x64 SSD1306 – Status em tempo real
- LED RGB (3 pinos separados) – Estado da vaga
- Cabo Wi-Fi (simulado no Wokwi)

---
## ⚙️ Como Rodar o Projeto

### 1️⃣ No Wokwi

- Crie um novo projeto com ESP32.
- Substitua o arquivo criado por:
- esp32_contratacao.ino
- diagram.json
- Clique em Iniciar Simulação.
- Abra o console MQTT (HiveMQ Web Client) para enviar comandos.
- Observe o comportamento:
- Pressione o botão → muda para “avaliando”
- LED RGB muda de cor
- Dados aparecem no MQTT em tempo real






