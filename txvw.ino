#include <VirtualWire.h>

const int led_pin = 11;
const int transmit_pin = 12;
const int receive_pin = 2;
const int transmit_en_pin = 3;
char cadena[500]; //Creamos un array que almacenará los caracteres que escribiremos en la consola del PC. Le asignamos  un tope de caracteres, en este caso 30
byte posicion=0;  //Variable para cambiar la posición de los caracteres del array
int valor=0;  //Variable del valor entero

void setup()
{
    Serial.begin(9600);
    Serial.println("Tx envio de datos de virtualwire");
    Serial.println("Codigo de ejemplo de lectura de char");
    Serial.println("Codigo modificado por RedoDc.");
    // Initialise the IO and ISR
    vw_set_tx_pin(transmit_pin);
    vw_set_rx_pin(receive_pin);
    vw_set_ptt_pin(transmit_en_pin);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);       // Bits per sec
    pinMode(led_pin, OUTPUT);
}

byte count = 1;

void loop()
{
  leercadena();
  if (valor !=0){
  digitalWrite(led_pin, HIGH); // Flash a light to show transmitting
  vw_send((uint8_t *)cadena, valor);
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(led_pin, LOW);
  delay(100);
  valor=0;
  }
}

void leercadena(){
if(Serial.available()) //Nos dice si hay datos dentro del buffer
  {
    memset(cadena, 0,sizeof(cadena));//memset borra el contenido del array  "cadena" desde la posición 0 hasta el final sizeof
 
    while(Serial.available()>0) //Mientras haya datos en el buffer ejecuta la función
    {
      delay(5); //Poner un pequeño delay para mejorar la recepción de datos
      cadena[posicion]=Serial.read();//Lee un carácter del string "cadena" de la "posicion", luego lee el siguiente carácter con "posicion++"
      posicion++;
    }
     
    valor=(posicion);//Convertimos la cadena de caracteres en enteros
    Serial.print("Tx: ");
    Serial.print(cadena);//Imprimimos el valor 
    Serial.print(" [(DEBUG INFO) len  ");
    Serial.print(posicion);
    Serial.println("]");
    posicion=0;//Ponemos la posicion a 0
    }
  }
