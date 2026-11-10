
#include "SSD1306Wire.h"

// OLED SSD1306
// ESP32: SDA = GPIO 5, SCL = GPIO 4
SSD1306Wire display(0x3c, 5, 4);


// --------------------------------
// DIBUJAR CARA
// --------------------------------

void dibujarCara(int emocion, int boca) {

  display.clear();

  // Cabeza redonda
  display.drawCircle(64, 32, 29);

  // Emocion 0: Neutral
  // Emocion 1: Feliz
  // Emocion 2: Muy feliz
  // Emocion 3: Riendo

  if (emocion == 3) {

    // Ojos cerrados de felicidad
    display.drawLine(45, 24, 51, 19);
    display.drawLine(51, 19, 57, 24);

    display.drawLine(71, 24, 77, 19);
    display.drawLine(77, 19, 83, 24);

  } else {

    // Ojos abiertos
    display.fillCircle(51, 24, 3);
    display.fillCircle(77, 24, 3);

  }

  // Boca neutra
  if (emocion == 0) {

    display.drawLine(56, 44, 72, 44);

  }

  // Boca sonriente
  if (emocion == 1) {

    display.drawLine(53, 39, 57, 43);
    display.drawLine(57, 43, 64, 45);
    display.drawLine(64, 45, 71, 43);
    display.drawLine(71, 43, 75, 39);

  }

  // Boca abriendose progresivamente
  if (emocion == 2 || emocion == 3) {

    // Boca circular
    display.drawCircle(64, 42, boca);

    // Lengua cuando abre mucho la boca
    if (boca >= 8) {

      display.drawLine(59, 47, 69, 47);

    }

  }

  display.display();
}


// --------------------------------
// ANIMACION: PARPADEAR
// --------------------------------

void parpadear() {

  display.clear();

  display.drawCircle(64, 32, 29);

  // Ojos cerrados
  display.drawLine(44, 24, 58, 24);
  display.drawLine(70, 24, 84, 24);

  // Boca sonriente
  display.drawLine(53, 39, 57, 43);
  display.drawLine(57, 43, 64, 45);
  display.drawLine(64, 45, 71, 43);
  display.drawLine(71, 43, 75, 39);

  display.display();

  delay(150);
}


// --------------------------------
// CONFIGURACION
// --------------------------------

void setup() {

  display.init();
  display.setContrast(255);

}


// --------------------------------
// ANIMACION PRINCIPAL
// --------------------------------

void loop() {

  // 1. Cara neutral
  dibujarCara(0, 0);
  delay(1000);

  // 2. Parpadea
  parpadear();

  dibujarCara(0, 0);
  delay(300);

  // 3. Empieza a sonreir
  dibujarCara(1, 0);
  delay(400);

  // 4. La boca empieza a abrirse
  for (int i = 2; i <= 10; i++) {

    dibujarCara(2, i);
    delay(100);

  }

  // 5. Se queda muy feliz
  delay(700);

  // 6. Se rie con los ojos cerrados
  for (int i = 10; i >= 6; i--) {

    dibujarCara(3, i);
    delay(120);

  }

  // 7. Cierra progresivamente la boca
  for (int i = 6; i >= 1; i--) {

    dibujarCara(2, i);
    delay(100);

  }

  // 8. Vuelve a sonreir
  dibujarCara(1, 0);
  delay(800);

  // 9. Vuelve a neutral
  dibujarCara(0, 0);
  delay(1000);

}
