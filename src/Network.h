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
        WiFi.softAPConfig(IPAddress(192, 168, 1, 1), IPAddress(192, 168, 1, 1), IPAddress(255, 255, 255, 0), IPAddress(192, 168, 1, 2));
        return WiFi.softAP(ssid, password);
    }

    IPAddress GetIP()
    {
        return WiFi.softAPIP();
    }
};