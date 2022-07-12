const char website[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>Klakson</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
  html {
    font-family: Arial, Helvetica, sans-serif;
    text-align: center;
  }
  h1 {
    font-size: 1.8rem;
    color: white;
  }
  h2{
    font-size: 1.5rem;
    font-weight: bold;
    color: #563838;
  }
  .topnav {
    overflow: hidden;
    background-color: #A7414A;
  }
  body {
    margin: 0;
  }
  .content {
    padding: 15px;
    max-width: 600px;
    margin: 0 auto;
  }
  .card {
    background-color: #F8F7F9;;
    box-shadow: 2px 2px 12px 1px #282726;
    padding-top:10px;
    padding-bottom:20px;
  }
  .button {
    padding: 15px 50px;
    font-size: 24px;
    text-align: center;
    outline: none;
    color: #fff;
    background-color: #A37C27;
    border: none;
    border-radius: 5px;
    -webkit-touch-callout: none;
    -webkit-user-select: none;
    -khtml-user-select: none;
    -moz-user-select: none;
    -ms-user-select: none;
    user-select: none;
    -webkit-tap-highlight-color: rgba(0,0,0,0);
   }
   /*.button:hover {background-color: #0f8b8d}*/
   .button:active {
     background-color: #A37C27;
     box-shadow: 2 2px #CDCDCD;
     transform: translateY(2px);
   }
   .state {
     font-size: 1.5rem;
     color:#6A8A82;
     font-weight: bold;
   }
  </style>
<title>ESP Web Server</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="icon" href="data:,">
</head>
<body onload='updateData()'>
  <div class="topnav">
    <h1>SETTING KLAKSON</h1>
  </div>
  <div class="content">
    <div class="card">
      <h2>Status Sekarang</h2>
      <p class="state">Lagu : <span id="lagu">0</span></p>
      <p><button id="playl" class="button">Play</button></p>
      <p class="state">Klakson : <span id="klakson">0</span></p>
      <p><button id="playk" class="button">Play</button></p>
      <p class="state">Stop</p>
      <p><button id="stopp" class="button">Stop</button></p>
    </div>
  </div>
  <div class="content">
    <div class="card">
      <h2>Pilihan</h2>
      <table width='90%'>
        <tr>
          <td>
            <form>
              <h4>Lagu</h4>  
              <select id='ubahL' onchange="ubahl()">

              </select> 
            </form>  
          </td>
          <td>
            <form>  
              <h4>Klakson</h4>
              <select id='ubahK' onchange="ubahk()">

              </select> 
            </form>
          </td>
          </tr>
            
          <tr>
            <td>
              <p><button id="Ltotal" class="button" onClick="window.location.reload()">Refresh</button></p> 
            </td>
            <td>
              <p><button id="Ktotal" class="button" onClick="window.location.reload()">Refresh</button></p>
            </td>
            </tr>
      </table>
    </div>
  </div>
  <div class="content">
    <div class="card">
      <h2>Saklar</h2>
      <!-- <p class="state">Saklar Lock : <span id="lock">0</span></p>
      <p><button id="lockB" class="button">Change</button></p>
      <p class="state">Saklar unlock : <span id="unlock">0</span></p>
      <p><button id="unlockB" class="button">Change</button></p> -->
      <p class="state">Saklar Lock : <span id="lock">0</span></p>
      <p class="state">Saklar unlock : <span id="unlock">0</span></p>
      <p><button id="change" class="button">Change</button></p>
    </div>
  </div>
  <div class="content">
    <div class="card">
      <h2>Volume</h2>
      <table width='100%'> 
        <tr>
            <td>
                <input type="range" min="0" max="30" id="volume" onchange="volume()" style="width: 100%;">
            </td>
        </tr>
      </table>
    </div>
  </div>
    <!-- <div class="content">
      <div class="card">
        <h2>Error</h2>
        <p class="state">Total Lagu</p>
        <p><button id="Rtotal" class="button">Refresh</button></p>
      </div>
    </div>
  </div> -->
<script>

var laguNow;
var klaksonNow;
var lockNow;
var unlockNow;

var xmlHttp=createXmlHttpObject();
//var xmlHttp=createXmlHttpObject();

function createXmlHttpObject(){
 if(window.XMLHttpRequest){
    xmlHttp=new XMLHttpRequest();
 }else{
    xmlHttp=new ActiveXObject('Microsoft.XMLHTTP');// code for IE6, IE5
 }
 return xmlHttp;
}
//Data Total Lagu dan Klakson
if(xmlHttp.readyState==0 || xmlHttp.readyState==4){
   xmlHttp.open('POST','total',true);
   xmlHttp.onreadystatechange=dataTotal;
   xmlHttp.send(null);
}
function dataTotal(){
 if(xmlHttp.readyState==4 && xmlHttp.status==200){
   var data = xmlHttp.responseText;
   var myObj = JSON.parse(data);
   let laguT = parseInt(myObj.lagu);
   let klaksonT = parseInt(myObj.klakson);
   for(let i = 1; i<=laguT; i++){
     let pBaru = document.createElement('option');
     let teksBaru = document.createTextNode(String(i));
     pBaru.appendChild(teksBaru);
     pBaru.setAttribute('value', String(i));
     let sectionA = document.getElementById('ubahL')
     sectionA.appendChild(pBaru);
   }
   for(let i = 1; i<=klaksonT; i++){
     let pBaru = document.createElement('option');
     let teksBaru = document.createTextNode(String(i));
     pBaru.appendChild(teksBaru);
     pBaru.setAttribute('value', String(i));
     let sectionA = document.getElementById('ubahK')
     sectionA.appendChild(pBaru);
   }
 }
}

//Data Lagu dan Klakson sekarang
function updateData() {
  if(xmlHttp.readyState==0 || xmlHttp.readyState==4){
   xmlHttp.open('POST','play',true);
   xmlHttp.onreadystatechange=dataPlay;
   xmlHttp.send(null);
  }
  setTimeout('updateData()',500);
}
function dataPlay(){
 if(xmlHttp.readyState==4 && xmlHttp.status==200){
   var data = xmlHttp.responseText;
   var myObj = JSON.parse(data);
   laguNow = myObj.lagu;
   klaksonNow = myObj.klakson;
   lockNow = myObj.lock;
   unlockNow = myObj.unlock;
   document.getElementById('lagu').innerHTML=laguNow;
   document.getElementById('klakson').innerHTML=klaksonNow;
   document.getElementById('lock').innerHTML=lockNow;
   document.getElementById('unlock').innerHTML=unlockNow;
 }
}

//Data ubah Lagu
function ubahl(){
  laguNow = document.getElementById('ubahL').value;
  document.getElementById('lagu').innerHTML=String(laguNow);
  var xhr = new XMLHttpRequest();
  var url = "/ubahl";
  xhr.onreadystatechange = function() {
      if(this.onreadyState == 4  && this.status == 200) {
      console.log(xhr.responseText);
      }
  }
  xhr.open("POST", url, true);
  xhr.send(String(laguNow));
  xhr.onloadend = function(){
    console.log(xhr.status);
    if(this.status == 200) {
    var myObj = JSON.parse(this.responseText);
    console.log(myObj);
    }else{
    ubahL();
    }
  }
}

//Data ubah Klakson
function ubahk(){
  klaksonNow = document.getElementById('ubahK').value;
  document.getElementById('klakson').innerHTML=klaksonNow;
  var xhr = new XMLHttpRequest();
  var url = "/ubahk";
  xhr.onreadystatechange = function() {
      if(this.onreadyState == 4  && this.status == 200) {
      console.log(xhr.responseText);
      }
  }
  xhr.open("POST", url, true);
  xhr.send(klaksonNow);
  xhr.onloadend = function(){
    console.log(xhr.status);
    if(this.status == 200) {
    var myObj = JSON.parse(this.responseText);
    console.log(myObj);
    }else{
    ubahK();
    }
  }
}

//Button Lagu
document.getElementById('playl').addEventListener('click', playl);
function playl(){
  var xhr = new XMLHttpRequest();
  var url = "/playl";
  xhr.onreadystatechange = function() {
      if(this.onreadyState == 4  && this.status == 200) {
      console.log(xhr.responseText);
      }
  }
  xhr.open("POST", url, true);
  xhr.send(null);
  xhr.onloadend = function(){
    console.log(xhr.status);
    if(this.status == 200) {
    var myObj = JSON.parse(this.responseText);
    console.log(myObj);
    }else{
    playl();
    }
  }
}

//Button KLakson
document.getElementById('playk').addEventListener('click', playk);
function playk(){
  var xhr = new XMLHttpRequest();
  var url = "/playk";
  xhr.onreadystatechange = function() {
      if(this.onreadyState == 4  && this.status == 200) {
      console.log(xhr.responseText);
      }
  }
  xhr.open("POST", url, true);
  xhr.send(null);
  xhr.onloadend = function(){
    console.log(xhr.status);
    if(this.status == 200) {
    var myObj = JSON.parse(this.responseText);
    console.log(myObj);
    }else{
    playk();
    }
  }
}

//Button Stop
document.getElementById('stopp').addEventListener('click', stopp);
function stopp(){
  var xhr = new XMLHttpRequest();
  var url = "/stopp";
  xhr.onreadystatechange = function() {
      if(this.onreadyState == 4  && this.status == 200) {
      console.log(xhr.responseText);
      }
  }
  xhr.open("POST", url, true);
  xhr.send(null);
  xhr.onloadend = function(){
    console.log(xhr.status);
    if(this.status == 200) {
    var myObj = JSON.parse(this.responseText);
    console.log(myObj);
    }else{
    stopp();
    }
  }
}

// //Button Lock
// document.getElementById('lockB').addEventListener('click', lock);
// function lock(){
//   var xhr = new XMLHttpRequest();
//   var url = "/lock";
//   xhr.onreadystatechange = function() {
//       if(this.onreadyState == 4  && this.status == 200) {
//       console.log(xhr.responseText);
//       }
//   }
//   xhr.open("POST", url, true);
//   xhr.send(null);
//   xhr.onloadend = function(){
//     console.log(xhr.status);
//     if(this.status == 200) {
//     var myObj = JSON.parse(this.responseText);
//     console.log(myObj);
//     }else{
//     lock();
//     }
//   }
// }

// //Button Unlock
// document.getElementById('unlockB').addEventListener('click', unlock);
// function unlock(){
//   var xhr = new XMLHttpRequest();
//   var url = "/unlock";
//   xhr.onreadystatechange = function() {
//       if(this.onreadyState == 4  && this.status == 200) {
//       console.log(xhr.responseText);
//       }
//   }
//   xhr.open("POST", url, true);
//   xhr.send(null);
//   xhr.onloadend = function(){
//     console.log(xhr.status);
//     if(this.status == 200) {
//     var myObj = JSON.parse(this.responseText);
//     console.log(myObj);
//     }else{
//     unlock();
//     }
//   }
// }

//Button change
document.getElementById('change').addEventListener('click', change);
function change(){
  var xhr = new XMLHttpRequest();
  var url = "/change";
  xhr.onreadystatechange = function() {
      if(this.onreadyState == 4  && this.status == 200) {
      console.log(xhr.responseText);
      }
  }
  xhr.open("POST", url, true);
  xhr.send(null);
  xhr.onloadend = function(){
    console.log(xhr.status);
    if(this.status == 200) {
    var myObj = JSON.parse(this.responseText);
    console.log(myObj);
    }else{
    change();
    }
  }
}

//Volume
function volume(){
  let vol = document.getElementById('volume').value;
  var xhr = new XMLHttpRequest();
  var url = "/volume";
  xhr.onreadystatechange = function() {
      if(this.onreadyState == 4  && this.status == 200) {
      console.log(xhr.responseText);
      }
  }
  xhr.open("POST", url, true);
  xhr.send(vol);
  xhr.onloadend = function(){
    console.log(xhr.status);
    if(this.status == 200) {
    var myObj = JSON.parse(this.responseText);
    console.log(myObj);
    }else{
    volume();
    }
  }
}

// //Button Refresh Total
// document.getElementById('Rtotal').addEventListener('click', Rtotal);
// function Rtotal(){
//   var xhr = new XMLHttpRequest();
//   var url = "/Rtotal";
//   xhr.onreadystatechange = function() {
//       if(this.onreadyState == 4  && this.status == 200) {
//       console.log(xhr.responseText);
//       }
//   }
//   xhr.open("POST", url, true);
//   xhr.send(null);
//   xhr.onloadend = function(){
//     console.log(xhr.status);
//     if(this.status == 200) {
//     var myObj = JSON.parse(this.responseText);
//     console.log(myObj);
//     }else{
//     Rtotal();
//     }
//   }
// }

//Button Refresh lagu
document.getElementById('Ltotal').addEventListener('click', Ltotal);
function Ltotal(){
  var xhr = new XMLHttpRequest();
  var url = "/Ltotal";
  xhr.onreadystatechange = function() {
      if(this.onreadyState == 4  && this.status == 200) {
      console.log(xhr.responseText);
      }
  }
  xhr.open("POST", url, true);
  xhr.send(null);
  xhr.onloadend = function(){
    console.log(xhr.status);
    if(this.status == 200) {
    var myObj = JSON.parse(this.responseText);
    console.log(myObj);
    }else{
    Ltotal();
    }
  }
}

//Button Refresh klakson
document.getElementById('Ktotal').addEventListener('click', Ktotal);
function Ktotal(){
  var xhr = new XMLHttpRequest();
  var url = "/Ktotal";
  xhr.onreadystatechange = function() {
      if(this.onreadyState == 4  && this.status == 200) {
      console.log(xhr.responseText);
      }
  }
  xhr.open("POST", url, true);
  xhr.send(null);
  xhr.onloadend = function(){
    console.log(xhr.status);
    if(this.status == 200) {
    var myObj = JSON.parse(this.responseText);
    console.log(myObj);
    }else{
    Ktotal();
    }
  }
}
</script>
</body>
</html>
)rawliteral";
