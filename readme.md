# Sistema Inteligente de Contratação IoT (ESP32)
  
![Status](https://img.shields.io/badge/Status-Concluído-brightgreen)
![Version](https://img.shields.io/badge/Versão-1.0-blue)
![License](https://img.shields.io/badge/Licença-MIT-green)

---

## 👥 Desenvolvedores
- **Victoria Franceschini Pizza** – RM 550609  
- **Eric de Carvalho Rodrigues** – RM 550249
- **Pedro Henrique Menezes** - RM 97432

---

<p align="center">
<img src="https://img.shields.io/badge/-Feito%20com%20cafe-6f4e37?logo=buymeacoffee&logoColor=white" />
</p>

---

## 🧠 Sobre o Projeto
O processo de contratação atual ainda apresenta limitações importantes, mesmo em ambientes modernos. Em um cenário cada vez mais digital 
e orientado a dados, surgem problemas como:

- falta de sincronização entre candidato e recrutador durante a conversa
- dificuldade em registrar sinais do ambiente da entrevista em tempo real
- ausência de indicadores objetivos sobre condições de comunicação
- necessidade de automatizar etapas repetitivas e melhorar a precisão das avaliações

- Para acompanhar o futuro do trabalho, torna-se fundamental desenvolver sistemas que tornem o processo de entrevista mais claro, eficiente
e inteligente, utilizando sensores, automação e monitoramento contínuo para apoiar decisões e melhorar a experiência de todos os envolvidos.
---

## Solução Proposta 

Este projeto apresenta um Sistema Inteligente de Entrevistas IoT, desenvolvido com microcontroladores e comunicação MQTT/HTTP, capaz de:

- Identificar a posição do candidato por meio do sensor ultrassônico (HC-SR04), definindo automaticamente quando ele deve falar ou apenas escutar.
- Monitorar as condições da sala de entrevista com o sensor DHT22 (temperatura e umidade), garantindo conforto e registro ambiental.
- Medir o nível de luminosidade do ambiente através do LDR, auxiliando na avaliação da qualidade da sala.
- Exibir o estado da dinâmica de comunicação por meio de um semáforo de LEDs:
    - Verde → Candidato fala
    - Amarelo → Momento de transição
    - Vermelho → Recrutador fala

- Enviar todos os dados coletados — distância, temperatura, umidade, luminosidade e estado da conversa — para um servidor ou broker MQTT/HTTP, 
permitindo dashboards, monitoramento remoto e automação externa.

- Atuar como um módulo de apoio ao processo seletivo, oferecendo feedback objetivo e facilitando a análise de entrevistas em ambientes presenciais 
ou híbridos.
---

## 🚀 Tecnologias Utilizadas

Hardware

- Arduino UNO (ou ESP32, dependendo da montagem final)
- Sensor Ultrassônico HC-SR04 — detecção de posição do candidato
- DHT22 — leitura de temperatura e umidade da sala
- LDR — monitoramento da luminosidade ambiente
- LEDs (Verde, Amarelo e Vermelho) — semáforo de fala/escuta
- Cabeamento e resistores compatíveis
- Conexão via USB para envio dos dados ao gateway MQTT/HTTP
- Software / Comunicação
- C++ (Arduino IDE)
- JSON via Serial para integração com gateways
- MQTT ou HTTP para envio dos dados a dashboards e sistemas externos
- Wokwi IoT Simulator para prototipagem e testes

---

## 🔍 Como Funciona

- ✔ Monitoramento contínuo via sensores:
  - HC-SR04 para detectar a posição do candidato
  - DHT22 para medir temperatura e umidade
  - LDR para acompanhar a luminosidade da sala

- ✔ Semáforo inteligente para organizar a comunicação na entrevista:

  - Verde: candidato fala
  - Amarelo: momento de transição
  - Vermelho: recrutador fala

- ✔ Envio dos dados em JSON pela Serial, permitindo integração com MQTT ou HTTP por meio de um gateway externo
  -(ex.: Python, Node-RED, automações corporativas)
- ✔ Totalmente testável no Wokwi, inclusive com visualização do semáforo e sensores em tempo real
- ✔ Compatível com dashboards e automações como Node-RED, HiveMQ, ThingsBoard e APIs personalizadas
- ✔ Código simples, modular e fácil de estender para novas regras ou novos sensores

---

## 🎯 Funcionalidades

- Detectar automaticamente a posição do candidato através do sensor ultrassônico,
permitindo identificar quando ele está pronto para falar ou quando deve apenas escutar.
- Coletar dados ambientais da sala de entrevista (temperatura, umidade e luminosidade) para registro e análise.
- Controlar um semáforo inteligente com LEDs para indicar o estado da comunicação: candidato fala, transição ou recrutador fala.
- Enviar todos os dados estruturados em JSON para integração com sistemas externos via MQTT ou HTTP (por meio de um gateway).
- Fornecer informações em tempo real para dashboards, automações ou ferramentas do RH.
- Permitir que o sistema reaja automaticamente conforme métricas de ambiente ou proximidade, facilitando processos de análise e tomada de decisão.
---

## Componentes Utilizados

- *Hardware*
  - Arduino UNO (ou ESP32, dependendo da implementação final)
  - HC-SR04 — sensor ultrassônico para detectar a posição do candidato
  - DHT22 — sensor de temperatura e umidade
  - LDR (fotoresistor) — leitura da luminosidade ambiente
  - LEDs (Verde, Amarelo e Vermelho) — semáforo de fala/escuta
  - Cabos e resistores para conexão
  - Interface USB — comunicação com o gateway MQTT/HTTP

- *Software / Comunicação*
  - C++ (Arduino IDE)
  - JSON via Serial para integração com automações externas
  - MQTT ou HTTP através de gateway (ex.: Python, Node-RED)
  
---

## 🔗 Projeto no Wokwi: 

https://wokwi.com/projects/423418460094367745

--- 

## ⚙️ Como Rodar o Projeto

- Acesse o projeto no Wokwi:
  - https://wokwi.com/projects/423418460094367745
- Clique em Start Simulation para iniciar o sistema.
- Observe o funcionamento dos sensores em tempo real:
- Aproxime ou afaste o objeto do sensor ultrassônico → o semáforo muda entre candidato fala, transição e recrutador fala.
- Acompanhe no console do Serial Monitor os valores enviados em JSON (distância, temperatura, umidade, luminosidade e estado da conversa).

- Para integração com MQTT ou HTTP:

  - Utilize um gateway externo (ex.: Python, Node-RED ou plataforma de automação).
  - O gateway deve ler o JSON enviado pela Serial e publicar os dados em um tópico MQTT ou endpoint HTTP da sua escolha.

-O dashboard externo poderá exibir:
  - Estado do semáforo
  - Presença/posição do candidato
  - Ambiente da sala (temp/umidade/luz)
  - Histórico e gráficos do processo de entrevista





