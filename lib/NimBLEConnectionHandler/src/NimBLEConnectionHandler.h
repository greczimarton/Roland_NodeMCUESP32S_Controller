#include <Arduino.h>
#include <NimBLEDevice.h>
#include <RolandMidiMessenger.h>

#define SERVICE_UUID "03b80e5a-ede8-4b33-a751-6ce34ec4c700"
#define CHARACTERISTIC_UUID "7772e5db-3868-4112-a1a9-f2669d106bf3"

class NimBleConnectionHandler
{
public:
    static NimBLEClient *Client;
    static NimBLERemoteService *Service;
    static NimBLERemoteCharacteristic *Characteristic;
    uint8_t header;
    uint8_t timestamp;
    void Setup();
    void Connect();
    void SubscribeToNotifications();
    void InitializeConnection();
    std::vector<uint8_t> BuildMidiMessageFromMessageRequest(RolandMessageRequest messageRequest);
    void SendMidiMessageByRequest(RolandMessageRequest messageRequest);
    std::vector<uint8_t> BuildMidiMessageFromStringMessage(std::vector<uint8_t> message);
    void SendMidiMessageByString(std::string message);
    void SendMidiMessage(std::vector<uint8_t> midiMessage);
    void ReadMidiMessage();

private:
    void GetHeaderAndTimestamp();
};