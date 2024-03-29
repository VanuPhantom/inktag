#include "Arduino.h"
#include "Network.h"
#include "logging.h"

Network network("Inktag", "FuckEspressif!");

void setup()
{
  pinMode(15, OUTPUT);
  digitalWrite(15, HIGH);
  Serial.begin(9600);
  delay(3000);
  process([]()
          { return network.Start(); },
          "Starting AP...", "AP started ^w^", "Failed to start AP QwQ");
  digitalWrite(15, LOW);
}

void loop()
{
  Serial.println("Boop >v<");
  delay(2500);
}
