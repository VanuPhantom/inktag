#include "WiFi.h"
#include "Arduino.h"

class Network
{
public:
    char *ssid;
    char *password;

    Network(char *ssid, char *password)
    {
        this->ssid = ssid;
        this->password = password;
        // TODO: Throw an error if WiFi is unavailable
    }

    bool Start()
    {
        return WiFi.softAP(ssid, password);
    }

    IPAddress GetIP() {
        return WiFi.localIP();
    }
};