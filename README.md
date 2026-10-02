# 💡 Controle de Lâmpadas via Bluetooth com ESP32 & Assistente IA

![Mostra Técnica ETEC](https://img.shields.io/badge/ETEC-Philadelpho_Gouv%C3%AAia_Netto-0056b3?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Conclu%C3%ADdo-brightgreen?style=for-the-badge)
![Google Gemini](https://img.shields.io/badge/Google_Gemini-4285F4?style=for-the-badge&logo=googlecloud&logoColor=white)

Projeto apresentado para a **Mostra Técnica da ETEC Philadelpho Gouvêia Netto**, focado na automação residencial acessível e simplificada de iluminação, monitoramento ambiental e suporte ao usuário via **Inteligência Artificial (Google Gemini)**.

---

## 🛠️ Tecnologias Utilizadas

### Web, Interface & IA
![HTML5](https://img.shields.io/badge/HTML5-E34F26?style=for-the-badge&logo=html5&logoColor=white)
![CSS3](https://img.shields.io/badge/CSS3-1572B6?style=for-the-badge&logo=css3&logoColor=white)
![TypeScript](https://img.shields.io/badge/TypeScript-3178C6?style=for-the-badge&logo=typescript&logoColor=white)
![Google Gemini](https://img.shields.io/badge/Google_Gemini-8E75B2?style=for-the-badge&logo=googlegemini&logoColor=white)

### Hardware & Sistemas Embarcados
* **ESP32** (Microcontrolador com Bluetooth e Wi-Fi integrado)
* **C++ / Arduino IDE** (Lógica do circuito, sensores e acionamento)

---

## 📌 Sobre o Projeto

### ❓ O que o projeto faz?
De forma simples e intuitiva, o projeto permite que qualquer pessoa ligue ou desligue uma lâmpada diretamente pelo celular via **Bluetooth**, eliminando a necessidade de reformas ou instalações de interruptores tradicionais. 

Além do monitoramento de temperatura no display, a plataforma web conta com um **Chatbot com IA integrado** (Google Gemini API) treinado para responder dúvidas do público sobre o funcionamento do projeto e do site de forma simples e didática.

### 💡 O que ele resolve?
Instalar automação residencial com eletricistas ou módulos proprietários costuma ser caro. Com um custo estimado de apenas **R$ 100,00 a R$ 150,00** em componentes básicos, esta solução entrega:
- **Conforto:** Controle a iluminação à distância sem sair do lugar.
- **Acessibilidade:** Instalação simplificada e suporte interativo por IA para tirar dúvidas dos leitores leigos.
- **Informação:** Monitoramento contínuo da temperatura do cômodo.

### ⚙️ Como funciona?
1. **ESP32 (O Cérebro):** Gerencia os pinos do circuito, disponibiliza o sinal Bluetooth para conexão com o aplicativo/site e processa toda a lógica em C++.
2. **Módulo Relé:** Atua como o interruptor eletrônico que alimenta/corta a energia da lâmpada de forma segura.
3. **Sensor DHT11:** Realiza a leitura da temperatura e umidade do ambiente e envia os dados ao ESP32.
4. **Display LCD (I2C):** Exibe a interface com os valores atualizados do sensor para visualização direta no dispositivo.
5. **Sensor LDR:** Funciona como alternativa fotossensível para controle da lâmpada de acordo com a luminosidade ambiente.
6. **Assistente Virtual (Gemini API):** Processa perguntas em tempo real na interface web via Fetch API/TypeScript com tratamento automático de redundância de modelos (*fallback*).

---

## 🔌 Componentes de Hardware Utilizados

| Componente | Função |
| :--- | :--- |
| **ESP32** | Microcontrolador central e gerenciador do Bluetooth. |
| **Módulo Relé** | Interruptor responsivo acionado pelo ESP32 para controle da lâmpada. |
| **Módulo DHT11** | Sensor responsável pela medição de temperatura e umidade. |
| **Placa de Prototipagem (Protoboard)** | Base para montagem e organização dos pinos/conexões. |
| **Display LCD com Módulo I2C** | Tela de exibição dos dados de temperatura e interface visual. |
| **Resistor LDR** | Sensor fotossensível para automação baseada na luz ambiente. |

---

## 👥 Equipe & Colaboradores

| Foto / Avatar | Nome | Função no Projeto | Redes / Links |
| :---: | :--- | :--- | :---: |
| **L** | **Levi Santos** | Eletrônica, Firmware (ESP32/C++) & Desenvolvimento Web (TypeScript / Gemini API) | [<img src="https://img.shields.io/badge/GitHub-100000?style=flat&logo=github&logoColor=white"/>](https://github.com/LevizBlessedpo) |
| **R** | **Rodrigo Siqueira** | Montagem do Circuito e Material | [<img src="https://img.shields.io/badge/Instagram-E4405F?style=flat&logo=instagram&logoColor=white"/>](https://www.instagram.com/rodrigo.rst.1) |
| **RB** | **Ryan Bartolomei** | Montagem do Circuito e Lógica de Funcionamento | [<img src="https://img.shields.io/badge/Instagram-E4405F?style=flat&logo=instagram&logoColor=white"/>](https://www.instagram.com/ryan.b_sp) |

---

## 📝 Formulário de Avaliação

A sua opinião sobre o projeto é muito importante para a nossa evolução! Leva menos de 2 minutos para responder:

👉 [**Clique aqui para Avaliar o Projeto via Google Forms**](https://docs.google.com/forms/d/e/1FAIpQLSf-S5z8bwTJZY995n46qdAZtTOZvWFghy-c9VvfFofqC4ekHQ/viewform?usp=dialog)

---

## 📄 Licença e Direitos

Copyright © **ETEC Philadelpho Gouvêia Netto** — Todos os direitos reservados.