
const int pinoBotao = 2;     
const int lampada =  13;     

int estadoBotao = 0;
int ultimoEstado;

void setup() 
{
  pinMode(lampada, OUTPUT);
  pinMode(pinoBotao, INPUT_PULLUP);
  digitalWrite(lampada, LOW);
  ultimoEstado = 1;
}

void loop() 
{
  estadoBotao = digitalRead(pinoBotao);
  
  if (estadoBotao == LOW && ultimoEstado == 1) 
  {
    digitalWrite(lampada, HIGH);
    ultimoEstado = 0;
    delay(200);    
  } 
  
  else if (estadoBotao == LOW && ultimoEstado == 0)
  {
    digitalWrite(lampada, LOW);
    ultimoEstado = 1;
    delay(200);
  }
}
