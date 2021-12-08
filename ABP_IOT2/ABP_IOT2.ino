#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

#define FIREBASE_HOST "iot2farebasev-default-rtdb.firebaseio.com" //--> URL address of your Firebase Realtime Database. https://iot2farebasev-default-rtdb.firebaseio.com/
#define FIREBASE_AUTH "qlWl9Sjqu3Qurbm2AiF2J1OIBglzQP2ZtVeTCzCM" //--> Your firebase database secret code.

#define ON_Board_LED 2  
#define LED_Gre D5 

//----------------------------------------Sensor de procimidade
#define trig D6
#define echo D7

//----------------------------------------Sensor de Luz
#define pinoSensorLuz A0

//----------------------------------------SSID and Password of your WiFi router.
const char* ssid = "Viniphone"; 
const char* password = "nseioqcolocar"; 
//----------------------------------------

long randNumber;

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(500);
  
  WiFi.begin(ssid, password); 
  Serial.println("");
    
  pinMode(ON_Board_LED,OUTPUT); 
  pinMode(LED_Gre,OUTPUT);
  digitalWrite(ON_Board_LED, HIGH); 

  //----------------------------------------Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    //----------------------------------------Make the On Board Flashing LED on the process of connecting to the wifi router.
    digitalWrite(ON_Board_LED, LOW);
    delay(250);
    digitalWrite(ON_Board_LED, HIGH);
    delay(250);
    //----------------------------------------
  }
  //----------------------------------------
  digitalWrite(ON_Board_LED, HIGH); 
  //----------------------------------------If successfully connected to the wifi router, the IP Address that will be visited is displayed in the serial monitor.
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  //----------------------------------------

  //----------------------------------------Firebase Realtime Database Configuration.
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  //----------------------------------------
}

void loop() {
  //----------------------------------------Send data in the form of random value data to the Firebase Realtime Database.
  
  double distan = pulso();
  Serial.println("Valor do sensor de aproximidade em cm: " + String(distan));
  Firebase.setFloat("Vini/SensorAp", distan); 

  if (Firebase.failed()) { 
      Serial.print("Setting /Value failed (Sensor de distancia):");
      Serial.println(Firebase.error());  
      delay(500);
      return;
  }

  int valorLuz = analogRead(pinoSensorLuz);
  String vlLuz = String(valorLuz);
  Serial.println("Valor do sensor de luz: " + vlLuz);
  Firebase.setString("Vini/SensorLz", vlLuz); 

  if (Firebase.failed()) { 
      Serial.print("Setting /Value failed (Sensor de Luz):");
      Serial.println(Firebase.error());  
      delay(500);
      return;
  }

  String status = Firebase.getString("Vini/LED");

  if (status == "on") {
    digitalWrite(LED_Gre, HIGH);
    Serial.println("LED On");
    Serial.println();
  }

  if (status == "off") {
    digitalWrite(LED_Gre, LOW);
    Serial.println("LED off");
    Serial.println();
  }

  Serial.println("Setting successful");
  Serial.println();
  //----------------------------------------
  
  delay(5000);
}

float pulso(){
  long tempo;
  
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  
  tempo = pulseIn(echo, HIGH);
  return tempo*(0.034/2);
}
