#include <RolandWifiBLEServer.h>
#include <secrets.h>

void RolandWifiBLEServer::connectToWiFi()
{
    this->wifiServer = new WebServer(80);
    Serial.printf("Connecting to %s Wifi\n", SSID);

    WiFi.begin(SSID, PWD);

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }

    Serial.printf("Connected. IP: %s\n", WiFi.localIP().toString().c_str());
}

void RolandWifiBLEServer::setup_routing()
{
    this->wifiServer->on("/write", HTTP_POST, std::bind(&RolandWifiBLEServer::handleWrite, this));
    this->wifiServer->on("/writeMessage", HTTP_POST, std::bind(&RolandWifiBLEServer::handleWriteMessage, this));
}

void RolandWifiBLEServer::handleWrite()
{
    Serial.println("Got write POST request");
    if (this->wifiServer->hasArg("address") == false)
    {
        Serial.println("bad request no address in args");
        this->wifiServer->send(400);
        return;
    }
    if (this->wifiServer->hasArg("value") == false)
    {
        Serial.println("bad request no value in args");
        this->wifiServer->send(400);
        return;
    }

    int address = this->wifiServer->arg("address").toInt();
    int value = this->wifiServer->arg("value").toInt();
    Serial.printf("Address: %i, Value: %i\n", address, value);

    this->nimble.SendMidiMessageByRequest(RolandMessageRequest((RolandAddressNames)address, value));

    // Respond to the client
    this->wifiServer->send(200);
}

void RolandWifiBLEServer::handleWriteMessage()
{
    Serial.println("Got WriteMessage POST request");
    if (this->wifiServer->hasArg("message") == false)
    {
        Serial.println("bad request no message in args");
        this->wifiServer->send(400);
        return;
    }

    std::string message = this->wifiServer->arg("message").c_str();

    this->nimble.SendMidiMessageByString(message);

    // Respond to the client
    this->wifiServer->send(200);
}

void RolandWifiBLEServer::startWebServer()
{
    this->connectToWiFi();
    this->setup_routing();
    this->wifiServer->enableCORS(true);
    this->wifiServer->begin();
}