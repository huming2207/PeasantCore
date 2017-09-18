//
// Created by Ming Hu on 15/9/17.
//

#ifndef PEASANTCORE_NETWORK_H
#define PEASANTCORE_NETWORK_H

#include <Arduino.h>
#include <Preferences.h>
#include <time.h>
#include "WiFi.h"
#include "Macros.h"


class Network
{
    public:
        bool init(bool forceReset);
        void setTime();

    private:
        Preferences networkPreferences;
        void wifiEventCallback(WiFiEvent_t event);
        String timeZone = String("UTC");
};

#endif //PEASANTCORE_NETWORK_H
