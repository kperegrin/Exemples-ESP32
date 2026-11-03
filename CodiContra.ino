
#include <Keypad.h>

// Numero de filas y columnas
const uint8_t ROWS = 4;
const uint8_t COLS = 4;

// Distribucion de teclas
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

// Pines de las filas
uint8_t rowPins[ROWS] = { 19, 18, 5, 17 };

// Pines de las columnas
uint8_t colPins[COLS] = { 16, 4, 2, 15 };

// Crear objeto Keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Configuracion de la contraseña
String password = "1234";
String entrada = "";

void setup() {
  Serial.begin(9600);

  Serial.println("SISTEMA DE CONTRASENA");
  Serial.println("Introduce la contraseña y pulsa #");
}

void loop() {

  // Leer tecla pulsada
  char key = keypad.getKey();

  if (key) {

    // Si se pulsa un numero o una letra
    if (key != '#' && key != '*') {

      if (entrada.length() < 4) {
        entrada += key;

        Serial.print("*");
      }
    }

    // Si se pulsa #
    if (key == '#') {

      Serial.println();

      if (entrada == password) {
        Serial.println("ACCESO PERMITIDO");
      } 
      else {
        Serial.println("CONTRASENA INCORRECTA");
      }

      entrada = "";
    }

    // Si se pulsa *
    if (key == '*') {
      entrada = "";
      Serial.println();
      Serial.println("Entrada borrada");
    }
  }
}
