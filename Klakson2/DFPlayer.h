void setDF(){
  while (!myDFPlayer.begin(mySoftwareSerial, true, true)){
    delay(1);
  }
  delay(1000);
  myDFPlayer.stop();
  myDFPlayer.stop();
  delay(200);
  myDFPlayer.volume(vol); 
  delay(500);
  myDFPlayer.playFolder(1, 1); 
  delay(10);
  myDFPlayer.disableLoop();
  delay(4000);
  myDFPlayer.stop();
  delay(500);
  myDFPlayer.stop();
  delay(1000);
}

void PlayLagu(bool baca){
  if(baca==true){
    if(stateL==false){
      myDFPlayer.playFolder(2, playL);
      delay(10);
      myDFPlayer.enableLoop();
      //stateG=true;
      stateL=true;
      //pesan+="<p>L1</p>";
    }
  }else{
    if(stateL==true){
      myDFPlayer.stop();
      stateL=false;
      //pesan+="<p>L0</p>";
    }
  }
//  if (stateL != baca){
//    stateL=baca;
//    if(baca==HIGH){
//      myDFPlayer.playFolder(2, playL);
//      delay(10);
//      myDFPlayer.enableLoop();
//    }else{
//      myDFPlayer.stop();
//    }
//    //stateG=true;
//  }
}

void PlayKlakson(bool baca){
  if(baca==true){
    if(stateK==false){
      myDFPlayer.playFolder(3, playK);
      delay(10);
      myDFPlayer.enableLoop();
      //stateG=false;
      stateK=true;
      //pesan+="<p>K1</p>";
    }
  }else{
    if(stateK==true){
      myDFPlayer.stop();
      stateK=false;
      //pesan+="<p>K0</p>";
    }
  }
//  if (stateK != baca){
//    stateK = baca;
//    if(baca==HIGH){
//      myDFPlayer.playFolder(3, playK);
//      delay(10);
//      myDFPlayer.enableLoop();
//    }else{
//      myDFPlayer.stop();
//    }
//    //stateG=false;
//  }
}

//void nextLK(){
//  bool baca = digitalRead(lanjut);
//  if(baca==true){
//    if(stateN==false){
//      stateN=true;
//      delay(500);
//    }
//  }else{
//    if(stateN==true){
//      if(stateG){
//        playL++;
//        //pesan+="<p>NL</p>";
//      }else{
//        playK++;
//        //pesan+="<p>NK</p>";
//      }
//      stateN=false;
//    }
//  }
//  if(playL>totalL){
//    playL=1;
//  }
//  if(playK>totalK){
//    playK=1;
//  }
//}

void henti(){
  //int baca = analogRead(A0);
  bool baca = digitalRead(D0);
  if(!baca){
  //if(baca<=500){
    myDFPlayer.stop();
    myDFPlayer.volume(20); 
    delay(500);
    myDFPlayer.playFolder(1, 2);
    delay(500);
    myDFPlayer.disableLoop();
    delay(6000);
    digitalWrite(relay, LOW);
    stateH=false;
  }
}
