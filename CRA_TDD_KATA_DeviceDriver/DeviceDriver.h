#pragma once
#include "FlashMemoryDevice.h"
#include <exception>
using namespace std;

class DeviceDriver
{
public:
    const int READ_TRY_CNT = 5;
    const int READ_SLEEP_TIME_MS = 500;

    DeviceDriver(FlashMemoryDevice *hardware);
    int read(long address);
    void write(long address, int data);


    class ReadFailException : public exception
    {
	    public:
	        explicit ReadFailException(char const* _Message) : exception(_Message) {}
    };
protected:
    FlashMemoryDevice *m_hardware;
};