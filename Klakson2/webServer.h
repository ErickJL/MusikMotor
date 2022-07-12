void total(){
  String Json = "";
  Json += "{\"lagu\":";
  Json += String(totalL);
  Json += ",\"klakson\":";
  Json += String(totalK);
  Json += "}";
  server.send(200,"text/xml",Json);
}

void play(){
  String Json = "";
  Json += "{\"lagu\":";
  Json += String(playL);
  Json += ",\"klakson\":";
  Json += String(playK);
  Json += ",\"lock\":\"";
  Json += String(lockS);
  Json += "\",\"unlock\":\"";
  Json += String(unlockS);
  Json += "\"}";
  server.send(200,"text/xml",Json);
}

void ubahl(){
  String data = server.arg("plain");
  playL = data.toInt();
  String response = "{\"ubahl\":1}";
  server.send(200, "/ubahl", response);
}

void ubahk(){
  String data = server.arg("plain");
  playK = data.toInt();
  String response = "{\"ubahk\":1}";
  server.send(200, "/ubahk", response);
}

void playl(){
  myDFPlayer.playFolder(2, playL);
  delay(10);
  myDFPlayer.enableLoop();
  String response = "{\"playl\":1}";
  server.send(200, "/playl", response);
}

void playk(){
  myDFPlayer.playFolder(3, playK);
  delay(10);
  myDFPlayer.enableLoop();
  String response = "{\"playk\":1}";
  server.send(200, "/playk", response);
}

void stopp(){
  myDFPlayer.stop();
  String response = "{\"stopp\":1}";
  server.send(200, "/stopp", response);
}

//void lock(){
//  lockB=!lockB;
//  if(lockB){
//    lockS="lagu";
//  }else{
//    lockS="klakson";
//  }
//  String response = "{\"lock\":1}";
//  server.send(200, "/lock", response);
//}
//
//void unlock(){
//  unlockB=!unlockB;
//  if(unlockB){
//    unlockS="lagu";
//  }else{
//    unlockS="klakson";
//  }
//  String response = "{\"unlock\":1}";
//  server.send(200, "/unlock", response);
//}

void change(){
  changeB=!changeB;
  if(changeB){
    lockS="klakson";
    unlockS="lagu";
  }else{
    lockS="lagu";
    unlockS="klakson";
  }
  String response = "{\"change\":1}";
  server.send(200, "/change", response);
}

void volume(){
  String data = server.arg("plain");
  vol = data.toInt();
  myDFPlayer.volume(vol); 
  String response = "{\"volume\":1}";
  server.send(200, "/volume", response);
}

void Ltotal(){
  totalL = myDFPlayer.readFileCountsInFolder(2);
  String response = "{\"Ltotal\":1}";
  server.send(200, "/Ltotal", response);
}

void Ktotal(){
  totalK = myDFPlayer.readFileCountsInFolder(3);
  String response = "{\"Ktotal\":1}";
  server.send(200, "/Ktotal", response);
}

void setServer(){
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_ip, gateway, netmask);
  WiFi.softAP(ssid, password);
  delay(500);

  server.on("/", [](){
    server.send_P(200, "text/html", website);
  });
//  server.on("/pesan", [](){
//    server.send(200, "text/html", pesan);
//  });
  server.on("/ubahl", HTTP_POST, ubahl);
  server.on("/ubahk", HTTP_POST, ubahk);
  server.on("/playl", HTTP_POST, playl);
  server.on("/playk", HTTP_POST, playk);
  server.on("/stopp", HTTP_POST, stopp);
//  server.on("/lock", HTTP_POST, lock);
//  server.on("/unlock", HTTP_POST, unlock);
  server.on("/change", HTTP_POST, change);
  server.on("/volume", HTTP_POST, volume);
  server.on("/Ltotal", HTTP_POST, Ltotal);
  server.on("/Ktotal", HTTP_POST, Ktotal);
  server.on("/total", total);
  server.on("/play", play);
  server.begin();
}
