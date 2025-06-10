#define BLYNK_AUTH_TOKEN "0ph0GR_yh242aDlhLFqtvCRNEP4eoDdZ"
#define BLYNK_TEMPLATE_ID "TMPL3RSZluKkU"
#define BLYNK_TEMPLATE_NAME "HOME AUTOMATION"
#define BLYNK_PRINT Serial // Enables Serial Monitor

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "SSID";
char pass[] = "PASSWORD";
char auth[] = "8txRdyG9jKUCI8Ak1a2FCo4WfXkYSuky";

#define relay1 13
#define virtual_pin1 V0

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  pinMode (relay1, OUTPUT);
  digitalWrite(relay1, LOW); //relay in normally open mode (IN pin = 0V, relay OFF)
}

BLYNK_WRITE(V0)
{
  int value1 = param.asInt();
  digitalWrite(relay1, value1);
}

void loop() {
  Blynk.run();
}
