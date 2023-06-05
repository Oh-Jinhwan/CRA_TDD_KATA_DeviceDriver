#pragma once
#include "FlashMemoryDevice.h"
#include <exception>
using namespace std;

class DeviceDriver
{
public:
    static const int READ_TRY_CNT = 5;
    static const int READ_SLEEP_TIME_MS = 500;
    static const int ERASE_DATA = 0xFF;

    DeviceDriver(FlashMemoryDevice *hardware);
    int read(long address);
    void write(long address, int data);


    class ReadFailException : public exception {
	    public:
	        explicit ReadFailException(char const* _Message) : exception(_Message) {}
    };

    class WriteFailException : public exception {
    public:
        explicit WriteFailException(char const* _Message) : exception(_Message) {}
    };
protected:
    FlashMemoryDevice *m_hardware;
};