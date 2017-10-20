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
      break;
    }
     case 'e':{
        digitalWrite(ledVermelho,LOW);
        digitalWrite(ledAmarelo,LOW);
        digitalWrite(ledVerde,LOW);
        delay (50);
        digitalWrite(ledVerde,HIGH);
        delay (50);
        digitalWrite(ledVerde,LOW);
        delay (50);
        digitalWrite(ledVerde,HIGH);
        delay (50);
        break;
        }
     case 'd':{
        digitalWrite(ledVermelho,LOW);
        digitalWrite(ledAmarelo,LOW);
          tone (buzz, 500);
          delay (50);
          noTone(buzz);
          delay (50);
          tone (buzz, 500);
          delay (50);
          noTone(buzz);
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
    feedback('e');

    // Conecta no topic para receber mensagens
    if(client.subscribe("teste")==1){
    feedback('g');
    feedback('d');
    
    Serial.println("Conectado MQTT");
    
    }
  }else{
    Serial.println("erro ao conectar"); 
    delay(50); 
    feedback('r');
  }
  
}

void loop()
{
  client.loop();
  client.publish("mensagem","2");
  if (client.subscribe("mensagem")== 2){
      feedback('d');
      Serial.println("Recebido");
      }

}
