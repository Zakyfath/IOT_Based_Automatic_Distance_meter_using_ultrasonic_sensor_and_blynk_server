#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLql3oJmGY"
#define BLYNK_DEVICE_NAME "sensor jarak"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define  trig  D1
#define  echo  D2

long duration;
int distance;

// Auth Token dari Blynk App.

char auth[] = "7v18iho4vB2LVWSNyHikMLxgdWqmxPPq";
char ssid[] = "Infinix HOT 10S";   // your ssid 
char pass[] = "sitiyho9"; // your pass

BlynkTimer timer;

void setup()
{
  // Debug console
  pinMode(trig, OUTPUT);  // trigPin sebagai output ==> trigger keluarnya sinyal
  pinMode(echo, INPUT);   // echoPin sebagai input ==> menangkap sinyal pantul dari benda
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
void sendSensor()
{
  digitalWrite(trig, LOW);   // Makes trigPin low
  delayMicroseconds(2);       // delay

  digitalWrite(trig, HIGH);  // tigPin high
  delayMicroseconds(10);      // trigPin high for 10 micro seconds
  digitalWrite(trig, LOW);   // trigPin low

  duration = pulseIn(echo, HIGH);   //Read echo pin, time in microseconds
  distance = duration * 0.034 / 2;   //Calculating actual/real distance

  Serial.print("Distance = ");        //output jarak di serial monitor
  Serial.println(distance);
  
  Blynk.virtualWrite(V0, distance);
  delay(1000);                        //Pause for 3 seconds and start measuring distance again
}
