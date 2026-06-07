#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// =========================
// LCD I2C
// =========================
LiquidCrystal_I2C lcd(0x27, 16, 2);

// =========================
// WIFI
// =========================
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// =========================
// MQTT
// =========================
const char* mqtt_server = "58d56f41a21e404084a39947b30d44ab.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;

const char* mqtt_user = "ARISS";
const char* mqtt_password = "Aris123*";

// =========================
// DHT22
// =========================
#define DHTPIN 5
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// =========================
// HC-SR04
// =========================
#define TRIG 33
#define ECHO 15

// =========================
// LEDS
// =========================
#define LED_VERDE 18
#define LED_VERMELHO 19

WiFiClientSecure espClient;
PubSubClient client(espClient);

// =========================
// WIFI
// =========================
void setup_wifi() {

  Serial.println("Conectando ao WiFi...");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

// =========================
// MQTT
// =========================
void reconnect() {

  while (!client.connected()) {

    Serial.print("Conectando MQTT...");

    if (client.connect("ESP32_ARIS", mqtt_user, mqtt_password)) {

      Serial.println(" Conectado!");

    } else {

      Serial.print(" Erro: ");
      Serial.println(client.state());

      delay(3000);
    }
  }
}

// =========================
// SENSOR ULTRASSÔNICO
// =========================
float getDistance() {

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH);

  float distance = duration * 0.034 / 2.0;

  return distance;
}

// =========================
// SETUP
// =========================
void setup() {

  Serial.begin(115200);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_VERMELHO, LOW);

  dht.begin();

  // LCD I2C
  Wire.begin(42, 41);

  lcd.init();
  lcd.backlight();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ARIS");

  lcd.setCursor(0, 1);
  lcd.print("Inicializando");

  setup_wifi();

  espClient.setInsecure();

  client.setServer(mqtt_server, mqtt_port);

  delay(2000);
}

// =========================
// LOOP
// =========================
void loop() {

  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();
  float nivelAgua = getDistance();

  if (isnan(temperatura) || isnan(umidade)) {

    Serial.println("Erro ao ler DHT22!");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Erro DHT22");

    delay(2000);
    return;
  }

  // =========================
  // CONTROLE DOS LEDS
  // =========================

  bool alerta = false;

  if (temperatura < 20 || temperatura > 30) {
    alerta = true;
  }

  if (nivelAgua > 20) {
    alerta = true;
  }

  if (alerta) {

    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_VERMELHO, HIGH);

  } else {

    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_VERMELHO, LOW);
  }

  // =========================
  // LCD
  // =========================

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperatura, 1);
  lcd.print("C");

  lcd.setCursor(9, 0);
  lcd.print((int)umidade);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Agua:");
  lcd.print((int)nivelAgua);
  lcd.print("cm");

  // =========================
  // SERIAL
  // =========================

  Serial.println("\n===== ARIS =====");

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" C");

  Serial.print("Umidade: ");
  Serial.print(umidade);
  Serial.println(" %");

  Serial.print("Nivel Agua: ");
  Serial.print(nivelAgua);
  Serial.println(" cm");

  // =========================
  // MQTT
  // =========================

  client.publish("aris/temperatura", String(temperatura).c_str());
  client.publish("aris/umidade", String(umidade).c_str());
  client.publish("aris/nivel_agua", String(nivelAgua).c_str());

  delay(5000);
}