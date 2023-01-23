
// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLCu4RPpPW"
#define BLYNK_DEVICE_NAME "led test"
#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG
#include "GGalaxia.h"

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_WROVER_BOARD
//#define USE_TTGO_T7
//#define USE_ESP32C3_DEV_MODULE
//#define USE_ESP32S2_DEV_KIT

#include "BlynkEdgent.h"
#define BZ 15

const byte azul = 5;
const byte rojo = 16;
const byte verde = 17;
const int potY = 34;
const int potX = 35;
const int mic = 32;
int valY = 0;
int valX = 0;
int valMic = 0;
int status = 0;
int pushButton = 22;
int buttonState = 0;
int S1 = 21;
int StateS1 = 0;
int S2 = 23;
int StateS2 = 0;


BlynkTimer timer; 

void myTimer() 
{
  // This function describes what will happen with each timer tick
  // e.g. writing sensor value to datastream V5
  Blynk.virtualWrite(V5, valY);
  delay(10);
  Blynk.virtualWrite(V4, valX);
  delay(10);
  Blynk.virtualWrite(V3, valMic);
  delay(10);
  Blynk.virtualWrite(V6, !buttonState);
  delay(10);
  Blynk.virtualWrite(V7, StateS1);
  delay(10);
  Blynk.virtualWrite(V8, StateS2);
    
 
    
}
void setup()
{
  pinMode(BZ, OUTPUT); // declaracion de la variable
  ledcSetup(0, 0, 10);
  ledcAttachPin(BZ, 0);

  
  Serial.begin(115200);
  delay(1000);
  pinMode(verde, OUTPUT);
  pinMode(rojo, OUTPUT);
  pinMode(azul, OUTPUT);
  pinMode(pushButton, INPUT);
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);  
  timer.setInterval(1000L, myTimer);

  BlynkEdgent.begin();
}

void loop() {
  
   //De aquí borrar el "300" si se quiere un tono continuo
  
  valY = analogRead(potY);
  valX = analogRead(potX);
  valMic = analogRead(mic);  
  Serial.println(valMic);
  buttonState = digitalRead(pushButton); 
  StateS1 = digitalRead(S1);
  StateS2 = digitalRead(S2); 
  Serial.println(buttonState);
  
  BlynkEdgent.run();
  delay(500);
  timer.run(); 
   
  
}
BLYNK_WRITE(V0)
{
  int state = param.asInt();
  digitalWrite(azul,state);
   
}
BLYNK_WRITE(V1)
{
  int state = param.asInt();
  digitalWrite(rojo,state);
   
}
BLYNK_WRITE(V2)
{
  int state = param.asInt();
  digitalWrite(verde,state);
   
}
BLYNK_WRITE(V10)
{

Serial.print("Inicio Melodia --- ");
  for (int i=0 ; i < NOTAS; i++)
  {
     beep(duracion[i],melodia[i]);
  }
 
  Serial.println("FIN");
  delay(1500);  

   
}
void beep(float duracion, unsigned int nota)
{
   int frecuencia;  

   if(nota < 100)
   {
      // Calculamos la frecuencia a tocar, indice 0 Do4
      frecuencia = (int) 261.625 * pow(1.0594630943593,nota);
   }
   else frecuencia =0;
   
 
    ledcWriteTone(0, frecuencia); //Toca Tono definido en la frecuencia con su duración
    delay(duracion*500);
    ledcWrite(0,0);   
  
}
