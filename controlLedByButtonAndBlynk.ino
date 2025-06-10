#include "secrets.h"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define btn 13
#define built_in_led 2

int led_state = 0;
int last_btnstate = 1;

BlynkTimer timer;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(btn, INPUT_PULLUP);
  pinMode(built_in_led, OUTPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, SSID, PASSWORD);
  timer.setInterval(100L, checkBtn);
}

BLYNK_WRITE(V0)
{
  int widget = param.asInt();
  digitalWrite(built_in_led, widget);
  led_state = widget;        //Sync led state with app
}

void checkBtn()
{
  int current_btnstate = digitalRead(btn);
  if (last_btnstate == 1 && current_btnstate == 0)
  {
    led_state = !led_state;
    digitalWrite(built_in_led, led_state);
    Serial.print("Led State = ");
    Serial.println(led_state);
    Blynk.virtualWrite(V0, led_state);
  }
  last_btnstate = current_btnstate;
}
void loop() {

  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();
}
