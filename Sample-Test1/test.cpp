#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../CRA_TDD_KATA_DeviceDriver/DeviceDriver.cpp"
using namespace testing;

#define NOT_IMPORTANT_ADDR (0x00000000)

class MockFlashMemoryDevice : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(DeviceDriverTest, ReadSuccess) {
	MockFlashMemoryDevice mockFlashMemoryDevice;
	EXPECT_CALL(mockFlashMemoryDevice, read)
		.Times(5)
		.WillRepeatedly(Return('A'));

	DeviceDriver deviceDriver(&mockFlashMemoryDevice);
	EXPECT_THAT(deviceDriver.read(NOT_IMPORTANT_ADDR), Eq('A'));
}

TEST(DeviceDriverTest, ReadFail) {
	MockFlashMemoryDevice mockFlashMemoryDevice;
	EXPECT_CALL(mockFlashMemoryDevice, read)
		.Times(2)
		.WillOnce(Return('B'))
		.WillOnce(Return('A'))
		.WillRepeatedly(Return('B'));

	DeviceDriver deviceDriver(&mockFlashMemoryDevice);
	EXPECT_THROW(deviceDriver.read(NOT_IMPORTANT_ADDR), DeviceDriver::ReadFailException);
}