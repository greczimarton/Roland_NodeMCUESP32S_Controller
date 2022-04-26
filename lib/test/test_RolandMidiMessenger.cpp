#include "test_RolandMidiMessenger.h"

// CREATION TESTS
void test_rolandmessagerequest_write_creation()
{
    RolandMessageRequest rmq(RolandAddressNames::CONNECTION, 1);
    TEST_ASSERT_EQUAL(rmq.CmdType, RolandCmdType::ROLAND_CMD_WRITE);
    TEST_ASSERT_EQUAL(rmq.DataAsInt, 1);

    TEST_ASSERT_TRUE(rmq.Register.Name == "CONNECTION");
    std::array<int, 4> expectedAddress{0x01, 0x00, 0x03, 0x06};
    TEST_ASSERT_TRUE(rmq.Register.Address.size() == expectedAddress.size());
    for (int i = 0; i < rmq.Register.Address.size(); i++)
    {
        TEST_ASSERT_TRUE(rmq.Register.Address[i] == expectedAddress[i])
    }
    TEST_ASSERT_TRUE(rmq.Register.Size == 1)
}

void test_rolandmessagerequest_read_creation()
{
    RolandMessageRequest rmq(RolandAddressNames::APPLICATION_MODE);
    TEST_ASSERT_EQUAL(rmq.CmdType, RolandCmdType::ROLAND_CMD_READ);
    TEST_ASSERT_TRUE(rmq.Register.Name == "APPLICATION_MODE");
    std::array<int, 4> expectedAddress{0x01, 0x00, 0x03, 0x00};
    TEST_ASSERT_TRUE(rmq.Register.Address.size() == expectedAddress.size());
    for (int i = 0; i < rmq.Register.Address.size(); i++)
    {
        TEST_ASSERT_TRUE(rmq.Register.Address[i] == expectedAddress[i])
    }
    TEST_ASSERT_TRUE(rmq.Register.Size == 2)
}

void runCreationTest()
{
    RUN_TEST(test_rolandmessagerequest_write_creation);
    RUN_TEST(test_rolandmessagerequest_read_creation);
}

// CHECKSUM TESTS
void test_checksum_write_calculation()
{
    RolandMessageRequest rmq(RolandAddressNames::CONNECTION, 1);
    int checksum = rmq.CalculateChecksum();
    TEST_ASSERT_EQUAL_HEX8(0x75, checksum);
}

void test_checksum_read_calculation()
{
    RolandMessageRequest rmq(RolandAddressNames::SEQUENCER_TEMPO_RO);
    int checksum = rmq.CalculateChecksum();
    TEST_ASSERT_EQUAL_HEX8(0x74, checksum);
}

void runChecksumTests()
{
    RUN_TEST(test_checksum_write_calculation);
    RUN_TEST(test_checksum_read_calculation);
}

// MIDIMESSAGEBUILDERTEST
void test_midimessage_write_building()
{
    RolandMessageRequest rmq(RolandAddressNames::CONNECTION, 1);
    std::vector<uint8_t> expectedMidiMessage = {0xF0, 0x41, 0x10, 0x00, 0x00, 0x00, 0x28, 0x12, 0x01, 0x00, 0x03, 0x06, 0x01, 0x75, 0xF7};
    std::vector<uint8_t> builtMidiMessage = rmq.BuildMidiMessage();

    for (int i = 0; i < builtMidiMessage.size(); i++)
    {
        TEST_ASSERT_EQUAL_INT(builtMidiMessage[i], expectedMidiMessage[i]);
    }
}

void test_midimessage_write_with_addresswith2size_building()
{
    RolandMessageRequest rmq(RolandAddressNames::APPLICATION_MODE, 1);
    uint8_t expectedMidiMessage[] = {0xF0, 0x41, 0x10, 0x00, 0x00, 0x00, 0x28, 0x12, 0x01, 0x00, 0x03, 0x00, 0x00, 0x01, 0x7B, 0xF7}; // change app mode to 0,1
    std::vector<uint8_t> builtMidiMessage = rmq.BuildMidiMessage();

    for (int i = 0; i < builtMidiMessage.size(); i++)
    {
        TEST_ASSERT_EQUAL_UINT8(builtMidiMessage[i], expectedMidiMessage[i]);
    }
}

void runMidiMessageBuilderTest()
{
    RUN_TEST(test_midimessage_write_with_addresswith2size_building);
    RUN_TEST(test_midimessage_write_building);
}

void runRolandMidiMessengerTests()
{
    runCreationTest();
    runChecksumTests();
    runMidiMessageBuilderTest();
}