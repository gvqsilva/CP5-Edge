#include <WiFi.h>
#include <PubSubClient.h> // Biblioteca MQTT
#include "DHT.h"
#include <Wire.h>
#include <stdio.h>

// Definições de MQTT
#define TOPICO_SUBSCRIBE    "/TEF/Esp0g4/cmd"        // Tópico de escuta MQTT
#define TOPICO_PUBLISH      "/TEF/Esp0g4/attrs"      // Tópico de envio de dados MQTT
#define TOPICO_PUBLISH_2    "/TEF/Esp0g4/attrs/l"    // Tópico de luminosidade
#define TOPICO_PUBLISH_3    "/TEF/Esp0g4/attrs/h"    // Tópico de umidade
#define TOPICO_PUBLISH_4    "/TEF/Esp0g4/attrs/t"    // Tópico de temperatura
#define ID_MQTT  "fiware_0g4"   // ID único do dispositivo no broker

// Definições do DHT 11 (Sensor de umidade e temperatura)
#define DHTTYPE DHT22   
#define DHTPIN 4 
DHT dht(DHTPIN, DHTTYPE);

// Configurações Wi-Fi
const char* SSID = "Wokwi-GUEST"; // Nome da rede Wi-Fi
const char* PASSWORD = "";        // Senha da rede Wi-Fi
  
// Configurações MQTT
const char* BROKER_MQTT = "20.120.178.219"; // Endereço do broker MQTT
int BROKER_PORT = 1883;                     // Porta do broker MQTT

// Saídas
int D4 = 2; // Led builtin do ESP32

// Variáveis globais
WiFiClient espClient; 
PubSubClient MQTT(espClient);
char EstadoSaida = '0'; // Estado da saída (LED)

void initSerial();
void initWiFi();
void initMQTT();
void reconectWiFi(); 
void mqtt_callback(char* topic, byte* payload, unsigned int length);
void VerificaConexoesWiFIEMQTT();
void InitOutput();
 
void setup() {
    InitOutput();
    initSerial();
    initWiFi();
    initMQTT();
    dht.begin();
    MQTT.publish(TOPICO_PUBLISH, "s|off");
}

// Inicializa a comunicação serial
void initSerial() {
    Serial.begin(115200);
}
 
// Conecta na rede Wi-Fi
void initWiFi() {
    delay(10);
    Serial.println("Conectando ao Wi-Fi...");
    reconectWiFi();
}
  
// Configura os parâmetros do MQTT
void initMQTT() {
    MQTT.setServer(BROKER_MQTT, BROKER_PORT);   
    MQTT.setCallback(mqtt_callback);            
}
  
// Função chamada quando uma mensagem é recebida no tópico MQTT
void mqtt_callback(char* topic, byte* payload, unsigned int length) {
    String msg;
     
    // Converte o payload recebido em string
    for(int i = 0; i < length; i++) {
       char c = (char)payload[i];
       msg += c;
    }
    
    Serial.print("Mensagem recebida: ");
    Serial.println(msg);
    
    // Aciona ou desliga o LED conforme o comando recebido
    if (msg.equals("Esp0g4@on|")) {
        digitalWrite(D4, HIGH);
        EstadoSaida = '1';
    }
    if (msg.equals("Esp0g4@off|")) {
        digitalWrite(D4, LOW);
        EstadoSaida = '0';
    }
}
  
// Reestabelece a conexão MQTT caso esteja desconectado
void reconnectMQTT() {
    while (!MQTT.connected()) {
        Serial.print("Conectando ao Broker MQTT...");
        if (MQTT.connect(ID_MQTT)) {
            Serial.println("Conectado!");
            MQTT.subscribe(TOPICO_SUBSCRIBE); 
        } else {
            Serial.println("Falha na conexão, tentando novamente em 2s");
            delay(2000);
        }
    }
}
  
// Reconecta ao Wi-Fi
void reconectWiFi() {
    if (WiFi.status() == WL_CONNECTED)
        return;
         
    WiFi.begin(SSID, PASSWORD);
     
    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
        Serial.print(".");
    }
   
    Serial.println("Conectado ao Wi-Fi.");
    Serial.println(WiFi.localIP());
}
 
// Verifica conexões Wi-Fi e MQTT, e reconecta se necessário
void VerificaConexoesWiFIEMQTT() {
    if (!MQTT.connected()) 
        reconnectMQTT();
     
    reconectWiFi();
}
 
// Envia o estado do LED para o broker MQTT
void EnviaEstadoOutputMQTT() {
    if (EstadoSaida == '1') {
      MQTT.publish(TOPICO_PUBLISH, "s|on");
      Serial.println("LED Ligado");
    }
    if (EstadoSaida == '0') {
      MQTT.publish(TOPICO_PUBLISH, "s|off");
      Serial.println("LED Desligado");
    }
    delay(1000);
}
 
// Inicializa o estado da saída (LED)
void InitOutput() {
    pinMode(D4, OUTPUT);
    digitalWrite(D4, HIGH); // Lógica invertida (HIGH = LED apagado)

    // Pisca o LED ao iniciar
    boolean toggle = false;
    for(int i = 0; i <= 10; i++) {
        toggle = !toggle;
        digitalWrite(D4, toggle);
        delay(200);           
    }
    digitalWrite(D4, LOW);
}
 
// Loop principal
void loop() {   
    const int potPin = 34;
    char msgBuffer[4];

    VerificaConexoesWiFIEMQTT(); // Verifica e mantém as conexões

    EnviaEstadoOutputMQTT(); // Envia o estado atual do LED

    // Leitura do sensor de luminosidade (LDR)
    int sensorValue = analogRead(potPin);   
    float luminosity = map(sensorValue, 0, 4095, 0, 100); 
    Serial.print("Luminosidade: ");
    Serial.print(luminosity);
    Serial.println("%");

    // Publica o valor da luminosidade no broker MQTT
    dtostrf(luminosity, 4, 1, msgBuffer);
    MQTT.publish(TOPICO_PUBLISH_2, msgBuffer);

    // Leitura do sensor DHT11
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    if (isnan(humidity) || isnan(temperature)) {
      Serial.println("Erro ao ler o sensor DHT-22!");
    }

    Serial.print("Umidade: ");
    Serial.print(humidity);
    Serial.print("% Temperatura: ");
    Serial.print(temperature);
    Serial.println("°C");

    // Publica os valores de umidade e temperatura no broker MQTT
    dtostrf(humidity, 4, 1, msgBuffer);
    MQTT.publish(TOPICO_PUBLISH_3, msgBuffer);
    
    dtostrf(temperature, 4, 1, msgBuffer);
    MQTT.publish(TOPICO_PUBLISH_4, msgBuffer);

    MQTT.loop(); // Mantém a conexão com o broker ativa
}
