# ARIS - Agricultura Inteligente Espacial

## Descrição do Projeto

O ARIS, Agricultura Inteligente Espacial, é um projeto desenvolvido para a Global Solution FIAP 2026/1 na disciplina Disruptive Architectures: IoT, IoB & Generative IA.

O projeto consiste em um protótipo funcional de Internet das Coisas utilizando ESP32 para monitoramento de uma estufa inteligente. A solução permite acompanhar temperatura, umidade e nível de água em tempo real, utilizando sensores conectados ao ESP32, comunicação Wi-Fi, protocolo MQTT, broker HiveMQ Cloud e dashboard em Node-RED.

A proposta do ARIS é aplicar tecnologias inspiradas na exploração espacial na agricultura terrestre. Em ambientes extremos, como estações espaciais, Marte ou Lua, o cultivo de alimentos depende de sensores, automação, monitoramento constante e controle ambiental. O ARIS adapta esse conceito para uma estufa inteligente na Terra, ajudando no controle das condições ambientais e no uso mais eficiente dos recursos agrícolas.

---

## Objetivo do Projeto

Desenvolver uma solução IoT funcional capaz de monitorar uma estufa inteligente em tempo real, utilizando ESP32, sensores, atuadores, interface local e dashboard.

O sistema coleta dados ambientais da estufa, envia as informações via MQTT e exibe os dados em um painel visual no Node-RED. Além disso, o projeto utiliza LEDs e LCD para indicar localmente o estado do ambiente monitorado.

---

## Problema

A agricultura enfrenta diversos desafios relacionados ao controle ambiental, desperdício de água, mudanças climáticas e falta de monitoramento em tempo real.

Entre os principais problemas estão:

- Falta de acompanhamento constante das condições da estufa;
- Desperdício de água em sistemas de irrigação;
- Perdas agrícolas causadas por temperatura e umidade inadequadas;
- Dificuldade de acesso a tecnologias simples de automação no campo;
- Impactos das mudanças climáticas na produção de alimentos.

Esses fatores podem comprometer a produtividade, aumentar custos e reduzir a sustentabilidade da produção agrícola.

---

## Solução Proposta

O ARIS propõe uma estufa inteligente monitorada por IoT.

O sistema utiliza sensores conectados ao ESP32 para coletar dados de temperatura, umidade e nível de água. Esses dados são enviados por Wi-Fi para um broker MQTT na nuvem e consumidos pelo Node-RED, onde são exibidos em um dashboard.

A solução também possui uma interface local com LCD I2C 16x2 e LEDs indicadores:

- LED verde: indica ambiente ideal;
- LED vermelho: indica situação de alerta.

---

## Relação com a Global Solution

O ARIS está conectado ao tema da Global Solution 2026/1 ao utilizar tecnologias inspiradas na exploração espacial para melhorar a agricultura na Terra.

Em missões espaciais, o cultivo de alimentos exige ambientes altamente controlados, sensores, automação e monitoramento contínuo. O ARIS aplica essa mesma lógica em uma estufa terrestre, criando um sistema capaz de acompanhar variáveis importantes para o desenvolvimento das plantas.

A solução contribui para:

- Agricultura inteligente;
- Monitoramento ambiental em tempo real;
- Redução de desperdício de água;
- Uso de dados para tomada de decisão;
- Sustentabilidade na produção de alimentos;
- Aplicação de tecnologias espaciais em problemas reais da Terra.

---

## Arquitetura da Solução

Fluxo geral do sistema:

    Sensores -> ESP32 -> Wi-Fi -> MQTT HiveMQ Cloud -> Node-RED -> Dashboard

Arquitetura escolhida:

    ESP32
    ↓
    Sensores
    ↓
    MQTT HiveMQ Cloud
    ↓
    Node-RED Dashboard
    ↓
    Monitoramento ARIS

---

## Tecnologias Utilizadas

- ESP32
- Wokwi
- Arduino C/C++
- Wi-Fi
- MQTT
- HiveMQ Cloud
- Node-RED
- Node-RED Dashboard
- DHT22
- HC-SR04
- LCD I2C 16x2
- LEDs

