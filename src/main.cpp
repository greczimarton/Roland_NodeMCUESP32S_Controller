#include <RolandWifiBLEServer.h>

RolandWifiBLEServer server;

void setup()
{
    Serial.begin(115200);
    server.nimble.Setup();
    server.nimble.Connect();
    server.nimble.SubscribeToNotifications();
    server.nimble.InitializeConnection();

    server.startWebServer();
}

void loop()
{
    server.wifiServer->handleClient();
}