#include <NimBLEConnectionHandler.h>
#include <WiFi.h>
#include <WebServer.h>

class RolandWifiBLEServer
{
public:
    NimBleConnectionHandler nimble;
    WebServer *wifiServer;
    void startWebServer();

private:
    void connectToWiFi();
    void setup_routing();
    void handleWrite();
};
// const char *SSID;
// const char *PWD;

// WebServer wifiServer;

// StaticJsonDocument<250> jsonDocument;
// NimBleConnectionHandler nimble;

// void connectToWiFi();
// void setup_routing();
// void handleWrite();
