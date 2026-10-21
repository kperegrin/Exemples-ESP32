
/*
  Projecte: A06 - LED Blink
  Descripció: Fa parpellejar un LED connectat al GPIO 23.
  Els temps d'encesa i d'apagat són configurables.
*/

// Constant del pin del LED
const int LED_PIN = 23;

// Temps configurables en mil·lisegons
int tempsEnces = 1000;
int tempsApagat = 1000;

void setup() {
  // Configurem el pin com a sortida
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Encén el LED
  digitalWrite(LED_PIN, HIGH);
  delay(tempsEnces);

  // Apaga el LED
  digitalWrite(LED_PIN, LOW);
  delay(tempsApagat);
}
