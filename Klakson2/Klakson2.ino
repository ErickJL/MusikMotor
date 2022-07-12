#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);
const char* ssid = "Motor";
const char* password = "binuscom";
IPAddress local_ip(192, 168, 4, 1);
IPAddress gateway(192, 168, 4, 1);
IPAddress netmask(255, 255, 255, 0);

#define relay D5
#define lockP D6
#define unlockP D7
//#define lanjut D8

int playL=1;
int playK=1;
int vol=20;
int totalL;
int totalK;

bool stateL = false;
bool stateK = false;
//bool stateN = false;
//bool stateG = false;
//bool lockB=false;
//bool unlockB=false;
bool changeB=false;
bool stateH=true;

//String pesan="<h3>Pesan</h3>";;

String lockS = "lagu";
String unlockS = "klakson";

SoftwareSerial mySoftwareSerial(D2, D3); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

#include "DFPlayer.h"
#include "web.h"
#include "webServer.h"

void setup(){
  //Pin
  pinMode(D0, INPUT);
  pinMode(relay, OUTPUT);
  pinMode(lockP, INPUT);
  pinMode(unlockP, INPUT);
//  pinMode(lanjut, INPUT);
  digitalWrite(relay, HIGH);

  mySoftwareSerial.begin(9600);
  Serial.begin(115200);

  setServer();
  delay(500);
  setDF();

//  bool baca = digitalRead(D0);
//  if(baca){
//    digitalWrite(relay, HIGH);
//    stateH=true;
//  }else{
//    stateH=false;
//    digitalWrite(relay, LOW);
//  }
}

void loop(){ 
  if(stateH){
    henti();
  }
  //nextLK();
  if(changeB){
    PlayKlakson(digitalRead(lockP));
    PlayLagu(digitalRead(unlockP));
  }else{
    PlayLagu(digitalRead(lockP));
    PlayKlakson(digitalRead(unlockP));
  }
//  if(lockB){
//    PlayLagu(digitalRead(lockP));
//  }else{
//    PlayKlakson(digitalRead(lockP));
//  }
//  if(unlockB){
//    PlayLagu(digitalRead(unlockP));
//  }else{
//    PlayKlakson(digitalRead(unlockP));
//  }
  server.handleClient();
}
