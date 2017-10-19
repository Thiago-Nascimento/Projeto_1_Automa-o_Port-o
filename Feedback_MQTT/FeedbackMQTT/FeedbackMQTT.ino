#include <SPI.h>
#include <UIPEthernet.h>
#include <utility/logging.h>
#include <PubSubClient.h>



//função feedback
void feedback(char msg)
{

int ledVerde = 8;
int ledAmarelo = 7;
int ledVermelho = 6;
char estadoconexao = 0;
int buzz = 5;


  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(buzz, OUTPUT);
  Serial.begin(9600);
  
  estadoconexao = msg;
   
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


// Update these with values suitable for your network.
byte mac[] = {0xDE, 0xED, 0xBA, 0xFE, 0xF1, 0x64};

// Callback function header
void callback(char *topic, byte *payload, unsigned int length);

EthernetClient ethClient;

// Dados do MQTT Cloud
PubSubClient client("m11.cloudmqtt.com", 11084, callback, ethClient);

// Funcçao que irá receber o retorno do servidor.
void callback(char *topic, byte *payload, unsigned int length)
{
  char c = payload;
  Serial.println(c);
  Serial.println(topic);

 

  byte *p = (byte *)malloc(length);
  memcpy(p, payload, length);
  free(p);
}

void setup()
{
  Serial.begin(9600);
  Serial.println("Iniciando...");
  Ethernet.begin(mac);
  feedback('y');

  // Faz a conexão no cloud com nome do dispositivo, usuário e senha respectivamente
  if (client.connect("arduino", "arduino", "ard123"))
  {
    // Envia uma mensagem para o cloud no topic portao
    client.publish("teste", "1");

    // Conecta no topic para receber mensagens
    client.subscribe("portao");
    client.subscribe("lampada");
    
    Serial.println("conectado Temperatura");
  }else{
    Serial.println("erro ao conectar");  
  }
  
}

void loop()
{
  client.loop();
}
