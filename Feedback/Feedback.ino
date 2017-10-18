int ledVerde = 10;
int ledAmarelo = 9;
int ledVermelho = 8;
char estadoconexao = 0;

void setup()
{
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  Serial.begin(9600);
  }

void loop()
{
  estadoconexao = Serial.read();
  Serial.print(estadoconexao);
  
  if(estadoconexao =='r')
  {
      digitalWrite(ledVerde,LOW);
      digitalWrite(ledAmarelo,LOW);
      digitalWrite(ledVermelho,HIGH); //sistema desconectado
      delay(100);
  	  digitalWrite(ledVermelho,LOW);
      delay(100);
    }
  else if(estadoconexao =='y')
  {
      digitalWrite(ledVermelho,LOW);
      digitalWrite(ledVerde,LOW);
      digitalWrite(ledAmarelo,HIGH); //sistema em conexão
      delay(100);
  	  digitalWrite(ledAmarelo,LOW);
      delay(100);
  }
  else if(estadoconexao =='g')
  {
    digitalWrite(ledVermelho,LOW);  //sistema conectado
    digitalWrite(ledAmarelo,LOW);
    digitalWrite(ledVerde,HIGH);
  }
}