#include "Arduino.h"
#include "Network.h"
#include "logging.h"
#include "HttpServer.h"

Network network("Inktag", "FuckEspressif!");
HttpServer httpServer;

void setup()
{
  pinMode(15, OUTPUT);
  digitalWrite(15, HIGH);
  Serial.begin(9600);
  delay(3000);
  process([]()
          { return network.Start(); },
          "Starting AP...", "AP started ^w^", "Failed to start AP QwQ");
  Serial.print("IP: ");
  Serial.print(network.GetIP());
  Serial.print("\n\r");
  httpServer.start();
  digitalWrite(15, LOW);
}

void loop()
{
  httpServer.handleConnection();
  Serial.println("Boop >v<");
  delay(2500);
}
