#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;

char auth[] = "INzjz7de62a1SjM0UMNel4_YXmD8Ja62";   //my auth token 
char ssid[] = "SMP2"; //My farm's wifi ssid
char pass[] = "bilvapriya@222"; //The wifi's Password
int failedattempt = 0;
int sensorData0 = 0;
long startMillis;  //some global variables available anywhere in the program
long currentMillis;
long thirtydelay;

void myTimerEvent(){
  sensorData0 = analogRead(A0);
  Blynk.virtualWrite(V1, sensorData0);
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print("i am here");
  digitalWrite(0, HIGH) ;
  digitalWrite(1, HIGH);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  Blynk.begin(auth,ssid,pass, "blynkforjit.onthewifi.com", 8080); //tries to connect to the blynk server
  timer.setInterval(1000L, myTimerEvent);
  
  if (Blynk.connected() == LOW) {
    failedattempt = failedattempt + 1;
    Serial.print("Failled attempt : ");
    Serial.print(failedattempt);
    if (failedattempt >= 200) {      //After 100 failled attempts it turns the "On Relay" on
      Serial.print("Turning on");
      digitalWrite(1,LOW);
      delay(1000);
      digitalWrite(1,HIGH);
      Serial.print("Turning 0ff");
      
      startMillis = millis();        
      thirtydelay = startMillis + 1800000;
      if (millis()>= thirtydelay) {  // After 30 min it turs it off
        digitalWrite(2,LOW);
        delay(1000);                 //Holds the "Off" Relay for 1 sec
        digitalWrite(2,HIGH);
        
      }
    }
  }
  else if (Blynk.connected() == HIGH); {
    failedattempt = 0 ;             
  } //Not needed but breaks if removed :(

}


void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  currentMillis = millis(); 
  timer.run();  

}
