#include <Arduino.h>
#include <stdint.h>

#define LOG_COLOR_BLACK     "\x1B[0m"
#define LOG_COLOR_RED       "\x1B[31m"
#define LOG_COLOR_GREEN     "\x1B[32m"
#define LOG_COLOR_YELLOW    "\x1B[33m"
#define LOG_COLOR_BLUE      "\x1B[34m"
#define LOG_COLOR_MAGENTA   "\x1B[35m"
#define LOG_COLOR_CYAN      "\x1B[36m"
#define LOG_COLOR_WHITE     "\x1B[37m"

#define LOG_INFO    LOG_COLOR_BLACK
#define LOG_SUCCESS LOG_COLOR_GREEN
#define LOG_WARN    LOG_COLOR_YELLOW
#define LOG_ERROR   LOG_COLOR_RED

class Logger
{
    public:
        Logger();

        ~Logger()
        {
            Serial.end();
        };

        bool init(uint32_t baud);
        void log(const char * log_str);
        void log(String logString);

    
};
