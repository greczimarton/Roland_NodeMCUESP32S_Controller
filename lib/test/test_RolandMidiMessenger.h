#include <Arduino.h>
#include <unity.h>
#include <RolandMidiMessenger.h>

void test_rolandmessagerequest_write_creation();
void test_rolandmessagerequest_read_creation();
void runCreationTest();

void test_checksum_write_calculation();
void test_checksum_read_calculation();
void runChecksumTests();

void test_midimessage_write_building();
void runMidiMessageBuilderTest();

void runRolandMidiMessengerTests();