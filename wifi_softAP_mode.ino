#include "secrets.h"
#include <WiFi.h>

WiFiServer server(80);
int ledPin = 2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(ledPin, INPUT_PULLUP);
  digitalWrite(ledPin, HIGH);

  WiFi.softAP(ssid, password);
  Serial.println(WiFi.softAPIP());
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = server.available();
  if(client)
  {
    String req = client.readStringUntil('\r'); // carriage return marks the end of a line
    client.flush(); //so that esp32 does not keep processing old bytes or extra bytes

    if(req.indexOf('/ON') != -1)
      {digitalWrite(ledPin, HIGH);}

    else if(req.indexOf('/OFF') != -1)
      {digitalWrite(ledPin, LOW);}
  }
  client.println("HTTP/1.1 200 OK");
  client.println("Content Type : text/html");
  client.println();//http protocol says to end header using a blank line;
  client.println("<html><body>");
  client.println("<h1>Esp32 Led Control</h1>");
  client.println("<a href = '/ON'><button>Turn On</button></a>"); //href="/ON" tells the browser to request the path /ON from the ESP32.
  client.println("<a href = '/OFF'><button>Turn OFF</button></a>");
  client.println("</body></html>");
  delay(1);
  client.stop();
}
