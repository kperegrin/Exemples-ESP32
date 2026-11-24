#include <WiFi.h>
#include <WebServer.h>

#define LED_PIN 18

const char WIFI_SSID[] = "Wokwi-GUEST";
const char WIFI_PASSWORD[] = "";

WebServer server(80);

int LED_state = LOW;
bool blinkMode = false;

unsigned long previousMillis = 0;
const unsigned long interval = 500;

// Generar pagina web
String getHTML() {
  String html = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Control LED ESP32</title>
    <style>
      body {
        font-family: Arial;
        text-align: center;
        margin-top: 50px;
        background: #eeeeee;
      }
      h1 { color: #222; }
      button {
        padding: 15px 25px;
        margin: 10px;
        border: none;
        border-radius: 8px;
        color: white;
        font-size: 17px;
        cursor: pointer;
      }
      .on { background: green; }
      .off { background: red; }
      .blink { background: blue; }
    </style>
  </head>
  <body>
    <h1>Control LED ESP32</h1>
  )rawliteral";

  html += "<h2>Estat del LED: ";

  if (blinkMode) {
    html += "PARPELLEJANT";
  } else if (LED_state == HIGH) {
    html += "ENCÈS";
  } else {
    html += "APAGAT";
  }

  html += R"rawliteral(</h2>
    <a href="/led1/on">
      <button class="on">ENCENDRE</button>
    </a>
    <a href="/led1/off">
      <button class="off">APAGAR</button>
    </a>
    <a href="/led1/blink">
      <button class="blink">PARPELLEJAR</button>
    </a>
  </body>
  </html>
  )rawliteral";

  return html;
}

// Pagina principal
void handleHome() {
  server.send(200, "text/html", getHTML());
}

// Encendre LED
void handleLedOn() {
  blinkMode = false;
  LED_state = HIGH;
  digitalWrite(LED_PIN, LED_state);

  server.send(200, "text/html", getHTML());
}

// Apagar LED
void handleLedOff() {
  blinkMode = false;
  LED_state = LOW;
  digitalWrite(LED_PIN, LED_state);

  server.send(200, "text/html", getHTML());
}

// Activar parpelleig
void handleLedBlink() {
  blinkMode = true;
  LED_state = LOW;
  digitalWrite(LED_PIN, LED_state);

  previousMillis = millis();

  server.send(200, "text/html", getHTML());
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Connectar WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connectant al WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connectat!");
  Serial.print("Adreca IP: ");
  Serial.println(WiFi.localIP());

  // Configurar rutes
  server.on("/", handleHome);
  server.on("/led1/on", handleLedOn);
  server.on("/led1/off", handleLedOff);
  server.on("/led1/blink", handleLedBlink);

  // Iniciar servidor
  server.begin();

  Serial.println("Servidor web iniciat!");
}

void loop() {
  server.handleClient();

  // Control no bloquejant del parpelleig
  if (blinkMode) {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;

      LED_state = !LED_state;
      digitalWrite(LED_PIN, LED_state);
    }
  }
}
