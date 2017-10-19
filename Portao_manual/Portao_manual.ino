
#include <Servo.h>

Servo portao;  

int pos = 0;    // variable to store the servo position
const int pinoBotao = 2;
int estadoBotao = 0;
int ultimoEstadoBotao;

void setup() 
{
  portao.attach(9);  
  pinMode(pinoBotao, INPUT_PULLUP);
  Serial.begin(9600);
  portao.write(0);
  ultimoEstadoBotao = 1;
}

void loop()
{
  estadoBotao = digitalRead(pinoBotao);
    
  if(estadoBotao == LOW && ultimoEstadoBotao == 1)
  {
    for (pos = 0; pos <= 89; pos += 1) 
    { 
      portao.write(pos);
      delay(15);                      
    }
    Serial.println("Estado Botao: ");
    Serial.println(estadoBotao);
    Serial.println("Ultimo estado do botao: "); 
    Serial.println(ultimoEstadoBotao);
    Serial.println("Portão Aberto...");
    Serial.println(pos);
    ultimoEstadoBotao = 0;
    delay(200);
  }

  estadoBotao = digitalRead(pinoBotao);
  
  if(estadoBotao == LOW && ultimoEstadoBotao == 0)  
  {
    for (pos = 90; pos >= 1; pos -= 1) 
    {
      portao.write(pos);              
      delay(15);                      
    }
    Serial.println("Estado Botao: ");
    Serial.println(estadoBotao);
    Serial.println("Ultimo estado do botao: "); 
    Serial.println(ultimoEstadoBotao);
    Serial.println("Portão Fechado...");
    Serial.println(pos);
    ultimoEstadoBotao = 1;
    delay(200);
  }
}

