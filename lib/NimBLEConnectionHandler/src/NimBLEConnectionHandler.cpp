#include "NimBLEConnectionHandler.h"

NimBLEClient *NimBleConnectionHandler::Client = nullptr;
NimBLERemoteService *NimBleConnectionHandler::Service = nullptr;
NimBLERemoteCharacteristic *NimBleConnectionHandler::Characteristic = nullptr;

void NimBleConnectionHandler::Setup()
{
    Serial.println("Starting NimBLE Client");
    NimBLEDevice::init("");
    NimBLEDevice::setSecurityAuth(BLE_SM_PAIR_AUTHREQ_SC);
    /** Optional: set the transmit power, default is 3db */
    NimBLEDevice::setPower(ESP_PWR_LVL_P9); /** +9db */
    Serial.println("NimBLE Client setup done");
}

void NimBleConnectionHandler::Connect()
{
    Serial.println("Connecting to server");
    this->Client = NimBLEDevice::createClient(NimBLEAddress("db:1e:e5:c5:c6:58", 1));
    NimBLEDevice::setMTU(128);

    bool isconnected = false;
    while (!isconnected)
    {
        this->Client->connect();
        delay(100);
        if (this->Client->isConnected())
        {
            isconnected = true;
        }
        else
        {
            Serial.println("Not Connected! Retrying...");
        }
    }

    Serial.println("Connected to: ");
    Serial.println(this->Client->getPeerAddress().toString().c_str());
    Serial.print("RSSI: ");
    Serial.println(this->Client->getRssi());

    this->Service = this->Client->getService(SERVICE_UUID);
    if (this->Service)
    {
        this->Characteristic = this->Service->getCharacteristic(CHARACTERISTIC_UUID);
    }
}

void NimBleConnectionHandler::InitializeConnection()
{
    Serial.println("Initialising connection");
    delay(1000);
    this->ReadMidiMessage();

    Serial.println("Change app mode");
    this->SendMidiMessageByRequest(RolandMessageRequest(RolandAddressNames::APPLICATION_MODE, 1));
    Serial.println("Connect command");
    this->SendMidiMessageByRequest(RolandMessageRequest(RolandAddressNames::CONNECTION, 1));
    Serial.println("Connection initialized");
}

/** Notification / Indication receiving handler callback */
void notificationCallback(NimBLERemoteCharacteristic *pRemoteCharacteristic, uint8_t *pData, size_t length, bool isNotify)
{
    std::string str = (isNotify == true) ? "Notification" : "Indication";
    str += " from ";
    str += std::string(pRemoteCharacteristic->getRemoteService()->getClient()->getPeerAddress());
    str += ", Value = ";
    Serial.print(str.c_str());
}

void NimBleConnectionHandler::SubscribeToNotifications()
{
    Serial.println("Subscribing to notifcations.");
    if (this->Characteristic->canNotify())
    {
        if (!this->Characteristic->subscribe(true, notificationCallback))
        {
            Serial.println("SUBSCRIPTION FAILED. DISCONNECTING...");
            this->Client->disconnect();
        }
    }
}

void NimBleConnectionHandler::GetHeaderAndTimestamp()
{
    auto currentTimeStamp = millis() & 0x01FFF;

    this->header = ((currentTimeStamp >> 7) & 0x3F) | 0x80; // 6 bits plus MSB
    this->timestamp = (currentTimeStamp & 0x7F) | 0x80;     // 7 bits plus MSB
};

std::vector<uint8_t> NimBleConnectionHandler::BuildMidiMessageFromMessageRequest(RolandMessageRequest messageRequest)
{
    this->GetHeaderAndTimestamp();
    std::vector<uint8_t> midiMessage = {header, timestamp};
    std::vector<uint8_t> midiCommand = messageRequest.BuildMidiMessage();

    midiMessage.insert(midiMessage.end(), midiCommand.begin(), midiCommand.end());
    Serial.print("\t");
    for (int i = 0; i < midiMessage.size(); i++)
    {
        Serial.print(midiMessage[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    return midiMessage;
};

void NimBleConnectionHandler::SendMidiMessageByRequest(RolandMessageRequest messageRequest)
{
    std::vector<uint8_t> midiMessage = this->BuildMidiMessageFromMessageRequest(messageRequest);
    this->SendMidiMessage(midiMessage);
    delay(1000);
}

void NimBleConnectionHandler::SendMidiMessage(std::vector<uint8_t> midiMessage)
{
    Serial.println("\tSending midi message");
    if (this->Characteristic)
    {
        if (this->Characteristic->writeValue((const uint8_t *)midiMessage.data(), midiMessage.size()))
        {
            Serial.println("\tMidi message sent");
        }
    }

    delay(100);
}

void NimBleConnectionHandler::ReadMidiMessage()
{
    std::string rply = this->Characteristic->readValue();
    Serial.print("\tReply Read: ");
    for (int i = 0; i < rply.length(); i++)
    {
        Serial.print(rply[i] < 16 ? "0" : "");
        Serial.print(rply[i], HEX);
        Serial.print(" ");
    }
    Serial.println();
}