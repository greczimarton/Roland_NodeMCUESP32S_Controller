#include "RolandMidiMessenger.h"

RolandRegister::RolandRegister(std::string name, std::array<int, 4> address, int size)
{
    this->Name = name;
    this->Address = address;
    this->Size = size;
};

RolandRegister RolandRegisterBuilder::GetRegisterByAddress(RolandAddressNames addressName)
{
    switch (addressName)
    {
    case RolandAddressNames::APPLICATION_MODE:
        return RolandRegister("APPLICATION_MODE", {0x01, 0x00, 0x03, 0x00}, 2);
    case RolandAddressNames::CONNECTION:
        return RolandRegister("CONNECTION", {0x01, 0x00, 0x03, 0x06}, 1);
    case RolandAddressNames::METRONOME_SW_TOGGLE:
        return RolandRegister("METRONOME_SW_TOGGLE", {0x01, 0x00, 0x05, 0x09}, 1);
    case RolandAddressNames::SEQUENCER_TEMPO_RO:
        return RolandRegister("SEQUENCER_TEMPO_RO", {0x01, 0x00, 0x01, 0x08}, 2);
    case RolandAddressNames::MASTER_VOLUME:
        return RolandRegister("MASTER_VOLUME", {0x01, 0x00, 0x02, 0x13}, 1);
    default:
        throw std::invalid_argument("received invalid address name");
    }
}

RolandMessageRequest::RolandMessageRequest(RolandAddressNames addressName, int dataAsInt)
{
    this->Register = RolandRegisterBuilder::GetRegisterByAddress(addressName);
    this->CmdType = RolandCmdType::ROLAND_CMD_WRITE;
    this->DataAsInt = dataAsInt;
}

RolandMessageRequest::RolandMessageRequest(RolandAddressNames addressName)
{
    this->Register = RolandRegisterBuilder::GetRegisterByAddress(addressName);
    this->CmdType = RolandCmdType::ROLAND_CMD_READ;
}

int RolandMessage::CalculateChecksum()
{
    int sum = 0;
    for (int i = 0; i < this->Register.Address.size(); i++)
    {
        sum += this->Register.Address[i];
    }

    if (this->CmdType == RolandCmdType::ROLAND_CMD_WRITE)
    {
        sum += this->DataAsInt;
    }
    else
    {
        sum += this->Register.Size;
    }

    int remainder = sum % 128;
    int checksum = 128 - remainder;
    return checksum;
}

std::vector<uint8_t> RolandMessageRequest::BuildMidiMessage()
{
    std::vector<uint8_t> midiMessage;

    midiMessage.insert(midiMessage.end(), 0xF0);
    // midiMessage.insert(midiMessage.end(), ROLAND_ID_BYTES.begin(), ROLAND_ID_BYTES.end());
    midiMessage.insert(midiMessage.end(), 0x41);
    midiMessage.insert(midiMessage.end(), 0x10);
    midiMessage.insert(midiMessage.end(), 0x00);
    midiMessage.insert(midiMessage.end(), 0x00);
    midiMessage.insert(midiMessage.end(), 0x00);
    midiMessage.insert(midiMessage.end(), 0x28);
    midiMessage.insert(midiMessage.end(), this->CmdType);
    midiMessage.insert(midiMessage.end(), this->Register.Address.begin(), this->Register.Address.end());
    for (int i = 0; i < this->Register.Size - 1; i++)
    {
        midiMessage.insert(midiMessage.end(), 0x00);
    }
    midiMessage.insert(midiMessage.end(), this->DataAsInt);
    midiMessage.insert(midiMessage.end(), this->CalculateChecksum());
    midiMessage.insert(midiMessage.end(), 0xF7);

    return midiMessage;
}
// const char RolandMessage::SYS_EX_START = 0xF0;
// const char RolandMessage::SYS_EX_END = 0xF7;
// const std::array<char, 3> RolandMessage::ROLAND_ID_BYTES = {0x41, 0x10, 0x42};