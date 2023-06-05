#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../CRA_TDD_KATA_DeviceDriver/DeviceDriver.cpp"
#include "../CRA_TDD_KATA_DeviceDriver/App.cpp"
using namespace testing;

#define NOT_IMPORTANT_ADDR (0x00000000)
#define NOT_IMPORTANT_DATA (0xA)
#define NOT_IMPORTANT_DATA_2 (0xB)

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
		.WillRepeatedly(Return(NOT_IMPORTANT_DATA));

	DeviceDriver deviceDriver(&mockFlashMemoryDevice);
	EXPECT_THAT(deviceDriver.read(NOT_IMPORTANT_ADDR), Eq(NOT_IMPORTANT_DATA));
}

TEST(DeviceDriverTest, ReadFail) {
	MockFlashMemoryDevice mockFlashMemoryDevice;
	EXPECT_CALL(mockFlashMemoryDevice, read)
		.Times(2)
		.WillOnce(Return(NOT_IMPORTANT_DATA))
		.WillOnce(Return(NOT_IMPORTANT_DATA_2))
		.WillRepeatedly(Return(NOT_IMPORTANT_DATA));

	DeviceDriver deviceDriver(&mockFlashMemoryDevice);
	EXPECT_THROW(deviceDriver.read(NOT_IMPORTANT_ADDR), DeviceDriver::ReadFailException);
}

TEST(DeviceDriverTest, WriteSuccess) {
	MockFlashMemoryDevice mockFlashMemoryDevice;
	EXPECT_CALL(mockFlashMemoryDevice, read)
		.Times(10)
		.WillOnce(Return(DeviceDriver::ERASE_DATA))
		.WillOnce(Return(DeviceDriver::ERASE_DATA))
		.WillOnce(Return(DeviceDriver::ERASE_DATA))
		.WillOnce(Return(DeviceDriver::ERASE_DATA))
		.WillOnce(Return(DeviceDriver::ERASE_DATA))
		.WillRepeatedly(Return(NOT_IMPORTANT_DATA));
	EXPECT_CALL(mockFlashMemoryDevice, write)
		.Times(1);

	DeviceDriver deviceDriver(&mockFlashMemoryDevice);
	EXPECT_NO_THROW(deviceDriver.write(NOT_IMPORTANT_ADDR, NOT_IMPORTANT_DATA));
	EXPECT_THAT(deviceDriver.read(NOT_IMPORTANT_ADDR), Eq(NOT_IMPORTANT_DATA));
}

TEST(DeviceDriverTest, WriteFail) {
	MockFlashMemoryDevice mockFlashMemoryDevice;
	EXPECT_CALL(mockFlashMemoryDevice, read)
		.Times(5)
		.WillRepeatedly(Return(NOT_IMPORTANT_DATA));
	EXPECT_CALL(mockFlashMemoryDevice, write)
		.Times(0);

	DeviceDriver deviceDriver(&mockFlashMemoryDevice);
	EXPECT_THROW(deviceDriver.write(NOT_IMPORTANT_ADDR, NOT_IMPORTANT_DATA), DeviceDriver::WriteFailException);
}

TEST(AppTest, ReadAndPrint) {
	MockFlashMemoryDevice mockFlashMemoryDevice;
	EXPECT_CALL(mockFlashMemoryDevice, read(0x0))
		.Times(5)
		.WillRepeatedly(Return('A'));
	EXPECT_CALL(mockFlashMemoryDevice, read(0x1))
		.Times(5)
		.WillRepeatedly(Return('B'));
	EXPECT_CALL(mockFlashMemoryDevice, read(0x2))
		.Times(5)
		.WillRepeatedly(Return('C'));

	DeviceDriver deviceDriver(&mockFlashMemoryDevice);
	App app(&deviceDriver);

	EXPECT_THAT(app.ReadAndPrint(0x0, 0x2), Eq("ABC"));
}

TEST(AppTest, WriteAll) {
	MockFlashMemoryDevice mockFlashMemoryDevice;
	EXPECT_CALL(mockFlashMemoryDevice, read)
		.Times(25)
		.WillRepeatedly(Return(DeviceDriver::ERASE_DATA));
	EXPECT_CALL(mockFlashMemoryDevice, write)
		.Times(5);

	DeviceDriver deviceDriver(&mockFlashMemoryDevice);
	App app(&deviceDriver);

	EXPECT_NO_THROW(app.WriteAll(NOT_IMPORTANT_DATA));
}