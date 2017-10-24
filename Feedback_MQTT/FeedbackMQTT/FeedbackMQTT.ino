#include <SPI.h>
#include <UIPEthernet.h>
#include <utility/logging.h>
#include <PubSubClient.h>

#include <Servo.h>

Servo portao;  

int pos = 0; 
const int pinoBotao = 4;
const int lampada =  3;
int estadoBotao = 0;
int ultimoEstadoBotao;

//função feedback
void acendeLed(int ledAceso,int ledApagado1, int ledApagado2)
{
  digitalWrite(ledApagado2,LOW);
  digitalWrite(ledApagado1,LOW);
  digitalWrite(ledAceso,HIGH); 
  }

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
      acendeLed(ledVermelho,ledVerde, ledAmarelo); //sistema desconectado
      delay(100);
      break;
    }
    case 'y':  {
      acendeLed(ledAmarelo,ledVermelho,ledVerde);  //sistema em conexÃ£o
      break;
      }
      
  
    case 'g':{
      acendeLed(ledVerde,ledAmarelo,ledVermelho);
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




char payload = 0;
char topic = 0;

// Update these with values suitable for your network.
byte mac[] = {0xDE, 0xED, 0xBA, 0xFE, 0xF1, 0x64};

// Callback function header
void callback(char* topic, byte* payload, unsigned int length);

EthernetClient ethClient;

// Dados do MQTT Cloud
PubSubClient client("m11.cloudmqtt.com", 11084, callback, ethClient);

void abrePortao()
{
  for (pos = 0; pos <= 89; pos += 1) 
  { 
    portao.write(pos);
    delay(15);                      
  }
  Serial.println("Portão Aberto...");
  client.publish("enviado","Portão aberto");
  client.publish("enviado","Lâmpada acesa");
  feedback('e');
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
  client.publish("enviado","Portão fechado");
  client.publish("enviado","Lâmpada apagada");
  feedback('e');
  ultimoEstadoBotao = 1;
  delay(200); 
}
// Funcçao que irá receber o retorno do servidor.
void callback(char* topic, byte* payload, unsigned int length)
{
  char* payloadAsChar = payload;
  payloadAsChar[length]=0;
  String msgRecebida = String (payloadAsChar);
  
  Serial.println(msgRecebida);
  Serial.println();
  Serial.println(topic);
  delay(100);
  feedback('d');


if(msgRecebida == "abre" && ultimoEstadoBotao == 1)
  {
    abrePortao();
    acendeLampada();
    Serial.println("");
    }
 
  else if(msgRecebida == "abre" && ultimoEstadoBotao == 0)  
  {
    fechaPortao();
    apagaLampada();
    Serial.println("");
  }

  byte* p = (byte* )malloc(length);
  memcpy(p, payload, length);
  free(p);
}

void setup()
{
  ultimoEstadoBotao = 1;
  Serial.begin(9600);
  Serial.println("Iniciando...");
  Ethernet.begin(mac);
  feedback('y');

  // Faz a conexão no cloud com nome do dispositivo, usuário e senha respectivamente
  if (client.connect("arduino", "arduino", "ard123"))
  {
    // Envia uma mensagem para o cloud no topic portao
    client.publish("teste", "v");
        

    // Conecta no topic para receber mensagens
  client.subscribe("recebido");
  
//   
  Serial.println("Conectado MQTT");
  delay(50);
  feedback('g');
    
  }else{
    Serial.println("erro ao conectar"); 
    delay(50); 
    feedback('r');
  }

//  setup do portão manual
   portao.attach(9);
  pinMode(lampada, OUTPUT);  
  pinMode(pinoBotao, INPUT_PULLUP);
  Serial.begin(9600);
  
  portao.write(0);
  digitalWrite(lampada, LOW);
  ultimoEstadoBotao = 1;
}

void loop()
{
  client.loop();

//abir e fechar portão com botão
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
