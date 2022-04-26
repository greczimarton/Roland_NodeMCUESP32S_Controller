#include <Arduino.h>
#include <unity.h>
#include <RolandMidiMessenger.h>
#include <test_RolandMidiMessenger.h>

void setup()
{
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN(); // IMPORTANT LINE!
    runRolandMidiMessengerTests();
    UNITY_END(); // stop unit testing
}

void loop()
{
}