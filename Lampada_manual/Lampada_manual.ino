
const int pinoBotao = 2;     
const int lampada =  12;     

int estadoBotao = 0;
int ultimoEstado;

void setup() 
{
  pinMode(lampada, OUTPUT);
  pinMode(pinoBotao, INPUT_PULLUP);
  digitalWrite(lampada, LOW);
  Serial.begin(9600);
  ultimoEstado = 1;
}

void acendeLampada()
{
  digitalWrite(lampada, HIGH);
  ultimoEstado = 0;
  Serial.println("Lampada acesa...");
  delay(215);
}

void apagaLampada()
{
  digitalWrite(lampada, LOW);
  ultimoEstado = 1;
  Serial.println("Lampada apagada...");
  delay(215);  
}

void loop() 
{
  estadoBotao = digitalRead(pinoBotao);
  
  if (estadoBotao == LOW && ultimoEstado == 1) 
  {
    acendeLampada();  
  } 
  
  else if (estadoBotao == LOW && ultimoEstado == 0)
  {
    apagaLampada();
  }
}
