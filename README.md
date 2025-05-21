# Sistema de Detecção de Vazamento de Água com ESP32 e MQTT

Este projeto simula um sistema de detecção de vazamento de água utilizando um ESP32, um buzzer ativo e comunicação via protocolo MQTT. A simulação foi realizada na plataforma Wokwi.

## 🛠️ Componentes Utilizados

- ESP32 (placa de desenvolvimento)
- Potenciômetro (simulando sensor de vazamento)
- Buzzer ativo
- Plataforma de simulação Wokwi
- Protocolo MQTT (via broker público)

## ⚙️ Funcionamento

- O ESP32 realiza a leitura do sensor através do pino analógico **GPIO36 (VP)**.
- Se o valor do sensor for **maior que 1000**, o sistema considera que há um **vazamento**.
- O buzzer é acionado (ligado) para emitir um **alerta sonoro**.
- Simultaneamente, uma **mensagem é publicada** via protocolo MQTT.

## 📡 Comunicação MQTT

- **Broker:** mqtt.eclipseprojects.io
- **Porta:** 1883 (padrão para conexões MQTT sem criptografia)
- **Tópico de publicação:** `sensor/vazamento`
- Mensagens enviadas:
  - `"Vazamento detectado"`
  - `"Sem vazamento"`

## 📊 Arquivos do Repositório

- `sketch.ino` → Código-fonte do projeto
- `diagram.json` → Arquivo de simulação do Wokwi
- `imagem-montagem.png` → Imagem do circuito montado
- `fluxograma.png` → Fluxograma de funcionamento do sistema
- `grafico-tempos.png` → Gráfico comparativo dos tempos de resposta
- `README.md` → Este arquivo de descrição

## 🎯 Objetivo

Demonstrar uma solução de baixo custo para detecção e notificação de vazamentos de água, utilizando conceitos de IoT, sensores, atuadores e comunicação via protocolo MQTT.

## 📝 Autor

Luan Inácio  
Aluno do curso de Análise e Desenvolvimento de Sistemas  
Disciplina: Objetos Inteligentes  
