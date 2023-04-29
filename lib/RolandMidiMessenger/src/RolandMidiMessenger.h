#ifndef ROLAND_MIDI_H
#define ROLAND_MIDI_H

#include <Arduino.h>
#include <array>
#include <vector>
#include <map>
#include <string>

enum RolandCmdType
{
    ROLAND_CMD_READ = 0x11,
    ROLAND_CMD_WRITE = 0x12,
};

class RolandRegister
{
public:
    std::string Name;
    std::array<int, 4> Address;
    int Size;
    RolandRegister() = default;
    RolandRegister(std::string name, std::array<int, 4> address, int size);
};

enum RolandAddressNames
{
    APPLICATION_MODE,
    CONNECTION,
    METRONOME_SW_TOGGLE,
    SEQUENCER_TEMPO_RO,
    MASTER_VOLUME,
    METRONOME_BEAT
};

class RolandRegisterBuilder
{
public:
    static RolandRegister GetRegisterByAddress(RolandAddressNames addressName);
};

// class RolandAddressMap
// {
// public:
//     // const RolandRegister ADDRESS_MAP_VERSION = RolandRegister("ADDRESS_MAP_VERSION", {0x01, 0x00, 0x08, 0x00}, 1);
//     static constexpr std::array<char, 4> ADDRESS_MAP_VERSION = {0x01, 0x00, 0x08, 0x00};
//     // const RolandRegister ALL_SONG_PLAY_MODE = RolandRegister("ALL_SONG_PLAY_MODE", {0x01, 0x00, 0x02, 0x15}, 1);
//     //  const char ALL_SONG_PLAY_MODE[4] = {0x01, 0x00, 0x02, 0x15};
//     const char AMBIENCE[4] = {0x01, 0x00, 0x02, 0x1A};
//     const char APPLICATION_MODE[4] = {0x01, 0x00, 0x03, 0x00};
//     const char ARRANGER_BALANCE[4] = {0x01, 0x00, 0x03, 0x05};
//     const char ARRANGER_PEDAL_FUNCTION[4] = {0x01, 0x00, 0x03, 0x03};
//     const char BRILLIANCE[4] = {0x01, 0x00, 0x02, 0x1C};
//     //constexpr static std::array<int, 4> CONNECTION = {0x01, 0x00, 0x03, 0x06};
//     const char DUAL_BALANCE[4] = {0x01, 0x00, 0x02, 0x05};
//     const char DUAL_OCTAVE_SHIFT[4] = {0x01, 0x00, 0x02, 0x04};
//     const char DUAL_TONE1_OCTAVE_SHIFT[4] = {0x01, 0x00, 0x02, 0x17};
//     const char HEADPHONES_CONNECTION[4] = {0x01, 0x00, 0x01, 0x10};
//     const char HEADPHONES3_D_AMBIENCE[4] = {0x01, 0x00, 0x02, 0x1B};
//     const char KEY_BOARD_MODE[4] = {0x01, 0x00, 0x02, 0x00};
//     const char KEY_TOUCH[4] = {0x01, 0x00, 0x02, 0x1D};
//     const char KEY_TRANSPOSE_RO[4] = {0x01, 0x00, 0x01, 0x01};
//     const char KEY_TRANSPOSE_WO[4] = {0x01, 0x00, 0x03, 0x07};
//     const char MASTER_TUNING[4] = {0x01, 0x00, 0x02, 0x18};
//     const char MASTER_VOLUME_LIMIT[4] = {0x01, 0x00, 0x02, 0x14};
//     const char MASTER_VOLUME[4] = {0x01, 0x00, 0x02, 0x13};
//     const char METRONOME_BEAT[4] = {0x01, 0x00, 0x02, 0x1F};
//     const char METRONOME_DOWN_BEAT[4] = {0x01, 0x00, 0x02, 0x23};
//     const char METRONOME_PATTERN[4] = {0x01, 0x00, 0x02, 0x20};
//     constexpr static std::array<int, 4> METRONOME_STATUS = {0x01, 0x00, 0x01, 0x0F};
//     constexpr static std::array<int, 4> METRONOME_SW_TOGGLE = {0x01, 0x00, 0x05, 0x09};
//     const char METRONOME_TONE[4] = {0x01, 0x00, 0x02, 0x22};
//     const char METRONOME_VOLUME[4] = {0x01, 0x00, 0x02, 0x21};
//     const char PAGE_TURN_NEXT_PAGE[4] = {0x01, 0x00, 0x06, 0x01};
//     const char PAGE_TURN_PREVIOUS_PAGE[4] = {0x01, 0x00, 0x06, 0x00};
//     const char SCORE_PAGE_TURN[4] = {0x01, 0x00, 0x03, 0x02};
//     const char SEQUENCER_ACCOMP_PART_SW_TOGGLE[4] = {0x01, 0x00, 0x05, 0x06};
//     const char SEQUENCER_BEAT_DENOMINATOR[4] = {0x01, 0x00, 0x01, 0x0B};
//     const char SEQUENCER_BEAT_NUMERATOR[4] = {0x01, 0x00, 0x01, 0x0A};
//     const char SEQUENCER_FF[4] = {0x01, 0x00, 0x05, 0x01};
//     const char SEQUENCER_LEFT_PART_SW_TOGGLE[4] = {0x01, 0x00, 0x05, 0x07};
//     const char SEQUENCER_MEASURE[4] = {0x01, 0x00, 0x01, 0x05};
//     const char SEQUENCER_NEXT_SONG[4] = {0x01, 0x00, 0x05, 0x0B};
//     const char SEQUENCER_PART_SW_ACCOMP[4] = {0x01, 0x00, 0x01, 0x0C};
//     const char SEQUENCER_PART_SW_LEFT[4] = {0x01, 0x00, 0x01, 0x0D};
//     const char SEQUENCER_PART_SW_RIGHT[4] = {0x01, 0x00, 0x01, 0x0E};
//     const char SEQUENCER_PLAY_STOP_TOGGLE[4] = {0x01, 0x00, 0x05, 0x05};
//     const char SEQUENCER_PREVIOUS_SONG[4] = {0x01, 0x00, 0x05, 0x0A};
//     const char SEQUENCER_RESET[4] = {0x01, 0x00, 0x05, 0x02};
//     const char SEQUENCER_REW[4] = {0x01, 0x00, 0x05, 0x00};
//     const char SEQUENCER_RIGHT_PART_SW_TOGGLE[4] = {0x01, 0x00, 0x05, 0x08};
//     const char SEQUENCER_STATUS[4] = {0x01, 0x00, 0x01, 0x03};
//     const char SEQUENCER_TEMPO_DOWN[4] = {0x01, 0x00, 0x05, 0x03};
//     const char SEQUENCER_TEMPO_NOTATION[4] = {0x01, 0x00, 0x01, 0x07};
//     const char SEQUENCER_TEMPO_RO[4] = {0x01, 0x00, 0x01, 0x08};
//     const char SEQUENCER_TEMPO_UP[4] = {0x01, 0x00, 0x05, 0x04};
//     const char SEQUENCER_TEMPO_WO[4] = {0x01, 0x00, 0x03, 0x09};
//     const char SERVER_SETUP_FILE_NAME[4] = {0x01, 0x00, 0x00, 0x00};
//     const char SONG_NUMBER[4] = {0x01, 0x00, 0x02, 0x10};
//     const char SONG_TONE_LANGUAGE[4] = {0x01, 0x00, 0x01, 0x00};
//     const char SONG_TRANSPOSE_RO[4] = {0x01, 0x00, 0x01, 0x02};
//     const char SONG_TRANSPOSE_WO[4] = {0x01, 0x00, 0x03, 0x08};
//     const char SOUND_EFFECT_STOP_ALL[4] = {0x01, 0x00, 0x04, 0x02};
//     const char SOUND_EFFECT[4] = {0x01, 0x00, 0x04, 0x00};
//     const char SPLIT_BALANCE[4] = {0x01, 0x00, 0x02, 0x03};
//     const char SPLIT_OCTAVE_SHIFT[4] = {0x01, 0x00, 0x02, 0x02};
//     const char SPLIT_POINT[4] = {0x01, 0x00, 0x02, 0x01};
//     const char SPLIT_RIGHT_OCTAVE_SHIFT[4] = {0x01, 0x00, 0x02, 0x16};
//     const char TEMPO_RESET[4] = {0x01, 0x00, 0x03, 0x0B};
//     const char TONE_FOR_DUAL[4] = {0x01, 0x00, 0x02, 0x0D};
//     const char TONE_FOR_SINGLE[4] = {0x01, 0x00, 0x02, 0x07};
//     const char TONE_FOR_SPLIT[4] = {0x01, 0x00, 0x02, 0x0A};
//     const char TRANSPOSE_MODE[4] = {0x01, 0x00, 0x02, 0x1E};
//     const char TWIN_PIANO_MODE[4] = {0x01, 0x00, 0x02, 0x06};
//     const char UPTIME[4] = {0x01, 0x00, 0x07, 0x00};
// };

// static char SYS_EX_START = 0xF0;
// static char SYS_EX_END = 0xF7;
// static std::array<char, 3> ROLAND_ID_BYTES = {0x41, 0x10, 0x42};

class RolandMessage
{
public:
    RolandCmdType CmdType;
    RolandRegister Register;
    int DataAsInt;
    int CalculateChecksum();
};

class RolandMessageRequest : public RolandMessage
{
public:
    RolandMessageRequest(RolandAddressNames addressName, int dataAsInt);
    RolandMessageRequest(RolandAddressNames addressName);
    std::vector<uint8_t> BuildMidiMessage();
};

#endif // ROLAND_MIDI_H