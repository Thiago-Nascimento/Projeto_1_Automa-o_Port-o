int ledVerde = 10;
int ledAmarelo = 9;
int ledVermelho = 8;
char estadoconexao = 0;
int buzz = 6;

void setup()
{
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(buzz, OUTPUT);
  Serial.begin(9600);
  }

void loop()
{
  estadoconexao = Serial.read();
  Serial.print(estadoconexao);
  
  switch (estadoconexao){
    case 'r': {
      digitalWrite(ledVerde,LOW);
      digitalWrite(ledAmarelo,LOW);
      digitalWrite(ledVermelho,HIGH); //sistema desconectado
      delay(100);
  	  digitalWrite(ledVermelho,LOW);
      delay(100);
      break;
    }
    case 'y':  {
      digitalWrite(ledVermelho,LOW);
      digitalWrite(ledVerde,LOW);
      digitalWrite(ledAmarelo,HIGH); //sistema em conexÃ£o
      delay(100);
  	  digitalWrite(ledAmarelo,LOW);
      delay(100);
      break;
  }
    case 'g':{
    digitalWrite(ledVermelho,LOW);  //sistema conectado
    digitalWrite(ledAmarelo,LOW);
    digitalWrite(ledVerde,HIGH);
    while (estadoconexao != 'r' || estadoconexao != 'y'){
      estadoconexao = Serial.read();

      if (estadoconexao == 'e'){
        digitalWrite(ledVerde,LOW);
        delay (50);
        digitalWrite(ledVerde,HIGH);
        delay (50);
        digitalWrite(ledVerde,LOW);
        delay (50);
        digitalWrite(ledVerde,HIGH);
        delay (50);
      }
      else if (estadoconexao == 'd'){
          tone (buzz, 500);
          delay (50);
          noTone(buzz);
          delay (50);
          tone (buzz, 500);
          delay (50);
          noTone(buzz);
      }
      else if (estadoconexao == 'y'){
        digitalWrite(ledVerde,LOW);
        digitalWrite(ledAmarelo,HIGH);
        delay(100);
        digitalWrite(ledAmarelo,LOW);
      break;}
      
      else if (estadoconexao == 'r'){
        digitalWrite(ledVerde,LOW);
        digitalWrite(ledVermelho,HIGH);
        delay(100);
        digitalWrite(ledVermelho,LOW);
      break;}
      
    }
    break;
       
  }
}
}

