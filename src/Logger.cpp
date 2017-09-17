#include "Logger.h"

bool Logger::init(uint32_t baud = 115200)
{
    Serial.begin(baud);
}

void Logger::log(String logString)
{
    log(logString.c_str());
}

void Logger::log(const char * log_str)
{
    Serial.print(log_str);
}