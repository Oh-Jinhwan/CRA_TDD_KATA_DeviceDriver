#include <string>
#include "DeviceDriver.h"

class App
{
public:
	const long START_ADDR = 0x00;
	const long END_ADDR = 0x04;

	App(DeviceDriver * deviceDriver) : deviceDriver(deviceDriver) {};
	string ReadAndPrint(long startAddr, long endAddr)
	{
		string str = "";
		for (long addr = startAddr; startAddr <= endAddr; startAddr++)
		{
			str += deviceDriver->read(startAddr);
		}
		return str;
	}
	void WriteAll(unsigned char value)
	{
		for (long addr = START_ADDR; addr <= END_ADDR; addr++)
		{
			deviceDriver->write(addr, value);
		}
	}

private:
	DeviceDriver *deviceDriver;
};