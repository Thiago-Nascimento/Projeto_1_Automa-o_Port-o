

int ledVerde = 8;
int ledAmarelo = 7;
int ledVermelho = 6;
char estadoconexao = 0;
int buzz = 5;

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
      while (estadoconexao == 'y'){
      
      if(Serial.available() > 0){
      estadoconexao = Serial.read();
      }

      digitalWrite(ledVermelho,LOW);
      digitalWrite(ledVerde,LOW);
      digitalWrite(ledAmarelo,HIGH); //sistema em conexÃ£o
      delay(100);
  	  digitalWrite(ledAmarelo,LOW);
      delay(100);
  
      }
      break;
      
  }
    case 'g':{
    digitalWrite(ledVermelho,LOW);  //sistema conectado
    digitalWrite(ledAmarelo,LOW);
    digitalWrite(ledVerde,HIGH);
    while (estadoconexao == 'g'){
      
        if(Serial.available() > 0){
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
        estadoconexao = 'g';
      }
      else if (estadoconexao == 'd'){
          tone (buzz, 500);
          delay (50);
          noTone(buzz);
          delay (50);
          tone (buzz, 500);
          delay (50);
          noTone(buzz);
          estadoconexao = 'g';
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
    }
    break;
       
  }
}
}

