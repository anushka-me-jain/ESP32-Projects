#include "secrets.h"
#define BLYNK_PRINT Serial // Enables Serial Monitor

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define relay1 13
#define push_btn 27
#define virtual_pin1 V0
int last_button_state = HIGH;
int relay_state = LOW;

BlynkTimer timer;

void checkButtonState(){
  int current_button_state = digitalRead(push_btn);
  if(last_button_state == HIGH && current_button_state == LOW)
  {  
    delay(50);
    Serial.println("Button Pressed!");
    relay_state = !relay_state;
    digitalWrite(relay1, relay_state);
    Serial.println("Relay State Changed");
    Blynk.virtualWrite(V0, relay_state);
  }
  last_button_state = current_button_state;
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, SSID, PASSWORD);
  pinMode(push_btn, INPUT_PULLUP);
  pinMode (relay1, OUTPUT);   //relay in normally open mode (IN pin = 0V, relay OFF)
  digitalWrite(relay1, relay_state); 
  timer.setInterval(100L, checkButtonState);
}


BLYNK_WRITE(V0)
{
  int value1 = param.asInt();
  Serial.println("Button Widget Pressed!");
  digitalWrite(relay1, value1);
  Serial.println("Relay State Changed");
  relay_state = value1;
}

void loop() {
  
  Blynk.run();
  timer.run();
}
