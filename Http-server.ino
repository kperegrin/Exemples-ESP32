
/*
  ESP32 HTTP IoT Server - Luisobri Industries

  Projecte de servidor web amb ESP32.
  Permet controlar dos LEDs des d'una pagina web.

  Per provar-ho:
  1. Inicia la simulacio a Wokwi.
  2. Connecta't a la xarxa WiFi Wokwi-GUEST.
  3. Utilitza Wokwi IoT Gateway.
  4. Obre http://localhost:9080 al navegador.
*/

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <uri/UriBraces.h>

// Configuracio de la xarxa WiFi
#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""
#define WIFI_CHANNEL 6

// Creacio del servidor web al port 80
WebServer server(80);

// Pins dels LEDs
const int LED1 = 26;
const int LED2 = 27;

// Variables per guardar l'estat dels LEDs
bool led1State = false;
bool led2State = false;


// ------------------------------------
// GENERAR LA PAGINA WEB
// ------------------------------------

void sendHtml() {

  String response = R"(
    <!DOCTYPE html><html>
      <head>
        <title>Luisobri Industries - ESP32</title>
        <meta name="viewport" content="width=device-width, initial-scale=1">

        <style>
          html {
            font-family: sans-serif;
            text-align: center;
            background-color: #eeeeee;
          }

          body {
            display: inline-flex;
            flex-direction: column;
            margin-top: 40px;
          }

          h1 {
            color: #222;
          }

          h2 {
            margin: 0;
          }

          div {
            display: grid;
            grid-template-columns: 1fr 1fr;
            grid-template-rows: auto auto;
            grid-auto-flow: column;
            grid-gap: 1em;
          }

          .btn {
            background-color: #16a085;
            border: none;
            color: white;
            padding: 0.5em 1em;
            font-size: 2em;
            text-decoration: none;
            border-radius: 8px;
          }

          .btn.OFF {
            background-color: #333;
          }
        </style>
      </head>

      <body>
        <h1>Luisobri Industries</h1>
        <h2>ESP32 LED Control</h2>

        <div>
          <h2>LED 1</h2>
          <a href="/toggle/1" class="btn LED1_TEXT">LED1_TEXT</a>

          <h2>LED 2</h2>
          <a href="/toggle/2" class="btn LED2_TEXT">LED2_TEXT</a>
        </div>
      </body>
    </html>
  )";

  // Actualitzar el text segons l'estat dels LEDs
  response.replace("LED1_TEXT", led1State ? "ON" : "OFF");
  response.replace("LED2_TEXT", led2State ? "ON" : "OFF");

  server.send(200, "text/html", response);
}


// ------------------------------------
// CONFIGURACIO INICIAL
// ------------------------------------

void setup() {

  Serial.begin(115200);

  // Configurar els pins com a sortides
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  // Connectar ESP32 a WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD, WIFI_CHANNEL);

  Serial.println("Connecting to WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println("\nConnected!");

  // Mostrar l'adreca IP del servidor
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Pagina principal
  server.on("/", sendHtml);


  // ------------------------------------
  // CONTROL DELS LEDS
  // ------------------------------------

  server.on(UriBraces("/toggle/{}"), []() {

    String led = server.pathArg(0);

    Serial.print("Changing LED: ");
    Serial.println(led);

    // Canviar l'estat del LED seleccionat
    switch (led.toInt()) {

      case 1:
        led1State = !led1State;
        digitalWrite(LED1, led1State);
        break;

      case 2:
        led2State = !led2State;
        digitalWrite(LED2, led2State);
        break;
    }

    // Actualitzar la pagina web
    sendHtml();

  });


  // Iniciar servidor
  server.begin();

  Serial.println("Luisobri Industries server started!");

}


// ------------------------------------
// BUCLE PRINCIPAL
// ------------------------------------

void loop() {

  // Gestionar les peticions del navegador
  server.handleClient();

  delay(2);
}
