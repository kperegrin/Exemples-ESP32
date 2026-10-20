// Código de ejemplo de variables en C

/* Variable Const: 
- Quiere decir una variable la cual no se cambiará y será estática durante todo el código; la mía marca en qué pin está conectado el LED.
*/
const int PIN_LED = 2;

/* Variable Int: 
- Quiere decir una variable la cual usaremos para guardar el número de vueltas del código, que suelen ser números enteros.
*/
int contador = 0;

/* Variable Long: 
- Quiere decir una variable la cual usaremos para guardar el tiempo de espera entre cada acción "Delay"; usaremos long porque nos permite números más grandes que int.
*/
long tiempoEspera = 1000;

/* Variable Float: 
- Quiere decir una variable la cual usaremos para guardar el número de la temperatura, ya que queremos que use decimales como normalmente se suele calcular.
*/
float temperatura = 24.5;

/* Variable Char: 
- Quiere decir una variable la cual usaremos para guardar un carácter como máximo; nosotros pondremos la letra A.
*/
char letra = 'A';

/* Variable Bool: 
- Quiere decir una variable la cual usaremos para guardar un resultado que solo puede ser false o true, que indicará si está encendido o no.
*/
bool encendido = true;

// Iniciamos la función de configuración donde marcamos Serial.begin.
void setup() {
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);
}


void loop() {
  if (encendido) {
    contador = contador + 1;
    // Si está encendido, aumenta el contador en 1 y muestra por pantalla las siguientes cosas:
    Serial.println(contador);
    Serial.println(temperatura);
    Serial.println(letra);
    
    // Enciende el LED, hace el delay y lo apaga.
    digitalWrite(PIN_LED, HIGH);
    delay(tiempoEspera);
    digitalWrite(PIN_LED, LOW);
    delay(tiempoEspera);
    
    // Si el contador es 5, encendido pasará a ser falso.
    if (contador == 5) {
      encendido = false;
    }
  }
}
