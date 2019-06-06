#include <SoftwareSerial.h>

SoftwareSerial ESP8266(10, 11); // TX, RX
const byte axeH = A0;
const byte axeV = A1;

String NomduReseauWifi = "Students"; // Garder les guillements
String MotDePasse      = ""; // Garder les guillements
String ipHost = "10.44.1.95";

int analogValue;
String buffeur = "";
/****************************************************************/
/*                             INIT                             */
/****************************************************************/
void setup()
{
  pinMode(axeH, INPUT);
  pinMode(axeV, INPUT);

  Serial.begin(115200);
  ESP8266.begin(115200);
  initESP8266();
}
/****************************************************************/
/*                        BOUCLE INFINIE                        */
/****************************************************************/
void loop()
{
  analogValue = analogRead(axeV);
  Serial.println(analogValue);

  Serial.println("8=====================================D");
  String cmd = "AT+CIPSEND=" + analogValue;
  envoieCommande(analogValue);
  recoitDuESP8266(1000);
    
  while (ESP8266.available())
  {
    Serial.println(ESP8266.read());
    delay(1000);
  }
  delay(100);
}
/****************************************************************/
/*                Fonction qui initialise l'ESP8266             */
/****************************************************************/
void initESP8266()
{
  Serial.println("**********************************************************");
  Serial.println("**************** DEBUT DE L'INITIALISATION ***************");
  Serial.println("**********************************************************");
  Serial.println("********************* RESET MODULE ***********************");
  envoieAuESP8266("AT+RST");
  recoitDuESP8266(2000);
  Serial.println("**********************************************************");
  envoieAuESP8266("AT+CWMODE=1");
  recoitDuESP8266(2000);
  Serial.println("****************** NETWORK CONNECTION ********************");
  envoieAuESP8266("AT+CWJAP=\"" + NomduReseauWifi + "\",\"" + MotDePasse + "\"");
  recoitDuESP8266(10000);
  Serial.println("**********************************************************");
  envoieAuESP8266("AT+CIPMUX=0");
  recoitDuESP8266(1000);
  Serial.println("************** CONNECTION TO SERVER NODE *****************");
  envoieAuESP8266("AT+CIPSTART=\"TCP\",\""+ipHost+"\",8080");
  recoitDuESP8266(1000);
  
  Serial.println("**********************************************************");
  //envoieAuESP8266("AT+CIPCLOSE");
  //recoitDuESP8266(1000);
  Serial.println("**********************************************************");
  Serial.println("***************** INITIALISATION TERMINEE ****************");
  Serial.println("**********************************************************");
  Serial.println("");
}

/****************************************************************/
/*        Fonction qui envoie une commande à l'ESP8266          */
/****************************************************************/
void envoieAuESP8266(String commande)
{
  buffeur = commande;
  ESP8266.println(buffeur);
}

void envoieCommande(int analogValue)
{
  Serial.print("AnalogValue : ");
  Serial.println(analogValue);
  ESP8266.print("AT+CIPSEND=");
  delay(100);
  ESP8266.println(4);
  delay(500);
  ESP8266.println(analogValue);
}

/****************************************************************/
/*Fonction qui lit et affiche les messages envoyés par l'ESP8266*/
/****************************************************************/
void recoitDuESP8266(const int timeout)
{
  String reponse = "";
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (ESP8266.available())
    {
      char c = ESP8266.read();
      reponse += c;
    }
  }
  Serial.print(reponse);
}
