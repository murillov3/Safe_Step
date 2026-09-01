# Descrição dos Componentes - Safe Step 

Este documento detalha as especificações técnicas e a função de cada componente utilizado no projeto **Safe Step**. O sistema foi projetado para ser modular, de baixo custo e focado em detectar obstáculos terrestres e suspensos.

---

## Lista de Hardware

### 1. Microcontrolador ESP32
* **Função:** Cérebro do projeto. Responsável por processar os sinais do sensor ultrassônico, executar a lógica de detecção e controlar os atuadores (motores e buzzer).
* **Vantagem:** Alto poder de processamento e baixo consumo de energia.

### 2. Sensor Ultrassônico (HC-SR04)
* **Função:** Emite ondas sonoras de alta frequência para medir a distância de objetos.
* **Diferencial:** Posicionado para identificar **objetos suspensos** (orelhões, galhos, placas), protegendo a parte superior do corpo do usuário.

### 3. Motores Vibracall (2 unidades)
* **Função:** Fornece **feedback tátil**. As vibrações alertam o usuário sobre a proximidade de obstáculos sem a necessidade de visão ou audição constante.

### 4. Buzzer
* **Função:** Fornece **feedback auditivo**. Emite bipes que variam em frequência conforme a proximidade do objeto, servindo como um alerta secundário de segurança.

### 5. Power Bank
* **Função:** Fonte de alimentação principal. Garante que o dispositivo seja portátil e recarregável, essencial para o uso em bengalas.

### 6. Componentes de Controle e Proteção
* **2x Transistores BC547:** Atuam como chaves eletrônicas para acionar os motores vibracall, já que o ESP32 não fornece corrente suficiente diretamente.
* **2x Diodos 1N4007:** Diodos de proteção (flyback) para evitar que picos de tensão dos motores danifiquem o microcontrolador.
* **Resistores:** * 2x 1kΩ (Limitadores de corrente para a base dos transistores).
    * 1x 100Ω (Para ajuste no circuito do buzzer ou LED indicador).

### 7. Estrutura de Montagem
* **Protoboard 170 furos:** Base compacta para fixação dos componentes e testes de circuito.
* **Jumpers:** Cabos de conexão para interligar todos os módulos.

---

## Esboço do Funcionamento
1. O **ESP32** solicita uma leitura ao **Sensor Ultrassônico**.
2. Se a distância lida for inferior ao limite de segurança (ex: 1 metro), o código processa a urgência.
3. O **Buzzer** e os **Motores Vibracall** são ativados simultaneamente.
4. Quanto mais perto o objeto, maior a intensidade ou frequência do feedback.

---

> **Nota:** Este projeto é uma evolução do TCC de Rafael Souza, focando na redução de custos.

--- 

**English**

## Hardware List

### 1. Microcontroller ESP32
* **Function:** The "brain" of the project. Responsible for processing signals from the ultrasonic sensor, executing the detection logic, and controlling the actuators (motors and buzzer).
* **Advantage**: High processing power and low power consumption.


### 2. Ultrassonic Sensor(HC-SR04)
* **Function:** Emits high-frequency sound waves to measure the distance to objects.
* **Key features:** Positioned to identify **suspended objects** (payphones, branches, signs), protecting the user's upper body.

### 3. Vibracall Pancake motors (2 units)
* **Function:** Provides **tactile feedback**. Vibrations alert the user to the proximity of obstacles without the need for constant vision or hearing.

### 4. Buzzer
* **Function:** Provides **auditory feedback**. It emits beeps that vary in frequency according to the proximity of the object, serving as a secondary safety alert.

### 5. Power Bank
* **Function:** Main power source. Ensures the device is portable and rechargeable, which is essential for use in canes.

### 6. Control and Protection Components
* **2x Transistors BC547:** Act as electronic switches to trigger the vibracall motors, as the ESP32 does not provide enough current directly.

* **2x Diodes 1N4007:** Protection diodes (flyback) to prevent voltage spikes from the motors from damaging the microcontroller.

* **Resistors:** * 2x 1kΩ (Current limiters for the transistor base).
    * 1x 100Ω (For adjusting the buzzer circuit or indicator LED).

### 7. Assembly Structure
* **170-points protoboard:** Compact base for mounting components and circuit testing.
* **Jumpers:** Connection cables to interconnect all modules.

---

## Operating Outline
1. The **ESP32** requests a reading from the Ultrasonic Sensor.
2. If the measured distance is below the safety threshold (e.g., 1 meter), the code processes the urgency.
3. The **Buzzer** and **Vibracall Motors** are activated simultaneously.
4. The closer the object, the higher the intensity or frequency of the feedback.

---

> **Note:** This project is an evolution of Rafael Souza's thesis, focusing on cost reduction.