---

## Tópicos MQTT Documentados

O ESP32 publica dados em três tópicos MQTT:

    aris/temperatura
    aris/umidade
    aris/nivel_agua

Esses tópicos atendem ao requisito mínimo da disciplina de possuir pelo menos três tópicos MQTT documentados.

---
## Regras de Funcionamento

### Temperatura

A faixa ideal de temperatura foi definida entre 20°C e 30°C.

Regras:

    Temperatura entre 20°C e 30°C -> Temperatura Ideal
    Temperatura abaixo de 20°C -> Temperatura Baixa
    Temperatura acima de 30°C -> Temperatura Alta

### Umidade

A faixa ideal de umidade foi definida entre 40% e 80%.

Regras:

    Umidade entre 40% e 80% -> Umidade Ideal
    Umidade abaixo de 40% -> Umidade Baixa
    Umidade acima de 80% -> Umidade Alta

### Nível de Água

O nível de água é avaliado com base na distância medida pelo sensor ultrassônico.

Regra:

    Nível de água até 20 cm -> Reservatório OK
    Nível de água acima de 20 cm -> Reservatório Baixo

---

## Funcionamento dos LEDs

### LED Verde

O LED verde acende quando o ambiente está em condição ideal.

Condição:

    Temperatura entre 20°C e 30°C
    E nível de água até 20 cm

### LED Vermelho

O LED vermelho acende quando existe alguma situação de alerta.

Condição:

    Temperatura menor que 20°C
    Ou temperatura maior que 30°C
    Ou nível de água maior que 20 cm

---

## Dashboard Node-RED

O dashboard foi desenvolvido no Node-RED para visualização dos dados em tempo real.

Tab:

    ARIS Dashboard

Group:

    Monitoramento

O dashboard contém:

- Gauge de temperatura;
- Gauge de umidade;
- Gauge de nível de água;
- Texto de alerta de temperatura;
- Texto de alerta de umidade;
- Texto de alerta de nível de água.

---

## Como Executar o Projeto

### 1. Abrir o projeto no Wokwi

Acesse o projeto no Wokwi:

https://wokwi.com/projects/466024476249026561

### 2. Executar a simulação

No Wokwi:

1. Abra o projeto com ESP32;
2. Verifique se o circuito possui DHT22, HC-SR04, LEDs e LCD I2C;
3. Clique em Start Simulation;
4. Veja o lcd
5. Verifique se o ESP32 conectou ao Wi-Fi e ao MQTT.

### 3. Importar o fluxo no Node-RED

No Node-RED:

1. Clique no menu superior direito;
2. Clique em Import;
3. Selecione o arquivo JSON do fluxo Node-RED;
4. Importe o fluxo;
5. Configure o broker MQTT do HiveMQ Cloud;
6. Clique em Deploy.

### 4. Acessar o dashboard

Após iniciar o Node-RED, acesse:

    http://localhost:1880/ui

O dashboard exibirá os dados recebidos do ESP32 em tempo real.

---

## Link do Projeto no Wokwi

https://wokwi.com/projects/466024476249026561

---

## Link do Vídeo Demonstrativo

https://www.youtube.com/watch?v=M2jvLPzo2ws

---

## Link do GitHub

https://github.com/ARIS-GlobalSolution/ARIS-Iot.git

---

## Integrantes

- Amandha Yumi — RM: 563549
- Giovanna Bardella — RM: 561439
- Erick Takeshi — RM: 566059
---

## Conclusão

O ARIS demonstra como tecnologias inspiradas na exploração espacial podem ser aplicadas na agricultura terrestre.

Por meio de ESP32, sensores, comunicação MQTT, LCD, LEDs e dashboard em tempo real, o projeto apresenta uma solução funcional de IoT para monitoramento de estufas inteligentes.

A solução atende aos requisitos da disciplina Disruptive Architectures: IoT, IoB & Generative IA e se conecta diretamente ao contexto da Global Solution 2026/1, promovendo inovação, sustentabilidade e uso inteligente de dados na agricultura.
