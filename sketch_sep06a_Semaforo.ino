/* 06 Septiembre de 2018
   Creación de un semáforo con Arduino UNO*/

// Leds del semáforo.
#define verde 2// verde.
#define ambar 4// ámbar.
#define rojo  7// rojo.

// Potenciómetro.
#define pot A5


// Leds del peatón.
#define peaton_rojo   8
#define peaton_blanco 9

// Botón.
#define boton 10

// Defino un int para hacer el delay.
int intervalo = 5000; //El tiempo que se tarda de cambiar el color rojo a verde.
int paro = 0; // Es el acumulador para cuantas veces el semáforo peatonal sea usado desde la última vez.
int estado = 0; //Mi estado para saber si está mi botón en HIGH.
int valorPot = 0;
void setup()
{

  pinMode(verde, OUTPUT); // verde.
  pinMode(ambar, OUTPUT); // ámbar.
  pinMode(rojo, OUTPUT); // rojo.

  pinMode(peaton_rojo, OUTPUT); //roja del peatón.
  pinMode(peaton_blanco, OUTPUT); // blanco del peatón.

  pinMode(boton, INPUT);

  // Inicializo todo: Peaton, rojo; Coches, verde.
  digitalWrite(verde, HIGH);
  digitalWrite(peaton_rojo, HIGH);
  Serial.begin(9600);
}

void loop()
{
  valorPot = analogRead(pot);

  estado = digitalRead(boton);
  // Aqui yo le digo que si el boton no se ha presionado desde la vez que se ha
  //encendido el arduino y este ha echo un cambio,
  if (estado == HIGH && (millis() - paro) > 5000)
  {
    Serial.print("Valor potenciometro:");
    Serial.println(valorPot);
    switchSemaforo();
  } else
  {

  }

}


void switchSemaforo()
{
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(verde, LOW);
    delay(valorPot);
    digitalWrite(verde, HIGH);
    delay(500);
  }
  digitalWrite(verde, LOW);
  digitalWrite(ambar, HIGH);
  delay(700);
  digitalWrite(ambar, LOW);
  delay(500);
  digitalWrite(rojo, HIGH);
  digitalWrite(peaton_rojo, LOW);
  digitalWrite(peaton_blanco, HIGH);
  delay(intervalo);

  for (int j = 0; j < 6; j++) //Parpadeo del led del peatón.
  {
    digitalWrite(peaton_blanco, HIGH);
    delay(valorPot);
    digitalWrite(peaton_blanco, LOW);
    delay(500);
  }
  digitalWrite(peaton_blanco, LOW);
  digitalWrite(peaton_rojo, HIGH);
  digitalWrite(rojo, LOW);
  digitalWrite(verde, HIGH);

  paro = millis(); //Aquí voy acumulando el tiempo de encendido del arduino para poder hacer el cambio.
}

// Pues aquí se termina todo jaja.

