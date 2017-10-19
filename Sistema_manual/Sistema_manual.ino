#include <Servo.h>

Servo portao;  

int pos = 0;    // variable to store the servo position
const int pinoBotao = 2;
const int lampada =  12;
int estadoBotao = 0;
int ultimoEstadoBotao;

void setup() 
{
  portao.attach(9);
  pinMode(lampada, OUTPUT);  
  pinMode(pinoBotao, INPUT_PULLUP);
  Serial.begin(9600);
  
  portao.write(0);
  digitalWrite(lampada, LOW);
  ultimoEstadoBotao = 1;
}

void acendeLampada()
{
  digitalWrite(lampada, HIGH);
  ultimoEstadoBotao = 0;
  Serial.println("Lampada acesa...");
  delay(215);
}

void apagaLampada()
{
  digitalWrite(lampada, LOW);
  ultimoEstadoBotao = 1;
  Serial.println("Lampada apagada...");
  delay(215);  
}

void abrePortao()
{
  for (pos = 0; pos <= 89; pos += 1) 
  { 
    portao.write(pos);
    delay(15);                      
  }
  Serial.println("Portão Aberto...");
  ultimoEstadoBotao = 0;
  delay(200); 
}

void fechaPortao()
{
  for (pos = 90; pos >= 1; pos -= 1) 
  {
    portao.write(pos);              
    delay(15);                      
  }
  Serial.println("Portão Fechado...");
  ultimoEstadoBotao = 1;
  delay(200); 
}

void loop()
{
  estadoBotao = digitalRead(pinoBotao);
    
  if(estadoBotao == LOW && ultimoEstadoBotao == 1)
  {
    abrePortao();
    acendeLampada();
    Serial.println("");
  }

  estadoBotao = digitalRead(pinoBotao);
  
  if(estadoBotao == LOW && ultimoEstadoBotao == 0)  
  {
    fechaPortao();
    apagaLampada();
    Serial.println("");
  }
}

