#include "DeviceDriver.h"
#include <windows.h>

DeviceDriver::DeviceDriver(FlashMemoryDevice *hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    unsigned char prevCh = m_hardware->read(address);
    for(int i = 1; i < READ_TRY_CNT; i++)
    {
		Sleep(READ_SLEEP_TIME_MS);
        unsigned char ch = m_hardware->read(address);
        if (ch != prevCh) throw ReadFailException("Read Fail");
        prevCh = ch;
    }
    return (int)prevCh;
}

void DeviceDriver::write(long address, int data)
{
    if (DeviceDriver::read(address) != ERASE_DATA) throw WriteFailException("Write Fail");
    m_hardware->write(address, (unsigned char)data);
}